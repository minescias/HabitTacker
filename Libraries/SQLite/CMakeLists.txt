add_library(SQLite sqlite3.c)
target_link_libraries(SQLite pthread dl)