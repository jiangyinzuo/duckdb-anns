# 查询执行

## Physical Operator

duckdb/src/include/duckdb/execution/physical_operator.hpp:30-32 submodule=duckdb version=v0.10.1 snippet_id=5
```cpp
//! PhysicalOperator is the base class of the physical operators present in the
//! execution plan
class PhysicalOperator {
```

```
duckdb/src/include/duckdb/execution/operator/aggregate/physical_hash_aggregate.hpp|60 col 7| class PhysicalHashAggregate : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/aggregate/physical_perfecthash_aggregate.hpp|19 col 7| class PhysicalPerfectHashAggregate : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/aggregate/physical_streaming_window.hpp|17 col 7| class PhysicalStreamingWindow : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/aggregate/physical_ungrouped_aggregate.hpp|23 col 7| class PhysicalUngroupedAggregate : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/aggregate/physical_window.hpp|18 col 7| class PhysicalWindow : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_create_secret.hpp|17 col 7| class PhysicalCreateSecret : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_execute.hpp|16 col 7| class PhysicalExecute : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_explain_analyze.hpp|16 col 7| class PhysicalExplainAnalyze : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_limit.hpp|18 col 7| class PhysicalLimit : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_limit_percent.hpp|18 col 7| class PhysicalLimitPercent : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_load.hpp|17 col 7| class PhysicalLoad : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_pragma.hpp|17 col 7| class PhysicalPragma : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_prepare.hpp|17 col 7| class PhysicalPrepare : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_reservoir_sample.hpp|19 col 7| class PhysicalReservoirSample : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_reset.hpp|21 col 7| class PhysicalReset : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_result_collector.hpp|18 col 7| class PhysicalResultCollector : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_set.hpp|21 col 7| class PhysicalSet : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_streaming_limit.hpp|17 col 7| class PhysicalStreamingLimit : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_streaming_sample.hpp|17 col 7| class PhysicalStreamingSample : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_transaction.hpp|17 col 7| class PhysicalTransaction : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_vacuum.hpp|18 col 7| class PhysicalVacuum : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/helper/physical_verify_vector.hpp|34 col 7| class PhysicalVerifyVector : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/join/physical_delim_join.hpp|19 col 7| class PhysicalDelimJoin : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/join/physical_positional_join.hpp|17 col 7| class PhysicalPositionalJoin : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/order/physical_order.hpp|20 col 7| class PhysicalOrder : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/order/physical_top_n.hpp|18 col 7| class PhysicalTopN : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/persistent/physical_batch_copy_to_file.hpp|20 col 7| class PhysicalBatchCopyToFile : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/persistent/physical_batch_insert.hpp|15 col 7| class PhysicalBatchInsert : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/persistent/physical_copy_database.hpp|16 col 7| class PhysicalCopyDatabase : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/persistent/physical_copy_to_file.hpp|20 col 7| class PhysicalCopyToFile : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/persistent/physical_delete.hpp|17 col 7| class PhysicalDelete : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/persistent/physical_export.hpp|31 col 7| class PhysicalExport : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/persistent/physical_insert.hpp|22 col 7| class PhysicalInsert : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/persistent/physical_update.hpp|18 col 7| class PhysicalUpdate : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/projection/physical_pivot.hpp|19 col 7| class PhysicalPivot : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/projection/physical_projection.hpp|16 col 7| class PhysicalProjection : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/projection/physical_tableinout_function.hpp|17 col 7| class PhysicalTableInOutFunction : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/projection/physical_unnest.hpp|17 col 7| class PhysicalUnnest : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/scan/physical_column_data_scan.hpp|17 col 7| class PhysicalColumnDataScan : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/scan/physical_dummy_scan.hpp|15 col 7| class PhysicalDummyScan : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/scan/physical_empty_result.hpp|15 col 7| class PhysicalEmptyResult : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/scan/physical_expression_scan.hpp|17 col 7| class PhysicalExpressionScan : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/scan/physical_positional_scan.hpp|19 col 7| class PhysicalPositionalScan : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/scan/physical_table_scan.hpp|20 col 7| class PhysicalTableScan : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/schema/physical_alter.hpp|17 col 7| class PhysicalAlter : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/schema/physical_attach.hpp|17 col 7| class PhysicalAttach : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/schema/physical_create_art_index.hpp|23 col 7| class PhysicalCreateARTIndex : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/schema/physical_create_function.hpp|17 col 7| class PhysicalCreateFunction : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/schema/physical_create_schema.hpp|17 col 7| class PhysicalCreateSchema : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/schema/physical_create_sequence.hpp|17 col 7| class PhysicalCreateSequence : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/schema/physical_create_table.hpp|17 col 7| class PhysicalCreateTable : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/schema/physical_create_type.hpp|17 col 7| class PhysicalCreateType : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/schema/physical_create_view.hpp|17 col 7| class PhysicalCreateView : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/schema/physical_detach.hpp|16 col 7| class PhysicalDetach : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/schema/physical_drop.hpp|17 col 7| class PhysicalDrop : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/set/physical_cte.hpp|18 col 7| class PhysicalCTE : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/set/physical_recursive_cte.hpp|18 col 7| class PhysicalRecursiveCTE : public PhysicalOperator {
duckdb/src/include/duckdb/execution/operator/set/physical_union.hpp|15 col 7| class PhysicalUnion : public PhysicalOperator {
duckdb/src/include/duckdb/execution/physical_operator.hpp|221 col 7| class CachingPhysicalOperator : public PhysicalOperator {
```

