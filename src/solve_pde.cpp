#include "../includes/global.h"
#include "../includes/prototype.h"
void spline_space::solve_pde(int loop_number){

    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    gsl_vector *v;
    v=cylinder.pde_result();
    //cylinder.spectrumFC();
    //printf("%f",gsl_vector_get(v,0));

    mesh=1.0/points;
    double h=points;
    int R_floor =R_sys*h+3;
    int L_floor =L_sys*h+3;
    h=1.0/h;

    const gsl_interp2d_type *interp_type_ = gsl_interp2d_bilinear;

    interp_r_accel_ = gsl_interp_accel_alloc();
    interp_z_accel_ = gsl_interp_accel_alloc();

    if(!spline_values_){
	spline_values_ = (double*)calloc((R_floor)*(L_floor), sizeof(double));
    }

    if(!spline_){
	spline_ = gsl_spline2d_alloc(interp_type_, R_floor, L_floor);
    }

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

    //set
    for(int z = 0 ; z <=L_floor-1; z++){
	gsl_spline2d_set(spline_, spline_values_, 0, z , 0.0);
    }//first line
    for(int r = 1; r <=R_floor-2; r++){
	    gsl_spline2d_set(spline_, spline_values_, r, 0 , 0.0);
	    gsl_spline2d_set(spline_, spline_values_, r, 1 , 0.0);
	    for(int z = 2 ; z <=L_floor-2; z++){
		gsl_spline2d_set(spline_, spline_values_, r, z , gsl_vector_get(v,(r-1)*(L_floor-3)+z-2));
	    }
	    gsl_spline2d_set(spline_, spline_values_, r, L_floor-1 , 0.0);
    }
    for(int z = 0 ; z <=L_floor-1; z++){
	gsl_spline2d_set(spline_, spline_values_, R_floor-1, z , 0.0);
    }

  gsl_vector_free (v);
}
