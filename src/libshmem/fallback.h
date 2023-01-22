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

#if !defined(PySHMEM_HAVE_shmem_amo_nbi)

#define PySHMEM_AMONBI_STD(TYPENAME, TYPE) \
static void shmem_##TYPENAME##_atomic_compare_swap_nbi(TYPE *fetch, TYPE *dest, TYPE cond, TYPE value, int pe) \
{(void)fetch; (void)dest; (void)cond; (void)value; (void)pe; PySHMEM_UNAVAILABLE;} \
static void shmem_##TYPENAME##_atomic_fetch_inc_nbi(TYPE *fetch, TYPE *dest, int pe) \
{(void)fetch; (void)dest; (void)pe; PySHMEM_UNAVAILABLE;} \
static void shmem_##TYPENAME##_atomic_fetch_add_nbi(TYPE *fetch, TYPE *dest, TYPE value, int pe) \
{(void)fetch; (void)dest; (void)value; (void)pe; PySHMEM_UNAVAILABLE;} \
static void shmem_ctx_##TYPENAME##_atomic_compare_swap_nbi(shmem_ctx_t ctx, TYPE *fetch, TYPE *dest, TYPE cond, TYPE value, int pe) \
{(void)ctx; (void)fetch; (void)dest; (void)cond; (void)value; (void)pe; PySHMEM_UNAVAILABLE;} \
static void shmem_ctx_##TYPENAME##_atomic_fetch_inc_nbi(shmem_ctx_t ctx, TYPE *fetch, TYPE *dest, int pe) \
{(void)ctx; (void)fetch; (void)dest; (void)pe; PySHMEM_UNAVAILABLE;} \
static void shmem_ctx_##TYPENAME##_atomic_fetch_add_nbi(shmem_ctx_t ctx, TYPE *fetch, TYPE *dest, TYPE value, int pe) \
{(void)ctx; (void)fetch; (void)dest; (void)value; (void)pe; PySHMEM_UNAVAILABLE;} /**/

#define PySHMEM_AMONBI_EXT(TYPENAME, TYPE) \
static void shmem_##TYPENAME##_atomic_fetch_nbi(TYPE *fetch, const TYPE *source, int pe) \
{(void)fetch; (void)source; (void)pe; PySHMEM_UNAVAILABLE;} \
static void shmem_##TYPENAME##_atomic_swap_nbi(TYPE *fetch, TYPE *dest, TYPE value, int pe) \
{(void)fetch; (void)dest; (void)value; (void)pe; PySHMEM_UNAVAILABLE;} \
static void shmem_ctx_##TYPENAME##_atomic_fetch_nbi(shmem_ctx_t ctx, TYPE *fetch, const TYPE *source, int pe) \
{(void)ctx; (void)fetch; (void)source; (void)pe; PySHMEM_UNAVAILABLE;} \
static void shmem_ctx_##TYPENAME##_atomic_swap_nbi(shmem_ctx_t ctx, TYPE *fetch, TYPE *dest, TYPE value, int pe) \
{(void)ctx; (void)fetch; (void)dest; (void)value; (void)pe; PySHMEM_UNAVAILABLE;} /**/

