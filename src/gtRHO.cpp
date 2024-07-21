#include "../includes/global.h"
#include "../includes/prototype.h"

double Wave_function::gtRHO(double x,double y){
//x=r,y=z
    double h= points;
    int R_floor =R_sys*h+3;
    int L_floor =L_sys*h+3;
    double value=0.0;
    double value2=0.0;
    gsl_spline2d_init(spline_, spline_r_coords_, spline_z_coords_, spline_values_, R_floor, L_floor);
    value = gsl_spline2d_eval( spline_, x, y,  interp_r_accel_,  interp_z_accel_);
    value2 = gsl_spline2d_eval( spline_, x, fabs(L_sys-y),  interp_r_accel_,  interp_z_accel_);
    return 0.5*value+0.5*value2;
    //return value;
}

