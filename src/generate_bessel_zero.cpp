
#include "../includes/global.h"
#include "../includes/prototype.h"
void generate_bessel_zero(){
  /*  int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);*/
    int Nmax=max(index_basis[0].Nmax,coulomb_expand_b_n);
    int o=0;
    double result=0.0;
    bessel_zero=(double *)calloc((Mmax+1)*Nmax,sizeof(double));
    bessel_Jn=(double *)calloc((Mmax+1)*Nmax,sizeof(double));
    for(int i=1;i<=Nmax;i++){
	for(int j=0;j<=Mmax;j++){
	    result=gsl_sf_bessel_zero_Jnu(j,i);
	    bessel_zero[o]=result;
	    bessel_Jn[o]=gsl_sf_bessel_Jn(j+1,result); 
//	    if(id==0) printf("bessel_zero[%d]=%e\tbessel_Jn[%d]=%e\tnmax=%d\n",o,bessel_zero[o],o,bessel_Jn[o],Nmax); 
	    o=o+1; 
	}
    }

}
