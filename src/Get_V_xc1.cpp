#include "../includes/global.h"
#include "../includes/prototype.h"
double Get_V_xc1(double r,double x,spline_space* ptr){
    double re=0.0;
    double den=3.0; 
    double rho_3;
    den=Psi_1.rho(r,x);
    //rho_psi(r,x);
    rho_3=pow(den,-1.0/3);
    re=-0.916*pow(den,1.0/3)/kf-0.096+0.0622*log(kf)
        -0.0622/3.0*log(den)-0.0232*rho_3*kf
        +0.004*kf*rho_3*log(kf*rho_3);
    return re;
}
