// Copyright 2021 The "MobileTimeTracker" project authors. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be
// found in the LICENSE file.

#include "app/select_rows.h"

#include <sqlite3.h>

namespace m_time_tracker {

const std::error_code SelectRows::kEcDone = ErrorCodeFromSqlite(SQLITE_DONE);

SelectRows::~SelectRows() {
  if (stmt_) {
    const int result = sqlite3_finalize(stmt_);
    VERIFY(result == SQLITE_OK);
  }
}

std::error_code SelectRows::NextRow() noexcept {
  VERIFY(stmt_);
  const int result = sqlite3_step(stmt_);
  if (result == SQLITE_ROW) {
    // Move succeeded.
    return std::error_code();
  }
  return ErrorCodeFromSqlite(result);
}

std::optional<int> SelectRows::IntColumn(int index) noexcept {
  VERIFY(stmt_);
  const int type = sqlite3_column_type(stmt_, index);
  if (type == SQLITE_NULL) {
    return std::nullopt;
  }
  return sqlite3_column_int(stmt_, index);
}

std::optional<int64_t> SelectRows::Int64Column(int index) noexcept {
  VERIFY(stmt_);
  const int type = sqlite3_column_type(stmt_, index);
  if (type == SQLITE_NULL) {
    return std::nullopt;
  }
  return sqlite3_column_int64(stmt_, index);
}

std::optional<std::string> SelectRows::StringColumn(int index) noexcept {
  VERIFY(stmt_);
  const int type = sqlite3_column_type(stmt_, index);
  if (type == SQLITE_NULL) {
    return std::nullopt;
  }
  const char* result = reinterpret_cast<const char*>(
      sqlite3_column_text(stmt_, index));
  VERIFY(result);
  return std::string(result);
}

}  // namespace m_time_tracker
