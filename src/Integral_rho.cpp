#include "../includes/global.h"
#include "../includes/prototype.h"
struct Integral_parameter
{
    FuncPtr pV;
    double x;
};

double FuncPtr_inner(double r,void *params){
    //x[0-L]<->r[0-R]
    Integral_parameter *para=(Integral_parameter *)params;
    double x=para->x;
    x=x*L_sys;
    r=r*R_sys;
   
    return (*para->pV)(r,x)*2*PI*r*R_sys*L_sys;
}
double FuncPtr_outer(double x,void *params){
    double lower_limit=0.0;
    double upper_limit=1.0;
    int key=4,limit=2000;
    double abs_error=1.0e-1;
    double rel_error=1.0e-1;
    double res,err,result;
    gsl_function f;
    gsl_integration_workspace *work;
    Integral_parameter *para=(Integral_parameter *)params;
    para->x=x;
    f.function=FuncPtr_inner;
    f.params=para;
    work=gsl_integration_workspace_alloc(20000);
    gsl_integration_qag(&f,lower_limit,upper_limit,abs_error,rel_error,limit,key,work,&res,&err);
    gsl_integration_workspace_free(work);
    return res;
}

double Integral_rho(FuncPtr pV){
                       double lower_limit=0.0;
                       double upper_limit=1.0;//0.2;
                       int key=4,limit=2000;
                       double abs_error=1.0e-1;
                       double rel_error=1.0e-1;

                       Integral_parameter para={pV,0.0};
                       gsl_function f;
                       gsl_integration_workspace *work;
                       f.function=FuncPtr_outer;
                       f.params=&para;

                       double err,result;
  
                       //double result1=0.0;
                       //for(int o=0;o<5;o++)
                       //{
                       work=gsl_integration_workspace_alloc(20000);
                       gsl_integration_qag(&f,lower_limit,upper_limit,abs_error,rel_error,limit,key,work,&result,&err);
                       gsl_integration_workspace_free(work); 
                       //result1=result1+result;
                       //upper_limit=0.2+upper_limit;
                       //lower_limit=lower_limit+0.2;
                       // }
                       return result;
                   }
