#ifndef PySHMEM_COMPAT_OPENMPI_H
#define PySHMEM_COMPAT_OPENMPI_H

#if INT32_MAX == INT_MAX
#define shmem_ctx_int32_atomic_fetch            shmem_ctx_int_atomic_fetch
#define shmem_ctx_int32_atomic_set              shmem_ctx_int_atomic_set
#define shmem_ctx_int32_atomic_swap             shmem_ctx_int_atomic_swap
#define shmem_ctx_int32_atomic_compare_swap     shmem_ctx_int_atomic_compare_swap
#define shmem_ctx_int32_atomic_fetch_inc        shmem_ctx_int_atomic_fetch_inc
#define shmem_ctx_int32_atomic_inc              shmem_ctx_int_atomic_inc
#define shmem_ctx_int32_atomic_fetch_add        shmem_ctx_int_atomic_fetch_add
#define shmem_ctx_int32_atomic_add              shmem_ctx_int_atomic_add
#endif

#if UINT32_MAX == UINT_MAX
#define shmem_ctx_uint32_atomic_fetch           shmem_ctx_uint_atomic_fetch
#define shmem_ctx_uint32_atomic_set             shmem_ctx_uint_atomic_set
#define shmem_ctx_uint32_atomic_swap            shmem_ctx_uint_atomic_swap
#define shmem_ctx_uint32_atomic_compare_swap    shmem_ctx_uint_atomic_compare_swap
#define shmem_ctx_uint32_atomic_fetch_inc       shmem_ctx_uint_atomic_fetch_inc
#define shmem_ctx_uint32_atomic_inc             shmem_ctx_uint_atomic_inc
#define shmem_ctx_uint32_atomic_fetch_add       shmem_ctx_uint_atomic_fetch_add
#define shmem_ctx_uint32_atomic_add             shmem_ctx_uint_atomic_add
#endif

#if INT64_MAX > LONG_MAX
#define shmem_ctx_int64_atomic_fetch            shmem_ctx_longlong_atomic_fetch
#define shmem_ctx_int64_atomic_set              shmem_ctx_longlong_atomic_set
#define shmem_ctx_int64_atomic_swap             shmem_ctx_longlong_atomic_swap
#define shmem_ctx_int64_atomic_compare_swap     shmem_ctx_longlong_atomic_compare_swap
#define shmem_ctx_int64_atomic_fetch_inc        shmem_ctx_longlong_atomic_fetch_inc
#define shmem_ctx_int64_atomic_inc              shmem_ctx_longlong_atomic_inc
#define shmem_ctx_int64_atomic_fetch_add        shmem_ctx_longlong_atomic_fetch_add
#define shmem_ctx_int64_atomic_add              shmem_ctx_longlong_atomic_add
#else
#define shmem_ctx_int64_atomic_fetch            shmem_ctx_long_atomic_fetch
#define shmem_ctx_int64_atomic_set              shmem_ctx_long_atomic_set
#define shmem_ctx_int64_atomic_swap             shmem_ctx_long_atomic_swap
#define shmem_ctx_int64_atomic_compare_swap     shmem_ctx_long_atomic_compare_swap
#define shmem_ctx_int64_atomic_fetch_inc        shmem_ctx_long_atomic_fetch_inc
#define shmem_ctx_int64_atomic_inc              shmem_ctx_long_atomic_inc
#define shmem_ctx_int64_atomic_fetch_add        shmem_ctx_long_atomic_fetch_add
#define shmem_ctx_int64_atomic_add              shmem_ctx_long_atomic_add
#endif

