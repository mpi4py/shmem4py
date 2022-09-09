/* --- */

#if defined(OSHMEM_MAJOR_VERSION)
#define PySHMEM_VENDOR_OpenMPI 1
#elif defined(OSHMPI_NUMVERSION)
#define PySHMEM_VENDOR_OSHMPI 1
#elif defined(CRAY_SHMEM_NUMVERSION)
#define PySHMEM_VENDOR_Cray 1
#elif defined(_SHMEM_API_H) && defined(_SHMEM_DEPR_H)
#define PySHMEM_VENDOR_OSSS 1
#elif defined(SHMEM_DEF_H) && defined(SHMEM_FUNCTION_ATTRIBUTES)
#define PySHMEM_VENDOR_Sandia 1
#endif

/* --- */

#include "libshmem/error.h"

/* --- */

/* Open MPI implementation */
#if defined(PySHMEM_VENDOR_OpenMPI)
#include "libshmem/config/openmpi.h"
#include "libshmem/compat/openmpi.h"
#endif

/* OSHMPI implementation */
#if defined(PySHMEM_VENDOR_OSHMPI)
#include "libshmem/config/oshmpi.h"
#include "libshmem/compat/oshmpi.h"
#endif

/* Cray implementation */
#if defined(PySHMEM_VENDOR_Cray)
#include "libshmem/config/cray.h"
#include "libshmem/compat/cray.h"
#endif

/* OSSS-UCX implementation */
#if defined(PySHMEM_VENDOR_OSSS)
#include "libshmem/config/osss.h"
#include "libshmem/compat/osss.h"
#endif

/* Sandia implementation */
#if defined(PySHMEM_VENDOR_Sandia)
#include "libshmem/config/sandia.h"
#include "libshmem/compat/sandia.h"
#endif

/* --- */

#include "libshmem/fallback.h"
#include "libshmem/initfini.h"
#include "libshmem/memalloc.h"

/* --- */
