#ifndef PySHMEM_COMPAT_NVIDIA_H
#define PySHMEM_COMPAT_NVIDIA_H

#define SHMEM_MAJOR_VERSION           NVSHMEM_MAJOR_VERSION
#define SHMEM_MINOR_VERSION           NVSHMEM_MINOR_VERSION
#define SHMEM_VENDOR_STRING           NVSHMEM_VENDOR_STRING
#define SHMEM_THREAD_SINGLE           NVSHMEM_THREAD_SINGLE
#define SHMEM_THREAD_FUNNELED         NVSHMEM_THREAD_FUNNELED
#define SHMEM_THREAD_SERIALIZED       NVSHMEM_THREAD_SERIALIZED
#define SHMEM_THREAD_MULTIPLE         NVSHMEM_THREAD_MULTIPLE
#define SHMEM_TEAM_WORLD              NVSHMEM_TEAM_WORLD
#define SHMEM_TEAM_SHARED             NVSHMEM_TEAM_SHARED
#define SHMEM_TEAM_INVALID            NVSHMEM_TEAM_INVALID
#define SHMEM_MAX_NAME_LEN            NVSHMEM_MAX_NAME_LEN 
#define SHMEM_CMP_EQ                  NVSHMEM_CMP_EQ
#define SHMEM_CMP_NE                  NVSHMEM_CMP_NE
#define SHMEM_CMP_GT                  NVSHMEM_CMP_GT
#define SHMEM_CMP_LE                  NVSHMEM_CMP_LE
#define SHMEM_CMP_LT                  NVSHMEM_CMP_LT
#define SHMEM_CMP_GE                  NVSHMEM_CMP_GE
#define SHMEM_SYNC_VALUE              NVSHMEMI_SYNC_VALUE
#define SHMEM_SYNC_SIZE               NVSHMEMI_SYNC_SIZE
#define SHMEM_REDUCE_MIN_WRKDATA_SIZE NVSHMEMI_REDUCE_MIN_WRKDATA_SIZE
// #define SHMEM_SIGNAL_ADD        NVSHMEM_SIGNAL_ADD // consts exist, but as of nvshmem 2.2.1 only "on stream" signals are exposed
// #define SHMEM_SIGNAL_SET        NVSHMEM_SIGNAL_SET // consts exist, but as of nvshmem 2.2.1 only "on stream" signals are exposed

#define SHMEM_TEAM_NUM_CONTEXTS 0
#define SHMEM_CTX_PRIVATE       0
#define SHMEM_CTX_SERIALIZED    0
#define SHMEM_CTX_NOSTORE       0

#define shmem_n_pes              nvshmem_n_pes
#define shmem_my_pe              nvshmem_my_pe
#define shmem_free               nvshmem_free
#define shmem_init               nvshmem_init
#define shmem_finalize           nvshmem_finalize
#define shmem_align              nvshmem_align
#define shmem_calloc             nvshmem_calloc
#define shmem_malloc             nvshmem_malloc
#define shmem_barrier_all        nvshmem_barrier_all
#define shmem_sync_all           nvshmem_sync_all
#define shmem_fence              nvshmem_fence
#define shmem_quiet              nvshmem_quiet
#define shmem_init_thread        nvshmem_init_thread
#define shmem_query_thread       nvshmem_query_thread
#define shmem_ptr                nvshmem_ptr
#define shmem_info_get_version   nvshmem_info_get_version
#define shmem_info_get_name      nvshmem_info_get_name
#define shmem_team_t             nvshmem_team_t
#define shmem_team_my_pe         nvshmem_team_my_pe
#define shmem_team_n_pes         nvshmem_team_n_pes
#define shmem_team_translate_pe  nvshmem_team_translate_pe
#define shmem_team_split_strided nvshmem_team_split_strided
#define shmem_team_split_2d      nvshmem_team_split_2d
#define shmem_team_config_t      nvshmem_team_config_t
#define shmem_team_destroy       nvshmem_team_destroy
#define shmem_team_sync          nvshmem_team_sync

