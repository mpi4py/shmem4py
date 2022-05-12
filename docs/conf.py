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
autodoc_type_aliases = {}
autodoc_mock_imports = []

intersphinx_mapping = {
    'python': ('https://docs.python.org/3/', None),
    'numpy': ('https://numpy.org/doc/stable/', None),
    'cffi': ('https://cffi.readthedocs.io/en/stable', None),
}

napoleon_preprocess_types = True

_numpy_types = [
    'NDArray',
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
    typename: f'numpy.typing.{typename}'
    for typename in _numpy_types
})

autodoc_type_aliases.update({
    typename: f'{typename}'
    for typename in _shmem_types
})

try:
    import sphinx_rtd_theme
    if 'sphinx_rtd_theme' not in extensions:
        extensions.append('sphinx_rtd_theme')
except ImportError:
    sphinx_rtd_theme = None


def _patch_util_inspect():
    from sphinx.util.inspect import TypeAliasForwardRef
    TypeAliasForwardRef.__getitem__ = lambda self, item: item


def _patch_domain_python():
    from sphinx.domains import python

    xref_info = {}
    for typename in _numpy_types:
        xref_info[f'numpy.typing.{typename}'] = {'reftype': 'data'}
    for typename in _shmem_types:
        xref_info[f'{typename}'] = {'reftype': 'data'}

    def make_xref(self, rolename, domain, target, *args, **kwargs):
        if target in ('None', 'True', 'False'):
            rolename = 'obj'
        pymodule = None
        reftype = None
        if target in xref_info:
            reftype = xref_info[target].get('reftype')
            pymodule, _, target  = target.rpartition('.')
        xref = make_xref_orig(self, rolename, domain, target, *args, *kwargs)
        if pymodule:
            xref.attributes['py:module'] = pymodule
        if reftype:
            xref.attributes['reftype'] = reftype
        return xref

    make_xref_orig = python.PyXrefMixin.make_xref
    python.PyXrefMixin.make_xref = make_xref


def setup(app):
    _patch_util_inspect()
    _patch_domain_python()

    import numpy.typing
    typing.TYPE_CHECKING = True
    import shmem4py.shmem
    typing.TYPE_CHECKING = False

    class CData: pass
    CData.__module__ = 'ffi'
    CData.__qualname__ = 'CData'
    for attr in _shmem_types:
        data = getattr(shmem4py.shmem, attr)
        if isinstance(data, typing.NewType):
            if data.__supertype__ == shmem4py.shmem.ffi.CData:
                data.__supertype__ = CData


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
