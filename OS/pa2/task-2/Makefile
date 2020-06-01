#===========================================
# Makefile for Task-2
# Author: Endadul Hoque <enhoque@syr.edu>
#===========================================

.PHONY: clean

TASK = 2
PROG = sol$(TASK)exe
SRC = solution-$(TASK).c
THINGS_TO_REMOVE = *.log *.out $(PROG)
IN = sample.in
EX = sample.ex
OUT = test.out

#==================================#

all: build 

build: $(PROG) 

$(PROG): $(SRC)
	gcc -Werror -Wall -o $@ $<

test: clean build $(PROG) $(IN) $(EX)
	./$(PROG) $(IN) $(OUT)
	@diff -NuZ $(OUT) $(EX) && \
	  echo "Test (input: $(IN), expected: $(EX)): Passed"

clean:
	rm -rf $(THINGS_TO_REMOVE)


