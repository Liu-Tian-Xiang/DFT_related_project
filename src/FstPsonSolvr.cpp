#include "../includes/global.h"
#include "../includes/prototype.h"

MKL_Complex16 *spline_space::FstPsonSolvr(int n1,int n2,int n3){

    //cout<<"n1="<<n1<<"\tn2="<<n2<<"\tn3="<<n3<<"\tFstPsonSolvr"<<endl;
    double tol=1e-13;
    MKL_Complex16 *F=(MKL_Complex16*)calloc(n1*n2*n3,sizeof(MKL_Complex16));

    double r[n1];
    double th[n2];
    double z[n3];
    chebpts(n1,r);
    trigpts(n2,th,PI);
    chebpts(n3,z);
    //for(int i=0;i<n1;i++){cout<<"r["<<i<<"]="<<r[i]<<endl;}
    //for(int i=0;i<n2;i++){cout<<"th["<<i<<"]="<<th[i]<<endl;}
    //for(int i=0;i<n3;i++){cout<<"z["<<i<<"]="<<z[i]<<endl;}

    for(int i=0;i<n1;i++){
	for(int j=0;j<n2;j++){
	    for(int kk=0;kk<n3;kk++){
		double rr=fabs(r[i])*R_sys;
		double zz=fabs(0.5*(z[kk]+1))*L_sys;
		double mix=interpV(rr,zz,&spline_vxc);
		//0.3*Psi_1.rho(rr,zz)+0.7*Psi_2.rho(rr,zz);
		if(rr<R & zz<L_sys-BoxMag & zz>BoxMag){mix=mix-n0;}
		F[i*n2*n3+j*n3+kk].real=mix;
		F[i*n2*n3+j*n3+kk].imag=0;
	    }
	}
    }


/*   
       FILE *f;
       f=fopen("./matlabcode/f100.txt","r");
       if(f==NULL){printf("The file was not opened");}
       fseek( f, 0L, SEEK_SET );
       for(int i=0;i<n1;i++){
       for(int k=0;k<n3;k++){
       for(int j=0;j<n2;j++){
       fscanf(f,"%lf",&F[i*n2*n3+j*n3+k].real);
       F[i*n2*n3+j*n3+k].imag=0.0;
       }
       }
       }
       fclose(f);
*/     
    MKL_Complex16 *FF=(MKL_Complex16*)calloc(n1*n2*n3,sizeof(MKL_Complex16));
    vals2coeffs(F,n1,n2,n3,FF);
    //printResult("F",FF,n1,n2,n3,tol);

    double *FReal=(double *)calloc(n1*n2*n3,sizeof(double));
    for(int i=0;i<n1*n2*n3;i++){
	FReal[i]=FF[i].real;
    }
    //printResult("FReal",FReal,n1,n2,n3,tol);

    double *XX=(double *)calloc(n1*n2*n3,sizeof(double));
    PoissonCylinder(FReal,tol,n1,n2,n3,XX);
    //printResult("XX",XX,n1,n2,n3,tol);
    //}
    MKL_Complex16 *zXX=(MKL_Complex16 *)calloc(n1*n2*n3,sizeof(MKL_Complex16));
    MKL_Complex16 *Final=(MKL_Complex16 *)calloc(n1*n2*n3,sizeof(MKL_Complex16));

    for(int i=0;i<n1*n2*n3;i++){
	zXX[i].real=XX[i];
	zXX[i].imag=0.0;
    }
    //printResult("zXX",zXX,n1,n2,n3,tol);
    coeffs2vals(zXX,n1,n2,n3,Final);

    free(F);
    free(FF);
    free(XX);
    free(zXX);
    free(FReal);

    return Final; 

}
