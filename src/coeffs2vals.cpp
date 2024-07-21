#include "../includes/global.h"
#include "../includes/prototype.h"


void coeffs2vals(MKL_Complex16 F[],int n1,int n2,int n3,MKL_Complex16 FF[]){

    for(int k=0;k<n3;k++){
	MKL_Complex16 Fk[n1*n2];
	for(int i=0;i<n1;i++){
	    for(int j=0;j<n2;j++){
		Fk[i*n2+j]=F[i*n2*n3+j*n3+k];
	    }
	}
	MKL_Complex16 tFk[2*(n1-1)*n2];
	c2coeffs2vals(Fk,n1,tFk,n2,k,3);

	for(int kk=0;kk<n2;kk++){
	    for (int i = 0; i < 2*(n1-1); i++ )
	    {
		if(i==0 | i==n1-1){
		    FF[i*n2*n3+kk*n3+k]=tFk[i*n2+kk];
		}else{
		    if(i<n1 & kk<n2){
			FF[i*n2*n3+kk*n3+k]=tFk[i*n2+kk];
		    }
		}

	    }
	}

	for(int i=0;i<n1;i++){
	    for(int j=0;j<n2;j++){
		Fk[j*n1+i]=FF[i*n2*n3+j*n3+k];
	    }
	}

	MKL_Complex16 triFk[n1*n2];
	tricoeffs2vals(Fk,n2,triFk,n1,k,3);

	for(int kk=0;kk<n1;kk++){
	    for (int i = 0; i < n2; i++ )
	    {
		FF[kk*n2*n3+i*n3+k].real=triFk[i*n1+kk].real;
		FF[kk*n2*n3+i*n3+k].imag=triFk[i*n1+kk].imag;
	    }
	}



    }
    ///////////////////////////////////////////
    for(int j=0;j<n2;j++){
	MKL_Complex16 Fj[n1*n3];
	for(int i=0;i<n1;i++){
	    for(int k=0;k<n3;k++){
		Fj[k*n1+i]=FF[i*n2*n3+j*n3+k];
		//printf("F(%d)=%lf\n",i*N*N+j*N+k,F[i*N*N+j*N+k]);
		//    cout<<"Fk1["<<i*n2+j<<"]=("<<Fk1[i*n2+j].real<<","<<Fk1[i*n2+j].imag<<")"<<endl;
	    }
	}
	MKL_Complex16 tFj[2*(n3-1)*n1];
	c2coeffs2vals(Fj,n3,tFj,n1,j,2);

	for(int kk=0;kk<n1;kk++){
	    for (int i = 0; i < 2*(n3-1); i++ )
	    {
		if(i==0 | i==n3-1){
		    FF[kk*n2*n3+j*n3+i]=tFj[i*n1+kk];
		}else{
		    if(i<n3 & kk<n1){
			FF[kk*n2*n3+j*n3+i]=tFj[i*n1+kk];
		    }
		}
	    }
	}



    }


}

