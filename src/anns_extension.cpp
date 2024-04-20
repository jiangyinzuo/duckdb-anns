#include "duckdb/common/types/data_chunk.hpp"
#include "duckdb/common/types/string_type.hpp"
#include "duckdb/common/types/vector.hpp"
#include "duckdb/common/vector_operations/unary_executor.hpp"
#include "duckdb/common/winapi.hpp"
#include "duckdb/execution/expression_executor_state.hpp"
#include "duckdb/function/table_function.hpp"
#include "duckdb/main/database.hpp"

#include <string>
#define DUCKDB_EXTENSION_MAIN

#include "duckdb.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/common/string_util.hpp"
#include "duckdb/function/scalar_function.hpp"
#include "duckdb/main/extension_util.hpp"
#include "anns_extension.hpp"

#include <duckdb/parser/parsed_data/create_scalar_function_info.hpp>

// OpenSSL linked through vcpkg
#include <openssl/opensslv.h>

namespace duckdb {

inline void AnnsScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {
	auto &name_vector = args.data[0];
	UnaryExecutor::Execute<string_t, string_t>(name_vector, result, args.size(), [&](string_t name) {
		return StringVector::AddString(result, "Anns " + name.GetString() + " 🐥");
		;
	});
}

inline void AnnsOpenSSLVersionScalarFun(DataChunk &args, ExpressionState &state, Vector &result) {
	auto &name_vector = args.data[0];
	UnaryExecutor::Execute<string_t, string_t>(name_vector, result, args.size(), [&](string_t name) {
		return StringVector::AddString(result, "Anns " + name.GetString() + ", my linked OpenSSL version is " +
		                                           OPENSSL_VERSION_TEXT);
		;
	});
}

inline void AnnsFunction(ClientContext &context, TableFunctionInput &data, DataChunk &output) {

}

static void LoadInternal(DatabaseInstance &instance) {
	// Register a scalar function
	auto anns_scalar_function = ScalarFunction("duckduck", {LogicalType::VARCHAR}, LogicalType::VARCHAR, AnnsScalarFun);
	ExtensionUtil::RegisterFunction(instance, anns_scalar_function);

	// Register another scalar function
	auto anns_openssl_version_scalar_function = ScalarFunction("anns_openssl_version", {LogicalType::VARCHAR},
	                                                            LogicalType::VARCHAR, AnnsOpenSSLVersionScalarFun);
	ExtensionUtil::RegisterFunction(instance, anns_openssl_version_scalar_function);

	TableFunction table_function("anns", {}, AnnsFunction);
}

void AnnsExtension::Load(DuckDB &db) {
	LoadInternal(*db.instance);
}
std::string AnnsExtension::Name() {
	return "anns";
}

} // namespace duckdb

extern "C" {

DUCKDB_EXTENSION_API void anns_init(duckdb::DatabaseInstance &db) {
	duckdb::DuckDB db_wrapper(db);
	db_wrapper.LoadExtension<duckdb::AnnsExtension>();
}

DUCKDB_EXTENSION_API const char *anns_version() {
	return duckdb::DuckDB::LibraryVersion();
}
}

#ifndef DUCKDB_EXTENSION_MAIN
#error DUCKDB_EXTENSION_MAIN not defined
#endif
