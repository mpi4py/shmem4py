# -*- mode: makefile-gmake -*-

PYTHON = python$(py)
SHMEMRUN = shmemrun
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
