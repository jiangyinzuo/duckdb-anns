# 文件系统层

自底向上

## FileSystem

（通过搜索fsync找到）

duckdb/src/include/duckdb/common/local_file_system.hpp:16-33 submodule=duckdb version=v0.10.1 snippet_id=29
```cpp
class LocalFileSystem : public FileSystem {
public:
	unique_ptr<FileHandle> OpenFile(const string &path, uint8_t flags, FileLockType lock = FileLockType::NO_LOCK,
	                                FileCompressionType compression = FileCompressionType::UNCOMPRESSED,
	                                FileOpener *opener = nullptr) override;

	//! Read exactly nr_bytes from the specified location in the file. Fails if nr_bytes could not be read. This is
	//! equivalent to calling SetFilePointer(location) followed by calling Read().
	void Read(FileHandle &handle, void *buffer, int64_t nr_bytes, idx_t location) override;
	//! Write exactly nr_bytes to the specified location in the file. Fails if nr_bytes could not be written. This is
	//! equivalent to calling SetFilePointer(location) followed by calling Write().
	void Write(FileHandle &handle, void *buffer, int64_t nr_bytes, idx_t location) override;
	//! Read nr_bytes from the specified file into the buffer, moving the file pointer forward by nr_bytes. Returns the
	//! amount of bytes read.
	int64_t Read(FileHandle &handle, void *buffer, int64_t nr_bytes) override;
	//! Write nr_bytes from the buffer into the file, moving the file pointer forward by nr_bytes.
	int64_t Write(FileHandle &handle, void *buffer, int64_t nr_bytes) override;

```

**VirtualFileSystem**

duckdb/src/include/duckdb/common/virtual_file_system.hpp:17-26 submodule=duckdb version=v0.10.1 snippet_id=30
```cpp
// bunch of wrappers to allow registering protocol handlers
class VirtualFileSystem : public FileSystem {
public:
	VirtualFileSystem();

	unique_ptr<FileHandle> OpenFile(const string &path, uint8_t flags, FileLockType lock = FileLockType::NO_LOCK,
	                                FileCompressionType compression = FileCompressionType::UNCOMPRESSED,
	                                FileOpener *opener = nullptr) override;

	void Read(FileHandle &handle, void *buffer, int64_t nr_bytes, idx_t location) override;
```

## FileHandle

文件系统层被FileHandle调用

duckdb/src/common/file_system.cpp:484-486 submodule=duckdb version=v0.10.1 snippet_id=31
```cpp
void FileHandle::Read(void *buffer, idx_t nr_bytes, idx_t location) {
	file_system.Read(*this, buffer, nr_bytes, location);
}
```

FileHandle::Read 被以下函数调用
```
duckdb/extension/json/buffered_json_reader.cpp|86 col 11| handle.Read(pointer, size, position);
duckdb/extension/json/buffered_json_reader.cpp|88 col 11| handle.Read(pointer, size, position);
duckdb/extension/json/buffered_json_reader.cpp|99 col 12| handle.Read(pointer, size, position);
duckdb/extension/parquet/include/thrift_tools.hpp|115 col 11| handle.Read(read_head.data.get(), read_head.size, read_head.location);
duckdb/extension/parquet/include/thrift_tools.hpp|137 col 12| handle.Read(prefetch_buffer->data.get(), prefetch_buffer->size, prefetch_buffer->location);
duckdb/extension/parquet/include/thrift_tools.hpp|148 col 12| handle.Read(buf, len, location);
duckdb/src/common/file_buffer.cpp|88 col 9| handle.Read(internal_buffer, internal_size, location);
duckdb/src/common/file_system.cpp|484 col 18| void FileHandle::Read(void *buffer, idx_t nr_bytes, idx_t location) {
duckdb/src/include/duckdb/common/file_system.hpp|59 col 18| DUCKDB_API void Read(void *buffer, idx_t nr_bytes, idx_t location);
duckdb/src/main/extension/extension_load.cpp|49 col 11| handle->Read((void *)to_hash.data(), len, iter);
duckdb/src/main/extension/extension_load.cpp|169 col 11| handle->Read((void *)signature.data(), signature.size(), signature_offset);
duckdb/src/storage/single_file_block_manager.cpp|47 col 9| handle.Read(magic_bytes, MainHeader::MAGIC_BYTE_SIZE, MainHeader::MAGIC_BYTE_OFFSET);
duckdb/src/storage/standard_buffer_manager.cpp|309 col 10| handle->Read(&block_size, sizeof(idx_t), 0);
duckdb/test/common/test_file_system.cpp|92 col 26| REQUIRE_NOTHROW(handle->Read((void *)test_data, sizeof(int64_t) * INTEGER_COUNT, 0));
duckdb/test/sql/storage/wal_torn_write.cpp|68 col 10| handle->Read(wal_contents.get(), wal_size, 0);
```