duckdb/src/include/duckdb/common/enums/physical_operator_type.hpp:18-121 submodule=duckdb version=v0.10.1 snippet_id=6
```cpp
enum class PhysicalOperatorType : uint8_t {
	INVALID,
	ORDER_BY,
	LIMIT,
	STREAMING_LIMIT,
	LIMIT_PERCENT,
	TOP_N,
	WINDOW,
	UNNEST,
	UNGROUPED_AGGREGATE,
	HASH_GROUP_BY,
	PERFECT_HASH_GROUP_BY,
	FILTER,
	PROJECTION,
	COPY_TO_FILE,
	BATCH_COPY_TO_FILE,
	RESERVOIR_SAMPLE,
	STREAMING_SAMPLE,
	STREAMING_WINDOW,
	PIVOT,
	COPY_DATABASE,

	// -----------------------------
	// Scans
	// -----------------------------
	TABLE_SCAN,
	DUMMY_SCAN,
	COLUMN_DATA_SCAN,
	CHUNK_SCAN,
	RECURSIVE_CTE_SCAN,
	CTE_SCAN,
	DELIM_SCAN,
	EXPRESSION_SCAN,
	POSITIONAL_SCAN,
	// -----------------------------
	// Joins
	// -----------------------------
	BLOCKWISE_NL_JOIN,
	NESTED_LOOP_JOIN,
	HASH_JOIN,
	CROSS_PRODUCT,
	PIECEWISE_MERGE_JOIN,
	IE_JOIN,
	LEFT_DELIM_JOIN,
	RIGHT_DELIM_JOIN,
	POSITIONAL_JOIN,
	ASOF_JOIN,
	// -----------------------------
	// SetOps
	// -----------------------------
	UNION,
	RECURSIVE_CTE,
	CTE,

	// -----------------------------
	// Updates
	// -----------------------------
	INSERT,
	BATCH_INSERT,
	DELETE_OPERATOR,
	UPDATE,

	// -----------------------------
	// Schema
	// -----------------------------
	CREATE_TABLE,
	CREATE_TABLE_AS,
	BATCH_CREATE_TABLE_AS,
	CREATE_INDEX,
	ALTER,
	CREATE_SEQUENCE,
	CREATE_VIEW,
	CREATE_SCHEMA,
	CREATE_MACRO,
	DROP,
	PRAGMA,
	TRANSACTION,
	CREATE_TYPE,
	ATTACH,
	DETACH,

	// -----------------------------
	// Helpers
	// -----------------------------
	EXPLAIN,
	EXPLAIN_ANALYZE,
	EMPTY_RESULT,
	EXECUTE,
	PREPARE,
	VACUUM,
	EXPORT,
	SET,
	LOAD,
	INOUT_FUNCTION,
	RESULT_COLLECTOR,
	RESET,
	EXTENSION,
	VERIFY_VECTOR,

	// -----------------------------
	// Secret
	// -----------------------------
	CREATE_SECRET,
};
```

## Sink

