.PHONY: clean test

THINGS_TO_REMOVE =  pids.log infloop


test: 
ifneq (, $(wildcard ./pids.log))
	@ps --no-headers -p $(shell cat pids.log) && echo "Some infloop are alive" || echo "No infloop is alive"

else
	@echo "Oops: You might have forgotten to run 'spawner.sh' first"
endif

clean:
	@rm -rf $(THINGS_TO_REMOVE)
