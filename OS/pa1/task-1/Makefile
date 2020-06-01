#====================================
# DO NOT EDIT/REMOVE THIS FILE
# Unless you know what you are doing
#====================================

SOL = solution-1.sh
THINGS_TO_REMOVE = Assignment-1 logs
SAMPLE = test1.ex

#====================================
SHELL := /bin/bash
V = 0

ifeq ($(V), 1)
  Q =
  FD = 
else
  Q = @
  FD = > /dev/null
endif
#====================================

all: 
	@echo "Does nothing! Need a target for make command"

.PHONY: clean post exec

clean:
	$(Q)echo "Cleaning up ..." $(FD)
	$(Q)rm -rf $(THINGS_TO_REMOVE)

exec:
	$(Q)echo "Executing ..." $(FD)
	$(Q)bash $(SOL)


NUMBERS := $(shell seq 1 10)
post:
	$(Q)$(foreach var,$(NUMBERS),find . -type f -name "response*$(var).sh";)


test: $(SAMPLE) clean exec
	$(Q)mkdir -p logs && rm -f logs/out.log
	$(Q)$(foreach var,$(NUMBERS),find . -type f -name "response*$(var).sh" >> logs/out.log;)
	$(Q)diff -NuZ logs/out.log $(SAMPLE)  && echo "Passed"

