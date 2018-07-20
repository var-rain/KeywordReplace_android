cmake_minimum_required(VERSION 3.4.1)

add_library( Keywords SHARED src/main/cpp/com_var_lib_keywords_Keywords.cpp src/main/cpp/com_var_lib_keywords_Keywords.h )

find_library( log-lib log )

target_link_libraries( Keywords ${log-lib} )