#define PySHMEM_AMONBI_BIT(TYPENAME, TYPE) \
static void shmem_##TYPENAME##_atomic_fetch_and_nbi(TYPE *fetch, TYPE *dest, TYPE value, int pe) \
{(void)fetch; (void)dest; (void)value; (void)pe; PySHMEM_UNAVAILABLE; PySHMEM_UNAVAILABLE;} \
static void shmem_##TYPENAME##_atomic_fetch_or_nbi (TYPE *fetch, TYPE *dest, TYPE value, int pe) \
{(void)fetch; (void)dest; (void)value; (void)pe; PySHMEM_UNAVAILABLE; PySHMEM_UNAVAILABLE;} \
static void shmem_##TYPENAME##_atomic_fetch_xor_nbi(TYPE *fetch, TYPE *dest, TYPE value, int pe) \
{(void)fetch; (void)dest; (void)value; (void)pe; PySHMEM_UNAVAILABLE; PySHMEM_UNAVAILABLE;} \
static void shmem_ctx_##TYPENAME##_atomic_fetch_and_nbi(shmem_ctx_t ctx, TYPE *fetch, TYPE *dest, TYPE value, int pe) \
{(void)ctx; (void)fetch; (void)dest; (void)value; (void)pe; PySHMEM_UNAVAILABLE; PySHMEM_UNAVAILABLE;} \
static void shmem_ctx_##TYPENAME##_atomic_fetch_or_nbi (shmem_ctx_t ctx, TYPE *fetch, TYPE *dest, TYPE value, int pe) \
{(void)ctx; (void)fetch; (void)dest; (void)value; (void)pe; PySHMEM_UNAVAILABLE; PySHMEM_UNAVAILABLE;} \
static void shmem_ctx_##TYPENAME##_atomic_fetch_xor_nbi(shmem_ctx_t ctx, TYPE *fetch, TYPE *dest, TYPE value, int pe) \
{(void)ctx; (void)fetch; (void)dest; (void)value; (void)pe; PySHMEM_UNAVAILABLE; PySHMEM_UNAVAILABLE;} /**/

PySHMEM_AMONBI_STD( int       , int                )
PySHMEM_AMONBI_STD( long      , long               )
PySHMEM_AMONBI_STD( longlong  , long long          )
PySHMEM_AMONBI_STD( uint      , unsigned int       )
PySHMEM_AMONBI_STD( ulong     , unsigned long      )
PySHMEM_AMONBI_STD( ulonglong , unsigned long long )
PySHMEM_AMONBI_STD( int32     , int32_t            )
PySHMEM_AMONBI_STD( int64     , int64_t            )
PySHMEM_AMONBI_STD( uint32    , uint32_t           )
PySHMEM_AMONBI_STD( uint64    , uint64_t           )
PySHMEM_AMONBI_STD( size      , size_t             )
PySHMEM_AMONBI_STD( ptrdiff   , ptrdiff_t          )

PySHMEM_AMONBI_EXT( int       , int                )
PySHMEM_AMONBI_EXT( long      , long               )
PySHMEM_AMONBI_EXT( longlong  , long long          )
PySHMEM_AMONBI_EXT( uint      , unsigned int       )
PySHMEM_AMONBI_EXT( ulong     , unsigned long      )
PySHMEM_AMONBI_EXT( ulonglong , unsigned long long )
PySHMEM_AMONBI_EXT( int32     , int32_t            )
PySHMEM_AMONBI_EXT( int64     , int64_t            )
PySHMEM_AMONBI_EXT( uint32    , uint32_t           )
PySHMEM_AMONBI_EXT( uint64    , uint64_t           )
PySHMEM_AMONBI_EXT( size      , size_t             )
PySHMEM_AMONBI_EXT( ptrdiff   , ptrdiff_t          )
PySHMEM_AMONBI_EXT( float     , float              )
PySHMEM_AMONBI_EXT( double    , double             )

PySHMEM_AMONBI_BIT( uint      , unsigned int       )
PySHMEM_AMONBI_BIT( ulong     , unsigned long      )
PySHMEM_AMONBI_BIT( ulonglong , unsigned long long )
PySHMEM_AMONBI_BIT( int32     , int32_t            )
PySHMEM_AMONBI_BIT( int64     , int64_t            )
PySHMEM_AMONBI_BIT( uint32    , uint32_t           )
PySHMEM_AMONBI_BIT( uint64    , uint64_t           )

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

#define SHMEM_CTX_INVALID ((shmem_ctx_t)(SHMEM_CTX_DEFAULT?NULL:((char*)SHMEM_CTX_DEFAULT-1)))

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

static long *_py_shmem_pSync_array = NULL;

