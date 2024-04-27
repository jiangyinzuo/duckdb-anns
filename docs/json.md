# JSON 插件源码

## Load JSON插件

需要注册JSON类型、自定义函数

duckdb/extension/json/json_extension.cpp:26-65 submodule=duckdb version=v0.10.1 snippet_id=13
```cpp
void JsonExtension::Load(DuckDB &db) {
	auto &db_instance = *db.instance;
	// JSON type
	auto json_type = LogicalType::JSON();
	ExtensionUtil::RegisterType(db_instance, LogicalType::JSON_TYPE_NAME, std::move(json_type));

	// JSON casts
	JSONFunctions::RegisterSimpleCastFunctions(DBConfig::GetConfig(db_instance).GetCastFunctions());
	JSONFunctions::RegisterJSONCreateCastFunctions(DBConfig::GetConfig(db_instance).GetCastFunctions());
	JSONFunctions::RegisterJSONTransformCastFunctions(DBConfig::GetConfig(db_instance).GetCastFunctions());

	// JSON scalar functions
	for (auto &fun : JSONFunctions::GetScalarFunctions()) {
		ExtensionUtil::RegisterFunction(db_instance, fun);
	}

	// JSON table functions
	for (auto &fun : JSONFunctions::GetTableFunctions()) {
		ExtensionUtil::RegisterFunction(db_instance, fun);
	}

	// JSON pragma functions
	for (auto &fun : JSONFunctions::GetPragmaFunctions()) {
		ExtensionUtil::RegisterFunction(db_instance, fun);
	}

	// JSON replacement scan
	auto &config = DBConfig::GetConfig(*db.instance);
	config.replacement_scans.emplace_back(JSONFunctions::ReadJSONReplacement);

	// JSON copy function
	auto copy_fun = JSONFunctions::GetJSONCopyFunction();
	ExtensionUtil::RegisterFunction(db_instance, std::move(copy_fun));

	// JSON macro's
	for (idx_t index = 0; json_macros[index].name != nullptr; index++) {
		auto info = DefaultFunctionGenerator::CreateInternalMacroInfo(json_macros[index]);
		ExtensionUtil::RegisterFunction(db_instance, *info);
	}
}
```

## JSON Type

这段代码不在插件中。JSON类型是VARCHAR类型的别名

duckdb/src/common/types.cpp:1445-1452 submodule=duckdb version=v0.10.1 snippet_id=14
```cpp
//===--------------------------------------------------------------------===//
// JSON Type
//===--------------------------------------------------------------------===//
LogicalType LogicalType::JSON() {
	auto json_type = LogicalType(LogicalTypeId::VARCHAR);
	json_type.SetAlias(JSON_TYPE_NAME);
	return json_type;
}
```

## 实际执行的TableFunction

3个参数中，`context`没有用上

duckdb/extension/json/json_functions/read_json.cpp:273-275 submodule=duckdb version=v0.10.1 snippet_id=15
```cpp
static void ReadJSONFunction(ClientContext &context, TableFunctionInput &data_p, DataChunk &output) {
	auto &gstate = data_p.global_state->Cast<JSONGlobalTableFunctionState>().state;
	auto &lstate = data_p.local_state->Cast<JSONLocalTableFunctionState>().state;
```

