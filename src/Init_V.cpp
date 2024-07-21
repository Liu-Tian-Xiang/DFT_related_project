#include "../includes/global.h"
#include "../includes/prototype.h"
double Init_V(double r,double x,spline_space* ptr){
    double W=4260/E_divide;//Ag eV 56.05
    if((r<R) & (x<(L_sys-BoxMag) & x>=(L_sys-BoxMag-L)) & (r>=0)){return -(Ef0+W);}//128.636//right
    else if((r<R) & ((x>BoxMag) & (x<=BoxMag+L)) & (r>=0)){return -(Ef0+W);}//128.636//left
    else {return 0.0;}
}
