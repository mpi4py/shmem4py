#include <shmem.h>

#if defined(OSHMEM_MAJOR_VERSION)
#define PySHMEM_VENDOR_OpenMPI 1
#elif defined(OSHMPI_NUMVERSION)
#define PySHMEM_VENDOR_OSHMPI 1
#elif defined(SHMEM_DEF_H) && defined(SHMEM_FUNCTION_ATTRIBUTES)
#define PySHMEM_VENDOR_Sandia 1
#elif defined(_SHMEM_API_H) && defined(_SHMEM_DEPR_H)
#define PySHMEM_VENDOR_OSSS 1
#endif

/* --- */

#ifndef PySHMEM_Thread_local
# if __STDC_VERSION__ >= 201112
#   define PySHMEM_Thread_local _Thread_local
# elif defined __GNUC__   || \
       defined __xlC__    || \
       defined __SUNPRO_C
#  define PySHMEM_Thread_local __thread
# elif defined _WIN32 &&   (  \
       defined _MSC_VER    || \
       defined __ICL       || \
       defined __DMC__     || \
       defined __BORLANDC__ )
#   define PySHMEM_Thread_local __declspec(thread)
# endif
#endif

PySHMEM_Thread_local static int _shmem_error = 0;

#define PySHMEM_UNAVAILABLE (_shmem_error = -1431655766) /*0xAAAAAAAA*/

/* --- */

/* OSSS-UCX OpenSHMEM implementation */

#if defined(PySHMEM_VENDOR_OSSS)

#define PySHMEM_HAVE_shmem_malloc_with_hints 1
#define PySHMEM_HAVE_shmem_team_t 1
#define PySHMEM_HAVE_SHMEM_CTX_INVALID 1
#define PySHMEM_HAVE_shmem_put_signal 1
#define PySHMEM_HAVE_shmem_signal_fetch 1
#define PySHMEM_HAVE_shmem_signal_wait_until 1
#define PySHMEM_HAVE_shmem_pcontrol 1

static
int shmem_team_create_ctx(shmem_team_t team, long options, shmem_ctx_t *ctx)
{
  if (team == SHMEM_TEAM_WORLD) {
    return shmem_ctx_create(options, ctx);
  }
  *ctx = SHMEM_CTX_INVALID;
  return PySHMEM_UNAVAILABLE;
}

static
int shmem_ctx_get_team(shmem_ctx_t ctx, shmem_team_t *team)
{
  if (ctx == SHMEM_CTX_INVALID) {
    *team = SHMEM_TEAM_INVALID;
    return -1;
  }
  if (ctx == SHMEM_CTX_DEFAULT) {
    *team = SHMEM_TEAM_WORLD;
    return 0;
  }
  *team = SHMEM_TEAM_INVALID;
  return PySHMEM_UNAVAILABLE;
}

static
int shmem_team_sync(shmem_team_t team)
{
  if (team == SHMEM_TEAM_WORLD) {
    shmem_sync_all();
    return 0;
  }
  return PySHMEM_UNAVAILABLE;
}

static
int PySHMEM_OSSS_shmem_team_get_config(shmem_team_t team, long config_mask, shmem_team_config_t *config)
{
  (void)config_mask;
  return shmem_team_get_config(team, config);
}
#define shmem_team_get_config PySHMEM_OSSS_shmem_team_get_config

#endif


/* --- */

/* Open MPI OpenSHMEM implementation */

#if defined(PySHMEM_VENDOR_OpenMPI)

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

/* --- */

/* OSHMPI OpenSHMEM implementation */

#if defined(PySHMEM_VENDOR_OSHMPI)

static
void *PySHMEM_OSHMPI_shmem_calloc(size_t count, size_t size)
{
  return shmem_calloc(1, count * size);
}
#define shmem_calloc PySHMEM_OSHMPI_shmem_calloc

#define PySHMEM_HAVE_shmem_team_t 1