#if UINT64_MAX > ULONG_MAX
#define shmem_ctx_uint64_atomic_fetch           shmem_ctx_ulonglong_atomic_fetch
#define shmem_ctx_uint64_atomic_set             shmem_ctx_ulonglong_atomic_set
#define shmem_ctx_uint64_atomic_swap            shmem_ctx_ulonglong_atomic_swap
#define shmem_ctx_uint64_atomic_compare_swap    shmem_ctx_ulonglong_atomic_compare_swap
#define shmem_ctx_uint64_atomic_fetch_inc       shmem_ctx_ulonglong_atomic_fetch_inc
#define shmem_ctx_uint64_atomic_inc             shmem_ctx_ulonglong_atomic_inc
#define shmem_ctx_uint64_atomic_fetch_add       shmem_ctx_ulonglong_atomic_fetch_add
#define shmem_ctx_uint64_atomic_add             shmem_ctx_ulonglong_atomic_add
#else
#define shmem_ctx_uint64_atomic_fetch           shmem_ctx_ulong_atomic_fetch
#define shmem_ctx_uint64_atomic_set             shmem_ctx_ulong_atomic_set
#define shmem_ctx_uint64_atomic_swap            shmem_ctx_ulong_atomic_swap
#define shmem_ctx_uint64_atomic_compare_swap    shmem_ctx_ulong_atomic_compare_swap
#define shmem_ctx_uint64_atomic_fetch_inc       shmem_ctx_ulong_atomic_fetch_inc
#define shmem_ctx_uint64_atomic_inc             shmem_ctx_ulong_atomic_inc
#define shmem_ctx_uint64_atomic_fetch_add       shmem_ctx_ulong_atomic_fetch_add
#define shmem_ctx_uint64_atomic_add             shmem_ctx_ulong_atomic_add
#endif

#if PTRDIFF_MAX > INT32_MAX
#define shmem_ctx_ptrdiff_atomic_fetch          shmem_ctx_int64_atomic_fetch
#define shmem_ctx_ptrdiff_atomic_set            shmem_ctx_int64_atomic_set
#define shmem_ctx_ptrdiff_atomic_swap           shmem_ctx_int64_atomic_swap
#define shmem_ctx_ptrdiff_atomic_compare_swap   shmem_ctx_int64_atomic_compare_swap
#define shmem_ctx_ptrdiff_atomic_fetch_inc      shmem_ctx_int64_atomic_fetch_inc
#define shmem_ctx_ptrdiff_atomic_inc            shmem_ctx_int64_atomic_inc
#define shmem_ctx_ptrdiff_atomic_fetch_add      shmem_ctx_int64_atomic_fetch_add
#define shmem_ctx_ptrdiff_atomic_add            shmem_ctx_int64_atomic_add
#else
#define shmem_ctx_ptrdiff_atomic_fetch          shmem_ctx_int32_atomic_fetch
#define shmem_ctx_ptrdiff_atomic_set            shmem_ctx_int32_atomic_set
#define shmem_ctx_ptrdiff_atomic_swap           shmem_ctx_int32_atomic_swap
#define shmem_ctx_ptrdiff_atomic_compare_swap   shmem_ctx_int32_atomic_compare_swap
#define shmem_ctx_ptrdiff_atomic_fetch_inc      shmem_ctx_int32_atomic_fetch_inc
#define shmem_ctx_ptrdiff_atomic_inc            shmem_ctx_int32_atomic_inc
#define shmem_ctx_ptrdiff_atomic_fetch_add      shmem_ctx_int32_atomic_fetch_add
#define shmem_ctx_ptrdiff_atomic_add            shmem_ctx_int32_atomic_add
#endif

