add_library(module_DataBase "")
target_sources(module_DataBase
  PRIVATE
      DataBase.cpp
  PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/DataBase.h
  )

target_include_directories(module_DataBase
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/MySql/include/
    # D:/vs/VSCodeC++/blog/src/DataBase/MySql/include/
)
target_link_libraries(module_DataBase
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/MySql/lib/libmysql.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/MySql/lib/libmysql.lib
)