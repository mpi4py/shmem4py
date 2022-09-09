import os
import sys
import glob
import cffi

srcdir = os.path.abspath(os.path.dirname(__file__))
if srcdir not in sys.path:
    sys.path.insert(0, srcdir)


def build_api(
    module="api",
    shmem_h="shmem.h",
    shmem_ctx_t='...*',
    shmem_team_t='...*',
):
    from apicodegen import generate
    ffi = cffi.FFI()
    with open(os.path.join(srcdir, "libshmem.h")) as h:
        code = h.read()
        code = code.replace(f'<shmem_ctx_t>', shmem_ctx_t)
        code = code.replace(f'<shmem_team_t>', shmem_team_t)
        ffi.cdef(code)
    for code in generate():
        ffi.cdef(code)
    ffi.cdef("""
    int shmem_alltoallsmem_x(
        shmem_team_t team,
        void *dest, const void *source,
        ptrdiff_t dst, ptrdiff_t sst,
        size_t size, size_t eltsize);
    """)
    ffi.cdef("""
    void *shmem_py_alloc(size_t size, size_t align, long hints, int clear);
    void  shmem_py_free(void *ptr);
    """)
    ffi.cdef("""
    extern int _shmem_error;
    """)
    ffi.cdef("""
    const  int _shmem_finalized;
    const  int _shmem_initialized;
    extern int _shmem_atexit_finalize;
    """)
    cmplxl = """
    typedef struct { long double real, imag; } complexl;
    """.strip()
    ffi.cdef(cmplxl)

    libshmem_c = "libshmem.c"
    source = f"#include <{shmem_h}>\n"
    source += f"#include <{libshmem_c}>\n"
    source += cmplxl
    depends = glob.glob(
        os.path.join(srcdir, '**', '*.[hc]'),
        recursive=True,
    )

    ffi.set_source(
        f"shmem4py.{module}", source,
        include_dirs=[srcdir],
        depends=depends,
    )

    return ffi


def ffibuilder():
    return build_api()


if __name__ == '__main__':
    from fficompiler import fficompiler
    cc = fficompiler.search('OSHCC', 'oshcc')
    ld = fficompiler.search('OSHLD')
    with fficompiler(cc, ld):
        cwd = os.getcwd()
        try:
            os.chdir(srcdir)
            ffibuilder().compile()
        finally:
            os.chdir(cwd)