#if !defined(SHMEM_TEAM_NUM_CONTEXTS)
#define SHMEM_TEAM_NUM_CONTEXTS 0
#endif

static
int PySHMEM_OSHMPI_shmem_team_sync(shmem_team_t team)
{
  if (team == SHMEM_TEAM_WORLD) {
    shmem_sync_all();
    return 0;
  }
  return shmem_team_sync(team);
}
#define shmem_team_sync PySHMEM_OSHMPI_shmem_team_sync

#endif

/* --- */

/* Sandia OpenSHMEM implementation */

#if defined(PySHMEM_VENDOR_Sandia)

#define PySHMEM_HAVE_shmem_malloc_with_hints 1
#define PySHMEM_HAVE_shmem_team_t 1
#define PySHMEM_HAVE_SHMEM_CTX_INVALID 1
#define PySHMEM_HAVE_shmem_put_signal 1
#define PySHMEM_HAVE_shmem_signal_fetch 1
#define PySHMEM_HAVE_shmem_signal_wait_until 1
#define PySHMEM_HAVE_shmem_broadcastmem 1
#define PySHMEM_HAVE_shmem_collectmem 1
#define PySHMEM_HAVE_shmem_alltoallmem 1
#define PySHMEM_HAVE_shmem_TYPENAME_alltoalls 1
#define PySHMEM_HAVE_shmem_OP_reduce 1
#define PySHMEM_HAVE_shmem_pcontrol 1

/* https://github.com/Sandia-OpenSHMEM/SOS/issues/1015 */
#undef PySHMEM_HAVE_shmem_signal_wait_until

static
int PySHMEM_SOS_shmem_team_get_config(shmem_team_t team, long config_mask, shmem_team_config_t *config)
{
  (void)config_mask;
  shmem_team_get_config(team, config);
  return 0;
}
#define shmem_team_get_config PySHMEM_SOS_shmem_team_get_config

#endif

/* --- */

#if !defined(PySHMEM_HAVE_shmem_malloc_with_hints)

#define SHMEM_MALLOC_ATOMICS_REMOTE 0
#define SHMEM_MALLOC_SIGNAL_REMOTE 0

static
void *shmem_malloc_with_hints(size_t size, long hints)
{
  (void)hints;
  return shmem_malloc(size);
}

#endif

/* --- */

#if !defined(PySHMEM_HAVE_shmem_put_signal)

#define SHMEM_SIGNAL_SET 0
#define SHMEM_SIGNAL_ADD 0

#define PySHMEM_RMA_SIGNAL_ARGS(TYPE) \
  TYPE *d, const TYPE *s, size_t n, uint64_t *a, uint64_t v, int o, int pe
#define PySHMEM_RMA_SIGNAL_USE_ARGS \
  (void)d; (void)s; (void)n; (void)a; (void)v; (void)o; (void)pe
#define PySHMEM_RMA_SIGNAL_CTXARGS(TYPE) \
  shmem_ctx_t ctx, PySHMEM_RMA_SIGNAL_ARGS(TYPE)
#define PySHMEM_RMA_SIGNAL_USE_CTXARGS \
  (void)ctx; PySHMEM_RMA_SIGNAL_USE_ARGS
#define PySHMEM_RMA_SIGNAL_UNAVAILABLE \
  do { (void) PySHMEM_UNAVAILABLE; } while (0)

#define PySHMEM_RMA_SIGNAL(NAME, TYPE)                                      \
static void shmem_##NAME##_signal(PySHMEM_RMA_SIGNAL_ARGS(TYPE))            \
{PySHMEM_RMA_SIGNAL_USE_ARGS; PySHMEM_RMA_SIGNAL_UNAVAILABLE;}              \
static void shmem_##NAME##_signal_nbi(PySHMEM_RMA_SIGNAL_ARGS(TYPE))        \
{PySHMEM_RMA_SIGNAL_USE_ARGS; PySHMEM_RMA_SIGNAL_UNAVAILABLE;}              \
static void shmem_ctx_##NAME##_signal(PySHMEM_RMA_SIGNAL_CTXARGS(TYPE))     \
{PySHMEM_RMA_SIGNAL_USE_CTXARGS; PySHMEM_RMA_SIGNAL_UNAVAILABLE;}           \
static void shmem_ctx_##NAME##_signal_nbi(PySHMEM_RMA_SIGNAL_CTXARGS(TYPE)) \
{PySHMEM_RMA_SIGNAL_USE_CTXARGS; PySHMEM_RMA_SIGNAL_UNAVAILABLE;}        /**/

