cmake_minimum_required(VERSION 3.16)
project(parallel_totient C)

set(CMAKE_C_STANDARD 11)

add_executable(totient_mpi src/mpi/main.c src/common.h src/mpi/cli.h)
add_executable(totient_openmp src/openmp/main.c src/common.h)
add_executable(totient src/single_threaded.c)

find_package(MPI REQUIRED)
target_link_libraries(totient_mpi PUBLIC MPI::MPI_C)

find_package(OpenMP REQUIRED)
target_link_libraries(totient_openmp PUBLIC OpenMP::OpenMP_C)

# add the __FILENAME__ macro to allow the debug to print the file
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")

if (NOT MSVC)
    target_compile_options(totient_openmp PRIVATE -Wall -Wextra -pedantic)
endif ()
