# README (For Tinyshell)

Clean command: 

    $ make clean

Build command: 

    $ make

Build command for printing debug messages (inside `tinyshell.c`):

    $ make debug


Run command (for **interactive** use):

    $ ./tshell

Run command (with stdin or input redirection):

    $ stdbuf -i0 -o0 ./tshell < input_file

  The prefix "stdbuf -i0 -o0" ensures that your program is executed
  as if it were running interactively.

Run command (with stdin, stdout, and stderr redirection):

    $ stdbuf -i0 -o0 ./tshell < input_file > log_file 2>&1

  The prefix "stdbuf -i0 -o0" ensures that your program is executed
  as if it were running interactively.




## How to test your program?

It is **recommended** that you manually test your shell program 
for each feature separately and incrementally before trying out
the test cases provided in this package.


You are provided with three sample inputs (`test-*.in`) 
and the corresponding expected outputs (`test-*.ex`).

(a) For simple test, use

    $ make test-simple

(b) For testing for errors, use

    $ make test-error

(c) For testing output redirection, use

    $ make test-io

  This `test-io.in` test case additionally creates two log files
  (`out-1.log` and `out-2.log`). The expected output (`test-io.ex`) 
  combines the content from all three files (`test-io.out`, 
  `out-1.log`, `out-2.log`) to be generated when you run this test.




**For testing all** the above test cases using one command

    $ make test-all


If it prints `passed` (each test), then your program passes the given test case.



## Troubleshooting if a test case failed

If your solution fails to pass any test case, the best way to
troubleshoot is to follow these steps:

  - Compile your program manually
  - Manually (not using `make`) run your shell program 
    and provide the test input (as shown when you use
    make to test your shell)

      E.g., 
          
        $ stdbuf -i0 -o0 ./tshell < test-simple.in > test-simple.out 2>&1

  - Manually check and debug the outcome to identify the bug/issue in
    your program




## Only for Advanced User (OPTIONAL)

**DO IT AT YOUR OWN RISK. NO ASSISTANCE WILL BE PROVIDED 
IF YOUR STUCK WITH THIS ADVANCED FEATURE.**

If you are concern about any memory leak in your program 
or looking forward to learn something new technology 
or willing to take additional challenges, you may check your
program for memory leak. For that you have to compile your program 
using different options to `gcc`. 

Build command for debugging memory corruptions in `tinyshell.c`:

    $ make asan

Note that any `make test-*` will clean and re-build your program with 
default build command. So you have to change the Makefile or run your 
program manually.