#define PySHMEM_RMA_SIGNAL_T(N, T) PySHMEM_RMA_SIGNAL( N##_put , T    )
#define PySHMEM_RMA_SIGNAL_S(S)    PySHMEM_RMA_SIGNAL( put##S  , void )
#define PySHMEM_RMA_SIGNAL_M()     PySHMEM_RMA_SIGNAL( putmem  , void )

PySHMEM_RMA_SIGNAL_T( float      , float              )
PySHMEM_RMA_SIGNAL_T( double     , double             )
PySHMEM_RMA_SIGNAL_T( longdouble , long double        )
PySHMEM_RMA_SIGNAL_T( char       , char               )
PySHMEM_RMA_SIGNAL_T( schar      , signed char        )
PySHMEM_RMA_SIGNAL_T( short      , short              )
PySHMEM_RMA_SIGNAL_T( int        , int                )
PySHMEM_RMA_SIGNAL_T( long       , long               )
PySHMEM_RMA_SIGNAL_T( longlong   , long long          )
PySHMEM_RMA_SIGNAL_T( uchar      , unsigned char      )
PySHMEM_RMA_SIGNAL_T( ushort     , unsigned short     )
PySHMEM_RMA_SIGNAL_T( uint       , unsigned int       )
PySHMEM_RMA_SIGNAL_T( ulong      , unsigned long      )
PySHMEM_RMA_SIGNAL_T( ulonglong  , unsigned long long )
PySHMEM_RMA_SIGNAL_T( int8       , int8_t             )
PySHMEM_RMA_SIGNAL_T( int16      , int16_t            )
PySHMEM_RMA_SIGNAL_T( int32      , int32_t            )
PySHMEM_RMA_SIGNAL_T( int64      , int64_t            )
PySHMEM_RMA_SIGNAL_T( uint8      , uint8_t            )
PySHMEM_RMA_SIGNAL_T( uint16     , uint16_t           )
PySHMEM_RMA_SIGNAL_T( uint32     , uint32_t           )
PySHMEM_RMA_SIGNAL_T( uint64     , uint64_t           )
PySHMEM_RMA_SIGNAL_T( size       , size_t             )
PySHMEM_RMA_SIGNAL_T( ptrdiff    , ptrdiff_t          )
PySHMEM_RMA_SIGNAL_S(   8 )
PySHMEM_RMA_SIGNAL_S(  16 )
PySHMEM_RMA_SIGNAL_S(  32 )
PySHMEM_RMA_SIGNAL_S(  64 )
PySHMEM_RMA_SIGNAL_S( 128 )
PySHMEM_RMA_SIGNAL_M()

#endif

#if !defined(PySHMEM_HAVE_shmem_signal_fetch)

static
uint64_t shmem_signal_fetch(const uint64_t *sig_addr)
{
  return shmem_uint64_atomic_fetch(sig_addr, shmem_my_pe());
}

#endif

#if !defined(PySHMEM_HAVE_shmem_signal_wait_until)

static
uint64_t shmem_signal_wait_until(uint64_t *sig_addr, int cmp, uint64_t cmp_value)
{
  shmem_uint64_wait_until(sig_addr, cmp, cmp_value);
  return shmem_signal_fetch(sig_addr); /* FIXME: wait and fetch is not atomic */
}

#endif

/* --- */

#if !defined(PySHMEM_HAVE_SHMEM_CTX_INVALID)

