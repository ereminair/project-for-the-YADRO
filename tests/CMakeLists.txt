# GoogleTest через FetchContent
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Сами тесты
file(GLOB TEST_FILES "*.cpp")

add_executable(tests ${TEST_FILES} ../src/Sorter.cpp ../src/Tape.cpp)
target_include_directories(tests PRIVATE ../include)

target_link_libraries(tests gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