## FileBuffer

duckdb/src/common/file_buffer.cpp:86-89 submodule=duckdb version=v0.10.1 snippet_id=32
```cpp
void FileBuffer::Read(FileHandle &handle, uint64_t location) {
	D_ASSERT(type != FileBufferType::TINY_BUFFER);
	handle.Read(internal_buffer, internal_size, location);
}
```

## SingleFileBlockManager

duckdb/src/storage/single_file_block_manager.cpp:257-270 submodule=duckdb version=v0.10.1 snippet_id=33
```cpp
void SingleFileBlockManager::ReadAndChecksum(FileBuffer &block, uint64_t location) const {
	// read the buffer from disk
	block.Read(*handle, location);

	// compute the checksum
	auto stored_checksum = Load<uint64_t>(block.InternalBuffer());
	uint64_t computed_checksum = Checksum(block.buffer, block.size);

	// verify the checksum
	if (stored_checksum != computed_checksum) {
		throw IOException("Corrupt database file: computed checksum %llu does not match stored checksum %llu in block",
		                  computed_checksum, stored_checksum);
	}
}
```

加载现有数据库

duckdb/src/storage/single_file_block_manager.cpp:223-235 submodule=duckdb version=v0.10.1 snippet_id=34
```cpp
void SingleFileBlockManager::LoadExistingDatabase() {
	uint8_t flags;
	FileLockType lock;
	GetFileFlags(flags, lock, false);

	// open the RDBMS handle
	auto &fs = FileSystem::Get(db);
	handle = fs.OpenFile(path, flags, lock);

	MainHeader::CheckMagicBytes(*handle);
	// otherwise, we check the metadata of the file
	ReadAndChecksum(header_buffer, 0);
	DeserializeHeaderStructure<MainHeader>(header_buffer.buffer);
```

duckdb/src/storage/single_file_block_manager.cpp:407-411 submodule=duckdb version=v0.10.1 snippet_id=35
```cpp
void SingleFileBlockManager::Read(Block &block) {
	D_ASSERT(block.id >= 0);
	D_ASSERT(std::find(free_list.begin(), free_list.end(), block.id) == free_list.end());
	ReadAndChecksum(block, BLOCK_START + block.id * Storage::BLOCK_ALLOC_SIZE);
}
```

BufferHandle

duckdb/src/storage/buffer/block_handle.cpp:72-94 submodule=duckdb version=v0.10.1 snippet_id=36
```cpp
BufferHandle BlockHandle::Load(shared_ptr<BlockHandle> &handle, unique_ptr<FileBuffer> reusable_buffer) {
	if (handle->state == BlockState::BLOCK_LOADED) {
		// already loaded
		D_ASSERT(handle->buffer);
		return BufferHandle(handle, handle->buffer.get());
	}

	auto &block_manager = handle->block_manager;
	if (handle->block_id < MAXIMUM_BLOCK) {
		auto block = AllocateBlock(block_manager, std::move(reusable_buffer), handle->block_id);
		block_manager.Read(*block);
		handle->buffer = std::move(block);
	} else {
		if (handle->can_destroy) {
			return BufferHandle();
		} else {
			handle->buffer = block_manager.buffer_manager.ReadTemporaryBuffer(handle->tag, handle->block_id,
			                                                                  std::move(reusable_buffer));
		}
	}
	handle->state = BlockState::BLOCK_LOADED;
	return BufferHandle(handle, handle->buffer.get());
}
```