static inline long *_py_shmem_pSync()
{
  if (!_py_shmem_pSync_array) {
    _py_shmem_pSync_array = (long *) shmem_malloc(SHMEM_SYNC_SIZE * sizeof(long));
    for (int i = 0; i < SHMEM_SYNC_SIZE; i++)
      _py_shmem_pSync_array[i] = SHMEM_SYNC_VALUE;
    shmem_sync_all();
  }
  return _py_shmem_pSync_array;
}

static size_t _py_shmem_pWrk_size  = 0;
static void  *_py_shmem_pWrk_array = NULL;

static inline void *_py_shmem_pWrk(size_t nreduce, size_t eltsize)
{
# define max(a,b) (((a)>(b))?(a):(b))
  size_t min_len  = max(nreduce/2 + 1, SHMEM_REDUCE_MIN_WRKDATA_SIZE);
  size_t wrk_size = max(min_len * eltsize, _py_shmem_pWrk_size);
  if (!_py_shmem_pWrk_array || _py_shmem_pWrk_size < wrk_size) {
    shmem_free(_py_shmem_pWrk_array);
    _py_shmem_pWrk_size  = wrk_size;
    _py_shmem_pWrk_array = shmem_malloc(wrk_size);
    shmem_sync_all();
  }
  return _py_shmem_pWrk_array;
}

#define PySHMEM_APPLY_STD_RMA_TYPES(PySHMEM_FN_MACRO)  \
    PySHMEM_FN_MACRO( float,      float              ) \
    PySHMEM_FN_MACRO( double,     double             ) \
    PySHMEM_FN_MACRO( longdouble, long double        ) \
    PySHMEM_FN_MACRO( char,       char               ) \
    PySHMEM_FN_MACRO( short,      short              ) \
    PySHMEM_FN_MACRO( schar,      signed char        ) \
    PySHMEM_FN_MACRO( int,        int                ) \
    PySHMEM_FN_MACRO( long,       long               ) \
    PySHMEM_FN_MACRO( longlong,   long long          ) \
    PySHMEM_FN_MACRO( uchar,      unsigned char      ) \
    PySHMEM_FN_MACRO( ushort,     unsigned short     ) \
    PySHMEM_FN_MACRO( uint,       unsigned int       ) \
    PySHMEM_FN_MACRO( ulong,      unsigned long      ) \
    PySHMEM_FN_MACRO( ulonglong,  unsigned long long ) \
    PySHMEM_FN_MACRO( int8,       int8_t             ) \
    PySHMEM_FN_MACRO( int16,      int16_t            ) \
    PySHMEM_FN_MACRO( int32,      int32_t            ) \
    PySHMEM_FN_MACRO( int64,      int64_t            ) \
    PySHMEM_FN_MACRO( uint8,      uint8_t            ) \
    PySHMEM_FN_MACRO( uint16,     uint16_t           ) \
    PySHMEM_FN_MACRO( uint32,     uint32_t           ) \
    PySHMEM_FN_MACRO( uint64,     uint64_t           ) \
    PySHMEM_FN_MACRO( size,       size_t             ) \
    PySHMEM_FN_MACRO( ptrdiff,    ptrdiff_t          )

/* --- */

#if !defined(PySHMEM_HAVE_shmem_broadcastmem)

#define PySHMEM_BROADCAST_BIT(N, dest, source, nbytes, root)          \
  do {                                                                \
    if ((nbytes) % (N>>3) == 0) {                                     \
      shmem_broadcast##N(dest, source, (nbytes)/(N>>3), root,         \
                         0, 0, shmem_n_pes(), _py_shmem_pSync());     \
      if (root == shmem_my_pe()) (void) memcpy(dest, source, nbytes); \
      return 0;                                                       \
    }                                                                 \
  } while(0);

