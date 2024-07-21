#include "../includes/global.h"
#include "../includes/prototype.h"
void spline_space::destroy_(){
    if(interp_r_accel_)
	gsl_interp_accel_free(interp_r_accel_);
    if(interp_z_accel_)
	gsl_interp_accel_free(interp_z_accel_);
    if(spline_)
	gsl_spline2d_free(spline_);
    if(spline_r_coords_)
	free(spline_r_coords_);
    if(spline_z_coords_)
	free(spline_z_coords_);
    if(spline_values_)
	free(spline_values_);
}
