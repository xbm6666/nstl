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
add_executable(queue_test "queue_test.cpp")
add_executable(priority_queue_test "priority_queue_test.cpp")
add_executable(priority_queue_benchmark "priority_queue_benchmark.cpp")
add_executable(set_test "set_test.cpp" )
add_executable(set_benchmark "set_benchmark.cpp" )
