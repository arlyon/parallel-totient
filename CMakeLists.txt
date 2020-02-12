cmake_minimum_required(VERSION 3.16)
project(parallel_totient C)

set(CMAKE_C_STANDARD 11)

add_executable(totient_mpi src/mpi/main.c src/common.h)
add_executable(totient_openmp src/openmp/main.c src/common.h)
add_executable(totient src/single_threaded.c)

find_package(mpi REQUIRED)
message(STATUS "Run: ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ${MPIEXEC_PREFLAGS} EXECUTABLE ${MPIEXEC_POSTFLAGS} ARGS")
target_link_libraries(totient_mpi PUBLIC MPI::MPI_C)

find_package(openmp REQUIRED)
target_link_libraries(totient_openmp PUBLIC OpenMP::OpenMP_C)

if (NOT MSVC)
    target_compile_options(totient_openmp PRIVATE -Wall -Wextra -pedantic)
endif ()
