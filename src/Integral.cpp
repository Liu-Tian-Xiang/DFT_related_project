#include "../includes/global.h"
#include "../includes/prototype.h"
struct Integral_parameter
{
    int n_1;
    int l_1;
    int n_2;
    int l_2;
    int m;
    Fun *pV;
    spline_space *ptr;
    double x;
};

double func_inner(double r,void *params){
    //x[0-L]<->r[0-R]
    double coef,x;
    Integral_parameter *para=(Integral_parameter *)params;

    x=para->x;
    x=x*L_sys;
    r=r*R_sys;
/*
    coef=2.0/L_sys*bess(r,para->m,para->n_1)
    *bess(r,para->m,para->n_2)
    *sin(para->l_1*PI*x/L_sys)
    *sin(para->l_2*PI*x/L_sys)
    *r;
    return (*para->pV)(r,x,para->ptr)*R_sys*L_sys*coef;
  */ 
    return system_basis(r,x,para->l_1,para->m,para->n_1)*((*para->pV)(r,x,para->ptr))*R_sys*L_sys*system_basis(r,x,para->l_2,para->m,para->n_2);
}
double func_outer(double x,void *params){
    double lower_limit=0.0;
    double upper_limit=1.0;
    int key=4,limit=2000;
    double abs_error=1.0e-4;
    double rel_error=1.0e-4;
    double res,err,result;
    gsl_function f;
    gsl_integration_workspace *work;
    Integral_parameter *para=(Integral_parameter *)params;
    para->x=x;
    f.function=func_inner;
    f.params=para;
    work=gsl_integration_workspace_alloc(2000000);
    gsl_integration_qag(&f,lower_limit,upper_limit,abs_error,rel_error,limit,key,work,&res,&err);
    gsl_integration_workspace_free(work);
    return res;
}

double Integral(int n_1,int l_1,int n_2,int l_2,int m,Fun/*cPtr*/ pV,spline_space *who){
    double lower_limit=0.0;//1.0/200;
    double upper_limit=1.0;
    int key=4,limit=20000;
    double abs_error=1.0e-3;
    double rel_error=1.0e-3;

    Integral_parameter para={n_1,l_1,n_2,l_2,m,&pV,who,0.0};
    gsl_function f;
    gsl_integration_workspace *work;
    f.function=func_outer;
    f.params=&para;
    double err,result;

    /*double result1=0.0;
    for(int o=0;o<5;o++)
    {*/
    work=gsl_integration_workspace_alloc(2000000);
    gsl_integration_qag(&f,lower_limit,upper_limit,abs_error,rel_error,limit,key,work,&result,&err);
    gsl_integration_workspace_free(work); 
    /*result1=result1+result;
    upper_limit=0.2+upper_limit;
    lower_limit=lower_limit+0.2;
    }*/
//    return (fabs(result)>1e-10?result:0.0);
    return result;

}
