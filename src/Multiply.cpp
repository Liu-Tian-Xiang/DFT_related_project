#include "../includes/global.h"
#include "../includes/prototype.h"

void multiply(lapack_complex_double* A,lapack_complex_double* B,lapack_complex_double *C,int ldR,int ldZ){

    MKL_Complex16 One={1,0};
    MKL_Complex16 Zero={0,0};
    cblas_zgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, ldR, ldZ, ldR, &One, A, ldR, B, ldZ, &Zero, C, ldZ);
}

double* Multiply(spMatrix *A,int ldA,int ldk,spMatrix *B,int ldB){
    double *R;
    R=(double *)calloc(ldA*ldB,sizeof(double));
    for(int i=0;i<ldA;i++){
	for(int j=0;j<ldB;j++){
	    ////////////////////
	    for(int k=0;k<ldk;k++){
		R[i*ldB+j]+=A->element(i,k)*B->element(k,j);
	    }
	    ////////////////////
	}
    }
    return R;
}


double* Multiply(double *A,int ldA,int ldk,spMatrix *B,int ldB){
    double *R;
    R=(double *)calloc(ldB*ldA,sizeof(double));
    for(int i=0;i<ldA;i++){
	for(int j=0;j<ldB;j++){
	    ////////////////////
	    for(int k=0;k<ldk;k++){
		R[i*ldB+j]+=A[i*ldk+k]*B->element(k,j);
	    }
	    ////////////////////
	}
    }
    return R;
}


double* Multiply(spMatrix *A,int ldA,int ldk,double *B,int ldB){
    double *R;
    R=(double *)calloc(ldA*ldB,sizeof(double));
    for(int i=0;i<ldA;i++){
	for(int j=0;j<ldB;j++){

	    for(int k=0;k<ldk;k++){
		R[i*ldB+j]+=A->element(i,k)*B[k*ldB+j];
	    }

	}
    }
    return R;
}



double* Multiply(double *A,int ldA,int ldk,double *B,int ldB){
    double *R;
    R=(double *)calloc(ldA*ldB,sizeof(double));
    for(int i=0;i<ldA;i++){
	for(int j=0;j<ldB;j++){

	    for(int k=0;k<ldk;k++){
		R[i*ldB+j]+=A[i*ldk+k]*B[k*ldB+j];
	    }

	}
    }
    return R;
}



