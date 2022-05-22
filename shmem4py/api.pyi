from typing import (
    Any,
    List,
    Union,
    TypeVar,
    Callable,
    overload,
)

_T = TypeVar('_T')
_PyBuffer = Any


class FFI:

    class CType:
        cname: str
        kind: str
        item: ffi.CType

    class CData:
        def __getitem__(self, item: int) -> Any: ...
        def __setitem__(self, item: int, value: Any) -> None: ...

    class buffer:
        @overload
        def __init__(self, cdata: ffi.CData) -> None: ...
        @overload
        def __init__(self, cdata: ffi.CData, size: int) -> None: ...

    class error(Exception):
        pass

    NULL: CData

    errno: int

    @staticmethod
    def new(cdecl: Any, init: Any = ...) -> CData: ...

    @overload
    @staticmethod
    def cast(ctype: str, value: Any) -> CData: ...
    @overload
    @staticmethod
    def cast(ctype: CType, value: Any) -> CData: ...

    @overload
    @staticmethod
    def string(cdata: CData) -> bytes: ...
    @overload
    @staticmethod
    def string(cdata: CData, maxlen: int) -> bytes: ...

    @staticmethod
    def unpack(cdata: CData, lenght: int) -> Union[bytes, str, List[Any]]: ...

    @overload
    @staticmethod
    def from_buffer(cdecl: str, python_buffer: _PyBuffer, require_writable: bool = ...) -> CData: ...
    @overload
    @staticmethod
    def from_buffer(cdecl: CType, python_buffer: _PyBuffer, require_writable: bool = ...) -> CData: ...
    @overload
    @staticmethod
    def from_buffer(python_buffer: _PyBuffer, require_writable: bool = ...) -> CData: ...

    @staticmethod
    def memmove(dest: CData, src: CData, n: int) -> None: ...

    @overload
    @staticmethod
    def typeof(ctype: str) -> CType: ...
    @overload
    @staticmethod
    def typeof(cdata: CData) -> CType: ...

    @overload
    @staticmethod
    def sizeof(ctype: str) -> int: ...
    @overload
    @staticmethod
    def sizeof(ctype: CType) -> int: ...
    @overload
    @staticmethod
    def sizeof(cdata: CData) -> int: ...

    @overload
    @staticmethod
    def alignof(ctype: str) -> int: ...
    @overload
    @staticmethod
    def alignof(ctype: CType) -> int: ...
    @overload
    @staticmethod
    def alignof(cdata: CData) -> int: ...

    @overload
    @staticmethod
    def offsetof(ctype: str, *args: Union[int, str]) -> int: ...
    @overload
    @staticmethod
    def offsetof(ctype: CType, *args: Union[int, str]) -> int: ...

    @staticmethod
    def addressof(cdata: CData, *args: Union[int, str]) -> CData: ...

    @staticmethod
    def gc(
        cdata: CData,
        destructor: Callable[[CData], None],
        size: int = ...
    ) -> CData: ...

    @staticmethod
    def new_handle(python_object: Any) -> CData: ...

    @staticmethod
    def from_handle(cdata: CData) -> Any: ...

    @staticmethod
    def new_allocator(
        malloc: Callable[[int], CData],
        free: Callable[[CData], None],
        should_clear_after_alloc: bool = ...,
    ) -> Callable[..., CData]: ...

    @overload
    @staticmethod
    def release(cdata: CData) -> None: ...
    @overload
    @staticmethod
    def release(cdata: ffi.buffer) -> None: ...

    @staticmethod
    def init_once(function: Callable[[], _T], tag: str) -> _T: ...

    @overload
    @staticmethod
    def getctype(ctype: str, extra: str = ...) -> str: ...
    @overload
    @staticmethod
    def getctype(ctype: CType, extra: str = ...) -> str: ...


class Lib:
    def __getattr__(self, attr: str) -> Any: ...
    def __setattr__(self, attr: str, value: Any) -> None: ...


ffi = FFI
lib: Lib = ...
