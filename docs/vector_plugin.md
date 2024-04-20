# DuckDB如何增加向量功能

以插件形式增加，可以参考两类DuckDB官方插件

数据类型插件

- json

其它数据库存储服务

- AWS
    - CALL 函数初始化
- AZURE
    - 直接 `SELECT * FROM az://...`
- IceBurg
```sql
SELECT count(*) FROM iceberg_scan('s3://bucketname/lineitem_iceberg/metadata/02701-1e474dc7-4723-4f8d-a8b3-b5f0454eb7ce.metadata.json', allow_moved_paths = true);
```

- [postgres](https://github.com/duckdb/postgres_scanner) / mysql
    - ATTACH语句初始化

1. 插件如何定义自定义函数？
2. DuckDB内部数据结构`duckdb::DataChunk`, `duckdb::Vector`如何适应向量数据类型？
3. 向量插件如何适应DuckDB的查询执行？
4. 如何初始化一些全局对象？
    - GPU内存管理？