static
int shmem_broadcastmem(shmem_team_t team,
                       void *dest, const void *source, size_t nbytes,
                       int root)
{
#if defined(PySHMEM_HAVE_shmem_broadcast)
  unsigned char *_dest = (unsigned char *) dest;
  const unsigned char * _source = (const unsigned char *) source;
  return shmem_uchar_broadcast(team, _dest, _source, nbytes, root);
#else
  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;
  PySHMEM_BROADCAST_BIT(64, dest, source, nbytes, root);
  PySHMEM_BROADCAST_BIT(32, dest, source, nbytes, root);
  return PySHMEM_UNAVAILABLE;
#endif
}

#endif

#if !defined(PySHMEM_HAVE_shmem_broadcast)

#define PySHMEM_BROADCAST(TYPENAME, TYPE)                             \
static int shmem_##TYPENAME##_broadcast                               \
(shmem_team_t team, TYPE *dest, const TYPE *source,                   \
 size_t nelems, int root)                                             \
{ return shmem_broadcastmem(team, dest, source,                       \
                            nelems*sizeof(TYPE), root); }

PySHMEM_APPLY_STD_RMA_TYPES(PySHMEM_BROADCAST)

#endif

/* --- */

#if !defined(PySHMEM_HAVE_shmem_collectmem)

#define PySHMEM_COLLECT_BIT(N, dest, source, nbytes)                  \
  do {                                                                \
    if ((nbytes) % (N>>3) == 0) {                                     \
      shmem_collect##N(dest, source, (nbytes)/(N>>3),                 \
                       0, 0, shmem_n_pes(), _py_shmem_pSync());       \
      return 0;                                                       \
    }                                                                 \
  } while(0);

static
int shmem_collectmem(shmem_team_t team,
                     void *dest, const void *source, size_t nbytes)
{
#if defined(PySHMEM_HAVE_shmem_collect)
  unsigned char *_dest = (unsigned char *) dest;
  const unsigned char * _source = (const unsigned char *) source;
  return shmem_uchar_collect(team, _dest, _source, nbytes);
#else
  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;
  PySHMEM_COLLECT_BIT(32, dest, source, nbytes);
  return PySHMEM_UNAVAILABLE;
#endif
}

#endif

#if !defined(PySHMEM_HAVE_shmem_collect)

#define PySHMEM_COLLECT(TYPENAME, TYPE)                               \
static int shmem_##TYPENAME##_collect                                 \
(shmem_team_t team, TYPE *dest, const TYPE *source, size_t nelems)    \
{ return shmem_collectmem(team, dest, source, nelems*sizeof(TYPE)); }

PySHMEM_APPLY_STD_RMA_TYPES(PySHMEM_COLLECT)

#endif

/* --- */

#if !defined(PySHMEM_HAVE_shmem_fcollectmem)

#define PySHMEM_FCOLLECT_BIT(N, dest, source, nbytes)                 \
  do {                                                                \
    if ((nbytes) % (N>>3) == 0) {                                     \
      shmem_fcollect##N(dest, source, (nbytes)/(N>>3),                \
                        0, 0, shmem_n_pes(), _py_shmem_pSync());      \
      return 0;                                                       \
    }                                                                 \
  } while(0);

static
int shmem_fcollectmem(shmem_team_t team,
                      void *dest, const void *source, size_t nbytes)
{
#if defined(PySHMEM_HAVE_shmem_fcollect)
  unsigned char *_dest = (unsigned char *) dest;
  const unsigned char * _source = (const unsigned char *) source;
  return shmem_uchar_fcollect(team, _dest, _source, nbytes);
#else
  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;
  PySHMEM_FCOLLECT_BIT(64, dest, source, nbytes);
  PySHMEM_FCOLLECT_BIT(32, dest, source, nbytes);
  return PySHMEM_UNAVAILABLE;
#endif
}

#endif

#if !defined(PySHMEM_HAVE_shmem_fcollect)

#define PySHMEM_FCOLLECT(TYPENAME, TYPE)                              \
static int shmem_##TYPENAME##_fcollect                                \
(shmem_team_t team, TYPE *dest, const TYPE *source, size_t nelems)    \
{ return shmem_fcollectmem(team, dest, source, nelems*sizeof(TYPE)); }

