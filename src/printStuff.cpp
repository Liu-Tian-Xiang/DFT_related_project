#include "../includes/global.h"
#include "../includes/prototype.h"
void push_sub(){

}
void printResult(char Name[],MKL_Complex16 F[],int n1,int n2,int n3,double tol){
    cout<<Name<<endl;
    cout<<endl;
    for(int kk=0;kk<n3;kk++){
	printf( "##%s(:,:,%d)=\n\n", Name,kk+1 );
	for(int j=0;j<n2;j++){
	    for(int i=0;i<n1;i++){
		if(F[i*n2*n3+j*n3+kk].real){
		    cout<<"F("<<i<<","<<j<<","<<kk<<")=("<<(fabs(F[i*n2*n3+j*n3+kk].real)<tol?0:F[i*n2*n3+j*n3+kk].real)<<","<<(fabs(F[i*n2*n3+j*n3+kk].real)<tol?0:F[i*n2*n3+j*n3+kk].imag)<<")"<<endl;
		}
	    }cout<<endl;
	}cout<<endl;
    }
}

void printResult(char Name[],double F[],int n1,int n2,int n3,double tol){
    cout<<Name<<endl;
    cout<<endl;
    for(int kk=0;kk<n3;kk++){
	printf( "##%s(:,:,%d)=\n\n", Name,kk+1 );
	for(int j=0;j<n2;j++){
	    for(int i=0;i<n1;i++){
		if(F[i*n2*n3+j*n3+kk]){
		    cout<<"F("<<i<<","<<j<<","<<kk<<")=("<<(fabs(F[i*n2*n3+j*n3+kk])<tol?0:F[i*n2*n3+j*n3+kk])<<")"<<endl;
		}
	    }cout<<endl;
	}cout<<endl;
    }
}


void print_matrix( char* desc, MKL_INT m, MKL_INT n, lapack_complex_double* a, MKL_INT lda ) {
    MKL_INT i, j;
    printf( "\n %s\n", desc );
    for( i = 0; i < m; i++ ) {
	for( j = 0; j < n; j++ )
	    printf( " (%6.6f,%6.6f)", a[i*lda+j].real, a[i*lda+j].imag );
	printf( "\n" );
    }
}

void print_rmatrix( char* desc, MKL_INT m, MKL_INT n, double* a, MKL_INT lda ) {
    MKL_INT i, j;
    printf( "\n %s\n", desc );
    for( i = 0; i < m; i++ ) {
	for( j = 0; j < n; j++ ) printf( " %6.6f", a[i*lda+j] );
	printf( "\n" );
    }
}



