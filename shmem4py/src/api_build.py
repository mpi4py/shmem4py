import os
import cffi

srcdir = os.path.abspath(os.path.dirname(__file__))
with open(os.path.join(srcdir, "generate.py")) as h:
    exec(h.read())


def api_build(
    module="api",
    shmem_h="shmem.h",
    shmem_ctx_t='...*',
    shmem_team_t='...*',
):
    ffi = cffi.FFI()
    with open(os.path.join(srcdir, "libshmem.h")) as h:
        code = h.read()
        code = code.replace(f'<shmem_ctx_t>', shmem_ctx_t)
        code = code.replace(f'<shmem_team_t>', shmem_team_t)
        ffi.cdef(code)
    for code in generate():
        ffi.cdef(code)
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

    ffi.set_source(
        f"shmem4py.{module}", source,
        include_dirs=[srcdir],
        extra_compile_args=["-forward-unknown-to-host-compiler","-x c++"],
        extra_link_args=["-L/home/rogowsm/opt/nvshmem/lib","-lnvshmem","-lcuda"],
    )

    return ffi


def ffibuilder():
    return api_build(shmem_h="nvshmem.h",shmem_team_t="int")


if __name__ == '__main__':
    from fficompiler import fficompiler
    cc = fficompiler.search('nvcc')
    ld = fficompiler.search('nvcc')
    with fficompiler(cc, ld):
        ffibuilder().compile()
