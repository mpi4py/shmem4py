python = python
PYTHON = $(python)$(py)

oshrun ?= oshrun mpiexec mpirun prun
OSHRUN := $(firstword \
          $(foreach cmd, $(oshrun), \
          $(if $(shell command -v $(cmd) 2>/dev/null), $(cmd))))

npes = 1
testfile = $(wildcard *.py)
testlist = $(testfile:%.py=%)
.SECONDARY:
test:   $(foreach test,$(testlist),test-$(test));
test-%: $(foreach test,$(testlist),test-$(test)-%);

define testrule
test-$1:
	$$(OSHRUN) -n $$(npes) $$(PYTHON) -u $1.py
test-$1-%: npes=$$*
test-$1-%:
	$$(OSHRUN) -n $$(npes) $$(PYTHON) -u $1.py
endef

$(foreach test,$(testlist),$(eval $(call testrule,$(test))))
