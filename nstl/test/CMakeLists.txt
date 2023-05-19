include_directories("E:/VS/google_test/include/")
include_directories(..)

link_directories("E:/VS/google_test/lib/")
link_libraries(gtestd)
link_libraries(gmockd)

find_package ( benchmark REQUIRED )
link_libraries(benchmark::benchmark)
link_libraries(shlwapi)


add_executable(vector_benchmark "vector_benchmark.cpp")
add_executable(vector_test "vector_test.cpp")
add_executable(stack_test "stack_test.cpp")
add_executable(deque_test "deque_test.cpp")
add_executable(deque_benchmark "deque_benchmark.cpp")