#define SHMEM_CTX_INVALID ((shmem_ctx_t)(SHMEM_CTX_DEFAULT?NULL:(SHMEM_CTX_DEFAULT-1)))

#endif

/* --- */

#if !defined(PySHMEM_HAVE_shmem_team_t)

typedef void *shmem_team_t;

#define SHMEM_TEAM_WORLD   ((shmem_team_t)0x01)
#define SHMEM_TEAM_SHARED  ((shmem_team_t)NULL)
#define SHMEM_TEAM_INVALID ((shmem_team_t)NULL)

static
int shmem_team_my_pe(shmem_team_t team)
{
  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;
  return shmem_my_pe();
}

static
int shmem_team_n_pes(shmem_team_t team)
{
  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;
  return shmem_n_pes();
}

static
int shmem_team_translate_pe(shmem_team_t src_team, int src_pe, shmem_team_t dest_team)
{
  if (src_team  != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;
  if (dest_team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;
  if (src_pe < 0 || src_pe >= shmem_n_pes()) return -1;
  return src_pe;
}

#define SHMEM_TEAM_NUM_CONTEXTS 0

typedef struct {
  int num_contexts;
} shmem_team_config_t;

static
int shmem_team_split_strided(shmem_team_t parent_team, int start, int stride, int size,
                             const shmem_team_config_t *config, long config_mask, shmem_team_t *new_team)
{
  (void)config; (void)config_mask;
  if (parent_team == SHMEM_TEAM_WORLD) {
    if (start == 0 && stride == 1 && size == shmem_n_pes())
      return (*new_team = SHMEM_TEAM_WORLD, 0);
  }
  *new_team = SHMEM_TEAM_INVALID;
  return PySHMEM_UNAVAILABLE;
}

static
int shmem_team_split_2d(shmem_team_t parent_team, int xrange,
                        const shmem_team_config_t *xaxis_config, long xaxis_mask, shmem_team_t *xaxis_team,
                        const shmem_team_config_t *yaxis_config, long yaxis_mask, shmem_team_t *yaxis_team)
{
  (void)parent_team; (void)xrange;
  (void)xaxis_config; (void)xaxis_mask; *xaxis_team = SHMEM_TEAM_INVALID;
  (void)yaxis_config, (void)yaxis_mask, *yaxis_team = SHMEM_TEAM_INVALID;
  return PySHMEM_UNAVAILABLE;
}

static
int shmem_team_get_config(shmem_team_t team, long config_mask, shmem_team_config_t *config)
{
  (void)config_mask;
  if (team == SHMEM_TEAM_WORLD) {
    config->num_contexts = 0;
    return 0;
  }
  return PySHMEM_UNAVAILABLE;
}

static
void shmem_team_destroy(shmem_team_t team)
{
  (void)team;
}

static
int shmem_team_create_ctx(shmem_team_t team, long options, shmem_ctx_t *ctx)
{
  if (team == SHMEM_TEAM_WORLD) {
    return shmem_ctx_create(options, ctx);
  }
  *ctx = SHMEM_CTX_INVALID;
  return PySHMEM_UNAVAILABLE;
}

static
int shmem_ctx_get_team(shmem_ctx_t ctx, shmem_team_t *team)
{
  if (ctx == SHMEM_CTX_DEFAULT) {
    *team = SHMEM_TEAM_WORLD;
    return 0;
  }
  *team = SHMEM_TEAM_INVALID;
  return PySHMEM_UNAVAILABLE;
}

static
int shmem_team_sync(shmem_team_t team)
{
  if (team == SHMEM_TEAM_WORLD) {
    shmem_sync_all();
    return 0;
  }
  return PySHMEM_UNAVAILABLE;
}

#endif

/* --- */

static
long *_py_shmem_pSync_array = NULL;

static inline
long *_py_shmem_pSync()
{
  if (!_py_shmem_pSync_array) {
    _py_shmem_pSync_array = (long *) shmem_malloc(SHMEM_SYNC_SIZE * sizeof(long));
    for (int i = 0; i < SHMEM_SYNC_SIZE; i++)
      _py_shmem_pSync_array[i] = SHMEM_SYNC_VALUE;
  }
  shmem_sync_all();
  return _py_shmem_pSync_array;
}

#if !defined(PySHMEM_HAVE_shmem_broadcastmem)

#define PySHMEM_BROADCAST(N, dest, source, nbytes, root)                \
  do {                                                                  \
    if (nbytes % (N>>3) == 0) {                                         \
      shmem_broadcast##N(dest, source, (nbytes)/(N>>3), root,           \
                         0, 0, shmem_n_pes(), _py_shmem_pSync());       \
      if (root == shmem_my_pe()) (void) memcpy(dest, source, nbytes);   \
      return 0;                                                         \
    }                                                                   \
  } while(0);

static
int shmem_broadcastmem(shmem_team_t team, void *dest, const void *source, size_t nbytes, int root)
{
  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;
  PySHMEM_BROADCAST(64, dest, source, nbytes, root);
  PySHMEM_BROADCAST(32, dest, source, nbytes, root);
  return PySHMEM_UNAVAILABLE;
}

#endif

#if !defined(PySHMEM_HAVE_shmem_collectmem)

#define PySHMEM_XCOLLECT(f, N, dest, source, nbytes)                    \
  do {                                                                  \
    if (nbytes % (N>>3) == 0) {                                         \
      shmem_##f##collect##N(dest, source, (nbytes)/(N>>3),              \
                            0, 0, shmem_n_pes(), _py_shmem_pSync());    \
      return 0;                                                         \
    }                                                                   \
  } while(0);
