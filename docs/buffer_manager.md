# Buffer Manager

接文件系统

duckdb/src/storage/standard_buffer_manager.cpp:153
```cpp
BufferHandle StandardBufferManager::Pin(shared_ptr<BlockHandle> &handle) {
	idx_t required_memory;
	{
		// lock the block
		lock_guard<mutex> lock(handle->lock);
		// check if the block is already loaded
		if (handle->state == BlockState::BLOCK_LOADED) {
			// the block is loaded, increment the reader count and return a pointer to the handle
			handle->readers++;
			return handle->Load(handle);
		}
		required_memory = handle->memory_usage;
	}
```

Pin被调用的位置
```
duckdb/src/common/sort/merge_sorter.cpp|337 col 38| auto result_handle = buffer_manager.Pin(result_block->block);
duckdb/src/common/sort/merge_sorter.cpp|419 col 43| auto result_data_handle = buffer_manager.Pin(result_data_block->block);
duckdb/src/common/sort/merge_sorter.cpp|427 col 39| result_heap_handle = buffer_manager.Pin(result_heap_block->block);
duckdb/src/common/sort/radix_sort.cpp|68 col 36| auto blob_handle = buffer_manager.Pin(blob_block.block);
duckdb/src/common/sort/radix_sort.cpp|284 col 32| auto handle = buffer_manager->Pin(block.block);
duckdb/src/common/sort/sort_state.cpp|274 col 42| auto new_block_handle = buffer_manager->Pin(new_block->block);
duckdb/src/common/sort/sort_state.cpp|279 col 39| auto block_handle = buffer_manager->Pin(block->block);
duckdb/src/common/sort/sort_state.cpp|294 col 47| auto unordered_data_handle = buffer_manager->Pin(unordered_data_block->block);
duckdb/src/common/sort/sort_state.cpp|300 col 45| auto ordered_data_handle = buffer_manager->Pin(ordered_data_block->block);
duckdb/src/common/sort/sort_state.cpp|329 col 46| auto ordered_heap_handle = buffer_manager->Pin(ordered_heap_block->block);
duckdb/src/common/sort/sort_state.cpp|353 col 40| auto sorting_handle = buffer_manager->Pin(sb.radix_sorting_data.back()->block);
duckdb/src/common/sort/sorted_block.cpp|71 col 39| auto data_handle_p = buffer_manager.Pin(data_block->block);
duckdb/src/common/sort/sorted_block.cpp|72 col 39| auto heap_handle_p = buffer_manager.Pin(heap_block->block);
duckdb/src/common/sort/sorted_block.cpp|227 col 33| radix_handle = buffer_manager.Pin(block->block);
duckdb/src/common/sort/sorted_block.cpp|238 col 32| data_handle = buffer_manager.Pin(data_block->block);
duckdb/src/common/sort/sorted_block.cpp|245 col 32| heap_handle = buffer_manager.Pin(heap_block->block);
duckdb/src/common/types/column/column_data_allocator.cpp|59 col 31| return alloc.buffer_manager->Pin(handle);
duckdb/src/common/types/column/column_data_allocator.cpp|118 col 58| chunk_state->handles[block_id] = alloc.buffer_manager->Pin(blocks[block_id].handle);
duckdb/src/common/types/row/row_data_collection.cpp|66 col 34| auto handle = buffer_manager.Pin(last_block.block);
duckdb/src/common/types/row/row_data_collection.cpp|76 col 33| auto handle = buffer_manager.Pin(new_block.block);
duckdb/src/common/types/row/row_data_collection_scanner.cpp|37 col 37| auto data_handle = buffer_manager.Pin(data_block->block);
duckdb/src/common/types/row/row_data_collection_scanner.cpp|55 col 38| auto heap_handle = buffer_manager.Pin(heap_block);
duckdb/src/common/types/row/row_data_collection_scanner.cpp|104 col 42| auto new_heap_handle = buffer_manager.Pin(swizzled_string_heap.blocks.back()->block);
duckdb/src/common/types/row/row_data_collection_scanner.cpp|134 col 37| data_handle = rows.buffer_manager.Pin(data_block->block);
duckdb/src/common/types/row/row_data_collection_scanner.cpp|144 col 37| heap_handle = heap.buffer_manager.Pin(heap_block->block);
duckdb/src/common/types/row/row_data_collection_scanner.cpp|188 col 41| auto data_handle = rows.buffer_manager.Pin(data_block.block);
duckdb/src/common/types/row/row_data_collection_scanner.cpp|194 col 41| auto heap_handle = heap.buffer_manager.Pin(heap_block.block);
duckdb/src/common/types/row/row_data_collection_scanner.cpp|264 col 51| pinned_blocks.emplace_back(rows.buffer_manager.Pin(data_block->block));
duckdb/src/common/types/row/row_data_collection_scanner.cpp|267 col 52| pinned_blocks.emplace_back(heap.buffer_manager.Pin(heap_block->block));
duckdb/src/common/types/row/tuple_data_allocator.cpp|449 col 70| it = pin_state.row_handles.emplace(row_block_index, buffer_manager.Pin(row_block.handle)).first;
duckdb/src/common/types/row/tuple_data_allocator.cpp|463 col 72| it = pin_state.heap_handles.emplace(heap_block_index, buffer_manager.Pin(heap_block.handle)).first;
duckdb/src/execution/index/fixed_size_buffer.cpp|102 col 36| auto dst_handle = buffer_manager.Pin(p_block_for_index.block_handle);
duckdb/src/execution/index/fixed_size_buffer.cpp|132 col 33| buffer_handle = buffer_manager.Pin(block_handle);
duckdb/src/execution/operator/csv_scanner/buffer_manager/csv_buffer.cpp|76 col 53| return make_shared<CSVBufferHandle>(buffer_manager.Pin(block), actual_buffer_size, last_buffer, file_number,
duckdb/src/include/duckdb/storage/buffer_manager.hpp|42 col 23| virtual BufferHandle Pin(shared_ptr<BlockHandle> &handle) = 0;
duckdb/src/include/duckdb/storage/compression/alp/alp_compress.hpp|99 col 27| handle = buffer_manager.Pin(current_segment->block);
duckdb/src/include/duckdb/storage/compression/alp/alp_scan.hpp|73 col 27| handle = buffer_manager.Pin(segment.block);
duckdb/src/include/duckdb/storage/compression/alprd/alprd_compress.hpp|111 col 27| handle = buffer_manager.Pin(current_segment->block);
duckdb/src/include/duckdb/storage/compression/alprd/alprd_scan.hpp|78 col 27| handle = buffer_manager.Pin(segment.block);
duckdb/src/include/duckdb/storage/compression/chimp/chimp_scan.hpp|143 col 27| handle = buffer_manager.Pin(segment.block);
duckdb/src/include/duckdb/storage/compression/patas/patas_scan.hpp|95 col 27| handle = buffer_manager.Pin(segment.block);
duckdb/src/include/duckdb/storage/standard_buffer_manager.hpp|62 col 15| BufferHandle Pin(shared_ptr<BlockHandle> &handle) final override;
duckdb/src/include/duckdb/storage/string_uncompressed.hpp|64 col 32| auto handle = buffer_manager.Pin(segment.block);
duckdb/src/include/duckdb/storage/string_uncompressed.hpp|76 col 32| auto handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/buffer/block_manager.cpp|34 col 35| auto old_handle = buffer_manager.Pin(old_block);
duckdb/src/storage/compression/bitpacking.cpp|488 col 27| handle = buffer_manager.Pin(current_segment->block);
duckdb/src/storage/compression/bitpacking.cpp|608 col 27| handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/dictionary_compression.cpp|180 col 35| current_handle = buffer_manager.Pin(current_segment->block);
duckdb/src/storage/compression/dictionary_compression.cpp|264 col 32| auto handle = buffer_manager.Pin(current_segment->block);
duckdb/src/storage/compression/dictionary_compression.cpp|440 col 33| state->handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/fixed_size_uncompressed.cpp|132 col 34| result->handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/fixed_size_uncompressed.cpp|172 col 31| auto handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/fixed_size_uncompressed.cpp|185 col 31| auto handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/fsst.cpp|221 col 35| current_handle = buffer_manager.Pin(current_segment->block);
duckdb/src/storage/compression/fsst.cpp|320 col 32| auto handle = buffer_manager.Pin(current_segment->block);
duckdb/src/storage/compression/fsst.cpp|522 col 33| state->handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/fsst.cpp|644 col 31| auto handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/rle.cpp|154 col 27| handle = buffer_manager.Pin(current_segment->block);
duckdb/src/storage/compression/rle.cpp|250 col 27| handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/string_uncompressed.cpp|68 col 34| result->handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/string_uncompressed.cpp|112 col 32| auto handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/string_uncompressed.cpp|164 col 32| auto handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/string_uncompressed.cpp|180 col 31| auto handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/string_uncompressed.cpp|308 col 27| handle = buffer_manager.Pin(state.head->block);
duckdb/src/storage/compression/string_uncompressed.cpp|334 col 32| auto handle = buffer_manager.Pin(block_handle);
duckdb/src/storage/compression/string_uncompressed.cpp|359 col 29| handle = buffer_manager.Pin(block_handle);
duckdb/src/storage/compression/string_uncompressed.cpp|372 col 32| auto handle = buffer_manager.Pin(entry->second.get().block);
duckdb/src/storage/compression/validity_uncompressed.cpp|212 col 34| result->handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/validity_uncompressed.cpp|383 col 31| auto handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/validity_uncompressed.cpp|397 col 31| auto handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/validity_uncompressed.cpp|405 col 32| auto handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/compression/validity_uncompressed.cpp|447 col 31| auto handle = buffer_manager.Pin(segment.block);
duckdb/src/storage/metadata/metadata_manager.cpp|60 col 33| handle.handle = buffer_manager.Pin(block.block);
duckdb/src/storage/metadata/metadata_manager.cpp|66 col 35| auto old_buffer = buffer_manager.Pin(block.block);
duckdb/src/storage/metadata/metadata_manager.cpp|181 col 32| auto handle = buffer_manager.Pin(block.block);
duckdb/src/storage/partial_block_manager.cpp|22 col 53| auto buffer_handle = block_manager.buffer_manager.Pin(block_handle);
duckdb/src/storage/standard_buffer_manager.cpp|118 col 9| return Pin(*block_ptr);
duckdb/src/storage/standard_buffer_manager.cpp|153 col 37| BufferHandle StandardBufferManager::Pin(shared_ptr<BlockHandle> &handle) {
duckdb/src/storage/table/column_checkpoint_state.cpp|83 col 35| auto old_handle = buffer_manager.Pin(other.block_handle);
duckdb/src/storage/table/column_checkpoint_state.cpp|85 col 35| auto new_handle = buffer_manager.Pin(block_handle);
duckdb/src/storage/table/column_checkpoint_state.cpp|146 col 37| auto old_handle = buffer_manager.Pin(segment->block);
duckdb/src/storage/table/column_checkpoint_state.cpp|148 col 37| auto new_handle = buffer_manager.Pin(pstate.block_handle);
duckdb/src/storage/table/column_segment.cpp|151 col 35| auto old_handle = buffer_manager.Pin(block);
duckdb/src/storage/wal_replay.cpp|552 col 40| auto buffer_handle = buffer_manager.Pin(block_handle);
duckdb/test/sql/storage/test_buffer_manager.cpp|168 col 27| handle = buffer_manager.Pin(block);
duckdb/test/sql/storage/test_buffer_manager.cpp|182 col 27| handle = buffer_manager.Pin(block);
duckdb/test/sql/storage/test_buffer_manager.cpp|238 col 29| auto pin = buffer_manager.Pin(blocks[i]);
duckdb/test/sql/storage/test_buffer_manager.cpp|256 col 29| auto pin = buffer_manager.Pin(blocks[i]);
duckdb/test/sql/storage/test_buffer_manager.cpp|272 col 29| auto pin = buffer_manager.Pin(blocks[i]);
duckdb/test/sql/storage/test_buffer_manager.cpp|289 col 29| auto pin = buffer_manager.Pin(blocks[i]);
```

