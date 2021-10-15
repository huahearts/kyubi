cmake_minimum_required(VERSION 2.8)
project(kyubi)

include (cmake/utils.cmake)
set(CMAKE_VERBOSE_MAKEFILE ON)
#set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated 
#-Werror -Wno-unused-function -Wno-builtin-macro-redefined")
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")

include_directories(.)
include_directories(/apps/kyubi/include)
link_directories(/apps/kyubi/lib)

find_library(YAMLCPP yaml-cpp)
#message("***", ${YAMLCPP})
set(LIB_SRC
    kyubi/log.cc
    kyubi/util.cc
    kyubi/config.cc
    )

add_library(kyubi SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(kyubi) #__FILE__
#add_library(sylar_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (sylar_STATIC PROPERTIES OUTPUT_NAME "sylar")

#add_executable(test tests/test.cc)
#add_dependencies(test kyubi)
#force_redefine_file_macro_for_sources(kyubi) #__FILE__
#target_link_libraries(test kyubi ${YAMLCPP})

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config kyubi)
force_redefine_file_macro_for_sources(test_config) #__FILE__
target_link_libraries(test_config kyubi ${YAMLCPP})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
  