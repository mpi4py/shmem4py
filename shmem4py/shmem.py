"""OpenSHMEM for Python."""
# pylint: disable=no-else-return
# pylint: disable=empty-docstring
# pylint: disable=too-many-arguments
# ---

import weakref as _wr
import numpy as np
from .api import ffi, lib

# ---


MAJOR_VERSION: int = lib.SHMEM_MAJOR_VERSION
MINOR_VERSION: int = lib.SHMEM_MINOR_VERSION
VENDOR_STRING: str = ffi.string(lib.SHMEM_VENDOR_STRING).decode()


def info_get_version() -> 'tuple[int, int]':
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


THREAD_SINGLE:     int = lib.SHMEM_THREAD_SINGLE
THREAD_FUNNELED:   int = lib.SHMEM_THREAD_FUNNELED
THREAD_SERIALIZED: int = lib.SHMEM_THREAD_SERIALIZED
THREAD_MULTIPLE:   int = lib.SHMEM_THREAD_MULTIPLE


def init() -> None:
    """
    """
    lib.shmem_init()


def finalize() -> None:
    """
    """
    lib.shmem_finalize()


def global_exit(status: int = 0) -> 'NoReturn':  # pragma: nocover
    """
    """
    lib.shmem_global_exit(status)


def init_thread(requested: int = THREAD_MULTIPLE) -> int:
    """
    """
    provided = ffi.new('int*', lib.SHMEM_THREAD_SINGLE)
    ierr = lib.shmem_init_thread(requested, provided)
    if ierr != 0:  # pragma: nocover
        raise RuntimeError(f"shmem_init_thread: error {ierr}")
    return provided[0]


def query_thread() -> int:
    """
    """
    provided = ffi.new('int*', lib.SHMEM_THREAD_SINGLE)
    lib.shmem_query_thread(provided)
    return provided[0]


# ---

def _initialize():
    # pylint: disable=import-outside-toplevel
    from . import rc
    if not rc.initialize:
        return
    if not rc.threads:
        init()
    else:
        level = rc.thread_level.upper()
        attr = f'SHMEM_THREAD_{level}'
        requested = getattr(lib, attr)
        init_thread(requested)
    # if rc.finalize is not False:
    #     pass


_initialize()


# ---


CTX_PRIVATE:    int = lib.SHMEM_CTX_PRIVATE
CTX_SERIALIZED: int = lib.SHMEM_CTX_SERIALIZED
CTX_NOSTORE:    int = lib.SHMEM_CTX_NOSTORE


