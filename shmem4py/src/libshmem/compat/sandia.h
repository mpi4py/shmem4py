#ifndef PySHMEM_COMPAT_SANDIA_H
#define PySHMEM_COMPAT_SANDIA_H

/* https://github.com/Sandia-OpenSHMEM/SOS/pull/1018 */
static
int PySHMEM_SOS_shmem_team_get_config(shmem_team_t team, long config_mask, shmem_team_config_t *config)
{
  (void)config_mask;
  shmem_team_get_config(team, config);
  return 0;
}
#define shmem_team_get_config PySHMEM_SOS_shmem_team_get_config

#endif
