#===========================================
# Makefile for Task-1
# Author: Endadul Hoque <enhoque@syr.edu>
#===========================================

.PHONY: clean run

TASK = 1
PROG = sol$(TASK)exe
SRC = solution-$(TASK).c
THINGS_TO_REMOVE = sample-input temp1/ temp2/ $(PROG) logs/
DATA = sample.tar
SAMPLE = test1.ex
LOGFILE = logs/out.log

#====================================
SHELL := /bin/bash
V = 0

ifeq ($(V), 1)
  Q =
  FD =
else
  Q = @
  #FD = > /dev/null
endif
#====================================

# All targets
#==================================#

all: build prep

build: $(PROG) 

$(PROG): $(SRC)
	$(Q)echo "Compiling ..." $(FD)
	$(Q)gcc -Werror -Wall -o $@ $<

prep: $(DATA)
	$(Q)echo "Unpacking input files ..." $(FD)
	$(Q)tar xf $(DATA)

run: $(PROG)
	$(Q)echo "Running program ..." $(FD)
	$(Q)./$(PROG) ./sample-input

test: clean build prep run
	$(Q)echo "Testing outcome ..." $(FD)
	$(Q)mkdir -p logs/ && rm -f $(LOGFILE)
	$(Q)find temp1/ -type f | LC_ALL=en_US.UTF-8 sort  > $(LOGFILE) && \
		find temp2/ -type f | LC_ALL=en_US.UTF-8 sort >> $(LOGFILE) && \
		diff -NuZ $(LOGFILE) $(SAMPLE) && echo "Test Result: [Passed]" || echo "Test Result: [Failed]"

clean:
	$(Q)echo "Cleaning up ..." $(FD)
	$(Q)rm -rf $(THINGS_TO_REMOVE)


