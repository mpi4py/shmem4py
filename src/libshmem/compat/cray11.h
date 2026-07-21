static int PySHMEM_Cray_shmem_char_max_reduce(shmem_team_t t, char *d, const char *s, size_t n) { shmem_char_max_reduce(t, d, s, n); return 0; }
#undef  shmem_char_max_reduce
#define shmem_char_max_reduce PySHMEM_Cray_shmem_char_max_reduce

static int PySHMEM_Cray_shmem_char_min_reduce(shmem_team_t t, char *d, const char *s, size_t n) { shmem_char_min_reduce(t, d, s, n); return 0; }
#undef  shmem_char_min_reduce
#define shmem_char_min_reduce PySHMEM_Cray_shmem_char_min_reduce

static int PySHMEM_Cray_shmem_char_sum_reduce(shmem_team_t t, char *d, const char *s, size_t n) { shmem_char_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_char_sum_reduce
#define shmem_char_sum_reduce PySHMEM_Cray_shmem_char_sum_reduce

static int PySHMEM_Cray_shmem_char_prod_reduce(shmem_team_t t, char *d, const char *s, size_t n) { shmem_char_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_char_prod_reduce
#define shmem_char_prod_reduce PySHMEM_Cray_shmem_char_prod_reduce

static int PySHMEM_Cray_shmem_schar_max_reduce(shmem_team_t t, signed char *d, const signed char *s, size_t n) { shmem_schar_max_reduce(t, d, s, n); return 0; }
#undef  shmem_schar_max_reduce
#define shmem_schar_max_reduce PySHMEM_Cray_shmem_schar_max_reduce

static int PySHMEM_Cray_shmem_schar_min_reduce(shmem_team_t t, signed char *d, const signed char *s, size_t n) { shmem_schar_min_reduce(t, d, s, n); return 0; }
#undef  shmem_schar_min_reduce
#define shmem_schar_min_reduce PySHMEM_Cray_shmem_schar_min_reduce

static int PySHMEM_Cray_shmem_schar_sum_reduce(shmem_team_t t, signed char *d, const signed char *s, size_t n) { shmem_schar_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_schar_sum_reduce
#define shmem_schar_sum_reduce PySHMEM_Cray_shmem_schar_sum_reduce

static int PySHMEM_Cray_shmem_schar_prod_reduce(shmem_team_t t, signed char *d, const signed char *s, size_t n) { shmem_schar_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_schar_prod_reduce
#define shmem_schar_prod_reduce PySHMEM_Cray_shmem_schar_prod_reduce

static int PySHMEM_Cray_shmem_short_max_reduce(shmem_team_t t, short *d, const short *s, size_t n) { shmem_short_max_reduce(t, d, s, n); return 0; }
#undef  shmem_short_max_reduce
#define shmem_short_max_reduce PySHMEM_Cray_shmem_short_max_reduce

static int PySHMEM_Cray_shmem_short_min_reduce(shmem_team_t t, short *d, const short *s, size_t n) { shmem_short_min_reduce(t, d, s, n); return 0; }
#undef  shmem_short_min_reduce
#define shmem_short_min_reduce PySHMEM_Cray_shmem_short_min_reduce

static int PySHMEM_Cray_shmem_short_sum_reduce(shmem_team_t t, short *d, const short *s, size_t n) { shmem_short_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_short_sum_reduce
#define shmem_short_sum_reduce PySHMEM_Cray_shmem_short_sum_reduce

static int PySHMEM_Cray_shmem_short_prod_reduce(shmem_team_t t, short *d, const short *s, size_t n) { shmem_short_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_short_prod_reduce
#define shmem_short_prod_reduce PySHMEM_Cray_shmem_short_prod_reduce

static int PySHMEM_Cray_shmem_int_max_reduce(shmem_team_t t, int *d, const int *s, size_t n) { shmem_int_max_reduce(t, d, s, n); return 0; }
#undef  shmem_int_max_reduce
#define shmem_int_max_reduce PySHMEM_Cray_shmem_int_max_reduce

static int PySHMEM_Cray_shmem_int_min_reduce(shmem_team_t t, int *d, const int *s, size_t n) { shmem_int_min_reduce(t, d, s, n); return 0; }
#undef  shmem_int_min_reduce
#define shmem_int_min_reduce PySHMEM_Cray_shmem_int_min_reduce

static int PySHMEM_Cray_shmem_int_sum_reduce(shmem_team_t t, int *d, const int *s, size_t n) { shmem_int_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_int_sum_reduce
#define shmem_int_sum_reduce PySHMEM_Cray_shmem_int_sum_reduce

static int PySHMEM_Cray_shmem_int_prod_reduce(shmem_team_t t, int *d, const int *s, size_t n) { shmem_int_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_int_prod_reduce
#define shmem_int_prod_reduce PySHMEM_Cray_shmem_int_prod_reduce

static int PySHMEM_Cray_shmem_long_max_reduce(shmem_team_t t, long *d, const long *s, size_t n) { shmem_long_max_reduce(t, d, s, n); return 0; }
#undef  shmem_long_max_reduce
#define shmem_long_max_reduce PySHMEM_Cray_shmem_long_max_reduce

static int PySHMEM_Cray_shmem_long_min_reduce(shmem_team_t t, long *d, const long *s, size_t n) { shmem_long_min_reduce(t, d, s, n); return 0; }
#undef  shmem_long_min_reduce
#define shmem_long_min_reduce PySHMEM_Cray_shmem_long_min_reduce

static int PySHMEM_Cray_shmem_long_sum_reduce(shmem_team_t t, long *d, const long *s, size_t n) { shmem_long_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_long_sum_reduce
#define shmem_long_sum_reduce PySHMEM_Cray_shmem_long_sum_reduce

static int PySHMEM_Cray_shmem_long_prod_reduce(shmem_team_t t, long *d, const long *s, size_t n) { shmem_long_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_long_prod_reduce
#define shmem_long_prod_reduce PySHMEM_Cray_shmem_long_prod_reduce

static int PySHMEM_Cray_shmem_longlong_max_reduce(shmem_team_t t, long long *d, const long long *s, size_t n) { shmem_longlong_max_reduce(t, d, s, n); return 0; }
#undef  shmem_longlong_max_reduce
#define shmem_longlong_max_reduce PySHMEM_Cray_shmem_longlong_max_reduce

static int PySHMEM_Cray_shmem_longlong_min_reduce(shmem_team_t t, long long *d, const long long *s, size_t n) { shmem_longlong_min_reduce(t, d, s, n); return 0; }
#undef  shmem_longlong_min_reduce
#define shmem_longlong_min_reduce PySHMEM_Cray_shmem_longlong_min_reduce

static int PySHMEM_Cray_shmem_longlong_sum_reduce(shmem_team_t t, long long *d, const long long *s, size_t n) { shmem_longlong_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_longlong_sum_reduce
#define shmem_longlong_sum_reduce PySHMEM_Cray_shmem_longlong_sum_reduce

static int PySHMEM_Cray_shmem_longlong_prod_reduce(shmem_team_t t, long long *d, const long long *s, size_t n) { shmem_longlong_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_longlong_prod_reduce
#define shmem_longlong_prod_reduce PySHMEM_Cray_shmem_longlong_prod_reduce

static int PySHMEM_Cray_shmem_ptrdiff_max_reduce(shmem_team_t t, ptrdiff_t *d, const ptrdiff_t *s, size_t n) { shmem_ptrdiff_max_reduce(t, d, s, n); return 0; }
#undef  shmem_ptrdiff_max_reduce
#define shmem_ptrdiff_max_reduce PySHMEM_Cray_shmem_ptrdiff_max_reduce

static int PySHMEM_Cray_shmem_ptrdiff_min_reduce(shmem_team_t t, ptrdiff_t *d, const ptrdiff_t *s, size_t n) { shmem_ptrdiff_min_reduce(t, d, s, n); return 0; }
#undef  shmem_ptrdiff_min_reduce
#define shmem_ptrdiff_min_reduce PySHMEM_Cray_shmem_ptrdiff_min_reduce

static int PySHMEM_Cray_shmem_ptrdiff_sum_reduce(shmem_team_t t, ptrdiff_t *d, const ptrdiff_t *s, size_t n) { shmem_ptrdiff_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_ptrdiff_sum_reduce
#define shmem_ptrdiff_sum_reduce PySHMEM_Cray_shmem_ptrdiff_sum_reduce

static int PySHMEM_Cray_shmem_ptrdiff_prod_reduce(shmem_team_t t, ptrdiff_t *d, const ptrdiff_t *s, size_t n) { shmem_ptrdiff_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_ptrdiff_prod_reduce
#define shmem_ptrdiff_prod_reduce PySHMEM_Cray_shmem_ptrdiff_prod_reduce

static int PySHMEM_Cray_shmem_uchar_and_reduce(shmem_team_t t, unsigned char *d, const unsigned char *s, size_t n) { shmem_uchar_and_reduce(t, d, s, n); return 0; }
#undef  shmem_uchar_and_reduce
#define shmem_uchar_and_reduce PySHMEM_Cray_shmem_uchar_and_reduce

static int PySHMEM_Cray_shmem_uchar_or_reduce(shmem_team_t t, unsigned char *d, const unsigned char *s, size_t n) { shmem_uchar_or_reduce(t, d, s, n); return 0; }
#undef  shmem_uchar_or_reduce
#define shmem_uchar_or_reduce PySHMEM_Cray_shmem_uchar_or_reduce

static int PySHMEM_Cray_shmem_uchar_xor_reduce(shmem_team_t t, unsigned char *d, const unsigned char *s, size_t n) { shmem_uchar_xor_reduce(t, d, s, n); return 0; }
#undef  shmem_uchar_xor_reduce
#define shmem_uchar_xor_reduce PySHMEM_Cray_shmem_uchar_xor_reduce

static int PySHMEM_Cray_shmem_uchar_max_reduce(shmem_team_t t, unsigned char *d, const unsigned char *s, size_t n) { shmem_uchar_max_reduce(t, d, s, n); return 0; }
#undef  shmem_uchar_max_reduce
#define shmem_uchar_max_reduce PySHMEM_Cray_shmem_uchar_max_reduce

static int PySHMEM_Cray_shmem_uchar_min_reduce(shmem_team_t t, unsigned char *d, const unsigned char *s, size_t n) { shmem_uchar_min_reduce(t, d, s, n); return 0; }
#undef  shmem_uchar_min_reduce
#define shmem_uchar_min_reduce PySHMEM_Cray_shmem_uchar_min_reduce

static int PySHMEM_Cray_shmem_uchar_sum_reduce(shmem_team_t t, unsigned char *d, const unsigned char *s, size_t n) { shmem_uchar_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_uchar_sum_reduce
#define shmem_uchar_sum_reduce PySHMEM_Cray_shmem_uchar_sum_reduce

static int PySHMEM_Cray_shmem_uchar_prod_reduce(shmem_team_t t, unsigned char *d, const unsigned char *s, size_t n) { shmem_uchar_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_uchar_prod_reduce
#define shmem_uchar_prod_reduce PySHMEM_Cray_shmem_uchar_prod_reduce

static int PySHMEM_Cray_shmem_ushort_and_reduce(shmem_team_t t, unsigned short *d, const unsigned short *s, size_t n) { shmem_ushort_and_reduce(t, d, s, n); return 0; }
#undef  shmem_ushort_and_reduce
#define shmem_ushort_and_reduce PySHMEM_Cray_shmem_ushort_and_reduce

static int PySHMEM_Cray_shmem_ushort_or_reduce(shmem_team_t t, unsigned short *d, const unsigned short *s, size_t n) { shmem_ushort_or_reduce(t, d, s, n); return 0; }
#undef  shmem_ushort_or_reduce
#define shmem_ushort_or_reduce PySHMEM_Cray_shmem_ushort_or_reduce

static int PySHMEM_Cray_shmem_ushort_xor_reduce(shmem_team_t t, unsigned short *d, const unsigned short *s, size_t n) { shmem_ushort_xor_reduce(t, d, s, n); return 0; }
#undef  shmem_ushort_xor_reduce
#define shmem_ushort_xor_reduce PySHMEM_Cray_shmem_ushort_xor_reduce

static int PySHMEM_Cray_shmem_ushort_max_reduce(shmem_team_t t, unsigned short *d, const unsigned short *s, size_t n) { shmem_ushort_max_reduce(t, d, s, n); return 0; }
#undef  shmem_ushort_max_reduce
#define shmem_ushort_max_reduce PySHMEM_Cray_shmem_ushort_max_reduce

static int PySHMEM_Cray_shmem_ushort_min_reduce(shmem_team_t t, unsigned short *d, const unsigned short *s, size_t n) { shmem_ushort_min_reduce(t, d, s, n); return 0; }
#undef  shmem_ushort_min_reduce
#define shmem_ushort_min_reduce PySHMEM_Cray_shmem_ushort_min_reduce

static int PySHMEM_Cray_shmem_ushort_sum_reduce(shmem_team_t t, unsigned short *d, const unsigned short *s, size_t n) { shmem_ushort_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_ushort_sum_reduce
#define shmem_ushort_sum_reduce PySHMEM_Cray_shmem_ushort_sum_reduce

static int PySHMEM_Cray_shmem_ushort_prod_reduce(shmem_team_t t, unsigned short *d, const unsigned short *s, size_t n) { shmem_ushort_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_ushort_prod_reduce
#define shmem_ushort_prod_reduce PySHMEM_Cray_shmem_ushort_prod_reduce

static int PySHMEM_Cray_shmem_uint_and_reduce(shmem_team_t t, unsigned int *d, const unsigned int *s, size_t n) { shmem_uint_and_reduce(t, d, s, n); return 0; }
#undef  shmem_uint_and_reduce
#define shmem_uint_and_reduce PySHMEM_Cray_shmem_uint_and_reduce

static int PySHMEM_Cray_shmem_uint_or_reduce(shmem_team_t t, unsigned int *d, const unsigned int *s, size_t n) { shmem_uint_or_reduce(t, d, s, n); return 0; }
#undef  shmem_uint_or_reduce
#define shmem_uint_or_reduce PySHMEM_Cray_shmem_uint_or_reduce

static int PySHMEM_Cray_shmem_uint_xor_reduce(shmem_team_t t, unsigned int *d, const unsigned int *s, size_t n) { shmem_uint_xor_reduce(t, d, s, n); return 0; }
#undef  shmem_uint_xor_reduce
#define shmem_uint_xor_reduce PySHMEM_Cray_shmem_uint_xor_reduce

static int PySHMEM_Cray_shmem_uint_max_reduce(shmem_team_t t, unsigned int *d, const unsigned int *s, size_t n) { shmem_uint_max_reduce(t, d, s, n); return 0; }
#undef  shmem_uint_max_reduce
#define shmem_uint_max_reduce PySHMEM_Cray_shmem_uint_max_reduce

static int PySHMEM_Cray_shmem_uint_min_reduce(shmem_team_t t, unsigned int *d, const unsigned int *s, size_t n) { shmem_uint_min_reduce(t, d, s, n); return 0; }
#undef  shmem_uint_min_reduce
#define shmem_uint_min_reduce PySHMEM_Cray_shmem_uint_min_reduce

static int PySHMEM_Cray_shmem_uint_sum_reduce(shmem_team_t t, unsigned int *d, const unsigned int *s, size_t n) { shmem_uint_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_uint_sum_reduce
#define shmem_uint_sum_reduce PySHMEM_Cray_shmem_uint_sum_reduce

static int PySHMEM_Cray_shmem_uint_prod_reduce(shmem_team_t t, unsigned int *d, const unsigned int *s, size_t n) { shmem_uint_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_uint_prod_reduce
#define shmem_uint_prod_reduce PySHMEM_Cray_shmem_uint_prod_reduce

static int PySHMEM_Cray_shmem_ulong_and_reduce(shmem_team_t t, unsigned long *d, const unsigned long *s, size_t n) { shmem_ulong_and_reduce(t, d, s, n); return 0; }
#undef  shmem_ulong_and_reduce
#define shmem_ulong_and_reduce PySHMEM_Cray_shmem_ulong_and_reduce

static int PySHMEM_Cray_shmem_ulong_or_reduce(shmem_team_t t, unsigned long *d, const unsigned long *s, size_t n) { shmem_ulong_or_reduce(t, d, s, n); return 0; }
#undef  shmem_ulong_or_reduce
#define shmem_ulong_or_reduce PySHMEM_Cray_shmem_ulong_or_reduce

static int PySHMEM_Cray_shmem_ulong_xor_reduce(shmem_team_t t, unsigned long *d, const unsigned long *s, size_t n) { shmem_ulong_xor_reduce(t, d, s, n); return 0; }
#undef  shmem_ulong_xor_reduce
#define shmem_ulong_xor_reduce PySHMEM_Cray_shmem_ulong_xor_reduce

static int PySHMEM_Cray_shmem_ulong_max_reduce(shmem_team_t t, unsigned long *d, const unsigned long *s, size_t n) { shmem_ulong_max_reduce(t, d, s, n); return 0; }
#undef  shmem_ulong_max_reduce
#define shmem_ulong_max_reduce PySHMEM_Cray_shmem_ulong_max_reduce

static int PySHMEM_Cray_shmem_ulong_min_reduce(shmem_team_t t, unsigned long *d, const unsigned long *s, size_t n) { shmem_ulong_min_reduce(t, d, s, n); return 0; }
#undef  shmem_ulong_min_reduce
#define shmem_ulong_min_reduce PySHMEM_Cray_shmem_ulong_min_reduce

static int PySHMEM_Cray_shmem_ulong_sum_reduce(shmem_team_t t, unsigned long *d, const unsigned long *s, size_t n) { shmem_ulong_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_ulong_sum_reduce
#define shmem_ulong_sum_reduce PySHMEM_Cray_shmem_ulong_sum_reduce

static int PySHMEM_Cray_shmem_ulong_prod_reduce(shmem_team_t t, unsigned long *d, const unsigned long *s, size_t n) { shmem_ulong_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_ulong_prod_reduce
#define shmem_ulong_prod_reduce PySHMEM_Cray_shmem_ulong_prod_reduce

static int PySHMEM_Cray_shmem_ulonglong_and_reduce(shmem_team_t t, unsigned long long *d, const unsigned long long *s, size_t n) { shmem_ulonglong_and_reduce(t, d, s, n); return 0; }
#undef  shmem_ulonglong_and_reduce
#define shmem_ulonglong_and_reduce PySHMEM_Cray_shmem_ulonglong_and_reduce

static int PySHMEM_Cray_shmem_ulonglong_or_reduce(shmem_team_t t, unsigned long long *d, const unsigned long long *s, size_t n) { shmem_ulonglong_or_reduce(t, d, s, n); return 0; }
#undef  shmem_ulonglong_or_reduce
#define shmem_ulonglong_or_reduce PySHMEM_Cray_shmem_ulonglong_or_reduce

static int PySHMEM_Cray_shmem_ulonglong_xor_reduce(shmem_team_t t, unsigned long long *d, const unsigned long long *s, size_t n) { shmem_ulonglong_xor_reduce(t, d, s, n); return 0; }
#undef  shmem_ulonglong_xor_reduce
#define shmem_ulonglong_xor_reduce PySHMEM_Cray_shmem_ulonglong_xor_reduce

static int PySHMEM_Cray_shmem_ulonglong_max_reduce(shmem_team_t t, unsigned long long *d, const unsigned long long *s, size_t n) { shmem_ulonglong_max_reduce(t, d, s, n); return 0; }
#undef  shmem_ulonglong_max_reduce
#define shmem_ulonglong_max_reduce PySHMEM_Cray_shmem_ulonglong_max_reduce

static int PySHMEM_Cray_shmem_ulonglong_min_reduce(shmem_team_t t, unsigned long long *d, const unsigned long long *s, size_t n) { shmem_ulonglong_min_reduce(t, d, s, n); return 0; }
#undef  shmem_ulonglong_min_reduce
#define shmem_ulonglong_min_reduce PySHMEM_Cray_shmem_ulonglong_min_reduce

static int PySHMEM_Cray_shmem_ulonglong_sum_reduce(shmem_team_t t, unsigned long long *d, const unsigned long long *s, size_t n) { shmem_ulonglong_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_ulonglong_sum_reduce
#define shmem_ulonglong_sum_reduce PySHMEM_Cray_shmem_ulonglong_sum_reduce

static int PySHMEM_Cray_shmem_ulonglong_prod_reduce(shmem_team_t t, unsigned long long *d, const unsigned long long *s, size_t n) { shmem_ulonglong_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_ulonglong_prod_reduce
#define shmem_ulonglong_prod_reduce PySHMEM_Cray_shmem_ulonglong_prod_reduce

static int PySHMEM_Cray_shmem_int8_and_reduce(shmem_team_t t, int8_t *d, const int8_t *s, size_t n) { shmem_int8_and_reduce(t, d, s, n); return 0; }
#undef  shmem_int8_and_reduce
#define shmem_int8_and_reduce PySHMEM_Cray_shmem_int8_and_reduce

static int PySHMEM_Cray_shmem_int8_or_reduce(shmem_team_t t, int8_t *d, const int8_t *s, size_t n) { shmem_int8_or_reduce(t, d, s, n); return 0; }
#undef  shmem_int8_or_reduce
#define shmem_int8_or_reduce PySHMEM_Cray_shmem_int8_or_reduce

static int PySHMEM_Cray_shmem_int8_xor_reduce(shmem_team_t t, int8_t *d, const int8_t *s, size_t n) { shmem_int8_xor_reduce(t, d, s, n); return 0; }
#undef  shmem_int8_xor_reduce
#define shmem_int8_xor_reduce PySHMEM_Cray_shmem_int8_xor_reduce

static int PySHMEM_Cray_shmem_int8_max_reduce(shmem_team_t t, int8_t *d, const int8_t *s, size_t n) { shmem_int8_max_reduce(t, d, s, n); return 0; }
#undef  shmem_int8_max_reduce
#define shmem_int8_max_reduce PySHMEM_Cray_shmem_int8_max_reduce

static int PySHMEM_Cray_shmem_int8_min_reduce(shmem_team_t t, int8_t *d, const int8_t *s, size_t n) { shmem_int8_min_reduce(t, d, s, n); return 0; }
#undef  shmem_int8_min_reduce
#define shmem_int8_min_reduce PySHMEM_Cray_shmem_int8_min_reduce

static int PySHMEM_Cray_shmem_int8_sum_reduce(shmem_team_t t, int8_t *d, const int8_t *s, size_t n) { shmem_int8_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_int8_sum_reduce
#define shmem_int8_sum_reduce PySHMEM_Cray_shmem_int8_sum_reduce

static int PySHMEM_Cray_shmem_int8_prod_reduce(shmem_team_t t, int8_t *d, const int8_t *s, size_t n) { shmem_int8_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_int8_prod_reduce
#define shmem_int8_prod_reduce PySHMEM_Cray_shmem_int8_prod_reduce

static int PySHMEM_Cray_shmem_int16_and_reduce(shmem_team_t t, int16_t *d, const int16_t *s, size_t n) { shmem_int16_and_reduce(t, d, s, n); return 0; }
#undef  shmem_int16_and_reduce
#define shmem_int16_and_reduce PySHMEM_Cray_shmem_int16_and_reduce

static int PySHMEM_Cray_shmem_int16_or_reduce(shmem_team_t t, int16_t *d, const int16_t *s, size_t n) { shmem_int16_or_reduce(t, d, s, n); return 0; }
#undef  shmem_int16_or_reduce
#define shmem_int16_or_reduce PySHMEM_Cray_shmem_int16_or_reduce

static int PySHMEM_Cray_shmem_int16_xor_reduce(shmem_team_t t, int16_t *d, const int16_t *s, size_t n) { shmem_int16_xor_reduce(t, d, s, n); return 0; }
#undef  shmem_int16_xor_reduce
#define shmem_int16_xor_reduce PySHMEM_Cray_shmem_int16_xor_reduce

static int PySHMEM_Cray_shmem_int16_max_reduce(shmem_team_t t, int16_t *d, const int16_t *s, size_t n) { shmem_int16_max_reduce(t, d, s, n); return 0; }
#undef  shmem_int16_max_reduce
#define shmem_int16_max_reduce PySHMEM_Cray_shmem_int16_max_reduce

static int PySHMEM_Cray_shmem_int16_min_reduce(shmem_team_t t, int16_t *d, const int16_t *s, size_t n) { shmem_int16_min_reduce(t, d, s, n); return 0; }
#undef  shmem_int16_min_reduce
#define shmem_int16_min_reduce PySHMEM_Cray_shmem_int16_min_reduce

static int PySHMEM_Cray_shmem_int16_sum_reduce(shmem_team_t t, int16_t *d, const int16_t *s, size_t n) { shmem_int16_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_int16_sum_reduce
#define shmem_int16_sum_reduce PySHMEM_Cray_shmem_int16_sum_reduce

static int PySHMEM_Cray_shmem_int16_prod_reduce(shmem_team_t t, int16_t *d, const int16_t *s, size_t n) { shmem_int16_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_int16_prod_reduce
#define shmem_int16_prod_reduce PySHMEM_Cray_shmem_int16_prod_reduce

static int PySHMEM_Cray_shmem_int32_and_reduce(shmem_team_t t, int32_t *d, const int32_t *s, size_t n) { shmem_int32_and_reduce(t, d, s, n); return 0; }
#undef  shmem_int32_and_reduce
#define shmem_int32_and_reduce PySHMEM_Cray_shmem_int32_and_reduce

static int PySHMEM_Cray_shmem_int32_or_reduce(shmem_team_t t, int32_t *d, const int32_t *s, size_t n) { shmem_int32_or_reduce(t, d, s, n); return 0; }
#undef  shmem_int32_or_reduce
#define shmem_int32_or_reduce PySHMEM_Cray_shmem_int32_or_reduce

static int PySHMEM_Cray_shmem_int32_xor_reduce(shmem_team_t t, int32_t *d, const int32_t *s, size_t n) { shmem_int32_xor_reduce(t, d, s, n); return 0; }
#undef  shmem_int32_xor_reduce
#define shmem_int32_xor_reduce PySHMEM_Cray_shmem_int32_xor_reduce

static int PySHMEM_Cray_shmem_int32_max_reduce(shmem_team_t t, int32_t *d, const int32_t *s, size_t n) { shmem_int32_max_reduce(t, d, s, n); return 0; }
#undef  shmem_int32_max_reduce
#define shmem_int32_max_reduce PySHMEM_Cray_shmem_int32_max_reduce

static int PySHMEM_Cray_shmem_int32_min_reduce(shmem_team_t t, int32_t *d, const int32_t *s, size_t n) { shmem_int32_min_reduce(t, d, s, n); return 0; }
#undef  shmem_int32_min_reduce
#define shmem_int32_min_reduce PySHMEM_Cray_shmem_int32_min_reduce

static int PySHMEM_Cray_shmem_int32_sum_reduce(shmem_team_t t, int32_t *d, const int32_t *s, size_t n) { shmem_int32_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_int32_sum_reduce
#define shmem_int32_sum_reduce PySHMEM_Cray_shmem_int32_sum_reduce

static int PySHMEM_Cray_shmem_int32_prod_reduce(shmem_team_t t, int32_t *d, const int32_t *s, size_t n) { shmem_int32_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_int32_prod_reduce
#define shmem_int32_prod_reduce PySHMEM_Cray_shmem_int32_prod_reduce

static int PySHMEM_Cray_shmem_int64_and_reduce(shmem_team_t t, int64_t *d, const int64_t *s, size_t n) { shmem_int64_and_reduce(t, d, s, n); return 0; }
#undef  shmem_int64_and_reduce
#define shmem_int64_and_reduce PySHMEM_Cray_shmem_int64_and_reduce

static int PySHMEM_Cray_shmem_int64_or_reduce(shmem_team_t t, int64_t *d, const int64_t *s, size_t n) { shmem_int64_or_reduce(t, d, s, n); return 0; }
#undef  shmem_int64_or_reduce
#define shmem_int64_or_reduce PySHMEM_Cray_shmem_int64_or_reduce

static int PySHMEM_Cray_shmem_int64_xor_reduce(shmem_team_t t, int64_t *d, const int64_t *s, size_t n) { shmem_int64_xor_reduce(t, d, s, n); return 0; }
#undef  shmem_int64_xor_reduce
#define shmem_int64_xor_reduce PySHMEM_Cray_shmem_int64_xor_reduce

static int PySHMEM_Cray_shmem_int64_max_reduce(shmem_team_t t, int64_t *d, const int64_t *s, size_t n) { shmem_int64_max_reduce(t, d, s, n); return 0; }
#undef  shmem_int64_max_reduce
#define shmem_int64_max_reduce PySHMEM_Cray_shmem_int64_max_reduce

static int PySHMEM_Cray_shmem_int64_min_reduce(shmem_team_t t, int64_t *d, const int64_t *s, size_t n) { shmem_int64_min_reduce(t, d, s, n); return 0; }
#undef  shmem_int64_min_reduce
#define shmem_int64_min_reduce PySHMEM_Cray_shmem_int64_min_reduce

static int PySHMEM_Cray_shmem_int64_sum_reduce(shmem_team_t t, int64_t *d, const int64_t *s, size_t n) { shmem_int64_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_int64_sum_reduce
#define shmem_int64_sum_reduce PySHMEM_Cray_shmem_int64_sum_reduce

static int PySHMEM_Cray_shmem_int64_prod_reduce(shmem_team_t t, int64_t *d, const int64_t *s, size_t n) { shmem_int64_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_int64_prod_reduce
#define shmem_int64_prod_reduce PySHMEM_Cray_shmem_int64_prod_reduce

static int PySHMEM_Cray_shmem_uint8_and_reduce(shmem_team_t t, uint8_t *d, const uint8_t *s, size_t n) { shmem_uint8_and_reduce(t, d, s, n); return 0; }
#undef  shmem_uint8_and_reduce
#define shmem_uint8_and_reduce PySHMEM_Cray_shmem_uint8_and_reduce

static int PySHMEM_Cray_shmem_uint8_or_reduce(shmem_team_t t, uint8_t *d, const uint8_t *s, size_t n) { shmem_uint8_or_reduce(t, d, s, n); return 0; }
#undef  shmem_uint8_or_reduce
#define shmem_uint8_or_reduce PySHMEM_Cray_shmem_uint8_or_reduce

static int PySHMEM_Cray_shmem_uint8_xor_reduce(shmem_team_t t, uint8_t *d, const uint8_t *s, size_t n) { shmem_uint8_xor_reduce(t, d, s, n); return 0; }
#undef  shmem_uint8_xor_reduce
#define shmem_uint8_xor_reduce PySHMEM_Cray_shmem_uint8_xor_reduce

static int PySHMEM_Cray_shmem_uint8_max_reduce(shmem_team_t t, uint8_t *d, const uint8_t *s, size_t n) { shmem_uint8_max_reduce(t, d, s, n); return 0; }
#undef  shmem_uint8_max_reduce
#define shmem_uint8_max_reduce PySHMEM_Cray_shmem_uint8_max_reduce

static int PySHMEM_Cray_shmem_uint8_min_reduce(shmem_team_t t, uint8_t *d, const uint8_t *s, size_t n) { shmem_uint8_min_reduce(t, d, s, n); return 0; }
#undef  shmem_uint8_min_reduce
#define shmem_uint8_min_reduce PySHMEM_Cray_shmem_uint8_min_reduce

static int PySHMEM_Cray_shmem_uint8_sum_reduce(shmem_team_t t, uint8_t *d, const uint8_t *s, size_t n) { shmem_uint8_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_uint8_sum_reduce
#define shmem_uint8_sum_reduce PySHMEM_Cray_shmem_uint8_sum_reduce

static int PySHMEM_Cray_shmem_uint8_prod_reduce(shmem_team_t t, uint8_t *d, const uint8_t *s, size_t n) { shmem_uint8_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_uint8_prod_reduce
#define shmem_uint8_prod_reduce PySHMEM_Cray_shmem_uint8_prod_reduce

static int PySHMEM_Cray_shmem_uint16_and_reduce(shmem_team_t t, uint16_t *d, const uint16_t *s, size_t n) { shmem_uint16_and_reduce(t, d, s, n); return 0; }
#undef  shmem_uint16_and_reduce
#define shmem_uint16_and_reduce PySHMEM_Cray_shmem_uint16_and_reduce

static int PySHMEM_Cray_shmem_uint16_or_reduce(shmem_team_t t, uint16_t *d, const uint16_t *s, size_t n) { shmem_uint16_or_reduce(t, d, s, n); return 0; }
#undef  shmem_uint16_or_reduce
#define shmem_uint16_or_reduce PySHMEM_Cray_shmem_uint16_or_reduce

static int PySHMEM_Cray_shmem_uint16_xor_reduce(shmem_team_t t, uint16_t *d, const uint16_t *s, size_t n) { shmem_uint16_xor_reduce(t, d, s, n); return 0; }
#undef  shmem_uint16_xor_reduce
#define shmem_uint16_xor_reduce PySHMEM_Cray_shmem_uint16_xor_reduce

static int PySHMEM_Cray_shmem_uint16_max_reduce(shmem_team_t t, uint16_t *d, const uint16_t *s, size_t n) { shmem_uint16_max_reduce(t, d, s, n); return 0; }
#undef  shmem_uint16_max_reduce
#define shmem_uint16_max_reduce PySHMEM_Cray_shmem_uint16_max_reduce

static int PySHMEM_Cray_shmem_uint16_min_reduce(shmem_team_t t, uint16_t *d, const uint16_t *s, size_t n) { shmem_uint16_min_reduce(t, d, s, n); return 0; }
#undef  shmem_uint16_min_reduce
#define shmem_uint16_min_reduce PySHMEM_Cray_shmem_uint16_min_reduce

static int PySHMEM_Cray_shmem_uint16_sum_reduce(shmem_team_t t, uint16_t *d, const uint16_t *s, size_t n) { shmem_uint16_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_uint16_sum_reduce
#define shmem_uint16_sum_reduce PySHMEM_Cray_shmem_uint16_sum_reduce

static int PySHMEM_Cray_shmem_uint16_prod_reduce(shmem_team_t t, uint16_t *d, const uint16_t *s, size_t n) { shmem_uint16_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_uint16_prod_reduce
#define shmem_uint16_prod_reduce PySHMEM_Cray_shmem_uint16_prod_reduce

static int PySHMEM_Cray_shmem_uint32_and_reduce(shmem_team_t t, uint32_t *d, const uint32_t *s, size_t n) { shmem_uint32_and_reduce(t, d, s, n); return 0; }
#undef  shmem_uint32_and_reduce
#define shmem_uint32_and_reduce PySHMEM_Cray_shmem_uint32_and_reduce

static int PySHMEM_Cray_shmem_uint32_or_reduce(shmem_team_t t, uint32_t *d, const uint32_t *s, size_t n) { shmem_uint32_or_reduce(t, d, s, n); return 0; }
#undef  shmem_uint32_or_reduce
#define shmem_uint32_or_reduce PySHMEM_Cray_shmem_uint32_or_reduce

static int PySHMEM_Cray_shmem_uint32_xor_reduce(shmem_team_t t, uint32_t *d, const uint32_t *s, size_t n) { shmem_uint32_xor_reduce(t, d, s, n); return 0; }
#undef  shmem_uint32_xor_reduce
#define shmem_uint32_xor_reduce PySHMEM_Cray_shmem_uint32_xor_reduce

static int PySHMEM_Cray_shmem_uint32_max_reduce(shmem_team_t t, uint32_t *d, const uint32_t *s, size_t n) { shmem_uint32_max_reduce(t, d, s, n); return 0; }
#undef  shmem_uint32_max_reduce
#define shmem_uint32_max_reduce PySHMEM_Cray_shmem_uint32_max_reduce

static int PySHMEM_Cray_shmem_uint32_min_reduce(shmem_team_t t, uint32_t *d, const uint32_t *s, size_t n) { shmem_uint32_min_reduce(t, d, s, n); return 0; }
#undef  shmem_uint32_min_reduce
#define shmem_uint32_min_reduce PySHMEM_Cray_shmem_uint32_min_reduce

static int PySHMEM_Cray_shmem_uint32_sum_reduce(shmem_team_t t, uint32_t *d, const uint32_t *s, size_t n) { shmem_uint32_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_uint32_sum_reduce
#define shmem_uint32_sum_reduce PySHMEM_Cray_shmem_uint32_sum_reduce

static int PySHMEM_Cray_shmem_uint32_prod_reduce(shmem_team_t t, uint32_t *d, const uint32_t *s, size_t n) { shmem_uint32_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_uint32_prod_reduce
#define shmem_uint32_prod_reduce PySHMEM_Cray_shmem_uint32_prod_reduce

static int PySHMEM_Cray_shmem_uint64_and_reduce(shmem_team_t t, uint64_t *d, const uint64_t *s, size_t n) { shmem_uint64_and_reduce(t, d, s, n); return 0; }
#undef  shmem_uint64_and_reduce
#define shmem_uint64_and_reduce PySHMEM_Cray_shmem_uint64_and_reduce

static int PySHMEM_Cray_shmem_uint64_or_reduce(shmem_team_t t, uint64_t *d, const uint64_t *s, size_t n) { shmem_uint64_or_reduce(t, d, s, n); return 0; }
#undef  shmem_uint64_or_reduce
#define shmem_uint64_or_reduce PySHMEM_Cray_shmem_uint64_or_reduce

static int PySHMEM_Cray_shmem_uint64_xor_reduce(shmem_team_t t, uint64_t *d, const uint64_t *s, size_t n) { shmem_uint64_xor_reduce(t, d, s, n); return 0; }
#undef  shmem_uint64_xor_reduce
#define shmem_uint64_xor_reduce PySHMEM_Cray_shmem_uint64_xor_reduce

static int PySHMEM_Cray_shmem_uint64_max_reduce(shmem_team_t t, uint64_t *d, const uint64_t *s, size_t n) { shmem_uint64_max_reduce(t, d, s, n); return 0; }
#undef  shmem_uint64_max_reduce
#define shmem_uint64_max_reduce PySHMEM_Cray_shmem_uint64_max_reduce

static int PySHMEM_Cray_shmem_uint64_min_reduce(shmem_team_t t, uint64_t *d, const uint64_t *s, size_t n) { shmem_uint64_min_reduce(t, d, s, n); return 0; }
#undef  shmem_uint64_min_reduce
#define shmem_uint64_min_reduce PySHMEM_Cray_shmem_uint64_min_reduce

static int PySHMEM_Cray_shmem_uint64_sum_reduce(shmem_team_t t, uint64_t *d, const uint64_t *s, size_t n) { shmem_uint64_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_uint64_sum_reduce
#define shmem_uint64_sum_reduce PySHMEM_Cray_shmem_uint64_sum_reduce

static int PySHMEM_Cray_shmem_uint64_prod_reduce(shmem_team_t t, uint64_t *d, const uint64_t *s, size_t n) { shmem_uint64_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_uint64_prod_reduce
#define shmem_uint64_prod_reduce PySHMEM_Cray_shmem_uint64_prod_reduce

static int PySHMEM_Cray_shmem_size_and_reduce(shmem_team_t t, size_t *d, const size_t *s, size_t n) { shmem_size_and_reduce(t, d, s, n); return 0; }
#undef  shmem_size_and_reduce
#define shmem_size_and_reduce PySHMEM_Cray_shmem_size_and_reduce

static int PySHMEM_Cray_shmem_size_or_reduce(shmem_team_t t, size_t *d, const size_t *s, size_t n) { shmem_size_or_reduce(t, d, s, n); return 0; }
#undef  shmem_size_or_reduce
#define shmem_size_or_reduce PySHMEM_Cray_shmem_size_or_reduce

static int PySHMEM_Cray_shmem_size_xor_reduce(shmem_team_t t, size_t *d, const size_t *s, size_t n) { shmem_size_xor_reduce(t, d, s, n); return 0; }
#undef  shmem_size_xor_reduce
#define shmem_size_xor_reduce PySHMEM_Cray_shmem_size_xor_reduce

static int PySHMEM_Cray_shmem_size_max_reduce(shmem_team_t t, size_t *d, const size_t *s, size_t n) { shmem_size_max_reduce(t, d, s, n); return 0; }
#undef  shmem_size_max_reduce
#define shmem_size_max_reduce PySHMEM_Cray_shmem_size_max_reduce

static int PySHMEM_Cray_shmem_size_min_reduce(shmem_team_t t, size_t *d, const size_t *s, size_t n) { shmem_size_min_reduce(t, d, s, n); return 0; }
#undef  shmem_size_min_reduce
#define shmem_size_min_reduce PySHMEM_Cray_shmem_size_min_reduce

static int PySHMEM_Cray_shmem_size_sum_reduce(shmem_team_t t, size_t *d, const size_t *s, size_t n) { shmem_size_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_size_sum_reduce
#define shmem_size_sum_reduce PySHMEM_Cray_shmem_size_sum_reduce

static int PySHMEM_Cray_shmem_size_prod_reduce(shmem_team_t t, size_t *d, const size_t *s, size_t n) { shmem_size_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_size_prod_reduce
#define shmem_size_prod_reduce PySHMEM_Cray_shmem_size_prod_reduce

static int PySHMEM_Cray_shmem_float_max_reduce(shmem_team_t t, float *d, const float *s, size_t n) { shmem_float_max_reduce(t, d, s, n); return 0; }
#undef  shmem_float_max_reduce
#define shmem_float_max_reduce PySHMEM_Cray_shmem_float_max_reduce

static int PySHMEM_Cray_shmem_float_min_reduce(shmem_team_t t, float *d, const float *s, size_t n) { shmem_float_min_reduce(t, d, s, n); return 0; }
#undef  shmem_float_min_reduce
#define shmem_float_min_reduce PySHMEM_Cray_shmem_float_min_reduce

static int PySHMEM_Cray_shmem_float_sum_reduce(shmem_team_t t, float *d, const float *s, size_t n) { shmem_float_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_float_sum_reduce
#define shmem_float_sum_reduce PySHMEM_Cray_shmem_float_sum_reduce

static int PySHMEM_Cray_shmem_float_prod_reduce(shmem_team_t t, float *d, const float *s, size_t n) { shmem_float_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_float_prod_reduce
#define shmem_float_prod_reduce PySHMEM_Cray_shmem_float_prod_reduce

static int PySHMEM_Cray_shmem_double_max_reduce(shmem_team_t t, double *d, const double *s, size_t n) { shmem_double_max_reduce(t, d, s, n); return 0; }
#undef  shmem_double_max_reduce
#define shmem_double_max_reduce PySHMEM_Cray_shmem_double_max_reduce

static int PySHMEM_Cray_shmem_double_min_reduce(shmem_team_t t, double *d, const double *s, size_t n) { shmem_double_min_reduce(t, d, s, n); return 0; }
#undef  shmem_double_min_reduce
#define shmem_double_min_reduce PySHMEM_Cray_shmem_double_min_reduce

static int PySHMEM_Cray_shmem_double_sum_reduce(shmem_team_t t, double *d, const double *s, size_t n) { shmem_double_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_double_sum_reduce
#define shmem_double_sum_reduce PySHMEM_Cray_shmem_double_sum_reduce

static int PySHMEM_Cray_shmem_double_prod_reduce(shmem_team_t t, double *d, const double *s, size_t n) { shmem_double_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_double_prod_reduce
#define shmem_double_prod_reduce PySHMEM_Cray_shmem_double_prod_reduce

static int PySHMEM_Cray_shmem_longdouble_max_reduce(shmem_team_t t, long double *d, const long double *s, size_t n) { shmem_longdouble_max_reduce(t, d, s, n); return 0; }
#undef  shmem_longdouble_max_reduce
#define shmem_longdouble_max_reduce PySHMEM_Cray_shmem_longdouble_max_reduce

static int PySHMEM_Cray_shmem_longdouble_min_reduce(shmem_team_t t, long double *d, const long double *s, size_t n) { shmem_longdouble_min_reduce(t, d, s, n); return 0; }
#undef  shmem_longdouble_min_reduce
#define shmem_longdouble_min_reduce PySHMEM_Cray_shmem_longdouble_min_reduce

static int PySHMEM_Cray_shmem_longdouble_sum_reduce(shmem_team_t t, long double *d, const long double *s, size_t n) { shmem_longdouble_sum_reduce(t, d, s, n); return 0; }
#undef  shmem_longdouble_sum_reduce
#define shmem_longdouble_sum_reduce PySHMEM_Cray_shmem_longdouble_sum_reduce

static int PySHMEM_Cray_shmem_longdouble_prod_reduce(shmem_team_t t, long double *d, const long double *s, size_t n) { shmem_longdouble_prod_reduce(t, d, s, n); return 0; }
#undef  shmem_longdouble_prod_reduce
#define shmem_longdouble_prod_reduce PySHMEM_Cray_shmem_longdouble_prod_reduce

static int PySHMEM_Cray_shmem_complexd_sum_reduce(shmem_team_t t, double _Complex *d, const double _Complex *s, size_t n) { shmem_double_sum_reduce(t, (double*)d, (const double*)s, 2*n); return 0; }
#undef  shmem_complexd_sum_reduce
#define shmem_complexd_sum_reduce PySHMEM_Cray_shmem_complexd_sum_reduce

static int PySHMEM_Cray_shmem_complexd_prod_reduce(shmem_team_t t, double _Complex *d, const double _Complex *s, size_t n) { (void)t; (void)d; (void)s; (void)n; return PySHMEM_UNAVAILABLE; }
#undef  shmem_complexd_prod_reduce
#define shmem_complexd_prod_reduce PySHMEM_Cray_shmem_complexd_prod_reduce

static int PySHMEM_Cray_shmem_complexf_sum_reduce(shmem_team_t t, float _Complex *d, const float _Complex *s, size_t n) { shmem_float_sum_reduce(t, (float*)d, (const float*)s, 2*n); return 0; }
#undef  shmem_complexf_sum_reduce
#define shmem_complexf_sum_reduce PySHMEM_Cray_shmem_complexf_sum_reduce

static int PySHMEM_Cray_shmem_complexf_prod_reduce(shmem_team_t t, float _Complex *d, const float _Complex *s, size_t n) { (void)t; (void)d; (void)s; (void)n; return PySHMEM_UNAVAILABLE; }
#undef  shmem_complexf_prod_reduce
#define shmem_complexf_prod_reduce PySHMEM_Cray_shmem_complexf_prod_reduce