#define shmem_double_max_reduce     nvshmem_double_max_reduce
#define shmem_double_min_reduce     nvshmem_double_min_reduce
#define shmem_double_prod_reduce    nvshmem_double_prod_reduce
#define shmem_double_sum_reduce     nvshmem_double_sum_reduce
#define shmem_float_max_reduce      nvshmem_float_max_reduce
#define shmem_float_min_reduce      nvshmem_float_min_reduce
#define shmem_float_prod_reduce     nvshmem_float_prod_reduce
#define shmem_float_sum_reduce      nvshmem_float_sum_reduce
#define shmem_int_max_reduce        nvshmem_int_max_reduce
#define shmem_int_min_reduce        nvshmem_int_min_reduce
#define shmem_int_prod_reduce       nvshmem_int_prod_reduce
#define shmem_int_sum_reduce        nvshmem_int_sum_reduce
#define shmem_longlong_max_reduce   nvshmem_longlong_max_reduce
#define shmem_longlong_min_reduce   nvshmem_longlong_min_reduce
#define shmem_longlong_prod_reduce  nvshmem_longlong_prod_reduce
#define shmem_longlong_sum_reduce   nvshmem_longlong_sum_reduce
#define shmem_long_max_reduce       nvshmem_long_max_reduce
#define shmem_long_min_reduce       nvshmem_long_min_reduce
#define shmem_long_prod_reduce      nvshmem_long_prod_reduce
#define shmem_long_sum_reduce       nvshmem_long_sum_reduce
#define shmem_short_max_reduce      nvshmem_short_max_reduce
#define shmem_short_min_reduce      nvshmem_short_min_reduce
#define shmem_short_prod_reduce     nvshmem_short_prod_reduce
#define shmem_short_sum_reduce      nvshmem_short_sum_reduce
#define shmem_uint_and_reduce       nvshmem_uint_and_reduce
#define shmem_uint_max_reduce       nvshmem_uint_max_reduce
#define shmem_uint_min_reduce       nvshmem_uint_min_reduce
#define shmem_uint_or_reduce        nvshmem_uint_or_reduce
#define shmem_uint_prod_reduce      nvshmem_uint_prod_reduce
#define shmem_uint_sum_reduce       nvshmem_uint_sum_reduce
#define shmem_uint_xor_reduce       nvshmem_uint_xor_reduce
#define shmem_ulong_and_reduce      nvshmem_ulong_and_reduce
#define shmem_ulonglong_and_reduce  nvshmem_ulonglong_and_reduce
#define shmem_ulonglong_max_reduce  nvshmem_ulonglong_max_reduce
#define shmem_ulonglong_min_reduce  nvshmem_ulonglong_min_reduce
#define shmem_ulonglong_or_reduce   nvshmem_ulonglong_or_reduce
#define shmem_ulonglong_prod_reduce nvshmem_ulonglong_prod_reduce
#define shmem_ulonglong_sum_reduce  nvshmem_ulonglong_sum_reduce
#define shmem_ulonglong_xor_reduce  nvshmem_ulonglong_xor_reduce
#define shmem_ulong_max_reduce      nvshmem_ulong_max_reduce
#define shmem_ulong_min_reduce      nvshmem_ulong_min_reduce
#define shmem_ulong_or_reduce       nvshmem_ulong_or_reduce
#define shmem_ulong_prod_reduce     nvshmem_ulong_prod_reduce
#define shmem_ulong_sum_reduce      nvshmem_ulong_sum_reduce
#define shmem_ulong_xor_reduce      nvshmem_ulong_xor_reduce
#define shmem_ushort_and_reduce     nvshmem_ushort_and_reduce
#define shmem_ushort_max_reduce     nvshmem_ushort_max_reduce
#define shmem_ushort_min_reduce     nvshmem_ushort_min_reduce
#define shmem_ushort_or_reduce      nvshmem_ushort_or_reduce
#define shmem_ushort_prod_reduce    nvshmem_ushort_prod_reduce
#define shmem_ushort_sum_reduce     nvshmem_ushort_sum_reduce
#define shmem_ushort_xor_reduce     nvshmem_ushort_xor_reduce
#define shmem_char_max_reduce       nvshmem_char_max_reduce    
#define shmem_char_min_reduce       nvshmem_char_min_reduce    
#define shmem_char_prod_reduce      nvshmem_char_prod_reduce   
#define shmem_char_sum_reduce       nvshmem_char_sum_reduce    
#define shmem_int16_and_reduce      nvshmem_int16_and_reduce   
#define shmem_int16_max_reduce      nvshmem_int16_max_reduce   
#define shmem_int16_min_reduce      nvshmem_int16_min_reduce   
#define shmem_int16_or_reduce       nvshmem_int16_or_reduce    
#define shmem_int16_prod_reduce     nvshmem_int16_prod_reduce  
#define shmem_int16_sum_reduce      nvshmem_int16_sum_reduce   
#define shmem_int16_xor_reduce      nvshmem_int16_xor_reduce   
#define shmem_int32_and_reduce      nvshmem_int32_and_reduce   
#define shmem_int32_max_reduce      nvshmem_int32_max_reduce   
#define shmem_int32_min_reduce      nvshmem_int32_min_reduce   
#define shmem_int32_or_reduce       nvshmem_int32_or_reduce    
#define shmem_int32_prod_reduce     nvshmem_int32_prod_reduce  
#define shmem_int32_sum_reduce      nvshmem_int32_sum_reduce   
#define shmem_int32_xor_reduce      nvshmem_int32_xor_reduce   
#define shmem_int64_and_reduce      nvshmem_int64_and_reduce   
#define shmem_int64_max_reduce      nvshmem_int64_max_reduce   
#define shmem_int64_min_reduce      nvshmem_int64_min_reduce   
#define shmem_int64_or_reduce       nvshmem_int64_or_reduce    
#define shmem_int64_prod_reduce     nvshmem_int64_prod_reduce  
#define shmem_int64_sum_reduce      nvshmem_int64_sum_reduce   
#define shmem_int64_xor_reduce      nvshmem_int64_xor_reduce   
#define shmem_int8_and_reduce       nvshmem_int8_and_reduce    
#define shmem_int8_max_reduce       nvshmem_int8_max_reduce    
#define shmem_int8_min_reduce       nvshmem_int8_min_reduce    
#define shmem_int8_or_reduce        nvshmem_int8_or_reduce     
#define shmem_int8_prod_reduce      nvshmem_int8_prod_reduce   
#define shmem_int8_sum_reduce       nvshmem_int8_sum_reduce    
#define shmem_int8_xor_reduce       nvshmem_int8_xor_reduce    
#define shmem_schar_max_reduce      nvshmem_schar_max_reduce   
#define shmem_schar_min_reduce      nvshmem_schar_min_reduce   
#define shmem_schar_prod_reduce     nvshmem_schar_prod_reduce  
#define shmem_schar_sum_reduce      nvshmem_schar_sum_reduce   
#define shmem_size_and_reduce       nvshmem_size_and_reduce    
#define shmem_size_max_reduce       nvshmem_size_max_reduce    
#define shmem_size_min_reduce       nvshmem_size_min_reduce    
#define shmem_size_or_reduce        nvshmem_size_or_reduce     
#define shmem_size_prod_reduce      nvshmem_size_prod_reduce   
#define shmem_size_sum_reduce       nvshmem_size_sum_reduce    
#define shmem_size_xor_reduce       nvshmem_size_xor_reduce    
#define shmem_uchar_and_reduce      nvshmem_uchar_and_reduce   
#define shmem_uchar_max_reduce      nvshmem_uchar_max_reduce   
#define shmem_uchar_min_reduce      nvshmem_uchar_min_reduce   
#define shmem_uchar_or_reduce       nvshmem_uchar_or_reduce    
#define shmem_uchar_prod_reduce     nvshmem_uchar_prod_reduce  
#define shmem_uchar_sum_reduce      nvshmem_uchar_sum_reduce   
#define shmem_uchar_xor_reduce      nvshmem_uchar_xor_reduce   
#define shmem_uint16_and_reduce     nvshmem_uint16_and_reduce  
#define shmem_uint16_max_reduce     nvshmem_uint16_max_reduce  
#define shmem_uint16_min_reduce     nvshmem_uint16_min_reduce  
#define shmem_uint16_or_reduce      nvshmem_uint16_or_reduce   
#define shmem_uint16_prod_reduce    nvshmem_uint16_prod_reduce 
#define shmem_uint16_sum_reduce     nvshmem_uint16_sum_reduce  
#define shmem_uint16_xor_reduce     nvshmem_uint16_xor_reduce  
#define shmem_uint32_and_reduce     nvshmem_uint32_and_reduce  
#define shmem_uint32_max_reduce     nvshmem_uint32_max_reduce  
#define shmem_uint32_min_reduce     nvshmem_uint32_min_reduce  
#define shmem_uint32_or_reduce      nvshmem_uint32_or_reduce   
#define shmem_uint32_prod_reduce    nvshmem_uint32_prod_reduce 
#define shmem_uint32_sum_reduce     nvshmem_uint32_sum_reduce  
#define shmem_uint32_xor_reduce     nvshmem_uint32_xor_reduce  
#define shmem_uint64_and_reduce     nvshmem_uint64_and_reduce  
#define shmem_uint64_max_reduce     nvshmem_uint64_max_reduce  
#define shmem_uint64_min_reduce     nvshmem_uint64_min_reduce  
#define shmem_uint64_or_reduce      nvshmem_uint64_or_reduce   
#define shmem_uint64_prod_reduce    nvshmem_uint64_prod_reduce 
#define shmem_uint64_sum_reduce     nvshmem_uint64_sum_reduce  
#define shmem_uint64_xor_reduce     nvshmem_uint64_xor_reduce  
#define shmem_uint8_and_reduce      nvshmem_uint8_and_reduce   
#define shmem_uint8_max_reduce      nvshmem_uint8_max_reduce   
#define shmem_uint8_min_reduce      nvshmem_uint8_min_reduce   
#define shmem_uint8_or_reduce       nvshmem_uint8_or_reduce    
#define shmem_uint8_prod_reduce     nvshmem_uint8_prod_reduce  
#define shmem_uint8_sum_reduce      nvshmem_uint8_sum_reduce   
#define shmem_uint8_xor_reduce      nvshmem_uint8_xor_reduce   

