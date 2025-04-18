#include "../includes/global.h"
#include "../includes/prototype.h"
double single_bessel_two(double r,void *params){
    int* n=(int*)params; 
    return r*bess(r,0.0,*n);
}
double positive_contribution_two(int n,int l){

    double lower_limit=0.0;
    double upper_limit=R;//1.0;
    int key=4,limit=20000;
    double abs_error=1.0e-9;
    double rel_error=1.0e-9;
    //struct single_bessel para={n};
    gsl_function f;
    gsl_integration_workspace *work;
    f.function=single_bessel_two;
    f.params=&n;//&para;
    double res,err,result;
    work=gsl_integration_workspace_alloc(200000);
    gsl_integration_qag(&f,lower_limit,upper_limit,abs_error,rel_error,limit,key,work,&res,&err);
    gsl_integration_workspace_free(work);

    double sinx_x=(l!=0?2*L_sys*sin(0.5*l*PI*L/L_sys)/(l*PI*L):1.0);
    double sinx_x2=(l!=0?2*L_sys*sin(0.5*l*PI*(L+N)/L_sys)/(l*PI*(L+N)):1.0);
    result= (2*PI*PI)*l*n0*L*(L+N)*res*sinx_x*sinx_x2/L_sys;
    return result;
//    return 0.0;

}

