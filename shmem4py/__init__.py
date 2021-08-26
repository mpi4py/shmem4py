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
        Request for thread support (default: False).
    thread_level : {'multiple', 'serialized', 'funneled', 'single'}
        Level of thread support to request (default: 'multiple').
    finalize : None or bool
        Automatic finalization at exit (default: None).

    """

    initialize: bool = True
    threads: bool = False
    thread_level: str = 'multiple'
    finalize: 'Optional[bool]' = None

    def __init__(self, **kwargs: 'Any') -> None:
        self(**kwargs)

    def __setattr__(self, name: str, value: 'Any') -> None:
        if not hasattr(self, name):
            raise TypeError(f"object has no attribute '{name}'")
        super().__setattr__(name, value)

    def __call__(self, **kwargs: 'Any') -> None:
        for key in kwargs:
            if not hasattr(self, key):
                raise TypeError(f"unexpected argument '{key}'")
        for key, value in kwargs.items():
            setattr(self, key, value)

    def __repr__(self) -> str:
        return f'<{__name__}.rc>'


rc = Rc()
__import__('sys').modules[__name__ + '.rc'] = rc