#0  duckdb::ReadJSONFunction (context=..., data_p=..., output=...) at /root/duckdb-anns/duckdb/extension/json/json_functions/read_json.cpp:274
#1  0x0000558da16222b5 in duckdb::PhysicalTableScan::GetData (this=0x616000081080, context=..., chunk=..., input=...) at /root/duckdb-anns/duckdb/src/execution/operator/scan/physical_table_scan.cpp:74
#2  0x0000558d9e28667e in duckdb::PipelineExecutor::GetData (this=0x614000001c40, chunk=..., input=...) at /root/duckdb-anns/duckdb/src/parallel/pipeline_executor.cpp:466
#3  0x0000558d9e286e4f in duckdb::PipelineExecutor::FetchFromSource (this=0x614000001c40, result=...) at /root/duckdb-anns/duckdb/src/parallel/pipeline_executor.cpp:492
#4  0x0000558d9e281bca in duckdb::PipelineExecutor::Execute (this=0x614000001c40, max_chunks=50) at /root/duckdb-anns/duckdb/src/parallel/pipeline_executor.cpp:203
#5  0x0000558d9e26e0de in duckdb::PipelineTask::ExecuteTask (this=0x606000013040, mode=duckdb::TaskExecutionMode::PROCESS_PARTIAL) at /root/duckdb-anns/duckdb/src/parallel/pipeline.cpp:40
#6  0x0000558d9e2542eb in duckdb::ExecutorTask::Execute (this=0x606000013040, mode=duckdb::TaskExecutionMode::PROCESS_PARTIAL) at /root/duckdb-anns/duckdb/src/parallel/executor_task.cpp:32
#7  0x0000558d9e264bf3 in duckdb::Executor::ExecuteTask (this=0x61300000bf00, dry_run=false) at /root/duckdb-anns/duckdb/src/parallel/executor.cpp:516
#8  0x0000558d9dd9435b in duckdb::ClientContext::ExecuteTaskInternal (this=0x616000053490, lock=..., result=..., dry_run=false) at /root/duckdb-anns/duckdb/src/main/client_context.cpp:539
#9  0x0000558d9dded86c in duckdb::PendingQueryResult::ExecuteTaskInternal (this=0x61300000c0c0, lock=...) at /root/duckdb-anns/duckdb/src/main/pending_query_result.cpp:63
#10 0x0000558d9ddede33 in duckdb::PendingQueryResult::ExecuteInternal (this=0x61300000c0c0, lock=...) at /root/duckdb-anns/duckdb/src/main/pending_query_result.cpp:73
#11 0x0000558d9ddee4bb in duckdb::PendingQueryResult::Execute (this=0x61300000c0c0) at /root/duckdb-anns/duckdb/src/main/pending_query_result.cpp:86
#12 0x0000558d9ddf134f in duckdb::PreparedStatement::Execute (this=0x6120000bcd40, values=..., allow_stream_result=false) at /root/duckdb-anns/duckdb/src/main/prepared_statement.cpp:85
#13 0x0000558d9c24fe6a in duckdb_shell_sqlite3_print_duckbox (pStmt=0x60c000031fc0, max_rows=40, max_width=0, null_value=0x7fff4e7bea6c "", columnar=0) at /root/duckdb-anns/duckdb/tools/sqlite3_api_wrapper/sqlite3_api_wrapper.cpp:250
#14 0x0000558d9c1b133c in exec_prepared_stmt (pArg=0x7fff4e7be950, pStmt=0x60c000031fc0) at /root/duckdb-anns/duckdb/tools/shell/shell.c:12900
#15 0x0000558d9c1b4b8f in shell_exec (pArg=0x7fff4e7be950, zSql=0x60b0000000f0 "select * from 'compile_commands.json';", pzErrMsg=0x7fff4e7be7b0) at /root/duckdb-anns/duckdb/tools/shell/shell.c:13235
#16 0x0000558d9c1e80dd in runOneSqlLine (p=0x7fff4e7be950, zSql=0x60b0000000f0 "select * from 'compile_commands.json';", in=0x0, startline=2) at /root/duckdb-anns/duckdb/tools/shell/shell.c:19664
#17 0x0000558d9c1e9587 in process_input (p=0x7fff4e7be950) at /root/duckdb-anns/duckdb/tools/shell/shell.c:19775
#18 0x0000558d9c1ee4a8 in main (argc=1, argv=0x7fff4e7bfdc8) at /root/duckdb-anns/duckdb/tools/shell/shell.c:20597


将`yyjson_val`转换成`Vector`

