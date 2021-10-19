#ifndef PySHMEM_Thread_local
# if __STDC_VERSION__ >= 201112
#   define PySHMEM_Thread_local _Thread_local
# elif defined __GNUC__   || \
       defined __xlC__    || \
       defined __SUNPRO_C
#  define PySHMEM_Thread_local __thread
# elif defined _WIN32 &&   (  \
       defined _MSC_VER    || \
       defined __ICL       || \
       defined __DMC__     || \
       defined __BORLANDC__ )
#   define PySHMEM_Thread_local __declspec(thread)
# endif
#endif

static PySHMEM_Thread_local int _shmem_error = 0;

#define PySHMEM_UNAVAILABLE (_shmem_error = -1431655766) /*0xAAAAAAAA*/
