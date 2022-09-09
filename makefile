python = python
PYTHON = $(python)$(py)

oshrun ?= oshrun mpiexec mpirun prun
OSHRUN := $(firstword \
          $(foreach cmd, $(oshrun), \
          $(if $(shell command -v $(cmd) 2>/dev/null), $(cmd))))

.PHONY: build
build:
	$(PYTHON) setup.py $(opt) build build_ext --inplace $(opt)

.PHONY: test
test:
	$(PYTHON) -m unittest discover -s test $(opt)

.PHONY: test-%
test-%:
	$(OSHRUN) -n $* $(PYTHON) -m unittest discover -s test $(opt)

.PHONY: lint
lint:
	-pycodestyle src/shmem4py
	-flake8 src/shmem4py
	-pylint shmem4py

.PHONY: cover cover-html
cover:
	$(PYTHON) -m coverage erase
	$(PYTHON) -m coverage run -m shmem4py > /dev/null
	$(PYTHON) -m coverage run -m unittest discover -s test
	$(PYTHON) -m coverage combine
	$(PYTHON) -m coverage report
cover-html: cover
	$(PYTHON) -m coverage html

.PHONY: clean
clean:
	-$(RM) -r build src/shmem4py/*.so src/shmem4py.egg-info
	-$(RM) -r */__pycache__ */*/__pycache__
	-$(RM) -r .coverage* htmlcov/
	-$(RM) -r .mypy_cache

.PHONY: develop develop-uninstall
develop:
	$(PYTHON) setup.py develop --prefix='' --user $(opt)
develop-uninstall:
	$(PYTHON) setup.py develop --prefix='' --user --uninstall $(opt)

.PHONY: install uninstall
install:
	$(PYTHON) setup.py $(opt) install --prefix='' --user $(opt)
uninstall:
	-$(RM) -r $(shell $(PYTHON) -m site --user-site)/shmem4py
	-$(RM) -r $(shell $(PYTHON) -m site --user-site)/shmem4py-*-py*.egg-info