#if SIZE_MAX > UINT32_MAX
#define shmem_ctx_size_atomic_fetch             shmem_ctx_uint64_atomic_fetch
#define shmem_ctx_size_atomic_set               shmem_ctx_uint64_atomic_set
#define shmem_ctx_size_atomic_swap              shmem_ctx_uint64_atomic_swap
#define shmem_ctx_size_atomic_compare_swap      shmem_ctx_uint64_atomic_compare_swap
#define shmem_ctx_size_atomic_fetch_inc         shmem_ctx_uint64_atomic_fetch_inc
#define shmem_ctx_size_atomic_inc               shmem_ctx_uint64_atomic_inc
#define shmem_ctx_size_atomic_fetch_add         shmem_ctx_uint64_atomic_fetch_add
#define shmem_ctx_size_atomic_add               shmem_ctx_uint64_atomic_add
#else
#define shmem_ctx_size_atomic_fetch             shmem_ctx_uint32_atomic_fetch
#define shmem_ctx_size_atomic_set               shmem_ctx_uint32_atomic_set
#define shmem_ctx_size_atomic_swap              shmem_ctx_uint32_atomic_swap
#define shmem_ctx_size_atomic_compare_swap      shmem_ctx_uint32_atomic_compare_swap
#define shmem_ctx_size_atomic_fetch_inc         shmem_ctx_uint32_atomic_fetch_inc
#define shmem_ctx_size_atomic_inc               shmem_ctx_uint32_atomic_inc
#define shmem_ctx_size_atomic_fetch_add         shmem_ctx_uint32_atomic_fetch_add
#define shmem_ctx_size_atomic_add               shmem_ctx_uint32_atomic_add
#endif

#if INT32_MAX == INT_MAX
#define shmem_int32_atomic_fetch            shmem_int_atomic_fetch
#define shmem_int32_atomic_set              shmem_int_atomic_set
#define shmem_int32_atomic_swap             shmem_int_atomic_swap
#define shmem_int32_atomic_compare_swap     shmem_int_atomic_compare_swap
#define shmem_int32_atomic_fetch_inc        shmem_int_atomic_fetch_inc
#define shmem_int32_atomic_inc              shmem_int_atomic_inc
#define shmem_int32_atomic_fetch_add        shmem_int_atomic_fetch_add
#define shmem_int32_atomic_add              shmem_int_atomic_add
#endif

#if UINT32_MAX == UINT_MAX
#define shmem_uint32_atomic_fetch           shmem_uint_atomic_fetch
#define shmem_uint32_atomic_set             shmem_uint_atomic_set
#define shmem_uint32_atomic_swap            shmem_uint_atomic_swap
#define shmem_uint32_atomic_compare_swap    shmem_uint_atomic_compare_swap
#define shmem_uint32_atomic_fetch_inc       shmem_uint_atomic_fetch_inc
#define shmem_uint32_atomic_inc             shmem_uint_atomic_inc
#define shmem_uint32_atomic_fetch_add       shmem_uint_atomic_fetch_add
#define shmem_uint32_atomic_add             shmem_uint_atomic_add
#endif

#if INT64_MAX > LONG_MAX
#define shmem_int64_atomic_fetch            shmem_longlong_atomic_fetch
#define shmem_int64_atomic_set              shmem_longlong_atomic_set
#define shmem_int64_atomic_swap             shmem_longlong_atomic_swap
#define shmem_int64_atomic_compare_swap     shmem_longlong_atomic_compare_swap
#define shmem_int64_atomic_fetch_inc        shmem_longlong_atomic_fetch_inc
#define shmem_int64_atomic_inc              shmem_longlong_atomic_inc
#define shmem_int64_atomic_fetch_add        shmem_longlong_atomic_fetch_add
#define shmem_int64_atomic_add              shmem_longlong_atomic_add
#else
#define shmem_int64_atomic_fetch            shmem_long_atomic_fetch
#define shmem_int64_atomic_set              shmem_long_atomic_set
#define shmem_int64_atomic_swap             shmem_long_atomic_swap
#define shmem_int64_atomic_compare_swap     shmem_long_atomic_compare_swap
#define shmem_int64_atomic_fetch_inc        shmem_long_atomic_fetch_inc
#define shmem_int64_atomic_inc              shmem_long_atomic_inc
#define shmem_int64_atomic_fetch_add        shmem_long_atomic_fetch_add
#define shmem_int64_atomic_add              shmem_long_atomic_add
#endif

