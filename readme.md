# Parallel Totient

> Deadline: March 13, 2020
> Robotarium cluster website: https://ecr-cluster.github.io

## Summary

For coursework 1 (CWK1) you will develop and measure parallel versions of a program using one of the following parallel 
programming technologies: C+MPI or OpenMP. You will compare the performance and programming models of these technologies. 
The parallel machines are nodes in the Robotarium high-performance cluster at Heriot-Watt.

## Submission instructions

There are two parts to the submission process.

1. Your source code implementation. Push your code to to the Heriot-Watt GitLab server: https://gitlab-student.macs.hw.ac.uk
  - Either create 1 GitLab project for each team member (i.e. 2 GitLab projects for your submission), or create 1 GitLab project with you both as Members (Settings → Members when looking at the project page on GitLab) i.e. just 1 GitLab project for your submission. Choose whichever option works best for you as a group.
  - Include the URLs to the GitLab project in your report.
2. A report. A PDF should be submitted on Vision (sub-menu Assessment) and as a hard copy in the drop-box near the MACS 
   School Office. Marks will be lost if your report does not following the structure outlined below or does not containing
   all of the specified results. 
   
## Learning Objectives of coursework 1

The Learning Outcomes (LO) of this F20DP course are listed at the end of this document. The learning objectives of 
coursework 1 is tied to many of these Learning Outcomes:
- MPI and OpenMP parallel programming skills (LO2, LO4, LO6).
- Ability to benchmark/measure parallel performance: efficiency, scalability and speedup (LO5). 
- Compare and contrast MPI and OpenMP parallel programming models (LO7).
    
The program that should be parallelised is the computation of the sum of Euler totient computations over a range of 
integer values. The Euler totient function computes, for a given integer n, the number of positive integers smaller 
than n and relatively prime to n, i.e. Φ(n) ≡| {m | m ∈ {1,...,n−1}∧m ⊥ n} |. Two numbers m and n are relatively prime, 
if the only integer number that divides both is 1. To test this, it is sufficient to establish that their greatest 
common divisor is 1, i.e. m ⊥ n ≡ gcd m n = 1. Thus, the task for this program is: for a given integer n, compute 
Σni=1Φ(n).

The following C code is a direct implementation of the above specification, as starting point for the parallel 
algorithm is on GitLab:

https://gitlab-student.macs.hw.ac.uk/f20dp-2019-20/totient-range

Try it out:

```bash
$ make
$ make test
$ ./totient 1 1000 $ ./totient 10 2000
```

## Organisation

The assessed coursework work is to be carried out in pairs, and you should choose your own partner. If you struggle to 
find a partner to team up with, I suggest you stay in the classroom after one of the lectures to meet other students
 that are in the same position.
Each member of the team chooses either MPI or OpenMP, and implements a parallel version of totient range in this 
technology and evaluates the performance of this parallel version:

- C with MPI for distributed memory parallelism using explicit message passing;
- C with OpenMP for shared memory multicore parallelism.

Together you can share ideas about how to parallelise the code and how to tune the parallel performance.
However, it needs to be clearly stated who implemented the parallel version using which technology. Together you should 
prepare a comparative report using the structure below. It is relatively easy to produce a simple parallelisation of 
both programs, however additional marks are available for thoughtful sequential and parallel performance tuning.
Tools that can help you, and have been discussed on these slides, are gprof and cachegrind for sequential C and OpenMP 
profiling functions like omp get wtime. You are welcome to use other tools, if you find them useful. In each case you 
should motivate your choice of tool and reflect how useful it was for tuning performance. For plotting parallel 
performance results gnuplot, R, Excel or one of many Python libraries are recommended.

A video has been created to describe the Sum Totient algorithm to be implemented in MPI and OpenMP. The video also 
gives suggestions on how to measure, plot and analyse your performance results:

https://web.microsoftstream.com/video/39738d62-57ad-4669-8d97-5de387b81471

## Structure of the report

### Section 1: Introduction (4 points)

This should give a short summary of the task to implement and parallelise, describe the software and hardware 
environments it is performed in, the parallel technologies used, and the learning objective of this coursework.

### Section 2: Sequential Performance Measurements (4 points) 