#define PySHMEM_COLLECT(N, dest, source, nbytes) \
  PySHMEM_XCOLLECT(, N, dest, source, nbytes)
#define PySHMEM_FCOLLECT(N, dest, source, nbytes) \
  PySHMEM_XCOLLECT(f, N, dest, source, nbytes)

static
int shmem_collectmem(shmem_team_t team, void *dest, const void *source, size_t nbytes)
{
  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;
  PySHMEM_COLLECT(32, dest, source, nbytes);
  return PySHMEM_UNAVAILABLE;
}

static
int shmem_fcollectmem(shmem_team_t team, void *dest, const void *source, size_t nbytes)
{
  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;
  PySHMEM_FCOLLECT(64, dest, source, nbytes);
  PySHMEM_FCOLLECT(32, dest, source, nbytes);
  return PySHMEM_UNAVAILABLE;
}

#endif

#if !defined(PySHMEM_HAVE_shmem_alltoallmem)

#define PySHMEM_ALLTOALL(N, dest, source, nbytes)                       \
  do {                                                                  \
    if (nbytes % (N>>3) == 0) {                                         \
      shmem_alltoall##N(dest, source, (nbytes)/(N>>3),                  \
                        0, 0, shmem_n_pes(), _py_shmem_pSync());        \
      return 0;                                                         \
    }                                                                   \
  } while(0);

static
int shmem_alltoallmem(shmem_team_t team, void *dest, const void *source, size_t nbytes)
{
  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;
  PySHMEM_ALLTOALL(64, dest, source, nbytes);
  PySHMEM_ALLTOALL(32, dest, source, nbytes);
  return PySHMEM_UNAVAILABLE;
}

#endif