void c2coeffs2vals(MKL_Complex16 Fk[],int ldFk,MKL_Complex16 FF[],int ldFF,int k,int flag){

    for(int i=1;i<ldFk-1;i++){
	for(int j=0;j<ldFF;j++){
	    Fk[i*ldFF+j].real=Fk[i*ldFF+j].real*0.5;
	    Fk[i*ldFF+j].imag=Fk[i*ldFF+j].imag*0.5;
	}
    }

    MKL_Complex16 tmp[2*(ldFk-1)*ldFF];

    for(int i=0;i<(ldFk-1);i++){
	for(int j=0;j<ldFF;j++){
	    tmp[i*ldFF+j]=Fk[i*ldFF+j];
	    tmp[(i+ldFk-1)*ldFF+j]=Fk[(ldFk-i-1)*ldFF+j];
	}
    }
    //print_matrix("tmp",2*ldFk-2,ldFF,tmp,ldFF);

    fftw_complex *in;
    int n = 2*ldFk-2;//100;
    fftw_complex *out;
    fftw_plan plan_forward;

    for(int kk=0;kk<ldFF;kk++){
	in = (fftw_complex*)fftw_malloc (sizeof ( fftw_complex ) * n );
	for (int i = 0; i < n; i++ )
	{
	    in[i][0] = tmp[i*ldFF+kk].real;
	    in[i][1] = tmp[i*ldFF+kk].imag;
	}
	out =(fftw_complex *)fftw_malloc ( sizeof ( fftw_complex ) * n );
	plan_forward = fftw_plan_dft_1d ( n, in, out, FFTW_FORWARD, FFTW_ESTIMATE );
	fftw_execute ( plan_forward );
	/////////////////////////////////


    for(int i=0;i<2*(ldFk-1);i++){
//	outt[i*ldFF+kk].real=out[i][0] / ( double ) ( n );
//	outt[i*ldFF+kk].imag=out[i][1] / ( double ) ( n );
	FF[i*ldFF+kk].real=out[ldFk-i-1][0];
	FF[i*ldFF+kk].imag=-out[ldFk-i-1][1];
    }


/*
 if(flag==3){
	for (int i = 0; i < 2*(ldFk-1); i++ )
	{
	    if(i==0 | i==ldFk-1){
		FF[i*ldFk*ldFF+kk*ldFF+k].real=out[ldFk-i-1][0];
		FF[i*ldFk*ldFF+kk*ldFF+k].imag=-out[ldFk-i-1][1];
	    }else{
		if(i<ldFk & kk<ldFk){
		    FF[i*ldFk*ldFF+kk*ldFF+k].real=out[ldFk-i-1][0];
		    FF[i*ldFk*ldFF+kk*ldFF+k].imag=-out[ldFk-i-1][1];
		}
	    }

	}
    }

    if(flag==2){
	for (int i = 0; i < 2*(ldFk-1); i++ )
	{
	    if(i==0 | i==ldFk-1){
		FF[kk*ldFk*ldFF+i+k*ldFF].real=out[ldFk-i-1][0];
		FF[kk*ldFk*ldFF+i+k*ldFF].imag=-out[ldFk-i-1][1];
	    }else{
		if(i<ldFk & kk<ldFF){
		    FF[kk*ldFk*ldFF+i+k*ldFF].real=out[ldFk-i-1][0];
		    FF[kk*ldFk*ldFF+i+k*ldFF].imag=-out[ldFk-i-1][1];
		}
	    }
	}
    }

*/
	fftw_destroy_plan ( plan_forward );
	fftw_free ( in );
	fftw_free ( out );
    }

    //return {0,0};

}


void tricoeffs2vals(MKL_Complex16 Fk[],int ldFk,MKL_Complex16 FF[],int ldFF,int k,int flag){

    //   print_matrix("tmp",2*ldFk-2,ldFF,tmp,ldFF);
    int i;
    fftw_complex *in;
    int n = ldFk;//100;
    fftw_complex *out;
    fftw_plan plan_backward;

    for(int kk=0;kk<ldFF;kk++){
	in = (fftw_complex*)fftw_malloc (sizeof ( fftw_complex ) * n );
	for ( i = 0; i < n; i++ )
	{
	    int ii;
	    double fix;
	    ii=(i+1-n/2-n%2<=0?i+n/2:i-n/2-n%2);
	    fix=((-n/2+i)%2?-1:1);
	    in[i][0]=fix*Fk[ii*ldFF+kk].real;
	    in[i][1]=fix*Fk[ii*ldFF+kk].imag;
	}
	/*
	   printf ( "\n" );
	   printf ( "  Input Data:\n" );
	   printf ( "\n" );
	   for ( i = 0; i < n; i++ )
	   {
	   printf ( "  %3d  %12f  %12f\n", i, in[i][0], in[i][1] );
	   }
	 */
	out =(fftw_complex *)fftw_malloc ( sizeof ( fftw_complex ) * n );
	plan_backward = fftw_plan_dft_1d ( n, in, out, FFTW_FORWARD, FFTW_ESTIMATE );
	fftw_execute ( plan_backward );

	/*
	   printf ( "\n" );
	   printf ( "  Recovered input data divided by N:\n" );
	   printf ( "\n" );
	 */

//	if(flag==3){
	    for ( i = 0; i < n; i++ )
	    {
		FF[i*ldFF+kk].real=out[i][0];
		FF[i*ldFF+kk].imag=out[i][1];
//		FF[kk*ldFk*ldFF+i*ldFF+k].real=out[i][0];
//		FF[kk*ldFk*ldFF+i*ldFF+k].imag=out[i][1];
	    }
//	}
/*
	if(flag==2){
	    for ( i = 0; i < n; i++ )
	    {
		FF[i*ldFk*ldFF+kk+k*ldFF].real=out[i][0];
		FF[i*ldFk*ldFF+kk+k*ldFF].imag=out[i][1];
	    }
	}
*/
	fftw_destroy_plan ( plan_backward );
	fftw_free ( in );
	fftw_free ( out );
    }

    //return {0,0};

}


