cmake_minimum_required(VERSION 3.10)

project(SH_TRI VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable( SH_TRI ${PROJECT_SOURCE_DIR}/example.cc )

target_include_directories( 	SH_TRI PUBLIC
								"${PROJECT_SOURCE_DIR}/../SH_Algebra/include"
								"${PROJECT_SOURCE_DIR}/include" )
