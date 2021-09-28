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
    ffi.cdef("""
    typedef struct { long double real, imag; } complexg;
    """)
    ffi.cdef("""
    int shmem_py_alltoalls(
    shmem_team_t team,
    void *dest, const void *source,
    ptrdiff_t dst, ptrdiff_t sst,
    size_t size, size_t eltsize);
    """)
    ffi.cdef("""
    void *shmem_py_malloc(size_t size);
    void *shmem_py_malloc_clear(size_t size);
    void *shmem_py_malloc_align(size_t align, size_t size);
    void *shmem_py_malloc_hints(size_t size, long hints);
    void  shmem_py_free(void *ptr);
    """)
    ffi.cdef("""
    extern int _shmem_error;
    const  int _shmem_finalized;
    const  int _shmem_initialized;
    extern int _shmem_atexit_finalize;
    """)
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
