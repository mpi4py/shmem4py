# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#

import os
import sys
import typing
import datetime
sys.path.insert(0, os.path.abspath('.'))
_today = datetime.datetime.now()


# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

package = 'shmem4py'

def pkg_version():
    import re
    here = os.path.dirname(__file__)
    pardir = [os.path.pardir]
    topdir = os.path.join(here, *pardir)
    srcdir = os.path.join(topdir, 'src')
    with open(os.path.join(srcdir, package, '__init__.py')) as f:
        m = re.search(r"__version__\s*=\s*'(.*)'", f.read())
        return m.groups()[0]


project = 'shmem4py'
author = 'Lisandro Dalcin'
copyright = f'{_today.year}, {author}'

# The full version, including alpha/beta/rc tags
release = pkg_version()
version = release.rsplit('.', 1)[0]


# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

needs_sphinx = '5.1.0'

extensions = [
    'sphinx.ext.coverage',
    'sphinx.ext.autodoc',
    'sphinx.ext.autosummary',
    'sphinx.ext.intersphinx',
    'sphinx.ext.napoleon',
    #'enum_tools.autoenum',
]

# templates_path = ['_templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

default_role = 'any'

nitpicky = True
nitpick_ignore = [
    ('py:class', r'shmem4py.shmem.T'),
]
nitpick_ignore_regex = [
]

autodoc_preserve_defaults = True
autodoc_typehints = 'description'
autodoc_typehints_format = 'short'
autodoc_type_aliases = {}
autodoc_mock_imports = []

intersphinx_mapping = {
    'python': ('https://docs.python.org/3/', None),
    'numpy': ('https://numpy.org/doc/stable/', None),
    'cffi': ('https://cffi.readthedocs.io/en/stable', None),
}

napoleon_preprocess_types = True

_numpy_types = [
    'DTypeLike',
    'ArrayLike',
]

_shmem_types = [
    'Number',
    'SigAddr',
    'CtxHandle',
    'TeamHandle',
    'LockHandle',
]

autodoc_type_aliases.update({
    typename: f'~numpy.typing.{typename}'
    for typename in _numpy_types
})

try:
    import sphinx_rtd_theme
    if 'sphinx_rtd_theme' not in extensions:
        extensions.append('sphinx_rtd_theme')
except ImportError:
    sphinx_rtd_theme = None


def _patch_domain_python():
    from sphinx.domains.python import PythonDomain
    PythonDomain.object_types['data'].roles += ('class',)


def _patch_numpy_typing():
    import numpy.typing
    from types import new_class
    from typing import Generic, TypeVar
    NDArray = new_class('NDArray', (Generic[TypeVar('T')],))
    NDArray.__module__ = numpy.typing.__name__
    numpy.typing.NDArray = NDArray


def _patch_cffi_typing():
    from types import new_class
    CData = new_class('CData')
    CData.__module__ = 'ffi'
    CData.__qualname__ = 'CData'
    from shmem4py import shmem
    for attr in _shmem_types:
        data = getattr(shmem, attr)
        if isinstance(data, typing.NewType):
            if data.__supertype__ == shmem.ffi.CData:
                data.__supertype__ = CData


def _setup_autodoc(app):
    from sphinx.ext import autodoc
    from sphinx.ext import autosummary
    from sphinx.util import inspect
    from sphinx.util import typing
    from sphinx.locale import _

    #

    def stringify_annotation(annotation, mode='fully-qualified-except-typing'):
        qualname = getattr(annotation, '__qualname__', '')
        module = getattr(annotation, '__module__', '')
        args = getattr(annotation, '__args__', None)
        if module == 'builtins' and qualname and args is not None:
            args = ', '.join(stringify_annotation(a, mode) for a in args)
            return f'{qualname}[{args}]'
        return stringify_annotation_orig(annotation, mode)

    try:
        stringify_annotation_orig = typing.stringify_annotation
        inspect.stringify_annotation = stringify_annotation
        typing.stringify_annotation = stringify_annotation
        autodoc.stringify_annotation = stringify_annotation
        autodoc.typehints.stringify_annotation = stringify_annotation
    except AttributeError:
        stringify_annotation_orig = typing.stringify
        inspect.stringify_annotation = stringify_annotation
        typing.stringify = stringify_annotation
        autodoc.stringify_typehint = stringify_annotation


def setup(app):
    _patch_domain_python()
    _setup_autodoc(app)

    _patch_numpy_typing()
    import numpy.typing
    typing.TYPE_CHECKING = True
    import shmem4py.shmem
    typing.TYPE_CHECKING = False
    _patch_cffi_typing()


# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = (
    'sphinx_rtd_theme' if 'sphinx_rtd_theme' in extensions else 'default'
)
# html_static_path = ['_static']


# -- Options for manual page output ---------------------------------------

# (source start file, name, description, authors, manual section).
man_pages = [
    ('index', package, project, [author], 3)
]
