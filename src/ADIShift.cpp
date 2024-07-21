#include "../includes/global.h"
#include "../includes/prototype.h"


int ADIshifts(double a,double b,double c,double d,double tol,double *p,double *q){
    double gam=(c-a)*(d-b)/(c-b)/(d-a);
    double alp=-1+2*gam+2*sqrt(pow(gam,2)-gam);

    //MKL_Complex16 AA[9]={{-a*alp,0},{a,0},{1,0},{-b,0},{b,0},{1,0},{c,0},{c,0},{1,0}};
    //MKL_Complex16 BB[9]={{-a*alp,0},{-alp,0},{a,0},{-b,0},{-1,0},{b,0},{c,0},{1,0},{c,0}};
    //    MKL_Complex16 CC[9]={{-alp,0},{a,0},{1,0},{-1,0},{b,0},{1,0},{1,0},{c,0},{1,0}};
    //MKL_Complex16 DD[9]={{-a*alp,0},{-alp,0},{1,0},{-b,0},{-1,0},{1,0},{c,0},{1,0},{1,0}};

    double A[9]={-a*alp,a,1,-b,b,1,c,c,1};
    //double A[9]={1,3,1,3,5,3,1,3,2};
    double B[9]={-a*alp,-alp,a,-b,-1,b,c,1,c};
    double C[9]={-alp,a,1,-1,b,1,1,c,1};
    double D[9]={-a*alp,-alp,1,-b,-1,1,c,1,1};
    //print_matrix(3,A);
    int ipiv[3];
    int info;
    info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR,3,3,A,3,ipiv);
    info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR,3,3,B,3,ipiv);
    //info = LAPACKE_zgetrf(LAPACK_ROW_MAJOR,3,3,CC,3,ipiv);
    info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR,3,3,C,3,ipiv);
    info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR,3,3,D,3,ipiv);

    double detA=1;
    double detB=1;
    double detC=-1;
    /*
       MKL_Complex16 detCC={1,0};
       MKL_Complex16 Zero={0,0};
       MKL_Complex16 One={1,0};
     */
    double detD=1;
    for(int i=0;i<3;i++) detA=detA*A[i*3+i];
    for(int i=0;i<3;i++) detB=detB*B[i*3+i];
    for(int i=0;i<3;i++) detC=detC*C[i*3+i];
    for(int i=0;i<3;i++) detD=detD*D[i*3+i];
    /*
       for(int i=0;i<3;i++) {
       Zero={0,0};
       cblas_zaxpy(1,&detCC,&CC[i*3+i],1,&Zero,1);
       detCC=Zero;
       }
     */
    //    cout<<"detCC={"<<detCC.real<<","<<detCC.imag<<"}"<<endl;
    /*
       for(int i=0;i<3;i++){
       for(int j=0;j<3;j++){
       cout<<"CC["<<i<<","<<j<<"]={"<<CC[i*3+j].real<<","<<CC[i*3+j].imag<<"}"<<endl;
    //    cout<<"C["<<i<<","<<j<<"]={"<<D[i*3+j]<<"}"<<endl;
    }cout<<endl;
    }
     */
    double J=floor(log(16*gam)*log(4/tol)/pow(PI,2))+1;

    int ldU=floor(J-0.5)+1;
    if(q==NULL & p==NULL){
	return ldU;
    }
    double U[ldU];
    for(int i=0;i<ldU;i++){
	U[i]=0.5+i;
    }
    double K;
    double dn[ldU];
    double sn;
    double cn;
    if(alp<1e7){
	K=gsl_sf_ellint_Kcomp(sqrt(1-1.0/pow(alp,2)),GSL_PREC_DOUBLE);
	for(int i=0;i<ldU;i++){
	    info=gsl_sf_elljac_e(U[i]*K/J,1-1.0/pow(alp,2),&sn,&cn,&dn[i]);
	}
    }else{
	K=gsl_sf_ellint_Kcomp(sqrt(2*log(2)+log(alp)+(-1+2*log(2)+log(alp))/pow(alp,2)/4),GSL_PREC_DOUBLE);
	double m1=1/pow(alp,2);
	for(int i=0;i<ldU;i++){
	    dn[i]=1.0/cosh(U[i]*K/J)+0.25*m1*(sinh(U[i]*K/J)*cosh(U[i]*K/J)+U[i]*K/J)*tanh(U[i]*K/J)/cosh(U[i]*K/J);
	}
    }
    for(int i=0;i<ldU;i++){
	p[i]=(detA*dn[i]*(-alp)+detB)/(detC*dn[i]*(-alp)+detD);
	//cout<<p[i]<<endl;
    }
    for(int i=0;i<ldU;i++){
	q[i]=(detA*dn[i]*(alp)+detB)/(detC*dn[i]*(alp)+detD);
	//cout<<q[i]<<endl;
    }

    return ldU;
}