#define shmem_double_atomic_fetch           nvshmem_double_atomic_fetch
#define shmem_double_atomic_set             nvshmem_double_atomic_set
#define shmem_double_atomic_swap            nvshmem_double_atomic_swap
#define shmem_float_atomic_fetch            nvshmem_float_atomic_fetch
#define shmem_float_atomic_set              nvshmem_float_atomic_set
#define shmem_float_atomic_swap             nvshmem_float_atomic_swap
#define shmem_int32_atomic_add              nvshmem_int32_atomic_add
#define shmem_int32_atomic_and              nvshmem_int32_atomic_and
#define shmem_int32_atomic_compare_swap     nvshmem_int32_atomic_compare_swap
#define shmem_int32_atomic_fetch            nvshmem_int32_atomic_fetch
#define shmem_int32_atomic_fetch_add        nvshmem_int32_atomic_fetch_add
#define shmem_int32_atomic_fetch_and        nvshmem_int32_atomic_fetch_and
#define shmem_int32_atomic_fetch_inc        nvshmem_int32_atomic_fetch_inc
#define shmem_int32_atomic_fetch_or         nvshmem_int32_atomic_fetch_or
#define shmem_int32_atomic_fetch_xor        nvshmem_int32_atomic_fetch_xor
#define shmem_int32_atomic_inc              nvshmem_int32_atomic_inc
#define shmem_int32_atomic_or               nvshmem_int32_atomic_or
#define shmem_int32_atomic_set              nvshmem_int32_atomic_set
#define shmem_int32_atomic_swap             nvshmem_int32_atomic_swap
#define shmem_int32_atomic_xor              nvshmem_int32_atomic_xor
#define shmem_int64_atomic_add              nvshmem_int64_atomic_add
#define shmem_int64_atomic_and              nvshmem_int64_atomic_and
#define shmem_int64_atomic_compare_swap     nvshmem_int64_atomic_compare_swap
#define shmem_int64_atomic_fetch            nvshmem_int64_atomic_fetch
#define shmem_int64_atomic_fetch_add        nvshmem_int64_atomic_fetch_add
#define shmem_int64_atomic_fetch_and        nvshmem_int64_atomic_fetch_and
#define shmem_int64_atomic_fetch_inc        nvshmem_int64_atomic_fetch_inc
#define shmem_int64_atomic_fetch_or         nvshmem_int64_atomic_fetch_or
#define shmem_int64_atomic_fetch_xor        nvshmem_int64_atomic_fetch_xor
#define shmem_int64_atomic_inc              nvshmem_int64_atomic_inc
#define shmem_int64_atomic_or               nvshmem_int64_atomic_or
#define shmem_int64_atomic_set              nvshmem_int64_atomic_set
#define shmem_int64_atomic_swap             nvshmem_int64_atomic_swap
#define shmem_int64_atomic_xor              nvshmem_int64_atomic_xor
#define shmem_int_atomic_add                nvshmem_int_atomic_add
#define shmem_int_atomic_compare_swap       nvshmem_int_atomic_compare_swap
#define shmem_int_atomic_fetch              nvshmem_int_atomic_fetch
#define shmem_int_atomic_fetch_add          nvshmem_int_atomic_fetch_add
#define shmem_int_atomic_fetch_inc          nvshmem_int_atomic_fetch_inc
#define shmem_int_atomic_inc                nvshmem_int_atomic_inc
#define shmem_int_atomic_set                nvshmem_int_atomic_set
#define shmem_int_atomic_swap               nvshmem_int_atomic_swap
#define shmem_long_atomic_add               nvshmem_long_atomic_add
#define shmem_long_atomic_compare_swap      nvshmem_long_atomic_compare_swap
#define shmem_long_atomic_fetch             nvshmem_long_atomic_fetch
#define shmem_long_atomic_fetch_add         nvshmem_long_atomic_fetch_add
#define shmem_long_atomic_fetch_inc         nvshmem_long_atomic_fetch_inc
#define shmem_long_atomic_inc               nvshmem_long_atomic_inc
#define shmem_long_atomic_set               nvshmem_long_atomic_set
#define shmem_long_atomic_swap              nvshmem_long_atomic_swap
#define shmem_longlong_atomic_add           nvshmem_longlong_atomic_add
#define shmem_longlong_atomic_compare_swap  nvshmem_longlong_atomic_compare_swap
#define shmem_longlong_atomic_fetch         nvshmem_longlong_atomic_fetch
#define shmem_longlong_atomic_fetch_add     nvshmem_longlong_atomic_fetch_add
#define shmem_longlong_atomic_fetch_inc     nvshmem_longlong_atomic_fetch_inc
#define shmem_longlong_atomic_inc           nvshmem_longlong_atomic_inc
#define shmem_longlong_atomic_set           nvshmem_longlong_atomic_set
#define shmem_longlong_atomic_swap          nvshmem_longlong_atomic_swap
#define shmem_ptrdiff_atomic_add            nvshmem_ptrdiff_atomic_add
#define shmem_ptrdiff_atomic_compare_swap   nvshmem_ptrdiff_atomic_compare_swap
#define shmem_ptrdiff_atomic_fetch          nvshmem_ptrdiff_atomic_fetch
#define shmem_ptrdiff_atomic_fetch_add      nvshmem_ptrdiff_atomic_fetch_add
#define shmem_ptrdiff_atomic_fetch_inc      nvshmem_ptrdiff_atomic_fetch_inc
#define shmem_ptrdiff_atomic_inc            nvshmem_ptrdiff_atomic_inc
#define shmem_ptrdiff_atomic_set            nvshmem_ptrdiff_atomic_set
#define shmem_ptrdiff_atomic_swap           nvshmem_ptrdiff_atomic_swap
#define shmem_size_atomic_add               nvshmem_size_atomic_add
#define shmem_size_atomic_compare_swap      nvshmem_size_atomic_compare_swap
#define shmem_size_atomic_fetch             nvshmem_size_atomic_fetch
#define shmem_size_atomic_fetch_add         nvshmem_size_atomic_fetch_add
#define shmem_size_atomic_fetch_inc         nvshmem_size_atomic_fetch_inc
#define shmem_size_atomic_inc               nvshmem_size_atomic_inc
#define shmem_size_atomic_set               nvshmem_size_atomic_set
#define shmem_size_atomic_swap              nvshmem_size_atomic_swap
#define shmem_uint32_atomic_add             nvshmem_uint32_atomic_add
#define shmem_uint32_atomic_and             nvshmem_uint32_atomic_and
#define shmem_uint32_atomic_compare_swap    nvshmem_uint32_atomic_compare_swap
#define shmem_uint32_atomic_fetch           nvshmem_uint32_atomic_fetch
#define shmem_uint32_atomic_fetch_add       nvshmem_uint32_atomic_fetch_add
#define shmem_uint32_atomic_fetch_and       nvshmem_uint32_atomic_fetch_and
#define shmem_uint32_atomic_fetch_inc       nvshmem_uint32_atomic_fetch_inc
#define shmem_uint32_atomic_fetch_or        nvshmem_uint32_atomic_fetch_or
#define shmem_uint32_atomic_fetch_xor       nvshmem_uint32_atomic_fetch_xor
#define shmem_uint32_atomic_inc             nvshmem_uint32_atomic_inc
#define shmem_uint32_atomic_or              nvshmem_uint32_atomic_or
#define shmem_uint32_atomic_set             nvshmem_uint32_atomic_set
#define shmem_uint32_atomic_swap            nvshmem_uint32_atomic_swap
#define shmem_uint32_atomic_xor             nvshmem_uint32_atomic_xor
#define shmem_uint64_atomic_add             nvshmem_uint64_atomic_add
#define shmem_uint64_atomic_and             nvshmem_uint64_atomic_and
#define shmem_uint64_atomic_compare_swap    nvshmem_uint64_atomic_compare_swap
#define shmem_uint64_atomic_fetch           nvshmem_uint64_atomic_fetch
#define shmem_uint64_atomic_fetch_add       nvshmem_uint64_atomic_fetch_add
#define shmem_uint64_atomic_fetch_and       nvshmem_uint64_atomic_fetch_and
#define shmem_uint64_atomic_fetch_inc       nvshmem_uint64_atomic_fetch_inc
#define shmem_uint64_atomic_fetch_or        nvshmem_uint64_atomic_fetch_or
#define shmem_uint64_atomic_fetch_xor       nvshmem_uint64_atomic_fetch_xor
#define shmem_uint64_atomic_inc             nvshmem_uint64_atomic_inc
#define shmem_uint64_atomic_or              nvshmem_uint64_atomic_or
#define shmem_uint64_atomic_set             nvshmem_uint64_atomic_set
#define shmem_uint64_atomic_swap            nvshmem_uint64_atomic_swap
#define shmem_uint64_atomic_xor             nvshmem_uint64_atomic_xor
#define shmem_uint_atomic_add               nvshmem_uint_atomic_add
#define shmem_uint_atomic_and               nvshmem_uint_atomic_and
#define shmem_uint_atomic_compare_swap      nvshmem_uint_atomic_compare_swap
#define shmem_uint_atomic_fetch             nvshmem_uint_atomic_fetch
#define shmem_uint_atomic_fetch_add         nvshmem_uint_atomic_fetch_add
#define shmem_uint_atomic_fetch_and         nvshmem_uint_atomic_fetch_and
#define shmem_uint_atomic_fetch_inc         nvshmem_uint_atomic_fetch_inc
#define shmem_uint_atomic_fetch_or          nvshmem_uint_atomic_fetch_or
#define shmem_uint_atomic_fetch_xor         nvshmem_uint_atomic_fetch_xor
#define shmem_uint_atomic_inc               nvshmem_uint_atomic_inc
#define shmem_uint_atomic_or                nvshmem_uint_atomic_or
#define shmem_uint_atomic_set               nvshmem_uint_atomic_set
#define shmem_uint_atomic_swap              nvshmem_uint_atomic_swap
#define shmem_uint_atomic_xor               nvshmem_uint_atomic_xor
#define shmem_ulong_atomic_add              nvshmem_ulong_atomic_add
#define shmem_ulong_atomic_and              nvshmem_ulong_atomic_and
#define shmem_ulong_atomic_compare_swap     nvshmem_ulong_atomic_compare_swap
#define shmem_ulong_atomic_fetch            nvshmem_ulong_atomic_fetch
#define shmem_ulong_atomic_fetch_add        nvshmem_ulong_atomic_fetch_add
#define shmem_ulong_atomic_fetch_and        nvshmem_ulong_atomic_fetch_and
#define shmem_ulong_atomic_fetch_inc        nvshmem_ulong_atomic_fetch_inc
#define shmem_ulong_atomic_fetch_or         nvshmem_ulong_atomic_fetch_or
#define shmem_ulong_atomic_fetch_xor        nvshmem_ulong_atomic_fetch_xor
#define shmem_ulong_atomic_inc              nvshmem_ulong_atomic_inc
#define shmem_ulong_atomic_or               nvshmem_ulong_atomic_or
#define shmem_ulong_atomic_set              nvshmem_ulong_atomic_set
#define shmem_ulong_atomic_swap             nvshmem_ulong_atomic_swap
#define shmem_ulong_atomic_xor              nvshmem_ulong_atomic_xor
#define shmem_ulonglong_atomic_add          nvshmem_ulonglong_atomic_add
#define shmem_ulonglong_atomic_and          nvshmem_ulonglong_atomic_and
#define shmem_ulonglong_atomic_compare_swap nvshmem_ulonglong_atomic_compare_swap
#define shmem_ulonglong_atomic_fetch        nvshmem_ulonglong_atomic_fetch
#define shmem_ulonglong_atomic_fetch_add    nvshmem_ulonglong_atomic_fetch_add
#define shmem_ulonglong_atomic_fetch_and    nvshmem_ulonglong_atomic_fetch_and
#define shmem_ulonglong_atomic_fetch_inc    nvshmem_ulonglong_atomic_fetch_inc
#define shmem_ulonglong_atomic_fetch_or     nvshmem_ulonglong_atomic_fetch_or
#define shmem_ulonglong_atomic_fetch_xor    nvshmem_ulonglong_atomic_fetch_xor
#define shmem_ulonglong_atomic_inc          nvshmem_ulonglong_atomic_inc
#define shmem_ulonglong_atomic_or           nvshmem_ulonglong_atomic_or
#define shmem_ulonglong_atomic_set          nvshmem_ulonglong_atomic_set
#define shmem_ulonglong_atomic_swap         nvshmem_ulonglong_atomic_swap
#define shmem_ulonglong_atomic_xor          nvshmem_ulonglong_atomic_xor

