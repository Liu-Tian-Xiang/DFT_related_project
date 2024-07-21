#include "../includes/global.h"
#include "../includes/prototype.h"
void spline_space::vxc(){

    mesh=1.0/points;
    double h=points;
    int R_floor =(R_sys)*h+3;
    int L_floor =(L_sys)*h+3;
    h=1.0/h;
    const gsl_interp2d_type *interp_type_ = gsl_interp2d_bilinear;

    interp_r_accel_ = gsl_interp_accel_alloc();
    interp_z_accel_ = gsl_interp_accel_alloc();

    if(!spline_r_coords_){
	spline_r_coords_ = (double*)calloc(R_floor, sizeof(double));
	for(int i=0;i<R_floor;i++){
	    spline_r_coords_[i] = i*h;
	}
    }

    if(!spline_z_coords_){
	spline_z_coords_ = (double*)calloc(L_floor, sizeof(double));
	for(int i=0;i<L_floor;i++){
	    spline_z_coords_[i] = i*h;
	}
    }

    if(!spline_values_){
	spline_values_ = (double*)calloc((R_floor)*(L_floor), sizeof(double));
    }

    if(!spline_){
	spline_ = gsl_spline2d_alloc(interp_type_, R_floor, L_floor);
    }

    for(int r = 0; r <R_floor; r++){
	for(int z = 0 ; z <L_floor; z++){
	    gsl_spline2d_set(spline_, spline_values_, r, z ,Get_V_xc2(r*h,z*h,NULL));
	}
    }
}
