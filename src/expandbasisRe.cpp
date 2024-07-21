#include "../includes/global.h"
#include "../includes/prototype.h"
struct basisReparameter
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

double basisReinner(double r,void *params){
    //x[0-L]<->r[0-R]
    double coef,x;
    basisReparameter *para=(basisReparameter *)params;

    x=para->x;
    x=x*L_sys*2;
    r=r*R_sys;

    return (*para->pV)(r,x,para->ptr)*R_sys*(L_sys*2)*expand(r,x,para->m,para->n_2,para->l_2,"Re");
}
double basisReouter(double x,void *params){
    double lower_limit=0.0;
    double upper_limit=1.0;
    int key=4,limit=2000;
    double abs_error=1.0e-4;
    double rel_error=1.0e-4;
    double res,err,result;
    gsl_function f;
    gsl_integration_workspace *work;
    basisReparameter *para=(basisReparameter *)params;
    para->x=x;
    f.function=basisReinner;
    f.params=para;
    work=gsl_integration_workspace_alloc(2000000);
    gsl_integration_qag(&f,lower_limit,upper_limit,abs_error,rel_error,limit,key,work,&res,&err);
    gsl_integration_workspace_free(work);
    return res;
}

double expandbasisRe(int n_1,int l_1,int n_2,int l_2,int m,Fun/*cPtr*/ pV,spline_space *who){
    double lower_limit=0.0;//1.0/200;
    double upper_limit=1.0;
    int key=4,limit=20000;
    double abs_error=1.0e-3;
    double rel_error=1.0e-3;

    basisReparameter para={n_1,l_1,n_2,l_2,m,&pV,who,0.0};
    gsl_function f;
    gsl_integration_workspace *work;
    f.function=basisReouter;
    f.params=&para;
    double err,result;

    work=gsl_integration_workspace_alloc(2000000);
    gsl_integration_qag(&f,lower_limit,upper_limit,abs_error,rel_error,limit,key,work,&result,&err);
    gsl_integration_workspace_free(work); 
    return result;

}