class Ctx:
    """Communication context."""

    def __new__(cls, ctx=None):
        self = object.__new__(cls)
        self.ob_ctx = lib.SHMEM_CTX_INVALID
        if isinstance(ctx, ffi.CData):
            if ffi.typeof(ctx) is not ffi.typeof('shmem_ctx_t'):
                raise TypeError
        elif isinstance(ctx, cls):
            ctx = ctx.ob_ctx
        elif ctx is None:
            ctx = lib.SHMEM_CTX_INVALID
        else:
            raise TypeError
        self.ob_ctx = ffi.new('shmem_ctx_t*', ctx)[0]
        return self

    def __eq__(self, other):
        if not isinstance(other, Ctx):
            return NotImplemented
        return self.ob_ctx == other.ob_ctx

    def __ne__(self, other):
        if not isinstance(other, Ctx):
            return NotImplemented
        return self.ob_ctx != other.ob_ctx

    def __bool__(self):
        return self.ob_ctx != lib.SHMEM_CTX_INVALID

    def __enter__(self):
        return self

    def __exit__(self, *args):
        self.destroy()

    @staticmethod
    def create(
        options: int = 0,
        team: 'Optional[Team]' = None,
    ) -> 'Ctx':
        """
        """
        ctx = ffi.new('shmem_ctx_t*', lib.SHMEM_CTX_INVALID)
        if team is None:
            ierr = lib.shmem_ctx_create(options, ctx)
        else:
            team = team.ob_team
            ierr = lib.shmem_team_create_ctx(team, options, ctx)
        if ierr != 0:  # pragma: nocover
            raise RuntimeError(f"shmem_team_create_ctx: error {ierr}")
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

    def get_team(self) -> 'Team':
        """
        """
        ctx = self.ob_ctx
        team = ffi.new('shmem_team_t*', lib.SHMEM_TEAM_INVALID)
        ierr = lib.shmem_ctx_get_team(ctx, team)
        if ierr != 0:  # pragma: nocover
            raise RuntimeError(f"shmem_ctx_get_team: error {ierr}")
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

    def __new__(cls, team=None):
        self = object.__new__(cls)
        self.ob_team = lib.SHMEM_TEAM_INVALID
        if isinstance(team, ffi.CData):
            if ffi.typeof(team) is not ffi.typeof('shmem_team_t'):
                raise TypeError
        elif isinstance(team, cls):
            team = team.ob_team
        elif team is None:
            team = lib.SHMEM_TEAM_INVALID
        else:
            raise TypeError
        self.ob_team = ffi.new('shmem_team_t*', team)[0]
        return self

    def __eq__(self, other):
        if not isinstance(other, Team):
            return NotImplemented
        return self.ob_team == other.ob_team

    def __ne__(self, other):
        if not isinstance(other, Team):
            return NotImplemented
        return self.ob_team != other.ob_team

    def __bool__(self):
        return self.ob_team != lib.SHMEM_TEAM_INVALID

    def __enter__(self):
        return self

    def __exit__(self, *args):
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

    def my_pe(self) -> int:
        """
        """
        team = self.ob_team
        return lib.shmem_team_my_pe(team)

    def n_pes(self) -> int:
        """
        """
        team = self.ob_team
        return lib.shmem_team_n_pes(team)

    def translate_pe(
        self,
        pe: 'Optional[int]' = None,
        team: 'Optional[Team]' = None,
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
        return lib.shmem_team_translate_pe(src_team, src_pe, dest_team)

    def create_ctx(
        self,
        options: int = 0,
    ) -> Ctx:
        """
        """
        team = self.ob_team
        ctx = ffi.new('shmem_ctx_t*', lib.SHMEM_CTX_INVALID)
        ierr = lib.shmem_team_create_ctx(team, options, ctx)
        if ierr != 0:  # pragma: nocover
            raise RuntimeError(f"shmem_team_create_ctx: error {ierr}")
        return Ctx(ctx[0])

    def sync(self) -> None:
        """
        """
        team = self.ob_team
        lib.shmem_team_sync(team)


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


def addr_accessible(addr, pe: int) -> bool:
    """
    """
    addr = _getbuffer(addr, readonly=True)[0]
    return bool(lib.shmem_addr_accessible(addr, pe))


# ---


def barrier_all() -> None:
    """
    """
    lib.shmem_barrier_all()


def sync_all() -> None:
    """
    """
    lib.shmem_sync_all()


# ---


def fence() -> None:
    """
    """
    lib.shmem_fence()


def quiet() -> None:
    """
    """
    lib.shmem_quiet()


# ---


class _RawAlign(dict):

    def __init__(self, clear: bool = True):
        super().__init__()
        self.clear = clear

    def __missing__(self, align: int):
        return ffi.new_allocator(
            lambda size: lib.shmem_align(align, size),
            lib.shmem_free,
            should_clear_after_alloc=self.clear,
        )


_raw_malign = _RawAlign(clear=False)

_raw_calign = _RawAlign(clear=True)

_raw_malloc = ffi.new_allocator(
    lib.shmem_malloc,
    lib.shmem_free,
    should_clear_after_alloc=False,
)

_raw_calloc = ffi.new_allocator(
    lambda size: lib.shmem_calloc(size, 1),
    lib.shmem_free,
    should_clear_after_alloc=False,
)

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
    'f4':  'float',
    'f8':  'double',
    'c8':  'float _Complex',
    'c16': 'double _Complex',
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

    'S1': 'char',
    'i1': 'int8',
    'i2': 'int16',
    'i4': 'int32',
    'i8': 'int64',
    'u1': 'uint8',
    'u2': 'uint16',
    'u4': 'uint32',
    'u8': 'uint64',
    'f4': 'float',
    'f8': 'double',
    'c8': 'complexf',
    'c16': 'complexd',
}