#if UINT64_MAX > ULONG_MAX
#define shmem_uint64_atomic_fetch           shmem_ulonglong_atomic_fetch
#define shmem_uint64_atomic_set             shmem_ulonglong_atomic_set
#define shmem_uint64_atomic_swap            shmem_ulonglong_atomic_swap
#define shmem_uint64_atomic_compare_swap    shmem_ulonglong_atomic_compare_swap
#define shmem_uint64_atomic_fetch_inc       shmem_ulonglong_atomic_fetch_inc
#define shmem_uint64_atomic_inc             shmem_ulonglong_atomic_inc
#define shmem_uint64_atomic_fetch_add       shmem_ulonglong_atomic_fetch_add
#define shmem_uint64_atomic_add             shmem_ulonglong_atomic_add
#else
#define shmem_uint64_atomic_fetch           shmem_ulong_atomic_fetch
#define shmem_uint64_atomic_set             shmem_ulong_atomic_set
#define shmem_uint64_atomic_swap            shmem_ulong_atomic_swap
#define shmem_uint64_atomic_compare_swap    shmem_ulong_atomic_compare_swap
#define shmem_uint64_atomic_fetch_inc       shmem_ulong_atomic_fetch_inc
#define shmem_uint64_atomic_inc             shmem_ulong_atomic_inc
#define shmem_uint64_atomic_fetch_add       shmem_ulong_atomic_fetch_add
#define shmem_uint64_atomic_add             shmem_ulong_atomic_add
#endif

#if PTRDIFF_MAX > INT32_MAX
#define shmem_ptrdiff_atomic_fetch          shmem_int64_atomic_fetch
#define shmem_ptrdiff_atomic_set            shmem_int64_atomic_set
#define shmem_ptrdiff_atomic_swap           shmem_int64_atomic_swap
#define shmem_ptrdiff_atomic_compare_swap   shmem_int64_atomic_compare_swap
#define shmem_ptrdiff_atomic_fetch_inc      shmem_int64_atomic_fetch_inc
#define shmem_ptrdiff_atomic_inc            shmem_int64_atomic_inc
#define shmem_ptrdiff_atomic_fetch_add      shmem_int64_atomic_fetch_add
#define shmem_ptrdiff_atomic_add            shmem_int64_atomic_add
#else
#define shmem_ptrdiff_atomic_fetch          shmem_int32_atomic_fetch
#define shmem_ptrdiff_atomic_set            shmem_int32_atomic_set
#define shmem_ptrdiff_atomic_swap           shmem_int32_atomic_swap
#define shmem_ptrdiff_atomic_compare_swap   shmem_int32_atomic_compare_swap
#define shmem_ptrdiff_atomic_fetch_inc      shmem_int32_atomic_fetch_inc
#define shmem_ptrdiff_atomic_inc            shmem_int32_atomic_inc
#define shmem_ptrdiff_atomic_fetch_add      shmem_int32_atomic_fetch_add
#define shmem_ptrdiff_atomic_add            shmem_int32_atomic_add
#endif

#if SIZE_MAX > UINT32_MAX
#define shmem_size_atomic_fetch             shmem_uint64_atomic_fetch
#define shmem_size_atomic_set               shmem_uint64_atomic_set
#define shmem_size_atomic_swap              shmem_uint64_atomic_swap
#define shmem_size_atomic_compare_swap      shmem_uint64_atomic_compare_swap
#define shmem_size_atomic_fetch_inc         shmem_uint64_atomic_fetch_inc
#define shmem_size_atomic_inc               shmem_uint64_atomic_inc
#define shmem_size_atomic_fetch_add         shmem_uint64_atomic_fetch_add
#define shmem_size_atomic_add               shmem_uint64_atomic_add
#else
#define shmem_size_atomic_fetch             shmem_uint32_atomic_fetch
#define shmem_size_atomic_set               shmem_uint32_atomic_set
#define shmem_size_atomic_swap              shmem_uint32_atomic_swap
#define shmem_size_atomic_compare_swap      shmem_uint32_atomic_compare_swap
#define shmem_size_atomic_fetch_inc         shmem_uint32_atomic_fetch_inc
#define shmem_size_atomic_inc               shmem_uint32_atomic_inc
#define shmem_size_atomic_fetch_add         shmem_uint32_atomic_fetch_add
#define shmem_size_atomic_add               shmem_uint32_atomic_add
#endif

#endif
