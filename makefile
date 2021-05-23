python = python
PYTHON = $(python)$(py)

.PHONY: build
build:
	$(PYTHON) setup.py build build_ext --inplace

.PHONY: test
test:
	$(PYTHON) -m unittest discover -s test/

SHMEMRUN = shmemrun
.PHONY: test-%
test-%:
	$(SHMEMRUN) -n $* $(PYTHON) -m unittest discover -s test/

.PHONY: lint
lint:
	-pycodestyle shmem4py
	-pylint shmem4py

.PHONY: cover
cover:
	$(PYTHON) -m coverage erase
	$(PYTHON) -m coverage run -m shmem4py > /dev/null
	$(PYTHON) -m coverage run -m unittest discover -s test/
	$(PYTHON) -m coverage combine
	$(PYTHON) -m coverage report
	$(PYTHON) -m coverage html

.PHONY: clean
clean:
	-$(RM) -r build shmem4py/*.so shmem4py.egg-info
	-$(RM) -r */__pycache__ */*/__pycache__
	-$(RM) -r .coverage* htmlcov/
	-find . -name '*.py[co]' -exec $(RM) {} ';'


.PHONY: install uninstall
install:
	$(PYTHON) setup.py install --prefix='' --user $(INSTALLOPT)
uninstall:
	-$(RM) -r $(shell $(PYTHON) -m site --user-site)/shmem4py
	-$(RM) -r $(shell $(PYTHON) -m site --user-site)/shmem4py-*-py*.egg-info
