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
