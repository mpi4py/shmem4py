enum /*shmem_thread_levels*/ {
  SHMEM_THREAD_SINGLE,
  SHMEM_THREAD_FUNNELED,
  SHMEM_THREAD_SERIALIZED,
  SHMEM_THREAD_MULTIPLE,
};

enum /*shmem_malloc_hints*/ {
  SHMEM_MALLOC_ATOMICS_REMOTE,
  SHMEM_MALLOC_SIGNAL_REMOTE,
};

enum /*shmem_ctx_attrs*/ {
  SHMEM_CTX_PRIVATE,
  SHMEM_CTX_SERIALIZED,
  SHMEM_CTX_NOSTORE,
};

enum /*shmem_config_mask*/ {
  SHMEM_TEAM_NUM_CONTEXTS,
};

enum /*shmem_signal_ops*/ {
  SHMEM_SIGNAL_SET,
  SHMEM_SIGNAL_ADD,
};

enum /*shmem_cmp_constants*/ {
  SHMEM_CMP_EQ,
  SHMEM_CMP_NE,
  SHMEM_CMP_GT,
  SHMEM_CMP_LE,
  SHMEM_CMP_LT,
  SHMEM_CMP_GE,
};

/* SHMEM version */
const int  SHMEM_MAJOR_VERSION;
const int  SHMEM_MINOR_VERSION;
const char *const SHMEM_VENDOR_STRING;

/* Setup and Exit Routines */
void shmem_init(void);
void shmem_finalize(void);
void shmem_global_exit(int status);

/* Query Routines */
int shmem_n_pes(void);
int shmem_my_pe(void);

/* Accessability routines */
int shmem_pe_accessible(int pe);
int shmem_addr_accessible(const void *addr, int pe);
void* shmem_ptr(const void *ptr, int pe);

/* Info Routines */
const int SHMEM_MAX_NAME_LEN;
void shmem_info_get_version(int *major, int *minor);
void shmem_info_get_name(char *name);

/* Thread Support */
int  shmem_init_thread(int requested, int *provided);
void shmem_query_thread(int *provided);

/* Memory Management Routines */
void* shmem_malloc(size_t size);
void* shmem_align(size_t align, size_t size);
void* shmem_realloc(void *ptr, size_t size);
void  shmem_free(void *ptr);
void* shmem_malloc_with_hints(size_t size, long hints);
void* shmem_calloc(size_t count, size_t size);

/* Team Management Routines */
typedef <shmem_team_t> shmem_team_t;
const shmem_team_t SHMEM_TEAM_WORLD;
const shmem_team_t SHMEM_TEAM_SHARED;
const shmem_team_t SHMEM_TEAM_INVALID;
int  shmem_team_my_pe(shmem_team_t team);
int  shmem_team_n_pes(shmem_team_t team);
int  shmem_team_translate_pe(shmem_team_t src_team, int src_pe, shmem_team_t dest_team);
typedef struct {int num_contexts;} shmem_team_config_t;
int  shmem_team_split_strided(shmem_team_t parent_team, int start, int stride, int size, const shmem_team_config_t *config, long config_mask, shmem_team_t *new_team);
int  shmem_team_split_2d(shmem_team_t parent_team, int xrange, const shmem_team_config_t *xaxis_config, long xaxis_mask, shmem_team_t *xaxis_team, const shmem_team_config_t *yaxis_config, long yaxis_mask, shmem_team_t *yaxis_team);
int  shmem_team_get_config(shmem_team_t team, long config_mask, shmem_team_config_t *config);
void shmem_team_destroy(shmem_team_t team);

/* Communication Management Routines */
typedef <shmem_ctx_t> shmem_ctx_t;
const shmem_ctx_t SHMEM_CTX_INVALID;
const shmem_ctx_t SHMEM_CTX_DEFAULT;
int  shmem_ctx_create(long options, shmem_ctx_t *ctx);
void shmem_ctx_destroy(shmem_ctx_t ctx);
int  shmem_ctx_get_team(shmem_ctx_t ctx, shmem_team_t *team);
int  shmem_team_create_ctx(shmem_team_t team, long options, shmem_ctx_t *ctx);

/* Signal Routines */
uint64_t shmem_signal_fetch(const uint64_t *sig_addr);
uint64_t shmem_signal_wait_until(uint64_t *sig_addr, int cmp, uint64_t cmp_value);

/* Collective Routines */
void shmem_barrier_all(void);
void shmem_sync_all(void);
int  shmem_team_sync(shmem_team_t team);

/* Memory Ordering Routines */
void shmem_ctx_fence(shmem_ctx_t ctx);
void shmem_ctx_quiet(shmem_ctx_t ctx);
void shmem_fence(void);
void shmem_quiet(void);

/* Distributed Locking Routines */
void shmem_set_lock(long *lock);
int  shmem_test_lock(long *lock);
void shmem_clear_lock(long *lock);

/* Profiling Interface */
void shmem_pcontrol(int level, ...);