`BufferManager`是个虚基类。只有`StandardBufferManager`一个子类。

duckdb/src/include/duckdb/storage/buffer_manager.hpp:25
```cpp
class BufferManager {
	friend class BufferHandle;
	friend class BlockHandle;
	friend class BlockManager;

public:
	BufferManager() {
	}
	virtual ~BufferManager() {
	}

public:
	static unique_ptr<BufferManager> CreateStandardBufferManager(DatabaseInstance &db, DBConfig &config);
	virtual BufferHandle Allocate(MemoryTag tag, idx_t block_size, bool can_destroy = true,
	                              shared_ptr<BlockHandle> *block = nullptr) = 0;
	//! Reallocate an in-memory buffer that is pinned.
	virtual void ReAllocate(shared_ptr<BlockHandle> &handle, idx_t block_size) = 0;
	virtual BufferHandle Pin(shared_ptr<BlockHandle> &handle) = 0;
	virtual void Unpin(shared_ptr<BlockHandle> &handle) = 0;
```

在这里创建。

duckdb/src/main/database.cpp:190
```cpp
void DatabaseInstance::Initialize(const char *database_path, DBConfig *user_config) {
duckdb/src/main/database.cpp:225
	buffer_manager = make_uniq<StandardBufferManager>(*this, config.options.temporary_directory);
```
