#include "gmx_blas.h"

void
F77_FUNC(dger,DGER)(int *m,
                    int *n,
                    double *alpha,
                    double *x,
                    int *incx,
                    double *y,
                    int *incy,
                    double *a,
                    int *lda)
{
  int ix,kx,jy;
  int i,j;
  double temp;

  if(*m<=0 || *n<=0 || *alpha==0.0)
    return;

  if(*incy>0)
    jy = 0;
  else
    jy = *incy * (1 - *n);

  if(*incx==1) {
    for(j=0;j<*n;j++,jy+=*incy)
      if(y[jy] != 0.0) {
	temp = *alpha * y[jy];
	for(i=0;i<*m;i++)
	  a[j*(*lda)+i] += temp*x[i];
      }
  } else {
    /* non-unit incx */
    if(*incx>0) 
      kx = 0;
    else
      kx = *incx * (1 - *m);
    
    for(j=0;j<*n;j++,jy+=*incy) {
      if(y[jy] != 0.0) {
	temp = *alpha * y[jy];
	ix = kx;
	for(i=0;i<*m;i++,ix+=*incx)
	  a[j*(*lda)+i] += temp*x[ix];
      }
    }
  }
  return;
}