"""OpenSHMEM for Python."""
# pylint: disable=too-many-lines
# pylint: disable=no-else-return
# pylint: disable=empty-docstring
# pylint: disable=too-many-arguments
from __future__ import annotations as _annotations
# ---

import os as _os
import enum as _enum
import weakref as _weakref
import functools as _functools
import typing as _typing

# ---

import numpy as np
from .api import ffi, lib

# ---

if _typing.TYPE_CHECKING:  # pragma: no cover
    import sys

    from typing import (
        Any,
        Union,
        NewType,
        TypeVar,
        Optional,
        Callable,
        NoReturn,
    )
    from typing import (
        Mapping,
        Sequence,
    )
    from typing import (
        List,
        Dict,
        Tuple,
    )
    if sys.version_info >= (3, 8):
        from typing import Literal
    else:
        from typing_extensions import Literal
    from numpy.typing import (
        DTypeLike,
        NDArray,
    )

    T = TypeVar('T', bound=np.generic)
    _Heap = _weakref.WeakValueDictionary[ffi.CData, ffi.CData]

    Number = Union[int, float, complex, np.generic]
    SigAddr = NewType('SigAddr', ffi.CData)
    CtxHandle = NewType('CtxHandle', ffi.CData)
    TeamHandle = NewType('TeamHandle', ffi.CData)
    LockHandle = NewType('LockHandle', ffi.CData)

# ---


def _chkerr(ierr: int, func: str = "shmem") -> None:
    if ierr != 0:
        if ierr == -1431655766:
            raise NotImplementedError(f"{func}")
        raise RuntimeError(f"{func}: error {ierr}")


def _chkint(ival: int, func: str = "shmem") -> None:
    if ival < 0:
        _chkerr(ival, func)


# ---


MAJOR_VERSION: int = lib.SHMEM_MAJOR_VERSION
MINOR_VERSION: int = lib.SHMEM_MINOR_VERSION
VENDOR_STRING: str = ffi.string(lib.SHMEM_VENDOR_STRING).decode()


def info_get_version() -> Tuple[int, int]:
    """
    """
    major = ffi.new('int*')
    minor = ffi.new('int*')
    lib.shmem_info_get_version(major, minor)
    return (major[0], minor[0])


def info_get_name() -> str:
    """
    """
    name = ffi.new('char[]', lib.SHMEM_MAX_NAME_LEN)
    lib.shmem_info_get_name(name)
    return ffi.string(name).decode()


# ---


class THREAD(_enum.IntEnum):
    """
    """
    SINGLE:     int = lib.SHMEM_THREAD_SINGLE
    FUNNELED:   int = lib.SHMEM_THREAD_FUNNELED
    SERIALIZED: int = lib.SHMEM_THREAD_SERIALIZED
    MULTIPLE:   int = lib.SHMEM_THREAD_MULTIPLE


THREAD_SINGLE:     THREAD = THREAD.SINGLE
THREAD_FUNNELED:   THREAD = THREAD.FUNNELED
THREAD_SERIALIZED: THREAD = THREAD.SERIALIZED
THREAD_MULTIPLE:   THREAD = THREAD.MULTIPLE


def init() -> None:
    """
    """
    lib.shmem_init()


def finalize() -> None:
    """
    """
    lib.shmem_finalize()


def global_exit(status: int = 0) -> NoReturn:  # pragma: no cover
    """
    """
    lib.shmem_global_exit(status)
    raise SystemExit(status)  # unreachable


def init_thread(requested: THREAD = THREAD_MULTIPLE) -> THREAD:
    """
    """
    provided = ffi.new('int*', lib.SHMEM_THREAD_SINGLE)
    ierr = lib.shmem_init_thread(requested, provided)
    _chkerr(ierr, "shmem_init_thread")
    return THREAD(provided[0])


def query_thread() -> THREAD:
    """
    """
    provided = ffi.new('int*', lib.SHMEM_THREAD_SINGLE)
    lib.shmem_query_thread(provided)
    return THREAD(provided[0])


# ---


def _initialize() -> None:
    # pylint: disable=import-outside-toplevel
    from . import rc

    def config(rcparams, name):
        assert hasattr(rcparams, name)
        value = _os.getenv(f'SHMEM4PY_RC_{name.upper()}')
        if value:
            value = value.lower()
            if value in ('true', 'yes', 'on', 'y', '1'):
                value = True
            if value in ('false', 'no', 'off', 'n', '0'):
                value = False
            setattr(rcparams, name, value)

    config(rc, 'initialize')
    config(rc, 'threads')
    config(rc, 'thread_level')
    config(rc, 'finalize')

    if rc.initialize:
        if rc.threads:
            level = rc.thread_level.upper()
            requested = getattr(THREAD, level)
            init_thread(requested)
        else:
            init()
        if rc.finalize is None:
            rc.finalize = True
    if rc.finalize:
        # pylint: disable=protected-access
        lib._shmem_atexit_finalize = 1


_initialize()


# ---


class CTX(_enum.IntFlag):
    """
    """
    PRIVATE:    int = lib.SHMEM_CTX_PRIVATE
    SERIALIZED: int = lib.SHMEM_CTX_SERIALIZED
    NOSTORE:    int = lib.SHMEM_CTX_NOSTORE


CTX_PRIVATE:    CTX = CTX.PRIVATE
CTX_SERIALIZED: CTX = CTX.SERIALIZED
CTX_NOSTORE:    CTX = CTX.NOSTORE


