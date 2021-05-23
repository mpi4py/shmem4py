from shmem4py.api import ffi
from shmem4py.api.lib import *

shmem_init()

mype = shmem_my_pe()

major = ffi.new('int*')
minor = ffi.new('int*')
name = ffi.new('char[]', SHMEM_MAX_NAME_LEN)
shmem_info_get_version(major, minor)
shmem_info_get_name(name)

major = major[0]
minor = minor[0]
name = ffi.string(name).decode()
assert major == SHMEM_MAJOR_VERSION
assert minor == SHMEM_MINOR_VERSION
assert name  == ffi.string(SHMEM_VENDOR_STRING).decode()

print(f"On PE {mype:03d}: MajorVersion={major} MinorVersion={minor} Name={repr(name)}")

shmem_finalize()
