/*
  Copyright 2022, The Cozo Project Authors.

  This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
  If a copy of the MPL was not distributed with this file,
  You can obtain one at https://mozilla.org/MPL/2.0/.
*/

#ifndef COZO_C_H
#define COZO_C_H

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually. */

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Open a database.
 *
 * `engine`:  which storage engine to use, can be "mem", "sqlite" or "rocksdb".
 * `path`:    should contain the UTF-8 encoded path name as a null-terminated C-string.
 * `db_id`:   will contain the ID of the database opened.
 * `options`: options for the DB constructor: engine dependent.
 *
 * When the function is successful, null pointer is returned,
 * otherwise a pointer to a C-string containing the error message will be returned.
 * The returned C-string must be freed with `cozo_free_str`.
 */
char *cozo_open_db(const char *engine, const char *path, const char *options, int32_t *db_id);

/**
 * Close a database.
 *
 * `db_id`: the ID representing the database to close.
 *
 * Returns `true` if the database is closed,
 * `false` if it has already been closed, or does not exist.
 */
bool cozo_close_db(int32_t db_id);

/**
 * Run query against a database.
 *
 * `db_id`:           the ID representing the database to run the query.
 * `script_raw`:      a UTF-8 encoded C-string for the CozoScript to execute.
 * `params_raw`:      a UTF-8 encoded C-string for the params of the query,
 *                    in JSON format. You must always pass in a valid JSON map,
 *                    even if you do not use params in your query
 *                    (pass "{}" in this case).
 * `immutable_query`: whether the query is read-only.
 *
 * Returns a UTF-8-encoded C-string that **must** be freed with `cozo_free_str`.
 * The string contains the JSON return value of the query.
 */
char *cozo_run_query(int32_t db_id,
                     const char *script_raw,
                     const char *params_raw,
                     bool immutable_query);

/**
 * Import data into relations
 *
 * Note that triggers are _not_ run for the relations, if any exists.
 * If you need to activate triggers, use queries with parameters.
 *
 * `db_id`:        the ID representing the database.
 * `json_payload`: a UTF-8 encoded JSON payload, in the same form as returned by exporting relations.
 *
 * Returns a UTF-8-encoded C-string indicating the result that **must** be freed with `cozo_free_str`.
 */
char *cozo_import_relations(int32_t db_id,
                            const char *json_payload);

/**
 * Export relations into JSON
 *
 * `db_id`:        the ID representing the database.
 * `json_payload`: a UTF-8 encoded JSON payload, see the manual for the expected fields.
 *
 * Returns a UTF-8-encoded C-string indicating the result that **must** be freed with `cozo_free_str`.
 */
char *cozo_export_relations(int32_t db_id,
                            const char *json_payload);

/**
 * Backup the database.
 *
 * `db_id`:    the ID representing the database.
 * `out_path`: path of the output file.
 *
 * Returns a UTF-8-encoded C-string indicating the result that **must** be freed with `cozo_free_str`.
 */
char *cozo_backup(int32_t db_id,
                  const char *out_path);

/**
 * Restore the database from a backup.
 *
 * `db_id`:   the ID representing the database.
 * `in_path`: path of the input file.
 *
 * Returns a UTF-8-encoded C-string indicating the result that **must** be freed with `cozo_free_str`.
 */
char *cozo_restore(int32_t db_id,
                   const char *in_path);

/**
 * Import data into relations from a backup
 *
 * Note that triggers are _not_ run for the relations, if any exists.
 * If you need to activate triggers, use queries with parameters.
 *
 * `db_id`:        the ID representing the database.
 * `json_payload`: a UTF-8 encoded JSON payload: `{"path": ..., "relations": [...]}`
 *
 * Returns a UTF-8-encoded C-string indicating the result that **must** be freed with `cozo_free_str`.
 */
char *cozo_import_from_backup(int32_t db_id,
                              const char *json_payload);

/**
 * Free any C-string returned from the Cozo C API.
 * Must be called exactly once for each returned C-string.
 *
 * `s`: the C-string to free.
 */
void cozo_free_str(char *s);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif /* COZO_C_H */