PySHMEM_APPLY_STD_RMA_TYPES(PySHMEM_FCOLLECT)

#endif

/* --- */

#if !defined(PySHMEM_HAVE_shmem_alltoallmem)

#define PySHMEM_ALLTOALL_BIT(N, dest, source, nbytes)                 \
  do {                                                                \
    if ((nbytes) % (N>>3) == 0) {                                     \
      shmem_alltoall##N(dest, source, (nbytes)/(N>>3),                \
                        0, 0, shmem_n_pes(), _py_shmem_pSync());      \
      return 0;                                                       \
    }                                                                 \
  } while(0);

static
int shmem_alltoallmem(shmem_team_t team,
                      void *dest, const void *source, size_t nbytes)
{
#if defined(PySHMEM_HAVE_shmem_alltoall)
  unsigned char *_dest = (unsigned char *) dest;
  const unsigned char * _source = (const unsigned char *) source;
  return shmem_uchar_alltoall(team, _dest, _source, nbytes);
#else
  if (team != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;
  PySHMEM_ALLTOALL_BIT(64, dest, source, nbytes);
  PySHMEM_ALLTOALL_BIT(32, dest, source, nbytes);
  return PySHMEM_UNAVAILABLE;
#endif
}

#endif

#if !defined(PySHMEM_HAVE_shmem_alltoall)

#define PySHMEM_ALLTOALL(TYPENAME, TYPE)                             \
static int shmem_##TYPENAME##_alltoall                               \
(shmem_team_t team, TYPE *dest, const TYPE *source, size_t nelems)   \
{ return shmem_alltoallmem(team, dest, source, nelems*sizeof(TYPE)); }

PySHMEM_APPLY_STD_RMA_TYPES(PySHMEM_ALLTOALL)

#endif

/* --- */

#if !defined(PySHMEM_HAVE_shmem_alltoallsmem)

static
int shmem_alltoallsmem(shmem_team_t team,
                       void *dest, const void *source,
                       ptrdiff_t dst, ptrdiff_t sst, size_t nbytes)
{
#if defined(PySHMEM_HAVE_shmem_alltoalls)
  unsigned char *_dest = (unsigned char *) dest;
  const unsigned char * _source = (const unsigned char *) source;
  return shmem_uchar_alltoalls(team, _dest, _source, dst, sst, nbytes);
#else
  (void)team; (void)dest; (void)source;
  (void)dst;  (void)sst;  (void)nbytes;
  return PySHMEM_UNAVAILABLE;
#endif
}

#endif

#if defined(PySHMEM_HAVE_shmem_alltoalls)

#define PySHMEM_ALLTOALLSMEM_X(N, team, dest, source, dst, sst, size, elsz)  \
  do {                                                                       \
    if ((elsz) % (N>>3) == 0) {                                              \
      ptrdiff_t i, n = (ptrdiff_t) (elsz) / (N>>3);                          \
      for (i = 0; i < n; i++) {                                              \
        uint##N##_t *d = (uint##N##_t*) (dest) + i;                          \
        const uint##N##_t *s = (uint##N##_t*) (source) + i;                  \
        int ierr = shmem_uint##N##_alltoalls((team), d, s,                   \
                                             (dst) * n, (sst) * n, size);    \
        if (ierr) return ierr;                                               \
      }                                                                      \
      return 0;                                                              \
    }                                                                        \
  } while(0)                                                              /**/

#else

#define PySHMEM_ALLTOALLSMEM_X(N, team, dest, source, dst, sst, size, elsz)  \
  do {                                                                       \
    if ((team) != SHMEM_TEAM_WORLD) return PySHMEM_UNAVAILABLE;              \
    if ((elsz) % (N>>3) == 0) {                                              \
      ptrdiff_t i, n = (ptrdiff_t) (elsz) / (N>>3);                          \
      for (i = 0; i < n; i++) {                                              \
        uint##N##_t *d = (uint##N##_t*) (dest) + i;                          \
        const uint##N##_t *s = (const uint##N##_t*) (source) + i;            \
        shmem_alltoalls##N(d, s, (dst) * n, (sst) * n, (size),               \
                           0, 0, shmem_n_pes(), _py_shmem_pSync()) ;         \
      }                                                                      \
      return 0;                                                              \
    }                                                                        \
  } while(0)                                                              /**/