#define shmem_char_p      nvshmem_char_p
#define shmem_double_p    nvshmem_double_p
#define shmem_float_p     nvshmem_float_p
#define shmem_int16_p     nvshmem_int16_p
#define shmem_int32_p     nvshmem_int32_p
#define shmem_int64_p     nvshmem_int64_p
#define shmem_int8_p      nvshmem_int8_p
#define shmem_int_p       nvshmem_int_p
#define shmem_long_p      nvshmem_long_p
#define shmem_longlong_p  nvshmem_longlong_p
#define shmem_ptrdiff_p   nvshmem_ptrdiff_p
#define shmem_schar_p     nvshmem_schar_p
#define shmem_short_p     nvshmem_short_p
#define shmem_size_p      nvshmem_size_p
#define shmem_uchar_p     nvshmem_uchar_p
#define shmem_uint16_p    nvshmem_uint16_p
#define shmem_uint32_p    nvshmem_uint32_p
#define shmem_uint64_p    nvshmem_uint64_p
#define shmem_uint8_p     nvshmem_uint8_p
#define shmem_uint_p      nvshmem_uint_p
#define shmem_ulong_p     nvshmem_ulong_p
#define shmem_ulonglong_p nvshmem_ulonglong_p
#define shmem_ushort_p    nvshmem_ushort_p

#define shmem_char_g      nvshmem_char_g
#define shmem_double_g    nvshmem_double_g
#define shmem_float_g     nvshmem_float_g
#define shmem_int16_g     nvshmem_int16_g
#define shmem_int32_g     nvshmem_int32_g
#define shmem_int64_g     nvshmem_int64_g
#define shmem_int8_g      nvshmem_int8_g
#define shmem_int_g       nvshmem_int_g
#define shmem_long_g      nvshmem_long_g
#define shmem_longlong_g  nvshmem_longlong_g
#define shmem_ptrdiff_g   nvshmem_ptrdiff_g
#define shmem_schar_g     nvshmem_schar_g
#define shmem_short_g     nvshmem_short_g
#define shmem_size_g      nvshmem_size_g
#define shmem_uchar_g     nvshmem_uchar_g
#define shmem_uint16_g    nvshmem_uint16_g
#define shmem_uint32_g    nvshmem_uint32_g
#define shmem_uint64_g    nvshmem_uint64_g
#define shmem_uint8_g     nvshmem_uint8_g
#define shmem_uint_g      nvshmem_uint_g
#define shmem_ulong_g     nvshmem_ulong_g
#define shmem_ulonglong_g nvshmem_ulonglong_g
#define shmem_ushort_g    nvshmem_ushort_g

#define shmem_char_put      nvshmem_char_put
#define shmem_double_put    nvshmem_double_put
#define shmem_float_put     nvshmem_float_put
#define shmem_int16_put     nvshmem_int16_put
#define shmem_int32_put     nvshmem_int32_put
#define shmem_int64_put     nvshmem_int64_put
#define shmem_int8_put      nvshmem_int8_put
#define shmem_int_put       nvshmem_int_put
#define shmem_long_put      nvshmem_long_put
#define shmem_longlong_put  nvshmem_longlong_put
#define shmem_ptrdiff_put   nvshmem_ptrdiff_put
#define shmem_schar_put     nvshmem_schar_put
#define shmem_short_put     nvshmem_short_put
#define shmem_size_put      nvshmem_size_put
#define shmem_uchar_put     nvshmem_uchar_put
#define shmem_uint16_put    nvshmem_uint16_put
#define shmem_uint32_put    nvshmem_uint32_put
#define shmem_uint64_put    nvshmem_uint64_put
#define shmem_uint8_put     nvshmem_uint8_put
#define shmem_uint_put      nvshmem_uint_put
#define shmem_ulong_put     nvshmem_ulong_put
#define shmem_ulonglong_put nvshmem_ulonglong_put
#define shmem_ushort_put    nvshmem_ushort_put

#define shmem_char_get      nvshmem_char_get
#define shmem_double_get    nvshmem_double_get
#define shmem_float_get     nvshmem_float_get
#define shmem_int16_get     nvshmem_int16_get
#define shmem_int32_get     nvshmem_int32_get
#define shmem_int64_get     nvshmem_int64_get
#define shmem_int8_get      nvshmem_int8_get
#define shmem_int_get       nvshmem_int_get
#define shmem_long_get      nvshmem_long_get
#define shmem_longlong_get  nvshmem_longlong_get
#define shmem_ptrdiff_get   nvshmem_ptrdiff_get
#define shmem_schar_get     nvshmem_schar_get
#define shmem_short_get     nvshmem_short_get
#define shmem_size_get      nvshmem_size_get
#define shmem_uchar_get     nvshmem_uchar_get
#define shmem_uint16_get    nvshmem_uint16_get
#define shmem_uint32_get    nvshmem_uint32_get
#define shmem_uint64_get    nvshmem_uint64_get
#define shmem_uint8_get     nvshmem_uint8_get
#define shmem_uint_get      nvshmem_uint_get
#define shmem_ulong_get     nvshmem_ulong_get
#define shmem_ulonglong_get nvshmem_ulonglong_get
#define shmem_ushort_get    nvshmem_ushort_get

#define shmem_char_iput      nvshmem_char_iput
#define shmem_double_iput    nvshmem_double_iput
#define shmem_float_iput     nvshmem_float_iput
#define shmem_int16_iput     nvshmem_int16_iput
#define shmem_int32_iput     nvshmem_int32_iput
#define shmem_int64_iput     nvshmem_int64_iput
#define shmem_int8_iput      nvshmem_int8_iput
#define shmem_int_iput       nvshmem_int_iput
#define shmem_long_iput      nvshmem_long_iput
#define shmem_longlong_iput  nvshmem_longlong_iput
#define shmem_ptrdiff_iput   nvshmem_ptrdiff_iput
#define shmem_schar_iput     nvshmem_schar_iput
#define shmem_short_iput     nvshmem_short_iput
#define shmem_size_iput      nvshmem_size_iput
#define shmem_uchar_iput     nvshmem_uchar_iput
#define shmem_uint16_iput    nvshmem_uint16_iput
#define shmem_uint32_iput    nvshmem_uint32_iput
#define shmem_uint64_iput    nvshmem_uint64_iput
#define shmem_uint8_iput     nvshmem_uint8_iput
#define shmem_uint_iput      nvshmem_uint_iput
#define shmem_ulong_iput     nvshmem_ulong_iput
#define shmem_ulonglong_iput nvshmem_ulonglong_iput
#define shmem_ushort_iput    nvshmem_ushort_iput

