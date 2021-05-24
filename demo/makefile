# -*- mode: makefile-gmake -*-

python = python
PYTHON = $(python)$(py)

shmemrun ?= shmemrun oshrun mpiexec mpirun
SHMEMRUN := $(firstword \
            $(foreach cmd, $(shmemrun), \
            $(if $(shell command -v $(cmd) 2>/dev/null), $(cmd))))
n = 1

testfile = $(wildcard *.py)
testname = $(testfile:%.py=%)
define testrule
test: test-$1
test-$1:
	$$(SHMEMRUN) -n $$(n) $$(PYTHON) -u $1.py
.PHONY: test test-$1
endef

$(foreach name, $(testname), \
  $(eval $(call testrule,$(name))))