static
int shmem_py_alltoalls(shmem_team_t team, void *dest, const void *source,
                       ptrdiff_t dst, ptrdiff_t sst, size_t size, size_t eltsize)
{
#if defined(PySHMEM_HAVE_shmem_TYPENAME_alltoalls)

  switch (eltsize) {
  case (1): return shmem_uint8_alltoalls (team, dest, source, dst, sst, size);
  case (2): return shmem_uint16_alltoalls(team, dest, source, dst, sst, size);
  case (4): return shmem_uint32_alltoalls(team, dest, source, dst, sst, size);
  case (8): return shmem_uint64_alltoalls(team, dest, source, dst, sst, size);
  }
  return PySHMEM_UNAVAILABLE;

#else

#define PySHMEM_ALLTOALLS(N, dest, source, dst, sst, size)      \
  shmem_alltoalls##N(dest, source, dst, sst, size,              \
                     0, 0, shmem_n_pes(), _py_shmem_pSync());

  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;
  switch (eltsize) {
  case (4): PySHMEM_ALLTOALLS(32, dest, source, dst, sst, size); return 0;
  case (8): PySHMEM_ALLTOALLS(64, dest, source, dst, sst, size); return 0;
  }
  return PySHMEM_UNAVAILABLE;

#endif
}

/* --- */

size_t _py_shmem_pWrk_size  = 0;
void  *_py_shmem_pWrk_array = NULL;

#if !defined(PySHMEM_HAVE_shmem_OP_reduce)

#define max(a,b) (((a)>(b))?(a):(b))

static inline
void *_py_shmem_pWrk(size_t nreduce, size_t eltsize)
{
  size_t min_len  = max(nreduce/2 + 1, SHMEM_REDUCE_MIN_WRKDATA_SIZE);
  size_t wrk_size = max(min_len * eltsize, _py_shmem_pWrk_size);
  if (_py_shmem_pWrk_size < wrk_size || !_py_shmem_pWrk_array) {
    shmem_free(_py_shmem_pWrk_array);
    _py_shmem_pWrk_size  = wrk_size;
    _py_shmem_pWrk_array = shmem_malloc(wrk_size);
  }
  shmem_sync_all();
  return _py_shmem_pWrk_array;
}

#define PySHMEM_REDUCE_OP(TYPENAME, TYPE, OP)                           \
static                                                                  \
int shmem_##TYPENAME##_##OP##_reduce(shmem_team_t team,                 \
                                     TYPE *dest,                        \
                                     const TYPE *source,                \
                                     size_t nreduce)                    \
{                                                                       \
  TYPE *pWrk  = (TYPE *) _py_shmem_pWrk(nreduce, sizeof(TYPE));         \
  long *pSync = _py_shmem_pSync();                                      \
  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;             \
  if (nreduce > INT_MAX) return -1;                                     \
  shmem_##TYPENAME##_##OP##_to_all(dest, source, (int) nreduce,         \
                                   0, 0, shmem_n_pes(), pWrk, pSync);   \
  return 0;                                                             \
}                                                                    /**/

#define PySHMEM_REDUCE_MAXMIN(TYPENAME, TYPE)    \
  PySHMEM_REDUCE_OP(TYPENAME, TYPE, max)         \
  PySHMEM_REDUCE_OP(TYPENAME, TYPE, min)

#define PySHMEM_REDUCE_SUMPROD(TYPENAME, TYPE)   \
  PySHMEM_REDUCE_OP(TYPENAME, TYPE, sum)         \
  PySHMEM_REDUCE_OP(TYPENAME, TYPE, prod)

#define PySHMEM_REDUCE_1(TYPENAME, TYPE) \
  PySHMEM_REDUCE_SUMPROD(TYPENAME, TYPE)

#define PySHMEM_REDUCE_2(TYPENAME, TYPE) \
  PySHMEM_REDUCE_SUMPROD(TYPENAME, TYPE) \
  PySHMEM_REDUCE_MAXMIN (TYPENAME, TYPE)

PySHMEM_REDUCE_2(short,      short)
PySHMEM_REDUCE_2(int,        int)
PySHMEM_REDUCE_2(long,       long)
PySHMEM_REDUCE_2(longlong,   long long)
PySHMEM_REDUCE_2(float,      float)
PySHMEM_REDUCE_2(double,     double)
PySHMEM_REDUCE_2(longdouble, long double)
PySHMEM_REDUCE_1(complexf,   float _Complex)
PySHMEM_REDUCE_1(complexd,   double _Complex)