#0  duckdb::TransformToString (vals=0x7fa7c0f1c200, alc=0x62f00000c518, result=..., count=484) at /root/duckdb-anns/duckdb/extension/json/json_functions/json_transform.cpp:348
#1  0x0000558da3bdd65c in duckdb::JSONTransform::Transform (vals=0x7fa7c0f1c200, alc=0x62f00000c518, result=..., count=484, options=...) at /root/duckdb-anns/duckdb/exten sion/json/json_functions/json_transform.cpp:893
#2  0x0000558da3bd36b0 in duckdb::JSONTransform::TransformObject (objects=0x62f000008410, alc=0x62f00000c518, count=484, names=..., result_vectors=..., options=...) at /root/duckdb-anns/duckdb/extension/json/json_functions/json_transform.cpp:454
#3  0x0000558da3c83e04 in duckdb::ReadJSONFunction (context=..., data_p=..., output=...) at /root/duckdb-anns/duckdb/extension/json/json_functions/read_json.cpp:291

---

把`output` DataChunk中的数据转换成JSON格式

duckdb/extension/json/json_functions/read_json.cpp:281-297 submodule=duckdb version=v0.10.1 snippet_id=16
```cpp
	if (!gstate.names.empty()) {
		vector<Vector *> result_vectors;
		result_vectors.reserve(gstate.column_indices.size());
		for (const auto &col_idx : gstate.column_indices) {
			result_vectors.emplace_back(&output.data[col_idx]);
		}

		D_ASSERT(gstate.bind_data.options.record_type != JSONRecordType::AUTO_DETECT);
		bool success;
		if (gstate.bind_data.options.record_type == JSONRecordType::RECORDS) {
			success = JSONTransform::TransformObject(values, lstate.GetAllocator(), count, gstate.names, result_vectors,
			                                         lstate.transform_options);
		} else {
			D_ASSERT(gstate.bind_data.options.record_type == JSONRecordType::VALUES);
			success = JSONTransform::Transform(values, lstate.GetAllocator(), *result_vectors[0], count,
			                                   lstate.transform_options);
		}
```

## TableFunction注册

创建TableFunction的时候，传递

- 函数名（在其它代码片段中被赋值）
- function: ReadJSONObjectsFunction: 被执行的函数
- bind: ReadJSONObjectsBind: 绑定的函数参数
- 全局变量状态 JSONGlobalTableFunctionState::Init
- 局部变量状态 JSONLocalTableFunctionState::Init

duckdb/extension/json/json_functions/read_json_objects.cpp:51-59 submodule=duckdb version=v0.10.1 snippet_id=17
```cpp
TableFunction GetReadJSONObjectsTableFunction(bool list_parameter, shared_ptr<JSONScanInfo> function_info) {
	auto parameter = list_parameter ? LogicalType::LIST(LogicalType::VARCHAR) : LogicalType::VARCHAR;
	TableFunction table_function({parameter}, ReadJSONObjectsFunction, ReadJSONObjectsBind,
	                             JSONGlobalTableFunctionState::Init, JSONLocalTableFunctionState::Init);
	JSONScan::TableFunctionDefaults(table_function);
	table_function.function_info = std::move(function_info);

	return table_function;
}
```
### ReadJSONObjectsBind

#### JSONScanData

这个类保存了一些函数参数

duckdb/extension/json/include/json_scan.hpp:84-84 submodule=duckdb version=v0.10.1 snippet_id=18
```cpp
struct JSONScanData : public TableFunctionData {
```

duckdb/extension/json/include/json_scan.hpp:98-113 submodule=duckdb version=v0.10.1 snippet_id=19
```cpp
public:
	//! Scan type
	JSONScanType type;

	//! File-specific options
	BufferedJSONReaderOptions options;

	//! Multi-file reader stuff
	MultiFileReaderBindData reader_bind;

	//! The files we're reading
	vector<string> files;
	//! Initial file reader
	unique_ptr<BufferedJSONReader> initial_reader;
	//! The readers
	vector<unique_ptr<BufferedJSONReader>> union_readers;
```


在`Bind`中被设置

duckdb/extension/json/json_scan.cpp:24-31 submodule=duckdb version=v0.10.1 snippet_id=20
```cpp
void JSONScanData::Bind(ClientContext &context, TableFunctionBindInput &input) {
	auto &info = input.info->Cast<JSONScanInfo>();
	type = info.type;
	options.format = info.format;
	options.record_type = info.record_type;
	auto_detect = info.auto_detect;

	for (auto &kv : input.named_parameters) {
```

这个结构体应该记录了用户SQL中传递的参数