class Ctx:
    """Communication context."""

    ob_ctx: CtxHandle

    def __new__(
        cls,
        ctx: Optional[Union[Ctx, CtxHandle]] = None,
    ) -> Ctx:
        if isinstance(ctx, ffi.CData):
            if ffi.typeof(ctx) is not ffi.typeof('shmem_ctx_t'):
                raise TypeError(f"unexpected ctype: {ffi.typeof(ctx)}")
            ob_ctx = ctx
        elif isinstance(ctx, Ctx):
            ob_ctx = ctx.ob_ctx
        elif ctx is None:
            ob_ctx = lib.SHMEM_CTX_INVALID
        else:
            raise TypeError(f"unexpected type: {type(ctx)}")
        ob_ctx = ffi.new('shmem_ctx_t*', ob_ctx)[0]
        self = super().__new__(cls)
        self.ob_ctx = ob_ctx
        return self

    def __eq__(self, other: Any) -> bool:
        if not isinstance(other, Ctx):
            return NotImplemented
        return self.ob_ctx == other.ob_ctx

    def __ne__(self, other: Any) -> bool:
        if not isinstance(other, Ctx):
            return NotImplemented
        return self.ob_ctx != other.ob_ctx

    def __bool__(self) -> bool:
        return self.ob_ctx != lib.SHMEM_CTX_INVALID

    def __enter__(self) -> Ctx:
        return self

    def __exit__(self, *args: Any) -> None:
        self.destroy()

    @staticmethod
    def create(
        options: int = 0,
        team: Optional[Team] = None,
    ) -> Ctx:
        """
        """
        ctx = ffi.new('shmem_ctx_t*', lib.SHMEM_CTX_INVALID)
        if team is None:
            ierr = lib.shmem_ctx_create(options, ctx)
            _chkerr(ierr, "shmem_ctx_create")
        else:
            team_ = team.ob_team
            ierr = lib.shmem_team_create_ctx(team_, options, ctx)
            _chkerr(ierr, "shmem_team_create_ctx")
        return Ctx(ctx[0])

    def destroy(self) -> None:
        """
        """
        if self is CTX_DEFAULT:
            return
        if self is CTX_INVALID:
            return
        ctx = self.ob_ctx
        self.ob_ctx = lib.SHMEM_CTX_INVALID
        if ctx == lib.SHMEM_CTX_DEFAULT:
            return
        if ctx == lib.SHMEM_CTX_INVALID:
            return
        lib.shmem_ctx_destroy(ctx)

    def get_team(self) -> Team:
        """
        """
        ctx = self.ob_ctx
        team = ffi.new('shmem_team_t*', lib.SHMEM_TEAM_INVALID)
        ierr = lib.shmem_ctx_get_team(ctx, team)
        _chkerr(ierr, "shmem_ctx_get_team")
        return Team(team[0])

    def fence(self) -> None:
        """
        """
        ctx = self.ob_ctx
        lib.shmem_ctx_fence(ctx)

    def quiet(self) -> None:
        """
        """
        ctx = self.ob_ctx
        lib.shmem_ctx_quiet(ctx)


CTX_DEFAULT: Ctx = Ctx(lib.SHMEM_CTX_DEFAULT)
CTX_INVALID: Ctx = Ctx(lib.SHMEM_CTX_INVALID)


# ---


class Team:
    """Team management."""

    ob_team: TeamHandle

    def __new__(
        cls,
        team: Optional[Union[Team, TeamHandle]] = None,
    ) -> Team:
        if isinstance(team, ffi.CData):
            if ffi.typeof(team) is not ffi.typeof('shmem_team_t'):
                raise TypeError(f"unexpected ctype: {ffi.typeof(team)}")
            ob_team = team
        elif isinstance(team, Team):
            ob_team = team.ob_team
        elif team is None:
            ob_team = lib.SHMEM_TEAM_INVALID
        else:
            raise TypeError(f"unexpected type: {type(team)}")
        ob_team = ffi.new('shmem_team_t*', ob_team)[0]
        self = super().__new__(cls)
        self.ob_team = ob_team
        return self

    def __eq__(self, other: Any) -> bool:
        if not isinstance(other, Team):
            return NotImplemented
        return self.ob_team == other.ob_team

    def __ne__(self, other: Any) -> bool:
        if not isinstance(other, Team):
            return NotImplemented
        return self.ob_team != other.ob_team

    def __bool__(self) -> bool:
        return self.ob_team != lib.SHMEM_TEAM_INVALID

    def __enter__(self) -> Team:
        return self

    def __exit__(self, *args: Any) -> None:
        self.destroy()

    def destroy(self) -> None:
        """
        """
        if self is TEAM_WORLD:
            return
        if self is TEAM_SHARED:
            return
        if self is TEAM_INVALID:
            return
        team = self.ob_team
        self.ob_team = lib.SHMEM_TEAM_INVALID
        if team == lib.SHMEM_TEAM_WORLD:
            return
        if team == lib.SHMEM_TEAM_SHARED:
            return
        if team == lib.SHMEM_TEAM_INVALID:
            return
        lib.shmem_team_destroy(team)

    def split_strided(
        self,
        start: int = 0,
        stride: int = 1,
        size: Optional[int] = None,
        config: Optional[Mapping[str, int]] = None,
        **kwargs: int,
    ) -> Team:
        """
        """
        team = self.ob_team
        if size is None:
            npes = lib.shmem_team_n_pes(team)
            size = len(range(start, npes, stride))
        if config is None:
            config = kwargs
        else:
            config = dict(config)
            config.update(kwargs)
        conf = ffi.new('shmem_team_config_t*')
        mask = 0
        for attr, value in config.items():
            setattr(conf, attr.lower(), value)
            mask |= getattr(lib, f'SHMEM_TEAM_{attr.upper()}')
        tnew = ffi.new('shmem_team_t*', lib.SHMEM_TEAM_INVALID)
        ierr = lib.shmem_team_split_strided(
            team, start, stride, size, conf, mask, tnew,
        )
        _chkerr(ierr, "shmem_team_split_strided")
        return Team(tnew[0])

    def get_config(self) -> Dict[str, int]:
        """
        """
        team = self.ob_team
        conf = ffi.new('shmem_team_config_t*')
        mask = lib.SHMEM_TEAM_NUM_CONTEXTS
        lib.shmem_team_get_config(team, mask, conf)
        return {attr: getattr(conf, attr) for attr in dir(conf)}

    def my_pe(self) -> int:
        """
        """
        team = self.ob_team
        mype = lib.shmem_team_my_pe(team)
        _chkint(mype, "shmem_team_my_pe")
        return mype

    def n_pes(self) -> int:
        """
        """
        team = self.ob_team
        npes = lib.shmem_team_n_pes(team)
        _chkint(npes, "shmem_team_n_pes")
        return npes

    def translate_pe(
        self,
        pe: Optional[int] = None,
        team: Optional[Team] = None,
    ) -> int:
        """
        """
        src_team = self.ob_team
        if pe is None:
            src_pe = lib.shmem_team_my_pe(src_team)
        else:
            src_pe = pe
        if team is None:
            dest_team = lib.SHMEM_TEAM_WORLD
        else:
            dest_team = team.ob_team
        dest_pe = lib.shmem_team_translate_pe(src_team, src_pe, dest_team)
        _chkint(dest_pe, "shmem_team_translate_pe")
        return dest_pe

    def create_ctx(
        self,
        options: int = 0,
    ) -> Ctx:
        """
        """
        team = self.ob_team
        ctx = ffi.new('shmem_ctx_t*', lib.SHMEM_CTX_INVALID)
        ierr = lib.shmem_team_create_ctx(team, options, ctx)
        _chkerr(ierr, "shmem_team_create_ctx")
        return Ctx(ctx[0])

    def sync(self) -> None:
        """
        """
        team = self.ob_team
        ierr = lib.shmem_team_sync(team)
        _chkerr(ierr, "shmem_team_sync")


