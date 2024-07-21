#include "../includes/global.h"
#include "../includes/prototype.h"

double interpV(double x,double y,spline_space *ptr){
//x=r,y=z
    double h=ptr->points;
    int R_floor =R_sys*h+3;
    int L_floor =L_sys*h+3;
    double value=0.0;
    double value2=0.0;
    h=1.0/h;
    gsl_spline2d_init(ptr->spline_, ptr->spline_r_coords_, ptr->spline_z_coords_, ptr->spline_values_, R_floor, L_floor);

    value = gsl_spline2d_eval(ptr->spline_, x, y, ptr->interp_r_accel_, ptr->interp_z_accel_);
    value2 = gsl_spline2d_eval(ptr->spline_, x, fabs(L_sys-y), ptr->interp_r_accel_, ptr->interp_z_accel_);

    return 0.5*value+0.5*value2;
    //return value;
}

