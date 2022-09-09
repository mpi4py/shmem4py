#ifndef PySHMEM_COMPAT_CRAY_H
#define PySHMEM_COMPAT_CRAY_H

static
void shmem_complexf_sum_to_all(float _Complex *dest, const float _Complex *source, int nreduce,
			       int PE_start, int logPE_stride, int PE_size,
			       float _Complex *pWrk, long *pSync)
{
  shmem_float_sum_to_all((float*)dest, (float*)source, 2*nreduce,
			 PE_start, logPE_stride, PE_size,
			 (float*)pWrk, pSync);
}

static
void shmem_complexd_sum_to_all(double _Complex *dest, const double _Complex *source, int nreduce,
			       int PE_start, int logPE_stride, int PE_size,
			       double _Complex *pWrk, long *pSync)
{
  shmem_double_sum_to_all((double*)dest, (double*)source, 2*nreduce,
			  PE_start, logPE_stride, PE_size,
			  (double*)pWrk, pSync);
}

static
void shmem_complexf_prod_to_all(float _Complex *dest, const float _Complex *source, int nreduce,
				int PE_start, int logPE_stride, int PE_size,
				float _Complex *pWrk, long *pSync)
{
  (void)dest; (void)source; (void)nreduce;
  (void)PE_start; (void)logPE_stride;
  (void)PE_size; (void)pWrk; (void)pSync;
  PySHMEM_UNAVAILABLE;
}

static
void shmem_complexd_prod_to_all(double _Complex *dest, const double _Complex *source, int nreduce,
				int PE_start, int logPE_stride, int PE_size,
				double _Complex *pWrk, long *pSync)
{
  (void)dest; (void)source; (void)nreduce;
  (void)PE_start; (void)logPE_stride; (void)PE_size;
  (void)pWrk; (void)pSync;
  PySHMEM_UNAVAILABLE;
}

#endif