#define shmem_char_iget      nvshmem_char_iget
#define shmem_double_iget    nvshmem_double_iget
#define shmem_float_iget     nvshmem_float_iget
#define shmem_int16_iget     nvshmem_int16_iget
#define shmem_int32_iget     nvshmem_int32_iget
#define shmem_int64_iget     nvshmem_int64_iget
#define shmem_int8_iget      nvshmem_int8_iget
#define shmem_int_iget       nvshmem_int_iget
#define shmem_long_iget      nvshmem_long_iget
#define shmem_longlong_iget  nvshmem_longlong_iget
#define shmem_ptrdiff_iget   nvshmem_ptrdiff_iget
#define shmem_schar_iget     nvshmem_schar_iget
#define shmem_short_iget     nvshmem_short_iget
#define shmem_size_iget      nvshmem_size_iget
#define shmem_uchar_iget     nvshmem_uchar_iget
#define shmem_uint16_iget    nvshmem_uint16_iget
#define shmem_uint32_iget    nvshmem_uint32_iget
#define shmem_uint64_iget    nvshmem_uint64_iget
#define shmem_uint8_iget     nvshmem_uint8_iget
#define shmem_uint_iget      nvshmem_uint_iget
#define shmem_ulong_iget     nvshmem_ulong_iget
#define shmem_ulonglong_iget nvshmem_ulonglong_iget
#define shmem_ushort_iget    nvshmem_ushort_iget

#define shmem_char_get_nbi      nvshmem_char_get_nbi
#define shmem_char_put_nbi      nvshmem_char_put_nbi
#define shmem_double_get_nbi    nvshmem_double_get_nbi
#define shmem_double_put_nbi    nvshmem_double_put_nbi
#define shmem_float_get_nbi     nvshmem_float_get_nbi
#define shmem_float_put_nbi     nvshmem_float_put_nbi
#define shmem_get128_nbi        nvshmem_get128_nbi
#define shmem_get16_nbi         nvshmem_get16_nbi
#define shmem_get32_nbi         nvshmem_get32_nbi
#define shmem_get64_nbi         nvshmem_get64_nbi
#define shmem_get8_nbi          nvshmem_get8_nbi
#define shmem_int16_get_nbi     nvshmem_int16_get_nbi
#define shmem_int16_put_nbi     nvshmem_int16_put_nbi
#define shmem_int32_get_nbi     nvshmem_int32_get_nbi
#define shmem_int32_put_nbi     nvshmem_int32_put_nbi
#define shmem_int64_get_nbi     nvshmem_int64_get_nbi
#define shmem_int64_put_nbi     nvshmem_int64_put_nbi
#define shmem_int8_get_nbi      nvshmem_int8_get_nbi
#define shmem_int8_put_nbi      nvshmem_int8_put_nbi
#define shmem_int_get_nbi       nvshmem_int_get_nbi
#define shmem_int_put_nbi       nvshmem_int_put_nbi
#define shmem_long_get_nbi      nvshmem_long_get_nbi
#define shmem_long_put_nbi      nvshmem_long_put_nbi
#define shmem_longlong_get_nbi  nvshmem_longlong_get_nbi
#define shmem_longlong_put_nbi  nvshmem_longlong_put_nbi
#define shmem_ptrdiff_get_nbi   nvshmem_ptrdiff_get_nbi
#define shmem_ptrdiff_put_nbi   nvshmem_ptrdiff_put_nbi
#define shmem_put128_nbi        nvshmem_put128_nbi
#define shmem_put16_nbi         nvshmem_put16_nbi
#define shmem_put32_nbi         nvshmem_put32_nbi
#define shmem_put64_nbi         nvshmem_put64_nbi
#define shmem_put8_nbi          nvshmem_put8_nbi
#define shmem_schar_get_nbi     nvshmem_schar_get_nbi
#define shmem_schar_put_nbi     nvshmem_schar_put_nbi
#define shmem_short_get_nbi     nvshmem_short_get_nbi
#define shmem_short_put_nbi     nvshmem_short_put_nbi
#define shmem_size_get_nbi      nvshmem_size_get_nbi
#define shmem_size_put_nbi      nvshmem_size_put_nbi
#define shmem_uchar_get_nbi     nvshmem_uchar_get_nbi
#define shmem_uchar_put_nbi     nvshmem_uchar_put_nbi
#define shmem_uint16_get_nbi    nvshmem_uint16_get_nbi
#define shmem_uint16_put_nbi    nvshmem_uint16_put_nbi
#define shmem_uint32_get_nbi    nvshmem_uint32_get_nbi
#define shmem_uint32_put_nbi    nvshmem_uint32_put_nbi
#define shmem_uint64_get_nbi    nvshmem_uint64_get_nbi
#define shmem_uint64_put_nbi    nvshmem_uint64_put_nbi
#define shmem_uint8_get_nbi     nvshmem_uint8_get_nbi
#define shmem_uint8_put_nbi     nvshmem_uint8_put_nbi
#define shmem_uint_get_nbi      nvshmem_uint_get_nbi
#define shmem_uint_put_nbi      nvshmem_uint_put_nbi
#define shmem_ulong_get_nbi     nvshmem_ulong_get_nbi
#define shmem_ulong_put_nbi     nvshmem_ulong_put_nbi
#define shmem_ulonglong_get_nbi nvshmem_ulonglong_get_nbi
#define shmem_ulonglong_put_nbi nvshmem_ulonglong_put_nbi
#define shmem_ushort_get_nbi    nvshmem_ushort_get_nbi
#define shmem_ushort_put_nbi    nvshmem_ushort_put_nbi

#define shmem_get128     nvshmem_get128
#define shmem_get16      nvshmem_get16
#define shmem_get32      nvshmem_get32
#define shmem_get64      nvshmem_get64
#define shmem_get8       nvshmem_get8
#define shmem_iget128    nvshmem_iget128
#define shmem_iget16     nvshmem_iget16
#define shmem_iget32     nvshmem_iget32
#define shmem_iget64     nvshmem_iget64
#define shmem_iget8      nvshmem_iget8
#define shmem_iput128    nvshmem_iput128
#define shmem_iput16     nvshmem_iput16
#define shmem_iput32     nvshmem_iput32
#define shmem_iput64     nvshmem_iput64
#define shmem_iput8      nvshmem_iput8
#define shmem_put128     nvshmem_put128
#define shmem_put16      nvshmem_put16
#define shmem_put32      nvshmem_put32
#define shmem_put64      nvshmem_put64
#define shmem_put8       nvshmem_put8

#define shmem_getmem     nvshmem_getmem
#define shmem_getmem_nbi nvshmem_getmem_nbi
#define shmem_putmem     nvshmem_putmem
#define shmem_putmem_nbi nvshmem_putmem_nbi

typedef int* shmem_ctx_t;
int one = 1; // TODO: 
const shmem_ctx_t SHMEM_CTX_DEFAULT = &one;

//
// compatibility
//

static int shmem_team_get_config(shmem_team_t team, long config_mask, shmem_team_config_t* config)
{
  (void)config_mask;
  nvshmem_team_get_config(team, config);
  return 0;
}

#define PySHMEM_HAVE_shmem_broadcastmem 1
static int shmem_broadcastmem(shmem_team_t team, void* dest, const void* source, size_t nelems, int PE_root)
{
  return nvshmem_uchar_broadcast(team, (unsigned char*)dest, (unsigned char*)source, nelems, PE_root);
}

#define PySHMEM_HAVE_shmem_collectmem 1
static int shmem_fcollectmem(shmem_team_t team, void* dest, const void* source, size_t nelems)
{
  return nvshmem_uchar_fcollect(team, (unsigned char*)dest, (unsigned char*)source, nelems);
}

#define PySHMEM_HAVE_shmem_alltoallmem 1
static int shmem_alltoallmem(shmem_team_t team, void* dest, const void* source, size_t nelems)
{
  return nvshmem_uchar_alltoall(team, (unsigned char*)dest, (unsigned char*)source, nelems);
}

static void shmem_longdouble_put(long double* target, const long double* source, size_t len, int pe)
{
  nvshmem_put128(target, source, len, pe);
}

static void shmem_longdouble_get(long double* target, const long double* source, size_t len, int pe)
{
  nvshmem_get128(target, source, len, pe);
}

