#include "../includes/global.h"
#include "../includes/prototype.h"
void vals2coeffs(MKL_Complex16 F[],int n1,int n2,int n3,MKL_Complex16 FF[]){
    for(int k=0;k<n3;k++){
	MKL_Complex16 Fk[n1*n2];
	for(int i=0;i<n1;i++){
	    for(int j=0;j<n2;j++){
		Fk[i*n2+j]=F[i*n2*n3+j*n3+k];
	    }
	}
	MKL_Complex16 tFk[2*(n1-1)*n2];
	c2vals2coeffs(Fk,n1,tFk,n2);

	for(int kk=0;kk<n2;kk++){
	    FF[kk*n3+k]=tFk[kk];
	    for (int i = 1; i < n1-1; i++ ){
		FF[i*n2*n3+kk*n3+k].real=2.0*tFk[i*n2+kk].real;
		FF[i*n2*n3+kk*n3+k].imag=2.0*tFk[i*n2+kk].imag;
	    }
	    FF[(n1-1)*n2*n3+kk*n3+k]=tFk[(n1-1)*n2+kk];
	}

	for(int i=0;i<n1;i++){
	    for(int j=0;j<n2;j++){
		Fk[j*n1+i]=FF[i*n2*n3+j*n3+k];
	    }
	}
	MKL_Complex16 triFk[n2*n1];
	trivals2coeffs(Fk,n2,triFk,n1);
//	print_matrix( "triFk", n2, n1, triFk, n2 );

	for(int kk=0;kk<n1;kk++){
	    for (int i = 0; i < n2; i++ ){
		int ii;
		double fix;
		ii=(i+1-n2/2-n2%2<=0?i+n2/2:i-n2/2-n2%2);
		fix=((-n2/2+i)%2?-1:1);
		FF[kk*n2*n3+ii*n3+k].real=fix*triFk[i*n1+kk].real;
		FF[kk*n2*n3+ii*n3+k].imag=fix*triFk[i*n1+kk].imag;
	    }
	}

    }
    ///////////////////////////////////////////
    for(int j=0;j<n2;j++){
	MKL_Complex16 Fj[n1*n3];
	for(int i=0;i<n1;i++){
	    for(int k=0;k<n3;k++){
		Fj[k*n1+i]=FF[i*n2*n3+j*n3+k];
	    }
	}
	MKL_Complex16 tFj[2*(n3-1)*n1];
	c2vals2coeffs(Fj,n3,tFj,n1);
	for(int kk=0;kk<n1;kk++){
	    FF[kk*n2*n3+j*n3]=tFj[kk];
	    for (int i = 1; i < n3-1; i++ )
	    {
		FF[kk*n2*n3+j*n3+i].real=2.0*tFj[i*n1+kk].real;
		FF[kk*n2*n3+j*n3+i].imag=2.0*tFj[i*n1+kk].imag;
	    }
	    FF[kk*n2*n3+j*n3+(n3-1)]=tFj[(n3-1)*n1+kk];
	}
    }
}

void trivals2coeffs(MKL_Complex16 Fk[],int ldFk,MKL_Complex16 FF[],int ldFF){
    fftw_complex *in;
    int n = ldFk;
    fftw_complex *out;
    fftw_plan plan_forward;
    for(int kk=0;kk<ldFF;kk++){
	in = (fftw_complex*)fftw_malloc (sizeof ( fftw_complex ) * n );
	for (int i = 0; i < n; i++ ){
	    in[i][0] = Fk[i*ldFF+kk].real;
	    in[i][1] = Fk[i*ldFF+kk].imag;
	}
	out =(fftw_complex *)fftw_malloc ( sizeof ( fftw_complex ) * n );
	plan_forward = fftw_plan_dft_1d ( n, in, out, FFTW_FORWARD, FFTW_ESTIMATE );
	fftw_execute ( plan_forward );
	for (int i = 0; i < n; i++ ){
	    FF[i*ldFF+kk].real=out[i][0]/((double)n);
	    FF[i*ldFF+kk].imag=out[i][1]/((double)n);
	}
	fftw_destroy_plan ( plan_forward );
	fftw_free ( in );
	fftw_free ( out );
    }
}

void c2vals2coeffs(MKL_Complex16 Fk[],int ldFk,MKL_Complex16 FF[],int ldFF){
    MKL_Complex16 tmp[2*(ldFk-1)*ldFF];
    for(int i=0;i<(ldFk-1);i++){
	for(int j=0;j<ldFF;j++){
	    tmp[i*ldFF+j]=Fk[(ldFk-i-1)*ldFF+j];
	    tmp[(i+ldFk-1)*ldFF+j]=Fk[i*ldFF+j];
	}
    }
    fftw_complex *in;
    int n = 2*ldFk-2;
    fftw_complex *out;
    fftw_plan plan_backward;

    for(int kk=0;kk<ldFF;kk++){
	in = (fftw_complex*)fftw_malloc (sizeof ( fftw_complex ) * n );
	for (int i = 0; i < n; i++ ){
	    in[i][0] = tmp[i*ldFF+kk].real;
	    in[i][1] = tmp[i*ldFF+kk].imag;
	}
	out =(fftw_complex *)fftw_malloc ( sizeof ( fftw_complex ) * n );
	plan_backward = fftw_plan_dft_1d ( n, in, out, FFTW_BACKWARD, FFTW_ESTIMATE );
	fftw_execute ( plan_backward );
	for(int i=0;i<2*(ldFk-1);i++){
	    FF[i*ldFF+kk].real=out[i][0] / ( double ) ( n );
	    FF[i*ldFF+kk].imag=out[i][1] / ( double ) ( n );
	}
	fftw_destroy_plan ( plan_backward );
	fftw_free ( in );
	fftw_free ( out );
    }
}

