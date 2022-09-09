static void *shmem_py_alloc(size_t size, size_t align, long hints, int clear)
{
  void *ptr;
  size = size ? size : 1;
  if (align) {
    ptr = shmem_align(align, size);
  } else if (hints) {
    ptr = shmem_malloc_with_hints(size, hints);
  } else if (clear) {
    ptr = shmem_calloc(size, 1); clear = 0;
  } else {
    ptr = shmem_malloc(size);
  }
  if (clear) {
    memset(ptr, 0, size);
    shmem_sync_all();
  }
  return ptr;
}

static void shmem_py_free(void *ptr)
{
  if (!_py_shmem_finalized) shmem_free(ptr);
}
