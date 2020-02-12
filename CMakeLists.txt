cmake_minimum_required(VERSION 3.16)
project(parallel_totient C)

set(CMAKE_C_STANDARD 11)

add_executable(parallel_totient_mpi mpi/main.c)
add_executable(parallel_totient_openmp openmp/main.c)

find_package(MPI REQUIRED)
message(STATUS "Run: ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ${MPIEXEC_PREFLAGS} EXECUTABLE ${MPIEXEC_POSTFLAGS} ARGS")
target_link_libraries(parallel_totient_mpi PUBLIC MPI::MPI_C)
target_link_libraries(parallel_totient_openmp PUBLIC MPI::MPI_C)
