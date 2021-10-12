#ifndef PySHMEM_COMPAT_OSSS_H
#define PySHMEM_COMPAT_OSSS_H

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