#define PySHMEM_REDUCE_UINT_OP(TYPENAME, TYPE, OP)                      \
static                                                                  \
int shmem_u##TYPENAME##_##OP##_reduce(shmem_team_t team,                \
                                      unsigned TYPE *dest,              \
                                      const unsigned TYPE *source,      \
                                      size_t nreduce)                   \
{                                                                       \
  TYPE *pWrk  = (TYPE *) _py_shmem_pWrk(nreduce, sizeof(TYPE));         \
  long *pSync = _py_shmem_pSync();                                      \
  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;             \
  if (nreduce > INT_MAX) return -1;                                     \
  shmem_##TYPENAME##_##OP##_to_all((TYPE *) dest,                       \
                                   (TYPE *) source,                     \
                                   (int) nreduce,                       \
                                   0, 0, shmem_n_pes(), pWrk, pSync);   \
  return 0;                                                             \
}                                                                    /**/

#define PySHMEM_REDUCE_UINT_XX(TYPENAME, TYPE, OP)                      \
static                                                                  \
int shmem_u##TYPENAME##_##OP##_reduce(shmem_team_t team,                \
                                      unsigned TYPE *dest,              \
                                      const unsigned TYPE *source,      \
                                      size_t nreduce)                   \
{                                                                       \
  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;             \
  if (nreduce > INT_MAX) return -1;                                     \
  (void)dest; (void)source;                                             \
  return PySHMEM_UNAVAILABLE;                                           \
}                                                                    /**/

#define PySHMEM_REDUCE_UINT(TYPENAME, TYPE)    \
  PySHMEM_REDUCE_UINT_OP(TYPENAME, TYPE, and)  \
  PySHMEM_REDUCE_UINT_OP(TYPENAME, TYPE, or)   \
  PySHMEM_REDUCE_UINT_OP(TYPENAME, TYPE, xor)  \
  PySHMEM_REDUCE_UINT_XX(TYPENAME, TYPE, min)  \
  PySHMEM_REDUCE_UINT_XX(TYPENAME, TYPE, max)  \
  PySHMEM_REDUCE_UINT_XX(TYPENAME, TYPE, sum)  \
  PySHMEM_REDUCE_UINT_XX(TYPENAME, TYPE, prod)

PySHMEM_REDUCE_UINT(short,    short)
PySHMEM_REDUCE_UINT(int,      int)
PySHMEM_REDUCE_UINT(long,     long)
PySHMEM_REDUCE_UINT(longlong, long long)

#endif

#if !defined(PySHMEM_HAVE_shmem_OP_reduce)

#define PySHMEM_REDUCE_FAIL_OP(TYPENAME, TYPE, OP)                      \
static                                                                  \
int shmem_##TYPENAME##_##OP##_reduce(shmem_team_t team,                 \
                                     TYPE *dest,                        \
                                     const TYPE *source,                \
                                     size_t nreduce)                    \
{                                                                       \
  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;             \
  if (nreduce > INT_MAX) return -1;                                     \
  (void)dest; (void)source;                                             \
  return PySHMEM_UNAVAILABLE;                                           \
}                                                                    /**/

#define PySHMEM_REDUCE_FAIL_1(TYPENAME, TYPE)  \
  PySHMEM_REDUCE_FAIL_OP(TYPENAME, TYPE, sum)  \
  PySHMEM_REDUCE_FAIL_OP(TYPENAME, TYPE, prod)

#define PySHMEM_REDUCE_FAIL_2(TYPENAME, TYPE)  \
  PySHMEM_REDUCE_FAIL_1 (TYPENAME, TYPE)       \
  PySHMEM_REDUCE_FAIL_OP(TYPENAME, TYPE, min)  \
  PySHMEM_REDUCE_FAIL_OP(TYPENAME, TYPE, max)