static void shmem_longdouble_p(long double* addr, long double value, int pe)
{
  nvshmem_put128(addr, &value, 1, pe);
}

static long double shmem_longdouble_g(const long double* addr, int pe)
{
  long double val;
  nvshmem_get128(&val, addr, 1, pe);
  return val;
}

static void shmem_longdouble_iput(long double* target, const long double* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe)
{
  nvshmem_iput128(target, source, tst, sst, len, pe);
}

static void shmem_longdouble_iget(long double* target, const long double* source, ptrdiff_t tst, ptrdiff_t sst, size_t len, int pe)
{
  nvshmem_iget128(target, source, tst, sst, len, pe);
}

static void shmem_longdouble_get_nbi(long double* dest, const long double* source, size_t nelems, int pe)
{
  nvshmem_get128_nbi(dest, source, nelems, pe);
}

static void shmem_longdouble_put_nbi(long double* dest, const long double* source, size_t nelems, int pe)
{
  nvshmem_put128_nbi(dest, source, nelems, pe);
}

static void* shmem_realloc(void* ptr, size_t size)
{
  if (ptr == NULL) {
    return shmem_malloc(size);
  }
  if (size == 0) {
    free(ptr);
    return NULL;
  }
  return NULL;
}

static int shmem_pe_accessible(int pe)
{
  (void)pe;
  return 1;
}

static int shmem_addr_accessible(const void* addr, int pe)
{
  (void)addr; (void)pe;
  return 1;
}

static int shmem_complexf_sum_reduce(shmem_team_t team, float _Complex* dest, const float _Complex* source, size_t nreduce) \
{                                                                                                                           \
  return nvshmem_float_sum_reduce(team,(float*)dest,(float*)source,2*nreduce);
}

static int shmem_complexd_sum_reduce(shmem_team_t team, double _Complex* dest, const double _Complex* source, size_t nreduce) \
{                                                                                                                           \
  return nvshmem_double_sum_reduce(team,(double*)dest,(double*)source,2*nreduce);
}

#define PySHMEM_REDUCE(OP)                                                                                            \
  static int shmem_ptrdiff_##OP##_reduce(shmem_team_t team, ptrdiff_t* dest, const ptrdiff_t* source, size_t nreduce) \
  {                                                                                                                   \
    switch (sizeof(ptrdiff_t)) {                                                                                      \
      case (4): return nvshmem_int32_sum_reduce(team, (int32_t*)dest, (int32_t*)source, nreduce);                     \
      case (8): return nvshmem_int64_sum_reduce(team, (int64_t*)dest, (int64_t*)source, nreduce);                     \
    }                                                                                                                 \
    return PySHMEM_UNAVAILABLE;                                                                                       \
}
PySHMEM_REDUCE(min)
PySHMEM_REDUCE(max)
PySHMEM_REDUCE(prod)
PySHMEM_REDUCE(sum)

static void shmem_ctx_fence(shmem_ctx_t ctx)
{
  if (ctx == SHMEM_CTX_DEFAULT) {
    shmem_fence();
  } else {
    PySHMEM_UNAVAILABLE;
  }
}
static void shmem_ctx_quiet(shmem_ctx_t ctx)
{
  if (ctx == SHMEM_CTX_DEFAULT) {
    shmem_quiet();
  } else {
    PySHMEM_UNAVAILABLE;
  }
}

static int shmem_ctx_get_team(shmem_ctx_t ctx, shmem_team_t* team)
{
  if (ctx == SHMEM_CTX_DEFAULT) {
    team = SHMEM_TEAM_WORLD;
    return 0;
  } 
  // else if (ctx == SHMEM_CTX_INVALID) {
  //   team = (shmem_team_t*)SHMEM_TEAM_INVALID;
  //   return 1;
  // }
  return PySHMEM_UNAVAILABLE;
}


//
// not implemented
//


static void    shmem_set_lock           (long *lock)                                                       { (void)lock; (void)PySHMEM_UNAVAILABLE; }                
static int     shmem_test_lock          (long *lock)                                                       { (void)lock; return PySHMEM_UNAVAILABLE; }
static void    shmem_clear_lock         (long *lock)                                                       { (void)lock; (void)PySHMEM_UNAVAILABLE; }                

static int     shmem_global_exit        (int status)                     { return PySHMEM_UNAVAILABLE; } // TODO: compat / abort+printf / nv + fail
static int     shmem_ctx_create         (long options, shmem_ctx_t *ctx) { return PySHMEM_UNAVAILABLE; } // TODO: see compatiblity below -> return DEFAULT context
static void    shmem_ctx_destroy        (shmem_ctx_t ctx)                { (void)ctx; (void)PySHMEM_UNAVAILABLE; } // TODO: see compatiblity below -> return DEFAULT context
static int     shmem_team_create_ctx    (shmem_team_t team, long options, shmem_ctx_t *ctx) { return PySHMEM_UNAVAILABLE; } // TODO: see compatiblity below -> return DEFAULT context

static
int shmem_collectmem(shmem_team_t team, void* dest, const void* source, size_t nelems)
{
  (void)team; (void)dest; (void)source; (void)nelems;
  return PySHMEM_UNAVAILABLE;
}

#define PySHMEM_WAIT_UNTIL(TYPENAME,TYPE)                                 \
static                                                                    \
void shmem_##TYPENAME##_wait_until(TYPE *ivar, int cmp, TYPE cmp_value)   \
{                                                                         \
  /* 0 being the CUDA default stream */                                   \
  nvshmemx_##TYPENAME##_wait_until_on_stream(ivar,cmp,cmp_value,0);       \
}
PySHMEM_WAIT_UNTIL(int32,     int32_t) 
PySHMEM_WAIT_UNTIL(ulonglong, unsigned long long)
PySHMEM_WAIT_UNTIL(ulong,     unsigned long)
PySHMEM_WAIT_UNTIL(uint,      unsigned int)
PySHMEM_WAIT_UNTIL(uint64,    uint64_t)
PySHMEM_WAIT_UNTIL(uint32,    uint32_t)
PySHMEM_WAIT_UNTIL(size,      size_t)
PySHMEM_WAIT_UNTIL(ptrdiff,   ptrdiff_t)
PySHMEM_WAIT_UNTIL(longlong,  long long)
PySHMEM_WAIT_UNTIL(long,      long)
PySHMEM_WAIT_UNTIL(int,       int)
PySHMEM_WAIT_UNTIL(int64,     int64_t)

#define PySHMEM_TEST(TYPENAME,TYPE)                               \
static                                                            \
int shmem_##TYPENAME##_test(TYPE *ivar, int cmp, TYPE cmp_value)  \
{                                                                 \
  /* FIXME: Abort. Also ask NVIDIA - those APIs should exist */   \
  (void)ivar; (void)cmp; (void)cmp_value;                         \
  return PySHMEM_UNAVAILABLE;                                     \
}
PySHMEM_TEST(int32,     int32_t)
PySHMEM_TEST(ulonglong, unsigned long long)
PySHMEM_TEST(ulong,     unsigned long)
PySHMEM_TEST(uint,      unsigned int)
PySHMEM_TEST(uint64,    uint64_t)
PySHMEM_TEST(uint32,    uint32_t)
PySHMEM_TEST(size,      size_t)
PySHMEM_TEST(ptrdiff,   ptrdiff_t)
PySHMEM_TEST(longlong,  long long)
PySHMEM_TEST(long,      long)
PySHMEM_TEST(int,       int)
PySHMEM_TEST(int64,     int64_t)


#define PySHMEM_REDUCE_UNAVAL(TYPENAME,TYPE,OP)                                                         \
static                                                                                                  \
int shmem_##TYPENAME##_##OP##_reduce(shmem_team_t team, TYPE *dest, const TYPE *source, size_t nreduce) \
{                                                                                                       \
  (void)team; (void)dest; (void)source; (void)nreduce;                                                  \
  return PySHMEM_UNAVAILABLE;                                                                           \
}
PySHMEM_REDUCE_UNAVAL(longdouble, long double,     sum)   // PySHMEM_REDUCE_FAIL_OP
PySHMEM_REDUCE_UNAVAL(longdouble, long double,     prod)  // PySHMEM_REDUCE_FAIL_OP 
PySHMEM_REDUCE_UNAVAL(longdouble, long double,     min)   // PySHMEM_REDUCE_FAIL_OP
PySHMEM_REDUCE_UNAVAL(longdouble, long double,     max)   // PySHMEM_REDUCE_FAIL_OP
PySHMEM_REDUCE_UNAVAL(complexf,   float _Complex,  prod)  // PySHMEM_REDUCE_FAIL_OP 
PySHMEM_REDUCE_UNAVAL(complexd,   double _Complex, prod)  // PySHMEM_REDUCE_FAIL_OP 

