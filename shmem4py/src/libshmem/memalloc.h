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
