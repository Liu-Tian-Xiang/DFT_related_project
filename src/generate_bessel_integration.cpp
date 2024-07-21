
#include "../includes/global.h"
#include "../includes/prototype.h"
void generate_bessel_integration(){
    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    int Nmax=index_basis[0].Nmax;
    int o=0;
    //extern double *besse;
    trip_integrate_bessel=(double *)calloc(coulomb_expand_b_n*Nmax*Nmax*(Mmax+1),sizeof(double));
    for(int i=1;i<=coulomb_expand_b_n;i++){
        for(int j=1;j<=Nmax;j++){
            for(int k=1;k<=Nmax;k++){
                for(int l=0;l<=Mmax;l++){
                    trip_integrate_bessel[o]=bessel_integration(i,j,k,l);
                    //		if(id==2) printf("bessel[%d][%d][%d][%d]=%e\n",i,j,k,l,trip_integrate_bessel[o]); 
                    o=o+1;
                }
            }
        }
    }
    //return besse;
}