static
void shmem_alltoalls32(void *target, const void *source, ptrdiff_t dst, ptrdiff_t sst,
                       size_t nelems, int PE_start, int logPE_stride, int PE_size, long *pSync)
{
  (void)target; (void)source; (void)dst; (void)sst; (void)nelems; (void)PE_start; (void)logPE_stride; (void)PE_size; (void)pSync;
  PySHMEM_UNAVAILABLE;
}

static
void shmem_alltoalls64(void *target, const void *source, ptrdiff_t dst, ptrdiff_t sst,
                       size_t nelems, int PE_start, int logPE_stride, int PE_size, long *pSync)
{
  (void)target; (void)source; (void)dst; (void)sst; (void)nelems; (void)PE_start; (void)logPE_stride; (void)PE_size; (void)pSync;
  PySHMEM_UNAVAILABLE;
}

//
// shmem_ctx_*
//

#define PySHMEM_CTX_PG(TYPENAME,TYPE)                                                                                                       \
static                                                                                                                                      \
void   shmem_ctx_##TYPENAME##_p(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe)                                                            \
{                                                                                                                                           \
  /* TODO: unless ctx==CTX_DEFAULT? */                                                                                                      \
  (void)ctx; (void)dest; (void)value; (void)pe;                                                                                             \
  (void)PySHMEM_UNAVAILABLE;                                                                                                                \
}                                                                                                                                           \
static                                                                                                                                      \
TYPE shmem_ctx_##TYPENAME##_g(shmem_ctx_t ctx, const TYPE *source, int pe)                                                                  \
{                                                                                                                                           \
  (void)ctx; (void)source; (void)pe;                                                                                                        \
  return (TYPE)PySHMEM_UNAVAILABLE;                                                                                                         \
}                                                                                                                                           \
static                                                                                                                                      \
void shmem_ctx_##TYPENAME##_put(shmem_ctx_t ctx, TYPE *dest, const TYPE *source, size_t count, int pe)                                      \
{                                                                                                                                           \
  (void)ctx; (void)dest; (void)source; (void)count; (void)pe;                                                                               \
  (void)PySHMEM_UNAVAILABLE;                                                                                                                \
}                                                                                                                                           \
static                                                                                                                                      \
void shmem_ctx_##TYPENAME##_get(shmem_ctx_t ctx, TYPE *dest, const TYPE *source, size_t count, int pe)                                      \
{                                                                                                                                           \
  (void)ctx; (void)dest; (void)source; (void)count; (void)pe;                                                                               \
  (void)PySHMEM_UNAVAILABLE;                                                                                                                \
}                                                                                                                                           \
static                                                                                                                                      \
void shmem_ctx_##TYPENAME##_iput     (shmem_ctx_t ctx, TYPE *dest, const TYPE *source, ptrdiff_t dst, ptrdiff_t sst, size_t count, int pe)  \
{                                                                                                                                           \
  (void)ctx; (void)dest; (void)source; (void)dst; (void)sst; (void)count; (void)pe;                                                         \
  (void)PySHMEM_UNAVAILABLE;                                                                                                                \
}                                                                                                                                           \
static                                                                                                                                      \
void shmem_ctx_##TYPENAME##_iget     (shmem_ctx_t ctx, TYPE *dest, const TYPE *source, ptrdiff_t dst, ptrdiff_t sst, size_t count, int pe)  \
{                                                                                                                                           \
  (void)ctx; (void)dest; (void)source; (void)dst; (void)sst; (void)count; (void)pe;                                                         \
  (void)PySHMEM_UNAVAILABLE;                                                                                                                \
}                                                                                                                                           \
static                                                                                                                                      \
void shmem_ctx_##TYPENAME##_put_nbi  (shmem_ctx_t ctx, TYPE *dest, const TYPE *source, size_t count, int pe)                                \
{                                                                                                                                           \
  (void)ctx; (void)dest; (void)source; (void)count; (void)pe;                                                                               \
  (void)PySHMEM_UNAVAILABLE;                                                                                                                \
}                                                                                                                                           \
static                                                                                                                                      \
void shmem_ctx_##TYPENAME##_get_nbi  (shmem_ctx_t ctx, TYPE *dest, const TYPE *source, size_t count, int pe)                                \
{                                                                                                                                           \
  (void)ctx; (void)dest; (void)source; (void)count; (void)pe;                                                                               \
  (void)PySHMEM_UNAVAILABLE;                                                                                                                \
}
PySHMEM_CTX_PG(ulonglong, unsigned long long)
PySHMEM_CTX_PG(ulong,     unsigned long)
PySHMEM_CTX_PG(uint32,    uint32_t)
PySHMEM_CTX_PG(uint64,    uint64_t)
PySHMEM_CTX_PG(uchar,    unsigned char)
PySHMEM_CTX_PG(uint,      unsigned int)
PySHMEM_CTX_PG(uint16,    uint16_t)
PySHMEM_CTX_PG(uint8,    uint8_t)
PySHMEM_CTX_PG(size,      size_t)
PySHMEM_CTX_PG(ptrdiff,   ptrdiff_t)
PySHMEM_CTX_PG(short,   short)
PySHMEM_CTX_PG(long,   long)
PySHMEM_CTX_PG(longlong,   long long)
PySHMEM_CTX_PG(longdouble,   long double)
PySHMEM_CTX_PG(schar, signed char)
PySHMEM_CTX_PG(int, int)
PySHMEM_CTX_PG(int8,     int8_t)
PySHMEM_CTX_PG(int16,     int16_t)
PySHMEM_CTX_PG(int32,     int32_t)
PySHMEM_CTX_PG(int64,     int64_t)
PySHMEM_CTX_PG(float,float)
PySHMEM_CTX_PG(char,char)
PySHMEM_CTX_PG(double,double)
PySHMEM_CTX_PG(ushort, unsigned short)

#define PySHMEM_CTX_MEM(RMA,NBI)                                                                        \
static                                                                                                  \
void   shmem_ctx_##RMA##mem##NBI(shmem_ctx_t ctx, void *dest, const void *source, size_t count, int pe) \
{                                                                                                       \
  (void)ctx; (void)dest; (void)source; (void)count; (void)pe;                                           \
  (void)PySHMEM_UNAVAILABLE;                                                                            \
} 
PySHMEM_CTX_MEM(put,_nbi)
PySHMEM_CTX_MEM(get,_nbi)
PySHMEM_CTX_MEM(put,)
PySHMEM_CTX_MEM(get,)

#define PySHMEM_CTX_SIZE(RMA,SIZE,NBI)                                                                  \
static                                                                                                  \
void shmem_ctx_##RMA##SIZE##NBI(shmem_ctx_t ctx, void *dest, const void *source, size_t count, int pe)  \
{                                                                                                       \
  (void)ctx; (void)dest; (void)source; (void)count; (void)pe;                                           \
  (void)PySHMEM_UNAVAILABLE;                                                                            \
} 
PySHMEM_CTX_SIZE(put,8,  _nbi)
PySHMEM_CTX_SIZE(put,16, _nbi)
PySHMEM_CTX_SIZE(put,32, _nbi)
PySHMEM_CTX_SIZE(put,64, _nbi)
PySHMEM_CTX_SIZE(put,128,_nbi)
PySHMEM_CTX_SIZE(get,8,  _nbi)
PySHMEM_CTX_SIZE(get,16, _nbi)
PySHMEM_CTX_SIZE(get,32, _nbi)
PySHMEM_CTX_SIZE(get,64, _nbi)
PySHMEM_CTX_SIZE(get,128,_nbi)
PySHMEM_CTX_SIZE(put,8,  )
PySHMEM_CTX_SIZE(put,16, )
PySHMEM_CTX_SIZE(put,32, )
PySHMEM_CTX_SIZE(put,64, )
PySHMEM_CTX_SIZE(put,128,)
PySHMEM_CTX_SIZE(get,8,  )
PySHMEM_CTX_SIZE(get,16, )
PySHMEM_CTX_SIZE(get,32, )
PySHMEM_CTX_SIZE(get,64, )
PySHMEM_CTX_SIZE(get,128,)