_heap = _wr.WeakValueDictionary()


def alloc(
    dtype: 'np.DTypeLike',
    size: int,
    align: 'Optional[int]' = None,
    clear: bool = True,
) -> ffi.CData:
    """
    """
    dtype = np.dtype(dtype)
    ctype = _numpy_to_shmem[dtype.char]
    cdecl = ffi.getctype(ctype, '[]')
    if align is None:
        if clear:
            cdata = _raw_calloc(cdecl, size)
        else:
            cdata = _raw_malloc(cdecl, size)
    else:
        if clear:
            cdata = _raw_calign[align](cdecl, size)
        else:
            cdata = _raw_malign[align](cdecl, size)
    _heap[ffi.cast('uintptr_t', cdata)] = cdata
    return cdata


def free(cdata: 'ffi.CData|Buffer') -> None:
    """
    """
    if not isinstance(cdata, ffi.CData):
        cdata = ffi.from_buffer(cdata)
    cdata = _heap.pop(ffi.cast('uintptr_t', cdata))
    ffi.release(cdata)


def fromcdata(
    cdata: ffi.CData,
    shape: 'Optional[int|tuple[int]]' = None,
    dtype: 'Optional[np.DTypeLike]' = None,
    order: 'str' = 'C',
) -> np.ndarray:
    """
    """
    if dtype is None:
        ctype = ffi.typeof(cdata).item
        dtype = _cffi_to_numpy[ctype.cname]
    dtype = np.dtype(dtype)
    itemsize = dtype.itemsize
    if shape is None:
        shape = ffi.sizeof(cdata) // itemsize
    nbytes = np.prod(shape, dtype='p') * itemsize
    buf = ffi.buffer(cdata, nbytes)
    a = np.frombuffer(buf, dtype)
    tmp = a.reshape(shape, order=order)
    a.shape = tmp.shape
    a.strides = tmp.strides
    return a


def new_array(
    shape: 'int|tuple[int]',
    dtype: 'np.DTypeLike' = float,
    order: 'str' = 'C',
    align: 'Optional[int]' = None,
    clear: 'bool' = True,
) -> np.ndarray:
    """
    """
    dtype = np.dtype(dtype)
    size = np.prod(shape, dtype='p')
    cdata = alloc(dtype, size, align, clear)
    buf = ffi.buffer(cdata)
    a = np.frombuffer(buf, dtype)
    tmp = a.reshape(shape, order=order)
    a.shape = tmp.shape
    a.strides = tmp.strides
    return a


def array(
    obj: 'Any',
    dtype: 'Optional[np.DTypeLike]' = None,
    order: 'str' = 'K',
    align: 'Optional[int]' = None,
) -> np.ndarray:
    """
    """
    tmp = np.array(obj, dtype, copy=False, order=order)
    a = new_array(tmp.size, tmp.dtype, align=align, clear=False)
    a.shape = tmp.shape
    a.strides = tmp.strides
    np.copyto(a, tmp, casting='no')
    return a


def empty(
    shape: 'int|tuple[int]',
    dtype: 'np.DTypeLike' = float,
    order: 'str' = 'C',
    align: 'Optional[int]' = None,
) -> np.ndarray:
    """
    """
    a = new_array(shape, dtype, order, align=align, clear=False)
    return a


def zeros(
    shape: 'int|tuple[int]',
    dtype: 'np.DTypeLike' = float,
    order: 'str' = 'C',
    align: 'Optional[int]' = None,
) -> np.ndarray:
    """
    """
    a = new_array(shape, dtype, order, align=align, clear=True)
    return a


