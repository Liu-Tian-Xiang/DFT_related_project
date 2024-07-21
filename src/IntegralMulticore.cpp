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

double func_Minner(double r,void *params){
    //x[0-L]<->r[0-R]
    double coef,x;
    Integral_parameter *para=(Integral_parameter *)params;
    x=para->x;
    x=x*L_sys;
    r=r*R_sys;
    coef=2.0/L_sys*bess(r,para->m,para->n_1)
    *bess(r,para->m,para->n_2)
    *sin(para->l_1*PI*x/L_sys)
    *sin(para->l_2*PI*x/L_sys)
    *r;
    return (*para->pV)(r,x,para->ptr)*R_sys*L_sys*coef;
}
double func_Mouter(double x,void *params){
    double lower_limit=0;
    double upper_limit=1;
    int key=4,limit=2000;
    double abs_error=1.0e-3;
    double rel_error=1.0e-3;
    double res,err;
    gsl_function f;
    gsl_integration_workspace *work;
    Integral_parameter *para=(Integral_parameter *)params;
    para->x=x;
    f.function=func_Minner;
    f.params=para;
    work=gsl_integration_workspace_alloc(2000);
    gsl_integration_qag(&f,lower_limit,upper_limit,abs_error,rel_error,limit,key,work,&res,&err);
    gsl_integration_workspace_free(work);
    return res;
}

double IntegralMulticore(int n_1,int l_1,int n_2,int l_2,int m,Fun/*cPtr*/ pV,spline_space *who){

    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);


    double lower_limit=id%4*0.25;
    double upper_limit=(id%4+1)*0.25;
    int key=4,limit=2000;
    double abs_error=1.0e-3;
    double rel_error=1.0e-3;
    double result1=0.0;
    Integral_parameter para={n_1,l_1,n_2,l_2,m,&pV,who,0.0};
    //Integral_parameter para={n_1,l_1,n_2,l_2,m,pV,id%4*0.25};
    gsl_function f;
    gsl_integration_workspace *work;
    f.function=func_Mouter;
    f.params=&para;

    double err,result;
    work=gsl_integration_workspace_alloc(2000);
    gsl_integration_qag(&f,lower_limit,upper_limit,abs_error,rel_error,limit,key,work,&result,&err);
    gsl_integration_workspace_free(work); 
    MPI_Reduce(&result, &result1, 1, MPI_DOUBLE, MPI_SUM,0, group[id/4].group_parts_comm);
    return result1;
}
//////////////////////////////////////////////////////////////////////////////
