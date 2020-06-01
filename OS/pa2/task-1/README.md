# README

Build command: `$ make`  
After building the program, it also unpacks the sample inputs.

Run command: `$ ./sol1exe sample-input`

Clean command: `$ make clean`

## How to test your program?

First, build and run your program with the provided `sample-input`
(extracted from `sample.tar`). Read the input file and check if your
program executed the commands as expected by observing the contents of
`temp1/` an `temp2/` directories.

Alternatively, you can simply use 

    $ make test

If your solution passes the test case, it should finally `Test Result:
[Passed]`. Otherwise, it prints the difference between the outcome of
your solution and the expected result.