duckdb/src/include/duckdb/execution/physical_operator.hpp:133-153 submodule=duckdb version=v0.10.1 snippet_id=7
```cpp
	// Sink interface

	//! The sink method is called constantly with new input, as long as new input is available. Note that this method
	//! CAN be called in parallel, proper locking is needed when accessing dat
	//! a inside the GlobalSinkState.
	virtual SinkResultType Sink(ExecutionContext &context, DataChunk &chunk, OperatorSinkInput &input) const;
	// The combine is called when a single thread has completed execution of its part of the pipeline, it is the final
	// time that a specific LocalSinkState is accessible. This method can be called in parallel while other Sink() or
	// Combine() calls are active on the same GlobalSinkState.
	virtual SinkCombineResultType Combine(ExecutionContext &context, OperatorSinkCombineInput &input) const;
	//! The finalize is called when ALL threads are finished execution. It is called only once per pipeline, and is
	//! entirely single threaded.
	//! If Finalize returns SinkResultType::FINISHED, the sink is marked as finished
	virtual SinkFinalizeType Finalize(Pipeline &pipeline, Event &event, ClientContext &context,
	                                  OperatorSinkFinalizeInput &input) const;
	//! For sinks with RequiresBatchIndex set to true, when a new batch starts being processed this method is called
	//! This allows flushing of the current batch (e.g. to disk)
	virtual SinkNextBatchType NextBatch(ExecutionContext &context, OperatorSinkNextBatchInput &input) const;

	virtual unique_ptr<LocalSinkState> GetLocalSinkState(ExecutionContext &context) const;
	virtual unique_ptr<GlobalSinkState> GetGlobalSinkState(ClientContext &context) const;
```
duckdb/src/include/duckdb/execution/physical_operator.hpp:161-171 submodule=duckdb version=v0.10.1 snippet_id=8
```cpp
	virtual bool IsSink() const {
		return false;
	}

	virtual bool ParallelSink() const {
		return false;
	}

	virtual bool RequiresBatchIndex() const {
		return false;
	}
```

### IsSink = true

Block操作，需要如蓄水池般积蓄所有数据后才能执行

duckdb/src/include/duckdb/execution/operator/aggregate/physical_hash_aggregate.hpp:60-60 submodule=duckdb version=v0.10.1 snippet_id=9
```cpp
class PhysicalHashAggregate : public PhysicalOperator {
```
duckdb/src/include/duckdb/execution/operator/aggregate/physical_hash_aggregate.hpp:121-127 submodule=duckdb version=v0.10.1 snippet_id=10
```cpp
	bool IsSink() const override {
		return true;
	}

	bool ParallelSink() const override {
		return true;
	}
```

默认是false，下面override的应该都是true
```
duckdb/src/execution/physical_operator.cpp|153 col 6| if (IsSink()) {
duckdb/src/execution/physical_operator.cpp|181 col 6| if (IsSink()) {
duckdb/src/include/duckdb/execution/operator/aggregate/physical_hash_aggregate.hpp|121 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/aggregate/physical_perfecthash_aggregate.hpp|59 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/aggregate/physical_ungrouped_aggregate.hpp|56 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/aggregate/physical_window.hpp|63 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/helper/physical_explain_analyze.hpp|41 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/helper/physical_limit.hpp|52 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/helper/physical_limit_percent.hpp|48 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/helper/physical_reservoir_sample.hpp|47 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/helper/physical_result_collector.hpp|37 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/helper/physical_vacuum.hpp|45 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/join/physical_asof_join.hpp|76 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/join/physical_blockwise_nl_join.hpp|63 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/join/physical_cross_product.hpp|45 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/join/physical_delim_join.hpp|31 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/join/physical_hash_join.hpp|98 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/join/physical_iejoin.hpp|58 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/join/physical_nested_loop_join.hpp|60 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/join/physical_piecewise_merge_join.hpp|67 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/join/physical_positional_join.hpp|43 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/order/physical_order.hpp|66 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/order/physical_top_n.hpp|50 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/persistent/physical_batch_copy_to_file.hpp|55 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/persistent/physical_batch_insert.hpp|65 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/persistent/physical_copy_to_file.hpp|61 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/persistent/physical_delete.hpp|48 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/persistent/physical_export.hpp|68 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/persistent/physical_insert.hpp|95 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/persistent/physical_update.hpp|52 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/schema/physical_create_art_index.hpp|67 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/schema/physical_create_type.hpp|40 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/set/physical_cte.hpp|43 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/operator/set/physical_recursive_cte.hpp|49 col 7| bool IsSink() const override {
duckdb/src/include/duckdb/execution/physical_operator.hpp|161 col 15| virtual bool IsSink() const {
duckdb/src/parallel/pipeline.cpp|185 col 14| if (!sink->IsSink()) {
duckdb/src/parallel/pipeline_executor.cpp|41 col 24| if (current_operator.IsSink() && current_operator.sink_state->state == SinkFinalizeType::NO_OUTPUT_POSSIBLE) {
```