TEAM_WORLD:   Team = Team(lib.SHMEM_TEAM_WORLD)
TEAM_SHARED:  Team = Team(lib.SHMEM_TEAM_SHARED)
TEAM_INVALID: Team = Team(lib.SHMEM_TEAM_INVALID)


# ---


def my_pe() -> int:
    """
    """
    return lib.shmem_my_pe()


def n_pes() -> int:
    """
    """
    return lib.shmem_n_pes()


def pe_accessible(pe: int) -> bool:
    """
    """
    return bool(lib.shmem_pe_accessible(pe))


def addr_accessible(
    addr: NDArray[Any],
    pe: int,
) -> bool:
    """
    """
    caddr = _getbuffer(addr, readonly=True)[0]
    return bool(lib.shmem_addr_accessible(caddr, pe))


def ptr(
    target: NDArray[T],
    pe: int,
) -> Optional[NDArray[T]]:
    """
    """
    caddr = _getbuffer(target, readonly=True)[0]
    cdata = lib.shmem_ptr(caddr, pe)
    if cdata == ffi.NULL:  # pragma: no branch
        return None        # pragma: no cover
    buf = ffi.buffer(cdata, target.nbytes)
    mem = memoryview(buf)  # type: ignore[arg-type]
    a = fromalloc(mem, target.size, target.dtype)
    a.shape = target.shape
    if target.ndim > 1:
        a.strides = target.strides
    a.flags.writeable = target.flags.writeable
    return a


# ---


_numpy_to_cffi = {
    'c': 'char',
    'b': 'signed char',
    'h': 'short',
    'i': 'int',
    'l': 'long',
    'q': 'long long',
    'B': 'unsigned char',
    'H': 'unsigned short',
    'I': 'unsigned int',
    'L': 'unsigned long',
    'Q': 'unsigned long long',
    'f': 'float',
    'd': 'double',
    'g': 'long double',
    'F': 'float _Complex',
    'D': 'double _Complex',
    'G': 'long double _Complex',

    'S1': 'char',
    'i1': 'int8_t',
    'i2': 'int16_t',
    'i4': 'int32_t',
    'i8': 'int64_t',
    'u1': 'uint8_t',
    'u2': 'uint16_t',
    'u4': 'uint32_t',
    'u8': 'uint64_t',

    f'f{np.dtype("f").itemsize}': 'float',
    f'f{np.dtype("d").itemsize}': 'double',
    f'f{np.dtype("g").itemsize}': 'long double',
    f'c{np.dtype("F").itemsize}': 'float _Complex',
    f'c{np.dtype("D").itemsize}': 'double _Complex',
    f'c{np.dtype("G").itemsize}': 'long double _Complex',
}

_cffi_to_numpy = {
    v: k for k, v in _numpy_to_cffi.items()
}

_numpy_to_shmem = {
    'c': 'char',
    'b': 'schar',
    'h': 'short',
    'i': 'int',
    'l': 'long',
    'q': 'longlong',
    'B': 'uchar',
    'H': 'ushort',
    'I': 'uint',
    'L': 'ulong',
    'Q': 'ulonglong',
    'f': 'float',
    'd': 'double',
    'g': 'longdouble',
    'F': 'complexf',
    'D': 'complexd',
    'G': 'complexl',

    'S1': 'char',
    'i1': 'int8',
    'i2': 'int16',
    'i4': 'int32',
    'i8': 'int64',
    'u1': 'uint8',
    'u2': 'uint16',
    'u4': 'uint32',
    'u8': 'uint64',

    f'f{np.dtype("f").itemsize}': 'float',
    f'f{np.dtype("d").itemsize}': 'double',
    f'f{np.dtype("g").itemsize}': 'longdouble',
    f'c{np.dtype("F").itemsize}': 'complexf',
    f'c{np.dtype("D").itemsize}': 'complexd',
    f'c{np.dtype("G").itemsize}': 'complexl',
}

_shmem_to_numpy = {
    v: k for k, v in _numpy_to_shmem.items()
}

_heap: _Heap = _weakref.WeakValueDictionary()


@_functools.lru_cache(maxsize=None)
def _get_allocator(
    align: Optional[int] = None,
    hints: Optional[int] = None,
    clear: bool = True,
) -> Callable[[Union[str, ffi.CType], int], ffi.CData]:
    align = align if align is not None else 0
    hints = hints if hints is not None else 0
    assert align >= 0 and hints >= 0
    return ffi.new_allocator(
        lambda size: lib.shmem_py_alloc(size, align, hints, clear),
        lib.shmem_py_free,
        should_clear_after_alloc=False,
    )


class MALLOC(_enum.IntFlag):
    """
    """
    ATOMICS_REMOTE: int = lib.SHMEM_MALLOC_ATOMICS_REMOTE
    SIGNAL_REMOTE:  int = lib.SHMEM_MALLOC_SIGNAL_REMOTE


MALLOC_ATOMICS_REMOTE: MALLOC = MALLOC.ATOMICS_REMOTE
MALLOC_SIGNAL_REMOTE:  MALLOC = MALLOC.SIGNAL_REMOTE


def alloc(
    count: int,
    size:  int = 1,
    align: Optional[int] = None,
    hints: Optional[int] = None,
    clear: bool = True,
) -> memoryview:
    """
    """
    allocator = _get_allocator(align, hints, clear)
    cdata = allocator('char[]', count*size)
    caddr = ffi.cast('uintptr_t', cdata)
    _heap[caddr] = cdata
    buf = ffi.buffer(cdata)
    mem = memoryview(buf)  # type: ignore[arg-type]
    return mem


def free(mem: Union[memoryview, NDArray[Any]]) -> None:
    """
    """
    if isinstance(mem, np.ndarray):
        mem = _typing.cast(memoryview, mem.base)
    assert isinstance(mem, memoryview), type(mem)
    assert isinstance(mem.obj, ffi.buffer), type(mem.obj)
    cdata = ffi.from_buffer(mem.obj)
    caddr = ffi.cast('uintptr_t', cdata)
    ffi.release(cdata)
    cdata = _heap.pop(caddr)
    ffi.release(cdata)


def fromalloc(
    mem: memoryview,
    shape: Optional[Union[int, Sequence[int]]] = None,
    dtype: DTypeLike = None,
    order: Literal['C', 'F'] = 'C',
) -> NDArray[Any]:
    """
    """
    assert isinstance(mem, memoryview), type(mem)
    assert isinstance(mem.obj, ffi.buffer), type(mem.obj)
    dtype = np.dtype(dtype)
    if shape is None:
        shape = mem.nbytes // dtype.itemsize
    a = np.frombuffer(mem, dtype)
    tmp = a.reshape(shape, order=order)
    a.shape = tmp.shape
    if tmp.ndim > 1:
        a.strides = tmp.strides
    return a


