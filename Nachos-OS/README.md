# Nachos Operating System
## Introduction 
* It's mainly to understand how System Calls & Virutal Memory System work on Nachos
* The project should be compiled well on Unix/Linux (lcs-vc-cis468.syr.edu)
* To understand how Kernal Mode & User Mode execute on Nachos

## Features
* System Calls Handlers: Read, Write, Fork, Exec, Halt, Add, Exit
* Multiprogramming enables to execute concurrently, e.g. `./nachos -x ../test/prog1 -x ../test/prog2 -x ../test/prog3`
* Allow time slice quantum (**-Q**) for **Round-Robin scheduling** on current program e.g. `./nachos -x ../test/prog1 -Q 100`
* Implement **SwapSpace** for reserve/allocate a dedicated space (aka backing store) on the disk
* Implement **Page Fault Handler** and **LRU** page replacement algorithm for Physical Memory
* The Nachos allows to run multiple programs and user programs that require larger memory

