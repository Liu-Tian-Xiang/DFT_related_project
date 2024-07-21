#include "../includes/global.h"
#include "../includes/prototype.h"

double rhoShell(double r,double x,spline_space* ptr){
    return 1;//Psi_1.rho(r,x);
    if(r<R && (x<(L_sys-BoxMag) && x>=(L_sys-BoxMag-L)) && r>=0){return Psi_1.rho(r,x)-n0;}//128.636//right
    else if(r<R && (x>(BoxMag) && x<=(BoxMag+L)) && r>=0){return Psi_1.rho(r,x)-n0;}//128.636//left
    else {return Psi_1.rho(r,x);}
}

