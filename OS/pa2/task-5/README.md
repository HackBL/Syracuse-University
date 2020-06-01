# README

Clean command: 

    $ make clean

Build command: 

    $ make

Generate input file:

    $ ./generate -s 0 -n 100 -o test.in

Run command:

    $ ./fastsort test.in test-sorted.out


## How to test your program?

You are provided with a sample input and the corresponding expected
output. To simply test your program, use 

    $ make test

If it prints `passed`, then your program passes the given test case.


## How to view binary files?
Use dump.c to view binary files: 

    $ gcc -Wall -Werror -o dump dump.c
    $ ./dump  <binary-record-file-to-view>

Or use `xxd`, `hexdump` or `bless` program to view your binary file.

