#!/usr/bin/env python
# Author:  Lisandro Dalcin
# Contact: dalcinl@gmail.com

"""
Python bindings for OpenSHMEM
"""

import os
import sys
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext as cmd_build_ext
from setuptools.command.install   import install   as cmd_install

topdir = os.path.abspath(os.path.dirname(__file__))
sys.path.insert(0, os.path.join(topdir, 'src'))

class build_ext(cmd_build_ext, object):
    def build_extensions(self):
        dwb = sys.dont_write_bytecode
        sys.dont_write_bytecode = True
        from fficompiler import fficompiler
        sys.dont_write_bytecode = dwb
        cc = fficompiler.search('OSHCC', 'oshcc')
        ld = fficompiler.search('OSHLD')
        fficompiler(cc, ld).configure(self.compiler)
        super(build_ext, self).build_extensions()

class install(cmd_install, object):
    def run(self):
        super(install, self).run()

setup(
    cffi_modules = [
        'src/ffibuilder.py:ffibuilder',
    ],
    cmdclass = {
        'build_ext': build_ext,
        'install': install,
    },
)
