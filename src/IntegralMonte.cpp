/*#include <iostream>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_miser.h>
#include <gsl/gsl_monte_plain.h>
#include <gsl/gsl_monte_vegas.h>*/
#include "../includes/global.h"
#include "../includes/prototype.h"

struct Integral_monte_parameter
{
    int n_1;
    int l_1;
    int n_2;
    int l_2;
    int m;
    Fun *pV;
    spline_space *ptr;
};

double my_f1(double* x_array, size_t dim, void*params){
//0->r;1->z
    Integral_monte_parameter *para=(Integral_monte_parameter *)params;
    double x,r;

    r=x_array[0]*R_sys;
    x=x_array[1]*L_sys;

    double coef;
    coef=2.0/L_sys*bess(r,para->m,para->n_1)
    *bess(r,para->m,para->n_2)
//    *sin(para->l_1*PI*x/L_sys)
//    *sin(para->l_2*PI*x/L_sys)
*(cos((para->l_1-para->l_2)*PI*x/L_sys)-cos((para->l_1+para->l_2)*PI*x/L_sys))*0.5
    *r;
/* 
if(dim!=2){
fprintf(stderr,"dim!=2");
abort();
}*/
    return (*para->pV)(r,x,para->ptr)*R_sys*L_sys*coef;
}


double my_f2(double* x_array, size_t dim, void*params){
//0->r;1->z
    Integral_monte_parameter *para=(Integral_monte_parameter *)params;
    double x,r;

    r=x_array[0]*R_sys;
    x=x_array[1]*L_sys;

    double coef;
    coef=2.0/L_sys*bess(r,para->m,para->n_1)
    *bess(r,para->m,para->n_2)
//    *sin(para->l_1*PI*x/L_sys)
//    *sin(para->l_2*PI*x/L_sys)
*(cos((para->l_1+para->l_2)*PI*x/L_sys))*0.5
    *r;
/* 
if(dim!=2){
fprintf(stderr,"dim!=2");
abort();
}*/
    return (*para->pV)(r,x,para->ptr)*R_sys*L_sys*coef;
}


double IntegralMonte(int n_1,int l_1,int n_2,int l_2,int m,Fun pV,spline_space *who){

    Integral_monte_parameter para={n_1,l_1,n_2,l_2,m,&pV,who};

    gsl_monte_function f;
    f.dim=2;
    f.f=my_f1;
    f.params=&para;

int calls=100000;
double xl[]={0.0,0.0},xu[]={1.0,1.0};
double result1,result2,er;
gsl_monte_plain_state*ps=gsl_monte_plain_alloc(2);
const gsl_rng_type*tp=gsl_rng_minstd;
gsl_rng*pr=gsl_rng_alloc(tp);
gsl_monte_plain_init(ps);
gsl_monte_plain_integrate(&f,xl,xu,2,calls,pr,ps,&result1,&er);

    f.f=my_f2;
gsl_monte_plain_integrate(&f,xl,xu,2,calls,pr,ps,&result2,&er);
//cout<<(result)<<endl;
return /*(fabs(result)>1000?result:0.0)*/result1-result2;

}

