cmake_minimum_required(VERSION 3.15)

project(LibOrganic LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


add_library(liborganic STATIC
	src/DecayManager.cpp
)

target_include_directories(liborganic
	PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
		   $<INSTALL_INTERFACE:include>
)

target_compile_features(liborganic PUBLIC cxx_std_20)
target_link_libraries(liborganic PUBLIC pthread)


add_executable(example src/main.cpp)
target_link_libraries(example PRIVATE liborganic)

install(TARGETS liborganic
		ARCHIVE DESTINATION lib
		LIBRARY DESTINATION lib
		RUNTIME DESTINATION bin)

install(DIRECTORY include/ DESTINATION include)

enable_testing()
