
#include "../includes/global.h"
#include "../includes/prototype.h"
void free_everything(){
    //cylinder.destroy_();

//    Psi_1.destroy();
//    Psi_2.destroy();
    if(trip_integrate_bessel){
	free(trip_integrate_bessel);
    }

	for(int i=0;i<=Mmax;i++){
//	    free(index_basis[i].Lmax);
	}

    if(index_basis){
	free(index_basis);
    }
    if(bessel_Jn){
	free(bessel_Jn);
    }
    if(bessel_zero){
	free(bessel_zero);    
    }

    printf("free_everything\n"); 
}
