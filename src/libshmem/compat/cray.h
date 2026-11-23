#ifndef PySHMEM_COMPAT_CRAY_H
#define PySHMEM_COMPAT_CRAY_H

#if CRAY_SHMEM_MAJOR_VERSION == 9
#include "cray09.h"
#endif

#if CRAY_SHMEM_MAJOR_VERSION == 11
#include "cray11.h"
#endif

#endif