#define PySHMEM_REDUCE_FAIL_3(TYPENAME, TYPE)  \
  PySHMEM_REDUCE_FAIL_2 (TYPENAME, TYPE)       \
  PySHMEM_REDUCE_FAIL_OP(TYPENAME, TYPE, and)  \
  PySHMEM_REDUCE_FAIL_OP(TYPENAME, TYPE, or)   \
  PySHMEM_REDUCE_FAIL_OP(TYPENAME, TYPE, xor)

PySHMEM_REDUCE_FAIL_2(char,  char)
PySHMEM_REDUCE_FAIL_2(schar, signed char)
PySHMEM_REDUCE_FAIL_3(uchar, unsigned char)

PySHMEM_REDUCE_FAIL_3(int8,    int8_t)
PySHMEM_REDUCE_FAIL_3(int16,   int16_t)
PySHMEM_REDUCE_FAIL_3(int32,   int32_t)
PySHMEM_REDUCE_FAIL_3(int64,   int64_t)
PySHMEM_REDUCE_FAIL_2(ptrdiff, ptrdiff_t)

PySHMEM_REDUCE_FAIL_3(uint8,   uint8_t)
PySHMEM_REDUCE_FAIL_3(uint16,  uint16_t)
PySHMEM_REDUCE_FAIL_3(uint32,  uint32_t)
PySHMEM_REDUCE_FAIL_3(uint64,  uint64_t)
PySHMEM_REDUCE_FAIL_3(size,    size_t)

#endif

/* --- */

typedef struct { long double real, imag; } complexg;

/* --- */

static int _py_shmem_finalized   = 0;
static int _py_shmem_initialized = 0;

static int _py_shmem_atexit_setup    = 0;
static int _py_shmem_atexit_finalize = 0;

static void _py_shmem_finalize(void)
{
  shmem_finalize();
  _py_shmem_finalized = 1;
}

static void _py_shmem_atexit_cb(void)
{
  if (_py_shmem_initialized)
    if (!_py_shmem_finalized)
      {
        if (_py_shmem_pWrk_array)
          shmem_free(_py_shmem_pWrk_array);
        _py_shmem_pWrk_array = NULL;
        if (_py_shmem_pSync_array)
          shmem_free(_py_shmem_pSync_array);
        _py_shmem_pSync_array = NULL;
        if (_py_shmem_atexit_finalize)
          _py_shmem_finalize();
      }
}

static void _py_shmem_atexit(void)
{
  if (!_py_shmem_atexit_setup)
    Py_AtExit(_py_shmem_atexit_cb);
  _py_shmem_atexit_setup = 1;
}

static void _py_shmem_init(void)
{
  int ierr = 0;
  shmem_init();
  if (!ierr) _py_shmem_atexit();
  if (!ierr) _py_shmem_initialized = 1;
}

static int _py_shmem_init_thread(int requested, int *provided)
{
  int ierr;
  ierr = shmem_init_thread(requested, provided);
  if (!ierr) _py_shmem_atexit();
  if (!ierr) _py_shmem_initialized = 1;
  return ierr;
}

#define shmem_init _py_shmem_init
#define shmem_finalize _py_shmem_finalize
#define shmem_init_thread _py_shmem_init_thread

#define _shmem_finalized _py_shmem_finalized
#define _shmem_initialized _py_shmem_initialized
#define _shmem_atexit_finalize _py_shmem_atexit_finalize

/* --- */

#define _py_size(size) ((size)?(size):1)

static void *shmem_py_malloc(size_t size)
{
  return shmem_malloc(_py_size(size));
}

static void *shmem_py_malloc_clear(size_t size)
{
  return shmem_calloc(_py_size(size), 1);
}

static void *shmem_py_malloc_align(size_t align, size_t size)
{
  return shmem_align(align, _py_size(size));
}

static void *shmem_py_malloc_hints(size_t size, long hints)
{
  return shmem_malloc_with_hints(_py_size(size), hints);
}

static void shmem_py_free(void *ptr)
{
  if (!_py_shmem_finalized) shmem_free(ptr);
}

#undef _py_size

/* --- */
