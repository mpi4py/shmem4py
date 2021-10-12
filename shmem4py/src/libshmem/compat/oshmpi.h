#ifndef PySHMEM_COMPAT_oshmpi_H
#define PySHMEM_COMPAT_oshmpi_H

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

/* https://github.com/pmodels/oshmpi/issues/122 */
static
void *PySHMEM_OSHMPI_shmem_calloc(size_t count, size_t size)
{
  return shmem_calloc(1, count * size);
}
#define shmem_calloc PySHMEM_OSHMPI_shmem_calloc

#endif