#endif

static
int shmem_alltoallsmem_x(shmem_team_t team,
                         void *dest, const void *source,
                         ptrdiff_t dst, ptrdiff_t sst,
                         size_t size, size_t eltsize)
{
  PySHMEM_ALLTOALLSMEM_X(64, team, dest, source, dst, sst, size, eltsize);
  PySHMEM_ALLTOALLSMEM_X(32, team, dest, source, dst, sst, size, eltsize);
#if defined(PySHMEM_HAVE_shmem_alltoalls)
  PySHMEM_ALLTOALLSMEM_X(16, team, dest, source, dst, sst, size, eltsize);
  PySHMEM_ALLTOALLSMEM_X(8 , team, dest, source, dst, sst, size, eltsize);
#endif
  return PySHMEM_UNAVAILABLE;
}

#if !defined(PySHMEM_HAVE_shmem_alltoalls)

#define PySHMEM_ALLTOALLS(TYPENAME, TYPE)                             \
static int shmem_##TYPENAME##_alltoalls                               \
(shmem_team_t team, TYPE *dest, const TYPE *source,                   \
 ptrdiff_t dst, ptrdiff_t sst, size_t nelems)                         \
{ return shmem_alltoallsmem_x(team, dest, source,                     \
                              dst, sst, nelems, sizeof(TYPE)); }

PySHMEM_APPLY_STD_RMA_TYPES(PySHMEM_ALLTOALLS)

#endif

/* --- */

#if !defined(PySHMEM_HAVE_shmem_reduce)

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

#if !defined(PySHMEM_HAVE_shmem_reduce)

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

PySHMEM_REDUCE_FAIL_2( char,    char          )
PySHMEM_REDUCE_FAIL_2( schar,   signed char   )
PySHMEM_REDUCE_FAIL_3( uchar,   unsigned char )

PySHMEM_REDUCE_FAIL_3( int8,    int8_t        )
PySHMEM_REDUCE_FAIL_3( int16,   int16_t       )
PySHMEM_REDUCE_FAIL_3( int32,   int32_t       )
PySHMEM_REDUCE_FAIL_3( int64,   int64_t       )
PySHMEM_REDUCE_FAIL_2( ptrdiff, ptrdiff_t     )

PySHMEM_REDUCE_FAIL_3( uint8,   uint8_t       )
PySHMEM_REDUCE_FAIL_3( uint16,  uint16_t      )
PySHMEM_REDUCE_FAIL_3( uint32,  uint32_t      )
PySHMEM_REDUCE_FAIL_3( uint64,  uint64_t      )
PySHMEM_REDUCE_FAIL_3( size,    size_t        )

#endif

/* --- */

#if !defined(PySHMEM_HAVE_shmem_wait_test_many)

static
int PySHMEM_is_empty_set(size_t nelems, const int *status)
{
  size_t i;
  if (nelems == 0)
    return 1;
  if (status == NULL)
    return 0;
  for (i = 0; i < nelems; i++)
    if (status[i] == 0)
      return 0;
  return 1;
}

#define PySHMEM_YIELD() do { } while(0)

#define PySHMEM_WAIT_ALL(TYPENAME, TYPE, cmp_value, cmp_value_i, suffix)       \
static                                                                         \
void shmem_##TYPENAME##_wait_until_all##suffix(TYPE *ivars, size_t nelems,     \
                                               const int *status,              \
                                               int cmp, TYPE cmp_value)        \
{                                                                              \
  size_t i;                                                                    \
  for (i = 0; i < nelems; i++) {                                               \
    if (status && status[i]) continue;                                         \
    shmem_##TYPENAME##_wait_until(ivars + i, cmp, cmp_value_i);                \
  }                                                                            \
}                                                                           /**/

