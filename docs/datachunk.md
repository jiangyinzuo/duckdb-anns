

The data chunk class is the intermediate representation used by the
execution engine of DuckDB. 
It effectively represents a subset of a relation.
It holds a set of vectors that all have the same length.

用一个duckdb::vector保存

duckdb/src/include/duckdb/common/types/data_chunk.hpp:43-50 submodule=duckdb version=v0.10.1 snippet_id=26
```cpp
class DataChunk {
public:
	//! Creates an empty DataChunk
	DUCKDB_API DataChunk();
	DUCKDB_API ~DataChunk();

	//! The vectors owned by the DataChunk.
	vector<Vector> data;
```

duckdb/src/include/duckdb/common/types/vector.hpp:66-80 submodule=duckdb version=v0.10.1 snippet_id=27
```cpp
//!  Vector of values of a specified PhysicalType.
class Vector {
	friend struct ConstantVector;
	friend struct DictionaryVector;
	friend struct FlatVector;
	friend struct ListVector;
	friend struct StringVector;
	friend struct FSSTVector;
	friend struct StructVector;
	friend struct UnionVector;
	friend struct SequenceVector;
	friend struct ArrayVector;

	friend class DataChunk;
	friend class VectorCacheBuffer;
```
duckdb/src/include/duckdb/common/types/vector.hpp:227-241 submodule=duckdb version=v0.10.1 snippet_id=28
```cpp
protected:
	//! The vector type specifies how the data of the vector is physically stored (i.e. if it is a single repeated
	//! constant, if it is compressed)
	VectorType vector_type;
	//! The type of the elements stored in the vector (e.g. integer, float)
	LogicalType type;
	//! A pointer to the data.
	data_ptr_t data;
	//! The validity mask of the vector
	ValidityMask validity;
	//! The main buffer holding the data of the vector
	buffer_ptr<VectorBuffer> buffer;
	//! The buffer holding auxiliary data of the vector
	//! e.g. a string vector uses this to store strings
	buffer_ptr<VectorBuffer> auxiliary;
```
