#include "../includes/global.h"
#include "../includes/prototype.h"
void Wave_function::create_vxc(){

    if(!Im_vxc_) Im_vxc_=(double *)calloc((2*coulomb_expand_b_l+1)*coulomb_expand_b_n,sizeof(double));
    if(!Re_vxc_) Re_vxc_=(double *)calloc((2*coulomb_expand_b_l+1)*coulomb_expand_b_n,sizeof(double));
    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    int o=0;
    int number=occupied_electrons;
    for(int n=1;n<=coulomb_expand_b_n;n++){
	for(int l=-coulomb_expand_b_l;l<=coulomb_expand_b_l;l++){
	    Im_vxc_[o]=expandbasisIm(0,0,n,l,0,rhoShell,NULL);
	    Re_vxc_[o]=expandbasisRe(0,0,n,l,0,rhoShell,NULL);
	    o=o+1; 
	}
    }
}