#define PySHMEM_WAIT_ANY(TYPENAME, TYPE, cmp_value, cmp_value_i, suffix)       \
static                                                                         \
size_t shmem_##TYPENAME##_wait_until_any##suffix(TYPE *ivars, size_t nelems,   \
                                                 const int *status,            \
                                                 int cmp, TYPE cmp_value)      \
{                                                                              \
  if (PySHMEM_is_empty_set(nelems, status)) return SIZE_MAX;                   \
  while (1) {                                                                  \
    size_t i; int done; size_t idx = SIZE_MAX;                                 \
    for (i = 0; i < nelems; i++) {                                             \
      if (status && status[i]) continue;                                       \
      done = shmem_##TYPENAME##_test(ivars + i, cmp, cmp_value_i);             \
      if (done) { idx = i; break; }                                            \
    }                                                                          \
    if (idx != SIZE_MAX) return idx;                                           \
    PySHMEM_YIELD();                                                           \
  }                                                                            \
}                                                                           /**/

#define PySHMEM_WAIT_SOME(TYPENAME, TYPE, cmp_value, cmp_value_i, suffix)      \
static                                                                         \
size_t shmem_##TYPENAME##_wait_until_some##suffix(TYPE *ivars, size_t nelems,  \
                                                  size_t *indices,             \
                                                  const int *status,           \
                                                  int cmp, TYPE cmp_value)     \
{                                                                              \
  if (PySHMEM_is_empty_set(nelems, status)) return 0;                          \
  while (1) {                                                                  \
    size_t i; int done; size_t num = 0;                                        \
    for (i = 0; i < nelems; i++) {                                             \
      if (status && status[i]) continue;                                       \
      done = shmem_##TYPENAME##_test(ivars + i, cmp, cmp_value_i);             \
      if (done) { indices[num++] = i; }                                        \
    }                                                                          \
    if (num != 0) return num;                                                  \
    PySHMEM_YIELD();                                                           \
  }                                                                            \
}                                                                           /**/

#define PySHMEM_TEST_ALL(TYPENAME, TYPE, cmp_value, cmp_value_i, suffix)       \
static                                                                         \
int shmem_##TYPENAME##_test_all##suffix(TYPE *ivars, size_t nelems,            \
                                        const int *status,                     \
                                        int cmp, TYPE cmp_value)               \
{                                                                              \
  size_t i; int done; int flag = 1;                                            \
  if (PySHMEM_is_empty_set(nelems, status)) return 1;                          \
  for (i = 0; i < nelems; i++) {                                               \
    if (status && status[i]) continue;                                         \
    done = shmem_##TYPENAME##_test(ivars + i, cmp, cmp_value_i);               \
    flag = flag && done;                                                       \
  }                                                                            \
  return flag;                                                                 \
}                                                                           /**/

#define PySHMEM_TEST_ANY(TYPENAME, TYPE, cmp_value, cmp_value_i, suffix)       \
static                                                                         \
size_t shmem_##TYPENAME##_test_any##suffix(TYPE *ivars, size_t nelems,         \
                                           const int *status,                  \
                                           int cmp, TYPE cmp_value)            \
{                                                                              \
  size_t i; int done; size_t idx = SIZE_MAX;                                   \
  if (PySHMEM_is_empty_set(nelems, status)) return SIZE_MAX;                   \
  for (i = 0; i < nelems; i++) {                                               \
    if (status && status[i]) continue;                                         \
    done = shmem_##TYPENAME##_test(ivars + i, cmp, cmp_value_i);               \
    if (done) { idx = i; break; }                                              \
  }                                                                            \
  return idx;                                                                  \
}                                                                           /**/