def new_array(
    shape: Union[int, Sequence[int]],
    dtype: DTypeLike = float,
    order: Literal['C', 'F'] = 'C',
    *,
    align: Optional[int] = None,
    hints: Optional[int] = None,
    clear: bool = True,
) -> NDArray[Any]:
    """
    """
    dtype = np.dtype(dtype)
    count = np.prod(shape, dtype='p')
    mem = alloc(count, dtype.itemsize, align, hints, clear)
    return fromalloc(mem, shape, dtype, order)


def del_array(a: NDArray[Any]) -> None:
    """
    """
    assert isinstance(a, np.ndarray), type(a)
    free(a)


def array(
    obj: Any,
    dtype: DTypeLike = None,
    *,
    order: Literal['K', 'A', 'C', 'F'] = 'K',
    align: Optional[int] = None,
    hints: Optional[int] = None,
) -> NDArray[Any]:
    """
    """
    tmp = np.array(obj, dtype, copy=False, order=order)
    a = new_array(tmp.size, tmp.dtype, align=align, hints=hints, clear=False)
    a.shape = tmp.shape
    if tmp.ndim > 1:
        a.strides = tmp.strides
    np.copyto(a, tmp, casting='no')
    lib.shmem_sync_all()
    return a


def empty(
    shape: Union[int, Sequence[int]],
    dtype: DTypeLike = float,
    order: Literal['C', 'F'] = 'C',
    *,
    align: Optional[int] = None,
    hints: Optional[int] = None,
) -> NDArray[Any]:
    """
    """
    a = new_array(shape, dtype, order, align=align, hints=hints, clear=False)
    return a


def zeros(
    shape: Union[int, Sequence[int]],
    dtype: DTypeLike = float,
    order: Literal['C', 'F'] = 'C',
    *,
    align: Optional[int] = None,
    hints: Optional[int] = None,
) -> NDArray[Any]:
    """
    """
    a = new_array(shape, dtype, order, align=align, hints=hints, clear=True)
    return a


def ones(
    shape: Union[int, Sequence[int]],
    dtype: DTypeLike = float,
    order: Literal['C', 'F'] = 'C',
    *,
    align: Optional[int] = None,
    hints: Optional[int] = None,
) -> NDArray[Any]:
    """
    """
    a = new_array(shape, dtype, order, align=align, hints=hints, clear=False)
    np.copyto(a, 1, casting='unsafe')
    lib.shmem_sync_all()
    return a


def full(
    shape: Union[int, Sequence[int]],
    fill_value: Number,
    dtype: DTypeLike = None,
    order: Literal['C', 'F'] = 'C',
    *,
    align: Optional[int] = None,
    hints: Optional[int] = None,
) -> NDArray[Any]:
    """
    """
    if dtype is None:
        dtype = np.array(fill_value).dtype
    a = new_array(shape, dtype, order, align=align, hints=hints, clear=False)
    np.copyto(a, fill_value, casting='unsafe')
    lib.shmem_sync_all()
    return a


# ---


def _shmem(ctx, ctype, name, chkerr=0):
    if ctx is None:
        if ctype is None:
            funcname = f'shmem_{name}'
        else:
            funcname = f'shmem_{ctype}_{name}'
        function = getattr(lib, funcname)
    else:
        if ctype is None:
            funcname = f'shmem_ctx_{name}'
        else:
            funcname = f'shmem_ctx_{ctype}_{name}'
        ctx_func = getattr(lib, funcname)

        def function(*args):
            return ctx_func(ctx.ob_ctx, *args)

    if not chkerr:
        return function

    def wrapper(*args):
        # pylint: disable=protected-access
        lib._shmem_error = 0
        result = function(*args)
        ierr = lib._shmem_error
        _chkerr(ierr, funcname)
        if chkerr > 1:
            _chkerr(result, funcname)
        return result

    return wrapper


def _getbuffer(
    obj: NDArray,
    readonly: bool = False,
) -> Tuple[ffi.CData, int, str]:
    if not isinstance(obj, np.ndarray):
        raise TypeError("object is not a NumPy array")
    flags = obj.flags
    if not readonly and not flags.writeable:
        raise ValueError("array object is read-only")
    if not flags.contiguous:
        if not flags.f_contiguous:
            raise ValueError("array object is not contiguous")
        obj = obj.T
    ctype = _numpy_to_shmem[obj.dtype.char]
    cdecl = ffi.getctype(ctype, '[]')
    cdata = ffi.from_buffer(cdecl, obj)
    return (cdata, obj.size, ctype)


def _ceildiv(p: int, q: int) -> int:
    return (p + q - 1) // q


# ---


def _parse_rma(target, source, size=None, tst=1, sst=1):
    tdata, tlen, ttype = _getbuffer(target, readonly=False)
    sdata, slen, stype = _getbuffer(source, readonly=True)

    assert ttype == stype
    ctype = ttype

    tsize = _ceildiv(tlen, tst)
    ssize = _ceildiv(slen, sst)
    if size is None:
        size = min(tsize, ssize)
    else:
        assert size <= tsize
        assert size <= ssize

    return (ctype, tdata, sdata, size)


def _shmem_rma(ctx, name, target, source, size, pe):
    ctype, target, source, size = _parse_rma(target, source, size)
    try:
        return _shmem(ctx, ctype, name)(target, source, size, pe)
    except AttributeError:
        size *= ffi.sizeof(ctype)
        return _shmem(ctx, None, f'{name}mem')(target, source, size, pe)


def _shmem_irma(ctx, name, target, source, tst, sst, size, pe):
    ctype, target, source, size = _parse_rma(target, source, size, tst, sst)
    return _shmem(ctx, ctype, f'i{name}')(target, source, tst, sst, size, pe)


def _shmem_rma_nbi(ctx, name, target, source, size, pe):
    ctype, target, source, size = _parse_rma(target, source, size)
    try:
        return _shmem(ctx, ctype, f'{name}_nbi')(target, source, size, pe)
    except AttributeError:
        size *= ffi.sizeof(ctype)
        return _shmem(ctx, None, f'{name}mem_nbi')(target, source, size, pe)