def ones(
    shape: 'int|tuple[int]',
    dtype: 'np.DTypeLike' = float,
    order: 'str' = 'C',
    align: 'Optional[int]' = None,
) -> np.ndarray:
    """
    """
    a = new_array(shape, dtype, order, align=align, clear=True)
    np.copyto(a, 1, casting='unsafe')
    return a


def full(
    shape: 'int|tuple[int]',
    fill_value: 'int|float',
    dtype: 'Optional[np.DTypeLike]' = None,
    order: 'str' = 'C',
    align: 'Optional[int]' = None,
) -> np.ndarray:
    """
    """
    if dtype is None:
        dtype = np.array(fill_value).dtype
    a = new_array(shape, dtype, order, align=align, clear=False)
    np.copyto(a, fill_value, casting='unsafe')
    return a


# ---


def _shmem(ctx, ctype, name):
    if ctx is None:
        attr = f'shmem_{ctype}_{name}'
        func = getattr(lib, f'shmem_{ctype}_{name}')
        return func
    else:
        attr = f'shmem_ctx_{ctype}_{name}'
        func = getattr(lib, attr)
        return lambda *args: func(ctx.ob_ctx, *args)


def _getbuffer(obj, readonly=False):
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


# ---


def _parse_rma(target, source, size=None, tst=1, sst=1):
    tdata, tlen, ttype = _getbuffer(target, readonly=False)
    sdata, slen, stype = _getbuffer(source, readonly=True)

    assert ttype == stype
    ctype = ttype

    def ceildiv(p, q):
        return (p + q - 1) // q

    tsize = ceildiv(tlen, tst)
    ssize = ceildiv(slen, sst)
    if size is None:
        size = min(tsize, ssize)
    else:
        assert size <= tsize
        assert size <= ssize

    return (ctype, tdata, sdata, size)


def _shmem_rma(ctx, name, target, source, size, pe):
    ctype, target, source, size = _parse_rma(target, source, size)
    return _shmem(ctx, ctype, name)(target, source, size, pe)


def _shmem_irma(ctx, name, target, source, tst, sst, size, pe):
    ctype, target, source, size = _parse_rma(target, source, size, tst, sst)
    return _shmem(ctx, ctype, f'i{name}')(target, source, tst, sst, size, pe)


def _shmem_rma_nbi(ctx, name, target, source, size, pe):
    ctype, target, source, size = _parse_rma(target, source, size)
    return _shmem(ctx, ctype, f'{name}_nbi')(target, source, size, pe)


def put(target, source, pe, size=None, ctx=None) -> None:
    """
    """
    return _shmem_rma(ctx, 'put', target, source, size, pe)


def get(target, source, pe, size=None, ctx=None) -> None:
    """
    """
    return _shmem_rma(ctx, 'get', target, source, size, pe)


def iput(target, source, pe, tst=1, sst=1, size=None, ctx=None) -> None:
    """
    """
    return _shmem_irma(ctx, 'put', target, source, tst, sst, size, pe)


def iget(target, source, pe, tst=1, sst=1, size=None, ctx=None) -> None:
    """
    """
    return _shmem_irma(ctx, 'get', target, source, tst, sst, size, pe)


def put_nbi(target, source, pe, size=None, ctx=None) -> None:
    """
    """
    return _shmem_rma_nbi(ctx, 'put', target, source, size, pe)


def get_nbi(target, source, pe, size=None, ctx=None) -> None:
    """
    """
    return _shmem_rma_nbi(ctx, 'get', target, source, size, pe)


# ---


def _parse_amo(remote, readonly=False):
    cdata, size, ctype = _getbuffer(remote, readonly=readonly)
    assert size == 1
    return (ctype, cdata)


def _shmem_amo(ctx, name, remote, *args, readonly=False):
    ctype, remote = _parse_amo(remote, readonly=readonly)
    return _shmem(ctx, ctype, f'atomic_{name}')(remote, *args)


