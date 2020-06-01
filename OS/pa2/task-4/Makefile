#===========================================
# Makefile for Task-4
# Author: Endadul Hoque <enhoque@syr.edu>
#===========================================
.PHONY: clean

TASK = 4
PROG = sol$(TASK)exe
SRC = solution-$(TASK).c
THINGS_TO_REMOVE = *.log *.out $(PROG)
IN = sample.in
EX = sample.ex
OUT = test.out

#=========================
# For colorful output
#=========================
ERROR_COLOR 	:= \033[0;31m
WARN_COLOR 	:= \033[0;33m
OK_COLOR	:= \033[0;32m
COM_COLOR	:= \033[0;34m
NO_COLOR	:= \033[0m


OK_STRING 	:= "$(OK_COLOR)[OK]$(NO_COLOR)"
PASSED_STRING 	:= "$(OK_COLOR)[PASSED]$(NO_COLOR)"
ERROR_STRING	:= "$(ERROR_COLOR)[ERRORS]$(NO_COLOR)"
FAILED_STRING	:= "$(ERROR_COLOR)[FAILED]$(NO_COLOR)"
WARN_STRING	:= "$(WARN_COLOR)[WARNINGS]$(NO_COLOR)"

#==================================#

all: build 

build: $(PROG) 


$(PROG): $(SRC)
	@printf "%b" "Building ... $(COM_COLOR)gcc -Wall -o $@ $<\t\t$(NO_COLOR)"
	@gcc -Werror -Wall -o $@ $< && \
	  echo $(OK_STRING) || echo $(FAILED_STRING)

test: clean build $(PROG) $(IN) $(EX)
	@printf "Running ... $(COM_COLOR)./$(PROG) < $(IN) > $(OUT) 2>&1\t$(NO_COLOR)"
	@stdbuf -i0 -o0 ./$(PROG) < $(IN) > $(OUT) 2>&1 && \
	  echo $(OK_STRING) || echo $(FAILED_STRING) 
	@printf "Test (input: $(IN), expected: $(EX)):\t\t" 
	@diff -NuZ $(OUT) $(EX) && \
	  echo $(PASSED_STRING) || echo $(FAILED_STRING)

clean:
	@printf "Cleaning ... $(COM_COLOR)rm -rf $(THINGS_TO_REMOVE)\t\t\t$(NO_COLOR)"
	@rm -rf $(THINGS_TO_REMOVE) && \
	  echo $(OK_STRING) || echo $(FAILED_STRING)

#$(PROG): $(SRC)
#	@printf "%b" "Building ... $<: $(COM_COLOR)"
#	@gcc -Wall -o $@ $< 
#	@RESULT=$$? ; \
#	echo "$(NO_COLOR)" ; \
#	if [ $$RESULT -ne 0 ]; then \
#		echo $(FAILED_STRING); \
#	else	\
#	  	echo $(OK_STRING); \
#	fi
#