## PhysicalTableInOutFunction

会在`PhysicalPlanGenerator::CreatePlan`的时候创建

duckdb/src/execution/physical_plan/plan_get.cpp:32-98 submodule=duckdb version=v0.10.1 snippet_id=11
```cpp
unique_ptr<PhysicalOperator> PhysicalPlanGenerator::CreatePlan(LogicalGet &op) {
	if (!op.children.empty()) {
		// this is for table producing functions that consume subquery results
		D_ASSERT(op.children.size() == 1);
		auto node = make_uniq<PhysicalTableInOutFunction>(op.types, op.function, std::move(op.bind_data), op.column_ids,
		                                                  op.estimated_cardinality, std::move(op.projected_input));
		node->children.push_back(CreatePlan(std::move(op.children[0])));
		return std::move(node);
	}
	if (!op.projected_input.empty()) {
		throw InternalException("LogicalGet::project_input can only be set for table-in-out functions");
	}

	unique_ptr<TableFilterSet> table_filters;
	if (!op.table_filters.filters.empty()) {
		table_filters = CreateTableFilterSet(op.table_filters, op.column_ids);
	}

	if (op.function.dependency) {
		op.function.dependency(dependencies, op.bind_data.get());
	}
	// create the table scan node
	if (!op.function.projection_pushdown) {
		// function does not support projection pushdown
		auto node = make_uniq<PhysicalTableScan>(op.returned_types, op.function, std::move(op.bind_data),
		                                         op.returned_types, op.column_ids, vector<column_t>(), op.names,
		                                         std::move(table_filters), op.estimated_cardinality, op.extra_info);
		// first check if an additional projection is necessary
		if (op.column_ids.size() == op.returned_types.size()) {
			bool projection_necessary = false;
			for (idx_t i = 0; i < op.column_ids.size(); i++) {
				if (op.column_ids[i] != i) {
					projection_necessary = true;
					break;
				}
			}
			if (!projection_necessary) {
				// a projection is not necessary if all columns have been requested in-order
				// in that case we just return the node

				return std::move(node);
			}
		}
		// push a projection on top that does the projection
		vector<LogicalType> types;
		vector<unique_ptr<Expression>> expressions;
		for (auto &column_id : op.column_ids) {
			if (column_id == COLUMN_IDENTIFIER_ROW_ID) {
				types.emplace_back(LogicalType::BIGINT);
				expressions.push_back(make_uniq<BoundConstantExpression>(Value::BIGINT(0)));
			} else {
				auto type = op.returned_types[column_id];
				types.push_back(type);
				expressions.push_back(make_uniq<BoundReferenceExpression>(type, column_id));
			}
		}

		auto projection =
		    make_uniq<PhysicalProjection>(std::move(types), std::move(expressions), op.estimated_cardinality);
		projection->children.push_back(std::move(node));
		return std::move(projection);
	} else {
		return make_uniq<PhysicalTableScan>(op.types, op.function, std::move(op.bind_data), op.returned_types,
		                                    op.column_ids, op.projection_ids, op.names, std::move(table_filters),
		                                    op.estimated_cardinality, op.extra_info);
	}
}
```

## Physical Plan

duckdb/src/include/duckdb/execution/physical_plan_generator.hpp:50-94 submodule=duckdb version=v0.10.1 snippet_id=12
```cpp
protected:
	unique_ptr<PhysicalOperator> CreatePlan(LogicalOperator &op);

	unique_ptr<PhysicalOperator> CreatePlan(LogicalAggregate &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalAnyJoin &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalColumnDataGet &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalComparisonJoin &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalCopyDatabase &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalCreate &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalCreateTable &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalCreateIndex &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalCreateSecret &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalCrossProduct &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalDelete &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalDelimGet &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalDistinct &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalDummyScan &expr);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalEmptyResult &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalExpressionGet &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalExport &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalFilter &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalGet &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalLimit &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalOrder &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalTopN &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalPositionalJoin &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalProjection &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalInsert &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalCopyToFile &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalExplain &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalSetOperation &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalUpdate &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalPrepare &expr);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalWindow &expr);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalExecute &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalPragma &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalSample &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalSet &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalReset &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalSimple &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalUnnest &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalRecursiveCTE &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalMaterializedCTE &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalCTERef &op);
	unique_ptr<PhysicalOperator> CreatePlan(LogicalPivot &op);
```
