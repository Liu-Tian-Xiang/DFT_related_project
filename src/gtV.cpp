#include "../includes/global.h"
#include "../includes/prototype.h"

double Wave_function::gtV(double x,double y){
//x=r,y=z
    double h= points;
    int R_floor =R_sys*h+3;
    int L_floor =L_sys*h+3;
    double value=0.0;
    double value2=0.0;
    gsl_spline2d_init(spline_V, spline_r_coords_V, spline_z_coords_V, spline_values_V, R_floor, L_floor);
    value = gsl_spline2d_eval( spline_V, x, y,  interp_r_accel_V,  interp_z_accel_V);
    value2 = gsl_spline2d_eval( spline_V, x, fabs(L_sys-y),  interp_r_accel_V,  interp_z_accel_V);
    return 0.5*value+0.5*value2;
    //return value;
}