duckdb/src/include/duckdb/function/table_function.hpp:83-96 submodule=duckdb version=v0.10.1 snippet_id=21
```cpp
struct TableFunctionBindInput {
	TableFunctionBindInput(vector<Value> &inputs, named_parameter_map_t &named_parameters,
	                       vector<LogicalType> &input_table_types, vector<string> &input_table_names,
	                       optional_ptr<TableFunctionInfo> info)
	    : inputs(inputs), named_parameters(named_parameters), input_table_types(input_table_types),
	      input_table_names(input_table_names), info(info) {
	}

	vector<Value> &inputs;
	named_parameter_map_t &named_parameters;
	vector<LogicalType> &input_table_types;
	vector<string> &input_table_names;
	optional_ptr<TableFunctionInfo> info;
};
```

#### JSONScanData 创建位置

在这里

duckdb/extension/json/json_functions/read_json_objects.cpp:7-20 submodule=duckdb version=v0.10.1 snippet_id=22
```cpp
unique_ptr<FunctionData> ReadJSONObjectsBind(ClientContext &context, TableFunctionBindInput &input,
                                             vector<LogicalType> &return_types, vector<string> &names) {
	auto bind_data = make_uniq<JSONScanData>();
	bind_data->Bind(context, input);

	bind_data->names.emplace_back("json");
	return_types.push_back(LogicalType::JSON());
	names.emplace_back("json");

	bind_data->reader_bind =
	    MultiFileReader::BindOptions(bind_data->options.file_options, bind_data->files, return_types, names);

	return std::move(bind_data);
}
```

## GlobalState和LocalState

GlobalState代表多线程并行执行一个TableFunction时，需要用到的状态变量。
LocalState是单线程内的状态变量

duckdb/extension/json/include/json_scan.hpp:274-293 submodule=duckdb version=v0.10.1 snippet_id=23
```cpp
struct JSONGlobalTableFunctionState : public GlobalTableFunctionState {
public:
	JSONGlobalTableFunctionState(ClientContext &context, TableFunctionInitInput &input);
	static unique_ptr<GlobalTableFunctionState> Init(ClientContext &context, TableFunctionInitInput &input);
	idx_t MaxThreads() const override;

public:
	JSONScanGlobalState state;
};

struct JSONLocalTableFunctionState : public LocalTableFunctionState {
public:
	JSONLocalTableFunctionState(ClientContext &context, JSONScanGlobalState &gstate);
	static unique_ptr<LocalTableFunctionState> Init(ExecutionContext &context, TableFunctionInitInput &input,
	                                                GlobalTableFunctionState *global_state);
	idx_t GetBatchIndex() const;

public:
	JSONScanLocalState state;
};
```

### GlobalState

duckdb/extension/json/json_scan.cpp:215-235 submodule=duckdb version=v0.10.1 snippet_id=24
```cpp
idx_t JSONGlobalTableFunctionState::MaxThreads() const {
	auto &bind_data = state.bind_data;

	if (!state.json_readers.empty() && state.json_readers[0]->HasFileHandle()) {
		// We opened and auto-detected a file, so we can get a better estimate
		auto &reader = *state.json_readers[0];
		if (bind_data.options.format == JSONFormat::NEWLINE_DELIMITED ||
		    reader.GetFormat() == JSONFormat::NEWLINE_DELIMITED) {
			return MaxValue<idx_t>(state.json_readers[0]->GetFileHandle().FileSize() / bind_data.maximum_object_size,
			                       1);
		}
	}

	if (bind_data.options.format == JSONFormat::NEWLINE_DELIMITED) {
		// We haven't opened any files, so this is our best bet
		return state.system_threads;
	}

	// One reader per file
	return bind_data.files.size();
}
```

### LocalState

duckdb/extension/json/json_scan.cpp:241-243 submodule=duckdb version=v0.10.1 snippet_id=25
```cpp
unique_ptr<LocalTableFunctionState> JSONLocalTableFunctionState::Init(ExecutionContext &context,
                                                                      TableFunctionInitInput &,
                                                                      GlobalTableFunctionState *global_state) {
```