def atomic_fetch(source, pe, ctx=None):
    """
    """
    return _shmem_amo(ctx, 'fetch', source, pe, readonly=True)


def atomic_set(target, value, pe, ctx=None):
    """
    """
    return _shmem_amo(ctx, 'set', target, value, pe)


def atomic_swap(target, value, pe, ctx=None):
    """
    """
    return _shmem_amo(ctx, 'swap', target, value, pe)


def atomic_compare_swap(target, cond, value, pe, ctx=None):
    """
    """
    return _shmem_amo(ctx, 'compare_swap', target, cond, value, pe)


def atomic_fetch_op(target, op, value, pe, ctx=None):
    """
    """
    if op == 'inc':
        return _shmem_amo(ctx, f'fetch_{op}', target, pe)
    return _shmem_amo(ctx, f'fetch_{op}', target, value, pe)


def atomic_op(target, op, value, pe, ctx=None):
    """
    """
    if op == 'inc':
        return _shmem_amo(ctx, op, target, pe)
    return _shmem_amo(ctx, op, target, value, pe)


def atomic_fetch_inc(target, pe, ctx=None):
    """
    """
    return _shmem_amo(ctx, 'fetch_inc', target, pe)


def atomic_inc(target, pe, ctx=None):
    """
    """
    return _shmem_amo(ctx, 'inc', target, pe)


def atomic_fetch_add(target, value, pe, ctx=None):
    """
    """
    return _shmem_amo(ctx, 'fetch_add', target, value, pe)


def atomic_add(target, value, pe, ctx=None):
    """
    """
    return _shmem_amo(ctx, 'add', target, value, pe)


def atomic_fetch_and(target, value, pe, ctx=None):
    """
    """
    return _shmem_amo(ctx, 'fetch_and', target, value, pe)


def atomic_and(target, value, pe, ctx=None):
    """
    """
    return _shmem_amo(ctx, 'and', target, value, pe)


def atomic_fetch_or(target, value, pe, ctx=None):
    """
    """
    return _shmem_amo(ctx, 'fetch_or', target, value, pe)


def atomic_or(target, value, pe, ctx=None):
    """
    """
    return _shmem_amo(ctx, 'or', target, value, pe)


def atomic_fetch_xor(target, value, pe, ctx=None):
    """
    """
    return _shmem_amo(ctx, 'fetch_xor', target, value, pe)


def atomic_xor(target, value, pe, ctx=None):
    """
    """
    return _shmem_amo(ctx, 'xor', target, value, pe)


# ---


OP_AND = 'and'
OP_OR = 'or'
OP_XOR = 'xor'
OP_MAX = 'max'
OP_MIN = 'min'
OP_SUM = 'sum'
OP_PROD = 'prod'


def reduce(target, source, op='sum', size=None, team=None):
    """
    """
    team = team.ob_team if team is not None else lib.SHMEM_TEAM_WORLD
    ctype, target, source, size = _parse_rma(target, source, size)
    return _shmem(None, ctype, f'{op}_reduce')(team, target, source, size)


# ---


CMP_EQ = lib.SHMEM_CMP_EQ
CMP_NE = lib.SHMEM_CMP_NE
CMP_GT = lib.SHMEM_CMP_GT
CMP_LE = lib.SHMEM_CMP_LE
CMP_LT = lib.SHMEM_CMP_LT
CMP_GE = lib.SHMEM_CMP_GE


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


def _parse_sync(addr, readonly=True):
    addr, size, ctype = _getbuffer(addr, readonly=readonly)
    assert size == 1
    return (ctype, addr)


def wait_until(addr, cmp, value) -> None:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, addr = _parse_sync(addr)
    return _shmem(None, ctype, 'wait_until')(addr, cmp, value)


def test(addr, cmp, value) -> bool:
    """
    """
    cmp = _parse_cmp(cmp)
    ctype, addr = _parse_sync(addr)
    return bool(_shmem(None, ctype, 'test')(addr, cmp, value))


# ---