Run the sequential version of the programs and analyse the performance, for an extra mark using a profiling tool such 
as those mentioned above. Discuss the sequential performance of, and possible improvements to, these programs. Of 
interest are in particular code on the critical path (hotspots) in the program and good cache usage. max 1 A4 page
### Section 3: Comparative Parallel Performance Measurements.
 
You should measure and record the following results in numbered sections of your report. The measurements are based on 
these inputs:
- DS1: calculating the sum of totients between 1 and 15000. • DS2: calculating the sum of totients between 1 and 30000. • DS3: calculating the sum of totients between 1 and 100000.
For each of these inputs, measure:
- SEQ: the sequential runtime on one of the AMD nodes on the cluster.
- MPI<n>: the runtime of the MPI implementation using <n> MPI processes, where n varies
between 1, 2, 4, 8, ..., 256 running on 4 nodes of the cluster.
- OpenMP: the runtime of the OpenMP implementation one 1-64 cores on an AMD node on the
cluster.

Runtime measurements should be repeated 3 times each.

#### Section 3a: Runtime Table (6 points)
Present your measurements in a table containing the median of the three runtimes as well as difference between the mean and the extreme values. Use a suitable unit to ensure readability.
#### Section 3b: Runtime Graphs (2 points)
Present your runtimes in three graphs, one for each problem size. The x-axis should be the parallel degree (MPI processes for MPI, or threads for OpenMP), the y-axis runtime.
#### Section 3c: Speedups (3 points)
Plot graphs for MPI and OpenMP, showing speedup graphs corresponding to the runtime results
for DS1, DS2 and DS3. Include the idea speedups as a line as well. Also show a table with the sequential performance and the best parallel runtimes of OpenMP and MPI.
#### Section 3d: Efficiency (4 points)
Plot the corresponding efficiency graphs. Analyse the efficiency performance of OpenMP and MPI,
speculate on the reasons for the efficiency performance, and discuss for which speedup graphs an efficiency graph is a sensible addition.
#### Section 3e: Hardware Utilisation (2 points)
Figure out how many operations on long values are being performed for the three different inputs. Then compute the number of operations per second that you achieved in your implementations for the different inputs and for different number of threads (OpenMP) and proceses (MPI). Plot these findings as graphs and explain how you obtained the number of operations.
#### Section 3f: Discussion (5 points)
A discussion of the comparative performance of scalability, efficiciency and speedups for both par- allel implementations. Try to identify a suitable platform-independent measure of performance and derive those figures from your experiments. Discuss the impact of the shared-memory and distributed-memory models of OpenMP and MPI respectively, and how these models might explain your results. Also discuss how Amdahl’s law impacts parallel performance of the Totient Range algorithm. max 1 A4 page
### Section 4: Programming Model Comparison (4 points)

An evaluation of the parallel programming models, specifically for implementing the totient application. You should 
indicate any challenges you encountered in constructing and parallelising your programs and discuss situations/
algorithms where each technology may usefully be applied.

### 5. (20 points) Appendix A and B

For each parallel implementation, the appendix should include a GitLab URL for your parallel Totient programs. 
Each implementation should clearly labelled with the single author’s name in the report and in the GitLab source code 
as a comment. Include a paragraph in the appendix, and possibly diagram(s), identifying the parallel paradigm used, 
and performance tuning approaches used.

> 4 additional marks are available for thoughtful sequential and parallel performance tuning throughout the report.
>
> 4 additional marks are available if you can reflect on how to use algorithmic knowledge of the Σni=1Φ(n) computation, with the goal of creating parallel tasks of approximately equivalent compu- tation size. Hint: try runBenchmark() in TotientRange.c and design a partitioning and agglomeration strategy to shorten runtimes further.

The total coursework mark (bonus points are included in your total mark) is calculated as follows:
Question: 1 2 3 4 5 6 7 Total Points: 4 4 22 4 20 0 0 54 BonusPoints: 0 0 0 0 0 4 4 8

## Notes
- Complete the C with MPI and OpenMP Lab exercises before starting the coursework.
- Check these slides for practical tips on performance measurements.
- Check the FAQ for more info on C+MPI etc usage and cluster configuration.
- Graphs and tables must have appropriate captions, and the axes must have appropriate labels.
- The Robotarium cluster uses a batch-job system to give you exclusive access to the cluster when you
  need it for measurements. Follow this link to familiarise yourself with the batch-job system.
