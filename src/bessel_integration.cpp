#include "../includes/global.h"
#include "../includes/prototype.h"
struct bessel
{
    int n;
    int n_1;
    int n_2;
    int m;
};

double bessel(double r,void *params){
    struct bessel *par=(struct bessel*)params;
    r=R_sys*r;
    return R_sys*r*bess(r,0.0,par->n)*bess(r,par->m,par->n_1)*bess(r,par->m,par->n_2);
}
double bessel_integration(int n,int n_1, int n_2,int m){
    double lower_limit=0.0;
    double upper_limit=1.0;
    int key=4,limit=2000;
    double abs_error=1.0e-8;
    double rel_error=1.0e-8;

    struct bessel para={n,n_1,n_2,m};
    gsl_function f;
    gsl_integration_workspace *work;
    f.function=bessel;
    f.params=&para;

    double res,err,result;
    work=gsl_integration_workspace_alloc(200000);
    gsl_integration_qag(&f,lower_limit,upper_limit,abs_error,rel_error,limit,key,work,&res,&err);
    gsl_integration_workspace_free(work);
    return res;
}

