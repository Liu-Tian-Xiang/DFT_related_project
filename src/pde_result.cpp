#include "../includes/global.h"
#include "../includes/prototype.h"

gsl_vector* spline_space::pde_result(){
    double *pde_matrix;
    double *pde_vector;
    double h=points;
    int R_floor=R_sys*h;
    int L_floor=L_sys*h;
    h=1.0/h;

//    double gap=0;

    int dim=(R_floor+1)*L_floor;
    pde_matrix=(double *)calloc(pow(dim,2.0),sizeof(double));
    pde_vector=(double *)calloc(dim,sizeof(double));

    pde_matrix[0]=6;//p
    pde_matrix[dim]=-4;//n
    pde_matrix[1]=-1;//e
    pde_vector[0]=-pow(h,2)*(0.3*Psi_1.rho(0.0,h)+0.7*Psi_1.rho(0.0,h));
    for(int i=1;i<=L_floor-2;i++){
	pde_matrix[i*(dim+1)]=6;
	pde_matrix[i*(dim+1)+dim]=-4;
	pde_matrix[i*(dim+1)+1]=-1;
	pde_matrix[i*(dim+1)-1]=-1;
	//if((i+1)*h>(BoxMag) & (i+1)*h<(L_sys-BoxMag)){
	//    pde_vector[i]=-pow(h,2)*(0.3*Psi_1.rho(0.0,(i+1)*h)+0.7*Psi_1.rho(0.0,(i+1)*h)-n0);
	//}else{
	    pde_vector[i]=-pow(h,2)*(0.3*Psi_1.rho(0.0,(i+1)*h)+0.7*Psi_1.rho(0.0,(i+1)*h));
	//}
    }
    pde_matrix[(L_floor-1)*(dim+1)]=6;
    pde_matrix[(L_floor-1)*(dim+1)+dim]=-4;
    pde_matrix[(L_floor-1)*(dim+1)-1]=-1;
    pde_vector[(L_floor-1)]=-pow(h,2)*(0.3*Psi_1.rho(0.0,(L_floor)*h)+0.7*Psi_1.rho(0.0,(L_floor)*h));
///////////////////////////////////////////center//line///
    for(int i=1;i<=R_floor;i++){
	pde_matrix[(dim+1)*i*(L_floor)]=4;
	pde_matrix[(dim+1)*i*(L_floor)+1]=-1;
	pde_matrix[(dim+1)*i*(L_floor)+dim]=-(1+0.5/i);
	pde_vector[i*(L_floor)]=-pow(h,2)*(0.3*Psi_1.rho(h*i,h)+0.7*Psi_1.rho(h*i,h));

	for(int j=1;j<=L_floor-2;j++){
	pde_matrix[(dim+1)*(i*(L_floor)+j)]=4;
	pde_matrix[(dim+1)*(i*(L_floor)+j)+1]=-1;
	pde_matrix[(dim+1)*(i*(L_floor)+j)-1]=-1;
	if(i!=R_floor) pde_matrix[(dim+1)*(i*(L_floor)+j)+dim]=-(1+0.5/i);
	pde_matrix[(dim+1)*(i*(L_floor)+j)-dim]=-(1-0.5/i);

	//if(i*h<R & (j+1)*h>(BoxMag) & (j+1)*h<(L_sys-BoxMag)){
	//    pde_vector[i*(L_floor-1)+j]=-pow(h,2)*(0.3*Psi_1.rho(h*i,(j+1)*h)+0.7*Psi_1.rho(h*i,(j+1)*h)-n0);
	//}else{
	    pde_vector[i*(L_floor)+j]=-pow(h,2)*(0.3*Psi_1.rho(h*i,(j+1)*h)+0.7*Psi_1.rho(h*i,(j+1)*h));
	//}

	}
	pde_matrix[(dim+1)*(i*(L_floor)+L_floor-1)]=4;
	pde_matrix[(dim+1)*(i*(L_floor)+L_floor-1)-1]=-1;
	pde_matrix[(dim+1)*(i*(L_floor)+L_floor-1)-dim]=-(1-0.5/i);
	pde_vector[i*(L_floor)+L_floor-1]=-pow(h,2)*(0.3*Psi_1.rho(h*i,(L_floor)*h)+0.7*Psi_1.rho(h*i,(L_floor)*h));
    }




  gsl_matrix_view m = gsl_matrix_view_array (pde_matrix, dim, dim);

  gsl_vector_view v = gsl_vector_view_array (pde_vector, dim);

  gsl_vector *x = gsl_vector_alloc (dim);
  
  int s;

  gsl_permutation * p = gsl_permutation_alloc (dim);

  gsl_linalg_LU_decomp (&m.matrix, p, &s);

  gsl_linalg_LU_solve (&m.matrix, p, &v.vector, x);

  free(pde_matrix);
  free(pde_vector);
  gsl_permutation_free (p);

  gsl_vector_scale (x,pow(1.0/h,2));
  return x;
}
