# Author:  Lisandro Dalcin
# Contact: dalcinl@gmail.com
"""OpenSHMEM for Python."""

__version__ = '0.1.0'
__author__ = 'Lisandro Dalcin'
__credits__ = 'OpenSHMEM Team'


class Rc:
    """Runtime configuration options.

    Attributes
    ----------
    initialize : bool
        Automatic initialization at import (default: True).
    threads : bool
        Request for thread support (default: True).
    thread_level : {'multiple', 'serialized', 'funneled', 'single'}
        Level of thread support to request (default: 'multiple').
    finalize : None or bool
        Automatic finalization at exit (default: None).

    """

    initialize = True
    threads = True
    thread_level = 'multiple'
    finalize = None

    def __init__(self, **kwargs):
        self(**kwargs)

    def __call__(self, **kwargs):
        for key in kwargs:
            if not hasattr(self, key):
                raise TypeError("unexpected argument '{0}'".format(key))
        for key, value in kwargs.items():
            setattr(self, key, value)

    def __repr__(self):
        return '<{0}.rc>'.format(__name__)


rc = Rc()
__import__('sys').modules[__name__ + '.rc'] = rc
