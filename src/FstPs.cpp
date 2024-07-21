#include "../includes/global.h"
#include "../includes/prototype.h"
void spline_space::FstPs(int loop_number){
    mesh=1.0/points;
    double h=points;
    int R_floor =R_sys*h+3;
    int L_floor =L_sys*h+3;
    h=1.0/h;

    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    int n1=R_floor*2; int n2=4; int n3=L_floor;

//    cout<<"n1="<<n1<<"\tn2="<<n2<<"\tn3="<<n3<<"\tFstPs"<<endl;
    MKL_Complex16 *FstResult=FstPsonSolvr(n1,n2,n3);
//    if(id==1) printResult("Fst",FstResult,n1,n2,n3,1e-13);

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

    for(int r = 0; r <R_floor; r++){
	for(int z = 0 ; z <L_floor; z++){
	    //double Setvalue=0;
	    //int position=((r+R_floor)*n2*n3+z);
	    //int position=((r+R_floor)*n2*n3+z);
	    //if(position<n1*n2*n3 & position>=0){
	//	Setvalue=FstResult[position].real;
	    //}
	    gsl_spline2d_set(spline_, spline_values_, r, z , FstResult[(r+R_floor)*n2*n3+z].real);
	}
    }

    free(FstResult);
}