#define PySHMEM_TEST_SOME(TYPENAME, TYPE, cmp_value, cmp_value_i, suffix)      \
static                                                                         \
size_t shmem_##TYPENAME##_test_some##suffix(TYPE *ivars, size_t nelems,        \
                                            size_t *indices,                   \
                                            const int *status,                 \
                                            int cmp, TYPE cmp_value)           \
{                                                                              \
  size_t i; int done; size_t num = 0;                                          \
  if (PySHMEM_is_empty_set(nelems, status)) return 0;                          \
  for (i = 0; i < nelems; i++) {                                               \
    if (status && status[i]) continue;                                         \
    done = shmem_##TYPENAME##_test(ivars + i, cmp, cmp_value_i);               \
    if (done) { indices[num++] = i; }                                          \
  }                                                                            \
  return num;                                                                  \
}                                                                           /**/


#define PySHMEM_SYNC_WAIT(SYNC, TYPENAME, TYPE) \
  SYNC(PySHMEM_WAIT_ALL,  TYPENAME, TYPE) \
  SYNC(PySHMEM_WAIT_ANY,  TYPENAME, TYPE) \
  SYNC(PySHMEM_WAIT_SOME, TYPENAME, TYPE)

#define PySHMEM_SYNC_TEST(SYNC, TYPENAME, TYPE) \
  SYNC(PySHMEM_TEST_ALL,  TYPENAME, TYPE) \
  SYNC(PySHMEM_TEST_ANY,  TYPENAME, TYPE) \
  SYNC(PySHMEM_TEST_SOME, TYPENAME, TYPE)

#define PySHMEM_SYNC_SCALAR(SYNC, TYPENAME, TYPE) \
  SYNC(TYPENAME, TYPE, cmp_value, cmp_value, /**/)

#define PySHMEM_SYNC_VECTOR(SYNC, TYPENAME, TYPE) \
  SYNC(TYPENAME, TYPE, cmp_value[], cmp_value[i], _vector)

#define PySHMEM_WAIT_SCALAR(TYPENAME, TYPE) \
  PySHMEM_SYNC_WAIT(PySHMEM_SYNC_SCALAR, TYPENAME, TYPE)

#define PySHMEM_WAIT_VECTOR(TYPENAME, TYPE) \
  PySHMEM_SYNC_WAIT(PySHMEM_SYNC_VECTOR, TYPENAME, TYPE)

#define PySHMEM_TEST_SCALAR(TYPENAME, TYPE) \
  PySHMEM_SYNC_TEST(PySHMEM_SYNC_SCALAR, TYPENAME, TYPE)

#define PySHMEM_TEST_VECTOR(TYPENAME, TYPE) \
  PySHMEM_SYNC_TEST(PySHMEM_SYNC_VECTOR, TYPENAME, TYPE)

#define PySHMEM_SYNC(TYPENAME, TYPE)  \
  PySHMEM_WAIT_SCALAR(TYPENAME, TYPE) \
  PySHMEM_WAIT_VECTOR(TYPENAME, TYPE) \
  PySHMEM_TEST_SCALAR(TYPENAME, TYPE) \
  PySHMEM_TEST_VECTOR(TYPENAME, TYPE)

PySHMEM_SYNC( int,        int                )
PySHMEM_SYNC( long,       long               )
PySHMEM_SYNC( longlong,   long long          )
PySHMEM_SYNC( uint,       unsigned int       )
PySHMEM_SYNC( ulong,      unsigned long      )
PySHMEM_SYNC( ulonglong,  unsigned long long )
PySHMEM_SYNC( int32,      int32_t            )
PySHMEM_SYNC( int64,      int64_t            )
PySHMEM_SYNC( uint32,     uint32_t           )
PySHMEM_SYNC( uint64,     uint64_t           )
PySHMEM_SYNC( size,       size_t             )
PySHMEM_SYNC( ptrdiff,    ptrdiff_t          )

#endif

/* --- */

#if !defined(PySHMEM_HAVE_shmem_pcontrol)

static
void shmem_pcontrol(int level, ...)
{
  (void)level;
}

#endif

/* --- */
