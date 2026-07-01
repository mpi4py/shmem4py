#define eq_ctx(a, b) ((a) == (b))
#define ctx2id(c) ((uintptr_t)(c))
#define id2ctx(i) ((shmem_ctx_t)(i))

#define eq_team(a, b) ((a) == (b))
#define team2id(t) ((uintptr_t)(t))
#define id2team(i) ((shmem_team_t)i)