#define PySHMEM_CTX_iSIZE(RMA,SIZE)                                                                                               \
static                                                                                                                            \
void shmem_ctx_i##RMA##SIZE(shmem_ctx_t ctx, void *dest, const void *source, ptrdiff_t dst, ptrdiff_t sst, size_t count, int pe)  \
{                                                                                                                                 \
  (void)ctx; (void)dest; (void)source; (void)dst; (void)sst; (void)count; (void)pe;                                               \
  (void)PySHMEM_UNAVAILABLE;                                                                                                      \
} 
PySHMEM_CTX_iSIZE(put,8  )
PySHMEM_CTX_iSIZE(put,16 )
PySHMEM_CTX_iSIZE(put,32 )
PySHMEM_CTX_iSIZE(put,64 )
PySHMEM_CTX_iSIZE(put,128)
PySHMEM_CTX_iSIZE(get,8  )
PySHMEM_CTX_iSIZE(get,16 )
PySHMEM_CTX_iSIZE(get,32 )
PySHMEM_CTX_iSIZE(get,64 )
PySHMEM_CTX_iSIZE(get,128)

#define PySHMEM_CTX_AMO_BIT(TYPENAME,TYPE,OP)                                                   \
static                                                                                          \
TYPE shmem_ctx_##TYPENAME##_atomic_fetch_##OP(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe)  \
{                                                                                               \
  (void)ctx; (void)dest; (void)value; (void)pe;                                                 \
  return (TYPE)PySHMEM_UNAVAILABLE;                                                             \
}                                                                                               \
static                                                                                          \
void shmem_ctx_##TYPENAME##_atomic_##OP(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe)        \
{                                                                                               \
  (void)ctx; (void)dest; (void)value; (void)pe;                                                 \
  (void)PySHMEM_UNAVAILABLE;                                                                    \
}

PySHMEM_CTX_AMO_BIT(uint,     unsigned int        ,and)
PySHMEM_CTX_AMO_BIT(ulong,    unsigned long       ,and)
PySHMEM_CTX_AMO_BIT(ulonglong,unsigned long long  ,and)
PySHMEM_CTX_AMO_BIT(int32,    int32_t             ,and)
PySHMEM_CTX_AMO_BIT(int64,    int64_t             ,and)
PySHMEM_CTX_AMO_BIT(uint32,   uint32_t            ,and)
PySHMEM_CTX_AMO_BIT(uint64,   uint64_t            ,and)

PySHMEM_CTX_AMO_BIT(uint,     unsigned int        ,or)
PySHMEM_CTX_AMO_BIT(ulong,    unsigned long       ,or)
PySHMEM_CTX_AMO_BIT(ulonglong,unsigned long long  ,or)
PySHMEM_CTX_AMO_BIT(int32,    int32_t             ,or)
PySHMEM_CTX_AMO_BIT(int64,    int64_t             ,or)
PySHMEM_CTX_AMO_BIT(uint32,   uint32_t            ,or)
PySHMEM_CTX_AMO_BIT(uint64,   uint64_t            ,or)

PySHMEM_CTX_AMO_BIT(uint,     unsigned int        ,xor)
PySHMEM_CTX_AMO_BIT(ulong,    unsigned long       ,xor)
PySHMEM_CTX_AMO_BIT(ulonglong,unsigned long long  ,xor)
PySHMEM_CTX_AMO_BIT(int32,    int32_t             ,xor)
PySHMEM_CTX_AMO_BIT(int64,    int64_t             ,xor)
PySHMEM_CTX_AMO_BIT(uint32,   uint32_t            ,xor)
PySHMEM_CTX_AMO_BIT(uint64,   uint64_t            ,xor)

#define PySHMEM_CTX_AMO_STD(TYPENAME,TYPE)                                                                  \
static                                                                                                      \
TYPE shmem_ctx_##TYPENAME##_atomic_fetch_add   (shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe)            \
{                                                                                                           \
  (void)ctx; (void)dest; (void)value; (void)pe;                                                             \
  return (TYPE)PySHMEM_UNAVAILABLE;                                                                         \
}                                                                                                           \
static                                                                                                      \
void shmem_ctx_##TYPENAME##_atomic_add           (shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe)          \
{                                                                                                           \
  (void)ctx; (void)dest; (void)value; (void)pe;                                                             \
  (void)PySHMEM_UNAVAILABLE;                                                                                \
}                                                                                                           \
static                                                                                                      \
TYPE shmem_ctx_##TYPENAME##_atomic_compare_swap(shmem_ctx_t ctx, TYPE *dest, TYPE cond, TYPE value, int pe) \
{                                                                                                           \
  (void)ctx; (void)dest; (void)cond; (void)value; (void)pe;                                                 \
  return (TYPE)PySHMEM_UNAVAILABLE;                                                                         \
}                                                                                                           \
static                                                                                                      \
TYPE shmem_ctx_##TYPENAME##_atomic_fetch_inc   (shmem_ctx_t ctx, TYPE *dest, int pe)                        \
{                                                                                                           \
  (void)ctx; (void)dest; (void)pe;                                                                          \
  return (TYPE)PySHMEM_UNAVAILABLE;                                                                         \
}                                                                                                           \
static                                                                                                      \
void shmem_ctx_##TYPENAME##_atomic_inc     (shmem_ctx_t ctx, TYPE *dest, int pe)                            \
{                                                                                                           \
  (void)ctx; (void)dest; (void)pe;                                                                          \
  (void)PySHMEM_UNAVAILABLE;                                                                                \
}
PySHMEM_CTX_AMO_STD(uint,     unsigned int      )
PySHMEM_CTX_AMO_STD(ulong,    unsigned long     )
PySHMEM_CTX_AMO_STD(ulonglong,unsigned long long)
PySHMEM_CTX_AMO_STD(int32,    int32_t           )
PySHMEM_CTX_AMO_STD(int64,    int64_t           )
PySHMEM_CTX_AMO_STD(uint32,   uint32_t          )
PySHMEM_CTX_AMO_STD(uint64,   uint64_t          )
PySHMEM_CTX_AMO_STD(int,      int               )
PySHMEM_CTX_AMO_STD(ptrdiff,  ptrdiff_t         )
PySHMEM_CTX_AMO_STD(size,     size_t            )
PySHMEM_CTX_AMO_STD(long,     long              )
PySHMEM_CTX_AMO_STD(longlong, long long         )

#define PySHMEM_CTX_AMO_EXT(TYPENAME,TYPE)                                               \
TYPE shmem_ctx_##TYPENAME##_atomic_fetch(shmem_ctx_t ctx, const TYPE *source, int pe)    \
{                                                                                        \
  (void)ctx; (void)source; (void)pe;                                                     \
  return (TYPE)PySHMEM_UNAVAILABLE;                                                      \
}                                                                                        \
void shmem_ctx_##TYPENAME##_atomic_set(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe)  \
{                                                                                        \
  (void)ctx; (void)dest; (void)value; (void)pe;                                          \
}                                                                                        \
TYPE shmem_ctx_##TYPENAME##_atomic_swap(shmem_ctx_t ctx, TYPE *dest, TYPE value, int pe) \
{                                                                                        \
  (void)ctx; (void)dest; (void)value; (void)pe;                                          \
  return (TYPE)PySHMEM_UNAVAILABLE;                                                      \
}

// std + float,double
PySHMEM_CTX_AMO_EXT(uint,     unsigned int      )
PySHMEM_CTX_AMO_EXT(ulong,    unsigned long     )
PySHMEM_CTX_AMO_EXT(ulonglong,unsigned long long)
PySHMEM_CTX_AMO_EXT(int32,    int32_t           )
PySHMEM_CTX_AMO_EXT(int64,    int64_t           )
PySHMEM_CTX_AMO_EXT(uint32,   uint32_t          )
PySHMEM_CTX_AMO_EXT(uint64,   uint64_t          )
PySHMEM_CTX_AMO_EXT(int,      int               )
PySHMEM_CTX_AMO_EXT(ptrdiff,  ptrdiff_t         )
PySHMEM_CTX_AMO_EXT(size,     size_t            )
PySHMEM_CTX_AMO_EXT(long,     long              )
PySHMEM_CTX_AMO_EXT(longlong, long long         )
PySHMEM_CTX_AMO_EXT(float,    float             )
PySHMEM_CTX_AMO_EXT(double,   double            )

#endif
