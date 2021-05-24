#include <shmem.h>

#if defined(OSHMEM_MAJOR_VERSION)

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

#if defined(OSHMPI_NUMVERSION)

static void *PySHMEM_OSHMPI_shmem_calloc(size_t count, size_t size)
{ return shmem_calloc(1, count * size); }
#define shmem_calloc PySHMEM_OSHMPI_shmem_calloc

#define PySHMEM_HAVE_shmem_team_t 1

#endif

/* --- */

#if !defined(PySHMEM_HAVE_shmem_malloc_with_hints)

#define SHMEM_MALLOC_ATOMICS_REMOTE 0
#define SHMEM_MALLOC_SIGNAL_REMOTE 0
#define shmem_malloc_with_hints(size, hints) shmem_malloc(size)

#endif

/* --- */

#if !defined(PySHMEM_HAVE_shmem_put_signal)

#define SHMEM_SIGNAL_SET 0
#define SHMEM_SIGNAL_ADD 0

#endif

/* --- */

#if !defined(PySHMEM_HAVE_SHMEM_CTX_INVALID)

#define SHMEM_CTX_INVALID ((shmem_ctx_t)(SHMEM_CTX_DEFAULT?NULL:(SHMEM_CTX_DEFAULT-1)))

#endif

/* --- */

#if !defined(PySHMEM_HAVE_shmem_team_t)

typedef void *shmem_team_t;

#define SHMEM_TEAM_WORLD   ((shmem_team_t)0x02)
#define SHMEM_TEAM_SHARED  ((shmem_team_t)0x01)
#define SHMEM_TEAM_INVALID ((shmem_team_t)NULL)

static
int shmem_team_my_pe(shmem_team_t team)
{
  return (team == SHMEM_TEAM_WORLD) ? shmem_my_pe() : (team == SHMEM_TEAM_SHARED) ? 0 : -1;
}

static
int shmem_team_n_pes(shmem_team_t team)
{
  return (team == SHMEM_TEAM_WORLD) ? shmem_n_pes() : (team == SHMEM_TEAM_SHARED) ? 1 : -1;
}

static
int shmem_team_translate_pe(shmem_team_t src_team, int src_pe, shmem_team_t dest_team)
{
  if (src_team == SHMEM_TEAM_WORLD) {
    if (dest_team == SHMEM_TEAM_WORLD)
      return (src_pe >= 0 && src_pe < shmem_n_pes()) ? src_pe : -1;
    if (dest_team == SHMEM_TEAM_SHARED)
      return (src_pe == shmem_my_pe()) ? 0 : -1;
  }
  if (src_team == SHMEM_TEAM_SHARED) {
    if (dest_team == SHMEM_TEAM_WORLD)
      return (src_pe == 0) ? shmem_my_pe() : -1;
    if (dest_team == SHMEM_TEAM_SHARED)
      return (src_pe == 0) ? 0 : -1;
  }
  return -1;
}

typedef struct {int num_contexts;} shmem_team_config_t;

static
int shmem_team_split_strided(shmem_team_t parent_team, int start, int stride, int size,
                             const shmem_team_config_t *config, long config_mask, shmem_team_t *new_team)
{
  (void)parent_team; (void)start; (void)stride; (void)size;
  (void)config; (void)config_mask; *new_team = SHMEM_TEAM_INVALID;
  return -1;
}

static
int shmem_team_split_2d(shmem_team_t parent_team, int xrange,
                        const shmem_team_config_t *xaxis_config, long xaxis_mask, shmem_team_t *xaxis_team,
                        const shmem_team_config_t *yaxis_config, long yaxis_mask, shmem_team_t *yaxis_team)
{
  (void)parent_team; (void)xrange;
  (void)xaxis_config; (void)xaxis_mask; *xaxis_team = SHMEM_TEAM_INVALID;
  (void)yaxis_config, (void)yaxis_mask, *yaxis_team = SHMEM_TEAM_INVALID;
  return -1;
}

static
int shmem_team_get_config(shmem_team_t team, long config_mask, shmem_team_config_t *config)
{
  (void)config_mask; (void)config; /* TODO */
  if (team == SHMEM_TEAM_WORLD)   return 0;
  if (team == SHMEM_TEAM_SHARED)  return 0;
  return -1;
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
  if (team == SHMEM_TEAM_SHARED) {
    *ctx = SHMEM_CTX_INVALID;
    return -1;
  }
  *ctx = SHMEM_CTX_INVALID;
  return -1;
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
  return 0;
}

static
int shmem_team_sync(shmem_team_t team)
{
  if (team == SHMEM_TEAM_WORLD)
    shmem_sync_all();
  if (team == SHMEM_TEAM_SHARED)
    return 0;
  return -1;
}

#endif

/* --- */

static int _py_shmem_initialized = 0;
static int _py_shmem_finalized   = 0;

static void _py_shmem_finalize(void)
{
  shmem_finalize();
  _py_shmem_finalized = 1;
}

static void _py_shmem_atexit(void)
{
  if (_py_shmem_initialized)
    if (!_py_shmem_finalized)
      _py_shmem_finalize();
}

static void _py_shmem_init(void)
{
  shmem_init();
  if (!_py_shmem_initialized) {
    Py_AtExit(_py_shmem_atexit);
    _py_shmem_initialized = 1;
  }
}

static int _py_shmem_init_thread(int requested, int *provided)
{
  int _retv;
  _retv = shmem_init_thread(requested, provided);
  if (!_py_shmem_initialized && !_retv) {
    Py_AtExit(_py_shmem_atexit);
    _py_shmem_initialized = 1;
  }
  return _retv;
}

#define shmem_init _py_shmem_init
#define shmem_finalize _py_shmem_finalize
#define shmem_init_thread _py_shmem_init_thread

/* --- */
