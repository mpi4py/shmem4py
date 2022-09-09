# Author:  Lisandro Dalcin
# Contact: dalcinl@gmail.com
"""Print shmem4py version."""
from __future__ import annotations as _annotations


def main() -> None:
    """Entry-point for ``python -m shmem4py ...``."""
    # pylint: disable=import-outside-toplevel
    package = __spec__.parent  # type: ignore[name-defined]
    from . import __version__
    print(f"{package} {__version__}")


if __name__ == '__main__':
    main()
