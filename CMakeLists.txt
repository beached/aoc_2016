cmake_minimum_required(VERSION 3.10)
project( aoc_2016 )

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include("${CMAKE_SOURCE_DIR}/glean/CMakeListsCompiler.txt")
include("${CMAKE_SOURCE_DIR}/glean/CMakeLists.txt")

add_definitions( -DBOOST_TEST_DYN_LINK -DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK )
find_package( Boost COMPONENTS system iostreams filesystem regex unit_test_framework REQUIRED )
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories( ${Boost_LIBRARY_DIRS} )
include_directories( SYSTEM ${Boost_INCLUDE_DIRS} )

find_package( Threads )

set( HEADER_FOLDER "include" )
set( SOURCE_FOLDER "src" )
set( TEST_FOLDER "tests" )

include_directories( ${HEADER_FOLDER} )

set( HEADER_FILES
)

set( SOURCE_FILES
#	${SOURCE_FOLDER}/day_03.cpp
)

#add_library ( aoc_2018_lib STATIC ${HEADER_FILES} ${SOURCE_FILES} )
#add_dependencies( aoc_2018_lib dependency_stub )

add_executable( day_07_test ${HEADER_FOLDER}/day_07.h ${HEADER_FILES} ${TEST_FOLDER}/day_07_test.cpp )
target_link_libraries( day_07_test ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} ${COMPILER_SPECIFIC_LIBS} ${CMAKE_THREAD_LIBS_INIT} )
add_dependencies( day_07_test dependency_stub )

