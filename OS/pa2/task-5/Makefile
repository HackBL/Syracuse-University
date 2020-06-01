#===========================================
# Makefile for Task-5
# Author: Endadul Hoque <enhoque@syr.edu>
#===========================================
.PHONY: clean

TASK = 5
PROG = fastsort
SRC = solution-$(TASK).c
IN = test.in
OUT = test-sorted.out
EX = sample-sorted.ex
GEN = generate
DUMP = dump
THINGS_TO_REMOVE = *.log *.out $(PROG) $(GEN) $(DUMP) $(IN) $(IN).txt $(OUT) $(OUT).txt

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

all: build util

build: $(PROG) 

util: $(GEN) $(DUMP)

$(PROG): $(SRC)
	@printf "%b" "Compiling ... $(COM_COLOR) [$<] -> $@\t\t$(NO_COLOR)"
	@gcc -Werror -Wall -o $@ $< && \
	  echo $(OK_STRING) || echo $(FAILED_STRING)


$(IN): $(GEN)
	@printf "%b" "Generating input ... $(COM_COLOR) $@ $(NO_COLOR)\t\t\t\t"
	@./$(GEN) -s 0 -n 10 -o $@ && \
	  echo $(OK_STRING) || echo $(FAILED_STRING)
	@chmod -x $(IN)

$(OUT): $(IN) $(PROG)
	@printf "%b" "Sorting ... output file: $(COM_COLOR) $@ $(NO_COLOR)\t\t"
	@./$(PROG) $(IN) $(OUT) && \
	  echo $(OK_STRING) || echo $(FAILED_STRING)
	@chmod -x $(OUT)



test: clean build util $(PROG)  $(IN) $(OUT) $(EX)
	@./$(DUMP) $(IN) > $(IN).txt 2>&1 && \
	printf "Test (input: $(IN).txt, expected: $(EX)):\t" && \
	./$(DUMP) $(OUT) > $(OUT).txt 2>&1 && \
	diff -NuZ $(OUT).txt $(EX) && \
	  echo $(PASSED_STRING) || echo $(FAILED_STRING)

clean:
	@printf "Cleaning ... $(COM_COLOR)rm -rf $(THINGS_TO_REMOVE)\t\t$(NO_COLOR)"
	@rm -rf $(THINGS_TO_REMOVE) && \
	  echo $(OK_STRING) || echo $(FAILED_STRING)

$(DUMP): $(DUMP).c
	@printf "%b" "Compiling ... $(COM_COLOR) [$(DUMP).c] -> $(DUMP)\t\t\t\t$(NO_COLOR)"
	@gcc -Wall -Werror -o $(DUMP) $(DUMP).c && \
	  echo $(OK_STRING) || echo $(FAILED_STRING)

$(GEN): $(GEN).c
	@printf "%b" "Compiling ... $(COM_COLOR) [$(GEN).c] -> $(GEN)\t\t\t$(NO_COLOR)"
	@gcc -Wall -Werror -o $(GEN) $(GEN).c && \
	  echo $(OK_STRING) || echo $(FAILED_STRING)

			

