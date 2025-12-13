cmake_minimum_required(VERSION 3.15)

project(LibOrganic 
    LANGUAGES CXX 
    VERSION 0.1.0
    DESCRIPTION "Biodegradable memory wrapper for C++20"
    HOMEPAGE_URL "https://github.com/alexandrusu1/LibOrganic"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(LIBORGANIC_BUILD_EXAMPLES "Build example programs" ON)

add_library(liborganic STATIC
    src/DecayManager.cpp
)

target_include_directories(liborganic
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(liborganic PUBLIC cxx_std_20)

find_package(Threads REQUIRED)
target_link_libraries(liborganic PUBLIC Threads::Threads)

if(LIBORGANIC_BUILD_EXAMPLES)
    add_executable(example src/main.cpp)
    target_link_libraries(example PRIVATE liborganic)

    add_executable(game_health examples/game_health.cpp)
    target_link_libraries(game_health PRIVATE liborganic)

    add_executable(expiring_secret examples/expiring_secret.cpp)
    target_link_libraries(expiring_secret PRIVATE liborganic)

    add_executable(memory_corruption examples/memory_corruption.cpp)
    target_link_libraries(memory_corruption PRIVATE liborganic)
endif()

install(TARGETS liborganic
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/LibOrganicConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

enable_testing()
