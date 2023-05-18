project(puzzle)

add_library(${PROJECT_NAME}
    include/puzzle/Board.hpp  src/Board.cpp
    include/puzzle/Solver.hpp src/Solver.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_library(puzzle::puzzle ALIAS ${PROJECT_NAME})

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(tests tests/test_board.cpp tests/test_solver.cpp)
target_link_libraries(tests PRIVATE GTest::GTest puzzle::puzzle)
gtest_discover_tests(tests)

if(COMPILE_OPTS)
    target_compile_options(${PROJECT_NAME} PUBLIC ${COMPILE_OPTS})
    target_link_options(${PROJECT_NAME} PUBLIC ${LINK_OPTS})

    target_compile_options(tests PUBLIC ${COMPILE_OPTS})
    target_link_options(tests PUBLIC ${LINK_OPTS})
endif()
