#include "../includes/global.h"
#include "../includes/prototype.h"

double *ultra1mx2cheb(double* Xk,int ldX,int rdX){
    double *S;
    double *Stemp;
    S=ultra1mx2leg_mat(ldX);
    double *Xout,*Xout2;
    Xout=Multiply(S,ldX,ldX,Xk,rdX);
    Stemp=leg2cheb_mat(ldX);
    Xout2=Multiply(Stemp,ldX,ldX,Xout,rdX);
    free(S);
    free(Xout);
    free(Stemp);
    return Xout2;
}

double *ultra1mx2leg_mat(int N){
    double d[N];
    double md[N];
    double *R;
    int shift[2]={0,-2};
    double Stemp[N*N];
    for(int i=0;i<N*N;i++){
	Stemp[i]=0.0;
    }
    for(int i=0;i<N;i++){
	d[i]=1;
	md[i]=-1;
	Stemp[i*N+i]=0.5*(i*1.0+1.0)*(i*1.0+2.0)/(1.5+i*1.0);
    }
    spMatrix SSS;
    SSS.Create_spMatrix(d,md,shift,N);
    R=Multiply(&SSS,N,N,Stemp,N);
    SSS.destroy_spMatrix();
    return R;
}



double *cheb2ultra(double *X,int ldX,int rdX){
    double *S;
    S=cheb2leg_mat(ldX);
    X=Multiply(S,ldX,ldX,X,rdX);
    spMatrix SS;
    SS=leg2ultra_mat(ldX);
    X=Multiply(&SS,ldX,ldX,X,rdX);
    free(S);
    SS.destroy_spMatrix();
    return X;
}

double *cheb2leg_mat(int N){
    double *vals;
    vals=(double *)calloc(2*N,sizeof(double));
    vals[0]=sqrt(PI);
    vals[1]=2/vals[0];
    for(int i=2;i<=2*(N-1);i+=2){
	vals[i]=vals[i-2]*(1-1.0/i);
	vals[i+1]=vals[i-1]*(1-1.0/(i+1));
    }
    double *L;
    L=(double *)calloc(N*N,sizeof(double));
    for(int j=0;j<N;j++){
	for(int k=j+2;k<N;k+=2){
	    L[j*(N)+k]= -k*(j+0.5)*(vals[k-j-2]/(k-j))*(vals[k+j-1]/(j+k+1));
	}
    }
    double c=sqrt(PI)/2;
    for(int j=1;j<=N-1;j++){
	L[j*N+j]=c/vals[2*j];
    }
    L[0]=1;
    free(vals);
    return L;
}

spMatrix leg2ultra_mat(int n){
    double lam=1.0/2;
    double v[n];
    for(int i=0;i<n;i++){v[i]=0;}
    int shift[2]={0,2};
    double w[n];
    for(int i=0;i<n;i++){w[i]=0;}
    v[0]=1;
    w[0]=0;
    v[1]=lam/(lam+1);
    w[1]=0;
    for(int i=2;i<=n-1;i++){
	v[i]=lam/(lam+i);
	w[i]=-lam/(lam+i);
    }
    spMatrix S;
    S.Create_spMatrix(v,w,shift,n);
    return S;
}

double *leg2cheb_mat(int N){
    double *vals;
    vals=(double *)calloc(2*N,sizeof(double));
    vals[0]=sqrt(PI);
    vals[1]=2/vals[0];
    for(int i=2;i<=2*(N-1);i+=2){
	vals[i]=vals[i-2]*(1-1.0/i);
	vals[i+1]=vals[i-1]*(1-1.0/(i+1));
    }
    double *M=(double *)calloc(N*N,sizeof(double));
    for(int j=0;j<N;j++){
	for(int k=j;k<N;k+=2){
	    M[j*(N)+k]=2/PI*vals[k-j]*vals[k+j];
	}
    }
    for(int i=0;i<N;i++){
	M[i]=0.5*M[i];
    }
    free(vals);
    return M;
}




