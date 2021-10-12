#ifndef PySHMEM_CONFIG_SANDIA_H
#define PySHMEM_CONFIG_SANDIA_H

#define PySHMEM_HAVE_shmem_malloc_with_hints 1
#define PySHMEM_HAVE_shmem_team_t 1
#define PySHMEM_HAVE_SHMEM_CTX_INVALID 1
#define PySHMEM_HAVE_shmem_amo_nbi 1
#define PySHMEM_HAVE_shmem_put_signal 1
#define PySHMEM_HAVE_shmem_signal_fetch 1
#define PySHMEM_HAVE_shmem_signal_wait_until 1
#define PySHMEM_HAVE_shmem_broadcastmem 1
#define PySHMEM_HAVE_shmem_collectmem 1
#define PySHMEM_HAVE_shmem_alltoallmem 1
#define PySHMEM_HAVE_shmem_TYPENAME_alltoalls 1
#define PySHMEM_HAVE_shmem_OP_reduce 1
#define PySHMEM_HAVE_shmem_wait_test_many 1
#define PySHMEM_HAVE_shmem_pcontrol 1

/* https://github.com/Sandia-OpenSHMEM/SOS/issues/1015 */
#undef PySHMEM_HAVE_shmem_signal_wait_until

#endif