def put(
    target,
    source,
    pe: int,
    size: Optional[int] = None,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_rma(ctx, 'put', target, source, size, pe)


def get(
    target,
    source,
    pe: int,
    size: Optional[int] = None,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_rma(ctx, 'get', target, source, size, pe)


def iput(
    target,
    source,
    pe: int,
    tst: int = 1,
    sst: int = 1,
    size: Optional[int] = None,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_irma(ctx, 'put', target, source, tst, sst, size, pe)


def iget(
    target,
    source,
    pe: int,
    tst: int = 1,
    sst: int = 1,
    size: Optional[int] = None,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_irma(ctx, 'get', target, source, tst, sst, size, pe)


def put_nbi(
    target,
    source,
    pe: int,
    size: Optional[int] = None,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_rma_nbi(ctx, 'put', target, source, size, pe)


def get_nbi(
    target,
    source,
    pe: int,
    size: Optional[int] = None,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_rma_nbi(ctx, 'get', target, source, size, pe)


# ---


def _parse_amo_op(op):
    assert isinstance(op, str)
    return f'{op}'.lower()


def _parse_amo_args(name, args):
    if name in ('inc', 'fetch_inc'):
        return name, args[1:]
    if name == 'fetch_set':
        return 'swap', args
    return name, args


def _parse_amo(remote, readonly=False):
    cdata, size, ctype = _getbuffer(remote, readonly=readonly)
    assert size == 1
    return (ctype, cdata)


def _shmem_amo(ctx, name, remote, *args, readonly=False):
    name, args = _parse_amo_args(name, args)
    ctype, remote = _parse_amo(remote, readonly=readonly)
    shmem_amo = _shmem(ctx, ctype, f'atomic_{name}')
    return shmem_amo(remote, *args)


def _shmem_amo_nbi(ctx, name, fetch, remote, *args, readonly=False):
    name, args = _parse_amo_args(name, args)
    ftype, fetch = _parse_amo(fetch, readonly=False)
    ctype, remote = _parse_amo(remote, readonly=readonly)
    assert ctype == ftype
    shmem_amo_nbi = _shmem(ctx, ctype, f'atomic_{name}_nbi', chkerr=1)
    return shmem_amo_nbi(fetch, remote, *args)


def atomic_set(
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_amo(ctx, 'set', target, value, pe)


def atomic_inc(
    target,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_amo(ctx, 'inc', target, None, pe)


def atomic_add(
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_amo(ctx, 'add', target, value, pe)


def atomic_and(
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_amo(ctx, 'and', target, value, pe)


def atomic_or(
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_amo(ctx, 'or', target, value, pe)


def atomic_xor(
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_amo(ctx, 'xor', target, value, pe)


def atomic_fetch(
    source,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> Number:
    """
    """
    return _shmem_amo(ctx, 'fetch', source, pe, readonly=True)


def atomic_swap(
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> Number:
    """
    """
    return _shmem_amo(ctx, 'swap', target, value, pe)


def atomic_compare_swap(
    target,
    cond,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> Number:
    """
    """
    return _shmem_amo(ctx, 'compare_swap', target, cond, value, pe)


def atomic_fetch_inc(
    target,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> Number:
    """
    """
    return _shmem_amo(ctx, 'fetch_inc', target, None, pe)


def atomic_fetch_add(
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> Number:
    """
    """
    return _shmem_amo(ctx, 'fetch_add', target, value, pe)


def atomic_fetch_and(
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> Number:
    """
    """
    return _shmem_amo(ctx, 'fetch_and', target, value, pe)


def atomic_fetch_or(
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> Number:
    """
    """
    return _shmem_amo(ctx, 'fetch_or', target, value, pe)


def atomic_fetch_xor(
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> Number:
    """
    """
    return _shmem_amo(ctx, 'fetch_xor', target, value, pe)


def atomic_fetch_nbi(
    fetch,
    source,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_amo_nbi(ctx, 'fetch', fetch, source, pe, readonly=True)


def atomic_swap_nbi(
    fetch,
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_amo_nbi(ctx, 'swap', fetch, target, value, pe)


def atomic_compare_swap_nbi(
    fetch,
    target,
    cond,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_amo_nbi(ctx, 'compare_swap', fetch, target, cond, value, pe)


def atomic_fetch_inc_nbi(
    fetch,
    target,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_amo_nbi(ctx, 'fetch_inc', fetch, target, None, pe)


def atomic_fetch_add_nbi(
    fetch,
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_amo_nbi(ctx, 'fetch_add', fetch, target, value, pe)


def atomic_fetch_and_nbi(
    fetch,
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_amo_nbi(ctx, 'fetch_and', fetch, target, value, pe)


def atomic_fetch_or_nbi(
    fetch,
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_amo_nbi(ctx, 'fetch_or', fetch, target, value, pe)


def atomic_fetch_xor_nbi(
    fetch,
    target,
    value: Number,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_amo_nbi(ctx, 'fetch_xor', fetch, target, value, pe)


class AMO(str, _enum.Enum):
    """
    """
    SET: str = 'set'
    INC: str = 'inc'
    ADD: str = 'add'
    AND: str = 'and'
    OR:  str = 'or'
    XOR: str = 'xor'


AMO_SET: AMO = AMO.SET
AMO_INC: AMO = AMO.INC
AMO_ADD: AMO = AMO.ADD
AMO_AND: AMO = AMO.AND
AMO_OR:  AMO = AMO.OR
AMO_XOR: AMO = AMO.XOR


def atomic_op(
    target,
    value: Number,
    op: AMO,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    op = _parse_amo_op(op)
    _shmem_amo(ctx, f'{op}', target, value, pe)


def atomic_fetch_op(
    target,
    value: Number,
    op: AMO,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> Number:
    """
    """
    op = _parse_amo_op(op)
    return _shmem_amo(ctx, f'fetch_{op}', target, value, pe)


def atomic_fetch_op_nbi(
    fetch,
    target,
    value: Number,
    op: AMO,
    pe: int,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    op = _parse_amo_op(op)
    return _shmem_amo_nbi(ctx, f'fetch_{op}', fetch, target, value, pe)


# ---


def _parse_signal(signal):
    return signal


def _shmem_rma_signal(
    ctx, name, nbi,
    target, source, size, pe,
    signal, value, sigop,
):
    ctype, target, source, size = _parse_rma(target, source, size)
    signal = _parse_signal(signal)
    try:
        funcname = f'{name}_signal{nbi}'
        shmem_rma_signal = _shmem(ctx, ctype, funcname, chkerr=1)
    except AttributeError:
        size *= ffi.sizeof(ctype)
        funcname = f'{name}mem_signal{nbi}'
        shmem_rma_signal = _shmem(ctx, None, funcname, chkerr=1)
    return shmem_rma_signal(target, source, size, signal, value, sigop, pe)


_signal_ctype: ffi.CType = ffi.typeof('uint64_t*')


def new_signal() -> SigAddr:
    """
    """
    hints = lib.SHMEM_MALLOC_SIGNAL_REMOTE
    allocator = _get_allocator(hints=hints)
    signal = allocator(_signal_ctype)  # type: ignore[call-arg]
    return _typing.cast('SigAddr', signal)


def del_signal(signal: SigAddr) -> None:
    """
    """
    assert ffi.typeof(signal) is _signal_ctype
    ffi.release(signal)


def signal_fetch(signal: SigAddr) -> int:
    """
    """
    return lib.shmem_signal_fetch(signal)


class SIGNAL(_enum.IntEnum):
    """
    """
    SET: int = lib.SHMEM_SIGNAL_SET
    ADD: int = lib.SHMEM_SIGNAL_ADD


SIGNAL_SET: SIGNAL = SIGNAL.SET
SIGNAL_ADD: SIGNAL = SIGNAL.ADD


def put_signal(
    target,
    source,
    pe: int,
    signal: SigAddr,
    value: int,
    sigop: SIGNAL,
    size: Optional[int] = None,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_rma_signal(
        ctx, 'put', '',
        target, source, size, pe,
        signal, value, sigop,
    )


def put_signal_nbi(
    target,
    source,
    pe: int,
    signal: SigAddr,
    value: int,
    sigop: SIGNAL,
    size: Optional[int] = None,
    ctx: Optional[Ctx] = None,
) -> None:
    """
    """
    _shmem_rma_signal(
        ctx, 'put', '_nbi',
        target, source, size, pe,
        signal, value, sigop,
    )


# ---


def _parse_team(team):
    if team is None:
        team = lib.SHMEM_TEAM_WORLD
        npes = lib.shmem_n_pes()
    else:
        team = team.ob_team
        npes = lib.shmem_team_n_pes(team)
    return (team, npes)


def _parse_bcast(target, source, size):
    tdata, tsize, ttype = _getbuffer(target, readonly=False)
    sdata, ssize, stype = _getbuffer(source, readonly=True)
    assert ttype == stype
    if size is None:
        size = min(tsize, ssize)
    else:
        assert size <= tsize
        assert size <= ssize
    return (stype, tdata, sdata, size)


def _parse_collect(target, source, size, npes=1):
    tdata, tsize, ttype = _getbuffer(target, readonly=False)
    sdata, ssize, stype = _getbuffer(source, readonly=True)
    assert ttype == stype
    if size is None:
        size = ssize
        assert size * npes <= tsize
    else:
        assert size <= ssize
        assert size * npes <= tsize
    return (stype, tdata, sdata, size)


def _parse_alltoall(target, source, size, npes, tst=1, sst=1):
    # pylint: disable=too-many-locals
    tdata, tlen, ttype = _getbuffer(target, readonly=False)
    sdata, slen, stype = _getbuffer(source, readonly=True)
    assert ttype == stype
    tsize = _ceildiv(tlen, tst)
    ssize = _ceildiv(slen, sst)
    if size is None:
        minsize = min(tsize, ssize)
        size, remainder = divmod(minsize, npes)
        assert remainder == 0
    else:
        assert size * npes <= tsize
        assert size * npes <= ssize
    return (stype, tdata, sdata, size)


def _parse_reduce_op(op):
    assert isinstance(op, str)
    return f'{op}'.lower()


def _parse_reduce(target, source, size):
    tdata, tsize, ttype = _getbuffer(target, readonly=False)
    sdata, ssize, stype = _getbuffer(source, readonly=True)
    assert ttype == stype
    if size is None:
        size = min(tsize, ssize)
    else:
        assert size <= tsize
        assert size <= ssize
    return (stype, tdata, sdata, size)


def _shmem_collective(ctype, name, size):
    try:
        funcname = f'{name}'
        shmem_collective = _shmem(None, ctype, funcname, chkerr=2)
    except AttributeError:
        funcname = f'{name}mem'
        shmem_collective = _shmem(None, None, funcname, chkerr=2)
        size *= ffi.sizeof(ctype)
    return shmem_collective, size


def barrier_all() -> None:
    """
    """
    lib.shmem_barrier_all()


def sync_all() -> None:
    """
    """
    lib.shmem_sync_all()


def sync(team: Optional[Team] = None) -> None:
    """
    """
    if team is None:
        lib.shmem_sync_all()
    else:
        ierr = lib.shmem_team_sync(team.ob_team)
        _chkerr(ierr, "shmem_team_sync")


def broadcast(
    target,
    source,
    root: int,
    size: Optional[int] = None,
    team: Optional[Team] = None,
) -> None:
    """
    """
    team, _ = _parse_team(team)
    ctype, target, source, size = _parse_bcast(target, source, size)
    shmem_broadcast, size = _shmem_collective(ctype, 'broadcast', size)
    shmem_broadcast(team, target, source, size, root)


def collect(
    target,
    source,
    size: Optional[int] = None,
    team: Optional[Team] = None,
) -> None:
    """
    """
    team, _ = _parse_team(team)
    ctype, target, source, size = _parse_collect(target, source, size)
    shmem_collect, size = _shmem_collective(ctype, 'collect', size)
    shmem_collect(team, target, source, size)


def fcollect(
    target,
    source,
    size: Optional[int] = None,
    team: Optional[Team] = None,
) -> None:
    """
    """
    team, npes = _parse_team(team)
    ctype, target, source, size = _parse_collect(target, source, size, npes)
    shmem_fcollect, size = _shmem_collective(ctype, 'fcollect', size)
    shmem_fcollect(team, target, source, size)


def alltoall(target, source, size=None, team=None) -> None:
    """
    """
    team, npes = _parse_team(team)
    args = (target, source, size, npes)
    ctype, target, source, size = _parse_alltoall(*args)
    shmem_alltoall, size = _shmem_collective(ctype, 'alltoall', size)
    shmem_alltoall(team, target, source, size)


def alltoalls(
    target,
    source,
    tst: int = 1,
    sst: int = 1,
    size: Optional[int] = None,
    team: Optional[Team] = None,
) -> None:
    """
    """
    team, npes = _parse_team(team)
    args = (target, source, size, npes, tst, sst)
    ctype, target, source, size = _parse_alltoall(*args)
    shmem_alltoalls, memsize = _shmem_collective(ctype, 'alltoalls', size)
    if size == memsize:
        shmem_alltoalls(team, target, source, tst, sst, size)
    else:
        itemsize = ffi.sizeof(ctype)
        shmem_alltoalls = _shmem(None, None, 'alltoallsmem_x', chkerr=2)
        shmem_alltoalls(team, target, source, tst, sst, size, itemsize)


class OP(str, _enum.Enum):
    """
    """
    AND:  str = 'and'
    OR:   str = 'or'
    XOR:  str = 'xor'
    MAX:  str = 'max'
    MIN:  str = 'min'
    SUM:  str = 'sum'
    PROD: str = 'prod'


OP_AND:  OP = OP.AND
OP_OR:   OP = OP.OR
OP_XOR:  OP = OP.XOR
OP_MAX:  OP = OP.MAX
OP_MIN:  OP = OP.MIN
OP_SUM:  OP = OP.SUM
OP_PROD: OP = OP.PROD


def reduce(
    target,
    source,
    op: OP = OP_SUM,
    size: Optional[int] = None,
    team: Optional[Team] = None,
) -> None:
    """
    """
    op = _parse_reduce_op(op)
    team_ = team.ob_team if team is not None else lib.SHMEM_TEAM_WORLD
    ctype, target, source, size = _parse_reduce(target, source, size)
    shmem_reduce = _shmem(None, ctype, f'{op}_reduce')
    ierr = shmem_reduce(team_, target, source, size)
    _chkerr(ierr, f"shmem_{ctype}_{op}_reduce")


def and_reduce(
    target,
    source,
    size: Optional[int] = None,
    team: Optional[Team] = None,
) -> None:
    """
    """
    reduce(target, source, OP_AND, size, team)


def or_reduce(
    target,
    source,
    size: Optional[int] = None,
    team: Optional[Team] = None,
) -> None:
    """
    """
    reduce(target, source, OP_OR, size, team)


def xor_reduce(
    target,
    source,
    size: Optional[int] = None,
    team: Optional[Team] = None,
) -> None:
    """
    """
    reduce(target, source, OP_XOR, size, team)


def max_reduce(
    target,
    source,
    size: Optional[int] = None,
    team: Optional[Team] = None,
) -> None:
    """
    """
    reduce(target, source, OP_MAX, size, team)


def min_reduce(
    target,
    source,
    size: Optional[int] = None,
    team: Optional[Team] = None,
) -> None:
    """
    """
    reduce(target, source, OP_MIN, size, team)


def sum_reduce(
    target,
    source,
    size: Optional[int] = None,
    team: Optional[Team] = None,
) -> None:
    """
    """
    reduce(target, source, OP_SUM, size, team)


def prod_reduce(
    target,
    source,
    size: Optional[int] = None,
    team: Optional[Team] = None,
) -> None:
    """
    """
    reduce(target, source, OP_PROD, size, team)


# ---


class CMP(_enum.IntEnum):
    """
    """
    EQ: int = lib.SHMEM_CMP_EQ
    NE: int = lib.SHMEM_CMP_NE
    GT: int = lib.SHMEM_CMP_GT
    LE: int = lib.SHMEM_CMP_LE
    LT: int = lib.SHMEM_CMP_LT
    GE: int = lib.SHMEM_CMP_GE


CMP_EQ: CMP = CMP.EQ
CMP_NE: CMP = CMP.NE
CMP_GT: CMP = CMP.GT
CMP_LE: CMP = CMP.LE
CMP_LT: CMP = CMP.LT
CMP_GE: CMP = CMP.GE


_str_to_cmp = {
    '==': CMP_EQ,
    '!=': CMP_NE,
    '>':  CMP_GT,
    '<=': CMP_LE,
    '<':  CMP_LT,
    '>=': CMP_GE,
}


def _parse_cmp(cmp):
    if isinstance(cmp, str):
        if cmp in _str_to_cmp:
            return _str_to_cmp[cmp]
        name = cmp.upper()
        attr = f'SHMEM_CMP_{name}'
        return getattr(lib, attr)
    return cmp


def _parse_sync_ivar(ivar, readonly=True):
    ivar, size, ctype = _getbuffer(ivar, readonly=readonly)
    assert size == 1
    return (ctype, ivar)


def _parse_sync_ivars(ivars, readonly=True):
    ivars, size, ctype = _getbuffer(ivars, readonly=readonly)
    return (ctype, ivars, size)


def _parse_sync_indices(nelems):
    return ffi.new('size_t[]', nelems)


def _parse_sync_status(status, nelems):
    if status is None:
        return ffi.NULL
    status = np.asarray(status, dtype='i')
    status, size, ctype = _getbuffer(status, readonly=True)
    assert size >= nelems
    assert ctype == 'int'
    return status


def _parse_sync_values(values, nelems, vtype):
    dtype = _shmem_to_numpy[vtype]
    values = np.asarray(values, dtype=dtype)
    values, size, ctype = _getbuffer(values, readonly=True)
    assert size >= nelems
    assert ctype == vtype
    return values


def _shmem_sync(ctype, name):
    return _shmem(None, ctype, name)


def wait_until(
    ivar,
    cmp: CMP,
    value: Number,
) -> None:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, ivar = _parse_sync_ivar(ivar)
    shmem_wait = _shmem_sync(ctype, 'wait_until')
    return shmem_wait(ivar, cmp, value)


def wait_until_all(
    ivars,
    cmp: CMP,
    value: Number,
    status: Optional[Sequence[int]] = None,
) -> None:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, ivars, nelems = _parse_sync_ivars(ivars)
    status = _parse_sync_status(status, nelems)
    shmem_wait = _shmem_sync(ctype, 'wait_until_all')
    return shmem_wait(ivars, nelems, status, cmp, value)


def wait_until_any(
    ivars,
    cmp: CMP,
    value: Number,
    status: Optional[Sequence[int]] = None,
) -> Optional[int]:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, ivars, nelems = _parse_sync_ivars(ivars)
    status = _parse_sync_status(status, nelems)
    shmem_wait = _shmem_sync(ctype, 'wait_until_any')
    index = shmem_wait(ivars, nelems, status, cmp, value)
    return index if index < nelems else None


def wait_until_some(
    ivars,
    cmp: CMP,
    value: Number,
    status: Optional[Sequence[int]] = None,
) -> List[int]:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, ivars, nelems = _parse_sync_ivars(ivars)
    indices = _parse_sync_indices(nelems)
    status = _parse_sync_status(status, nelems)
    shmem_wait = _shmem_sync(ctype, 'wait_until_some')
    num = shmem_wait(ivars, nelems, indices, status, cmp, value)
    return list(indices[0:num])


def wait_until_all_vector(
    ivars,
    cmp: CMP,
    values: Sequence[Number],
    status: Optional[Sequence[int]] = None,
) -> None:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, ivars, nelems = _parse_sync_ivars(ivars)
    status = _parse_sync_status(status, nelems)
    values = _parse_sync_values(values, nelems, ctype)
    shmem_wait = _shmem_sync(ctype, 'wait_until_all_vector')
    return shmem_wait(ivars, nelems, status, cmp, values)


def wait_until_any_vector(
    ivars,
    cmp: CMP,
    values: Sequence[Number],
    status: Optional[Sequence[int]] = None,
) -> Optional[int]:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, ivars, nelems = _parse_sync_ivars(ivars)
    status = _parse_sync_status(status, nelems)
    values = _parse_sync_values(values, nelems, ctype)
    shmem_wait = _shmem_sync(ctype, 'wait_until_any_vector')
    index = shmem_wait(ivars, nelems, status, cmp, values)
    return index if index < nelems else None


def wait_until_some_vector(
    ivars,
    cmp: CMP,
    values: Sequence[Number],
    status: Optional[Sequence[int]] = None,
) -> List[int]:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, ivars, nelems = _parse_sync_ivars(ivars)
    indices = _parse_sync_indices(nelems)
    status = _parse_sync_status(status, nelems)
    values = _parse_sync_values(values, nelems, ctype)
    shmem_wait = _shmem_sync(ctype, 'wait_until_some_vector')
    num = shmem_wait(ivars, nelems, indices, status, cmp, values)
    return list(indices[0:num])


def test(
    ivar,
    cmp: CMP,
    value: Number,
) -> bool:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, ivar = _parse_sync_ivar(ivar)
    shmem_test = _shmem_sync(ctype, 'test')
    flag = shmem_test(ivar, cmp, value)
    return bool(flag)


def test_all(
    ivars,
    cmp: CMP,
    value: Number,
    status: Optional[Sequence[int]] = None,
) -> bool:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, ivars, nelems = _parse_sync_ivars(ivars)
    status = _parse_sync_status(status, nelems)
    shmem_test = _shmem_sync(ctype, 'test_all')
    flag = shmem_test(ivars, nelems, status, cmp, value)
    return bool(flag)


def test_any(
    ivars,
    cmp: CMP,
    value: Number,
    status: Optional[Sequence[int]] = None,
) -> Optional[int]:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, ivars, nelems = _parse_sync_ivars(ivars)
    status = _parse_sync_status(status, nelems)
    shmem_test = _shmem_sync(ctype, 'test_any')
    index = shmem_test(ivars, nelems, status, cmp, value)
    return index if index < nelems else None


def test_some(
    ivars,
    cmp: CMP,
    value: Number,
    status: Optional[Sequence[int]] = None,
) -> List[int]:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, ivars, nelems = _parse_sync_ivars(ivars)
    indices = _parse_sync_indices(nelems)
    status = _parse_sync_status(status, nelems)
    shmem_test = _shmem_sync(ctype, 'test_some')
    num = shmem_test(ivars, nelems, indices, status, cmp, value)
    return list(indices[0:num])


def test_all_vector(
    ivars,
    cmp: CMP,
    values: Sequence[Number],
    status: Optional[Sequence[int]] = None,
) -> bool:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, ivars, nelems = _parse_sync_ivars(ivars)
    status = _parse_sync_status(status, nelems)
    values = _parse_sync_values(values, nelems, ctype)
    shmem_test = _shmem_sync(ctype, 'test_all_vector')
    return bool(shmem_test(ivars, nelems, status, cmp, values))


def test_any_vector(
    ivars,
    cmp: CMP,
    values: Sequence[Number],
    status: Optional[Sequence[int]] = None,
) -> Optional[int]:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, ivars, nelems = _parse_sync_ivars(ivars)
    status = _parse_sync_status(status, nelems)
    values = _parse_sync_values(values, nelems, ctype)
    shmem_test = _shmem_sync(ctype, 'test_any_vector')
    index = shmem_test(ivars, nelems, status, cmp, values)
    return index if index < nelems else None


def test_some_vector(
    ivars,
    cmp: CMP,
    values: Sequence[Number],
    status: Optional[Sequence[int]] = None,
) -> List[int]:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, ivars, nelems = _parse_sync_ivars(ivars)
    indices = _parse_sync_indices(nelems)
    status = _parse_sync_status(status, nelems)
    values = _parse_sync_values(values, nelems, ctype)
    shmem_test = _shmem_sync(ctype, 'test_some_vector')
    num = shmem_test(ivars, nelems, indices, status, cmp, values)
    return list(indices[0:num])


def signal_wait_until(
    signal: SigAddr,
    cmp: CMP,
    value: Number,
) -> int:
    """
    """
    cmp = _parse_cmp(cmp)
    signal = _parse_signal(signal)
    return lib.shmem_signal_wait_until(signal, cmp, value)


# ---


def fence(ctx: Optional[Ctx] = None) -> None:
    """
    """
    if ctx is None:
        lib.shmem_fence()
    else:
        lib.shmem_ctx_fence(ctx.ob_ctx)


def quiet(ctx: Optional[Ctx] = None) -> None:
    """
    """
    if ctx is None:
        lib.shmem_quiet()
    else:
        lib.shmem_ctx_quiet(ctx.ob_ctx)


# ---

_lock_ctype: ffi.CType = ffi.typeof('long*')


def new_lock() -> LockHandle:
    """
    """
    allocator = _get_allocator()
    lock = allocator(_lock_ctype)  # type: ignore[call-arg]
    return _typing.cast('LockHandle', lock)


def del_lock(lock: LockHandle) -> None:
    """
    """
    assert ffi.typeof(lock) is _lock_ctype
    ffi.release(lock)


def set_lock(lock: LockHandle) -> None:
    """
    """
    lib.shmem_set_lock(lock)


def test_lock(lock: LockHandle) -> bool:
    """
    """
    return bool(lib.shmem_test_lock(lock))


def clear_lock(lock: LockHandle) -> None:
    """
    """
    lib.shmem_clear_lock(lock)


class Lock:
    """Lock object."""

    _lock: Optional[LockHandle]

    def __init__(self) -> None:
        self._lock = None
        self._lock = new_lock()

    def destroy(self) -> None:
        """
        """
        lock = self._lock
        self._lock = None
        if lock is not None:
            del_lock(lock)

    def acquire(self, blocking: bool = True) -> bool:
        """
        """
        lock = self._lock
        assert lock is not None
        if blocking:
            set_lock(lock)
            return True
        return not test_lock(lock)

    def release(self) -> None:
        """
        """
        lock = self._lock
        assert lock is not None
        clear_lock(lock)

    def __enter__(self) -> None:
        self.acquire()

    def __exit__(self, *args) -> None:
        self.release()


# ---


def pcontrol(level: int = 1) -> None:
    """
    """
    lib.shmem_pcontrol(level)


# ---
