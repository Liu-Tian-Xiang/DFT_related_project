#include "../includes/global.h"
#include "../includes/prototype.h"
void Wave_function::stV(){

    double h=points;
    //mesh=1.0/points;
    int R_floor =(R_sys)*h+3;
    int L_floor =(L_sys)*h+3;
    h=1.0/h;
    const gsl_interp2d_type *interp_type_V = gsl_interp2d_bilinear;

    interp_r_accel_V = gsl_interp_accel_alloc();
    interp_z_accel_V = gsl_interp_accel_alloc();

    if(!spline_r_coords_V){
	spline_r_coords_V = (double*)calloc(R_floor, sizeof(double));
	for(int i=0;i<R_floor;i++){
	    spline_r_coords_V[i] = i*h;
	}
    }

    if(!spline_z_coords_V){
	spline_z_coords_V = (double*)calloc(L_floor, sizeof(double));
	for(int i=0;i<L_floor;i++){
	    spline_z_coords_V[i] = i*h;
	}
    }

    if(!spline_values_V){
	spline_values_V = (double*)calloc((R_floor)*(L_floor), sizeof(double));
    }

    if(!spline_V){
	spline_V = gsl_spline2d_alloc(interp_type_V, R_floor, L_floor);
    }

    if(MixV.spline_values_!=NULL){
	for(int r = 0; r <R_floor; r++){
	    for(int z = 0 ; z <L_floor; z++){
		gsl_spline2d_set(spline_V, spline_values_V, r, z ,0.3*CoulombPotential(r*h,z*h)+0.7*interpV(r*h,z*h,&MixV));
	    }
	}
    }else{
	for(int r = 0; r <R_floor; r++){
	    for(int z = 0 ; z <L_floor; z++){
		gsl_spline2d_set(spline_V, spline_values_V, r, z ,CoulombPotential(r*h,z*h));
	    }
	}
    }

}
