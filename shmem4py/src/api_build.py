import os
import cffi

ffibuilder = ffi = cffi.FFI()

srcdir = os.path.abspath(os.path.dirname(__file__))
with open(os.path.join(srcdir, "libshmem.h")) as h:
    ffi.cdef(h.read())
with open(os.path.join(srcdir, "generate.py")) as h:
    exec(h.read())
    for code in generate():
        ffi.cdef(code)
with open(os.path.join(srcdir, "libshmem.c")) as c:
    ffi.set_source(
        "shmem4py.api", c.read(),
        include_dirs=[srcdir],
    )

if __name__ == '__main__':
    from fficompiler import fficompiler
    cc = fficompiler.search('OSHCC', 'oshcc')
    ld = fficompiler.search('OSHLD')
    with fficompiler(cc, ld):
        ffibuilder.compile()
