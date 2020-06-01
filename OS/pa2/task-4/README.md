# README

Build command: 

    $ make

Run command (as an interactive program):

    $ ./sol4exe

OR using bash I/O redirection

    $ ./sol4exe < sample.in > test.out 2>&1 

Clean command: 

    $ make clean


## How to test your program?

You are provided with a sample input and the corresponding expected
output. To simply test your program, use 

    $ make test

If it prints `passed`, then your program passes the given test case.
