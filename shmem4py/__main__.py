# Author:  Lisandro Dalcin
# Contact: dalcinl@gmail.com
"""Print shmem4py version."""


def main():
    """Entry-point for ``python -m shmem4py ...``."""
    # pylint: disable=import-outside-toplevel
    package = __spec__.parent
    from . import __version__
    print(f"{package} {__version__}")


if __name__ == '__main__':
    main()
