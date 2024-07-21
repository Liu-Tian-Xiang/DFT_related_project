#include "../includes/global.h"
#include "../includes/prototype.h"
double bess(double r,int m, int n){
    double bessel;
    double p,Q0;
    int o=(n-1)*(Mmax+1)+m;

    Q0=bessel_zero[o];/*gsl_sf_bessel_zero_Jnu(m,n);//Q^n_m*/
    p=Q0*r/R_sys;//r*Q^n_m/R_sys
    bessel=gsl_sf_bessel_Jn(m,p)/bessel_Jn[o];//(gsl_sf_bessel_Jn(m+1,Q0));
    return sqrt(2)*bessel/R_sys;
}

double system_basis(double r,double x,int l,int m,int n){
    double bessel;
    double p,Q0;
    int o=(n-1)*(Mmax+1)+m;
    Q0=bessel_zero[o];/*gsl_sf_bessel_zero_Jnu(m,n);//Q^n_m*/
    p=Q0*r/R_sys;//r*Q^n_m/R_sys
    bessel=gsl_sf_bessel_Jn(m,p)/bessel_Jn[o];//(gsl_sf_bessel_Jn(m+1,Q0));
    bessel=sqrt(2)*bessel/R_sys;

    return sqrt(r)*bessel*sqrt(2.0/L_sys)*sin(l*PI*x/L_sys);
}
