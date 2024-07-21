#include "../includes/global.h"
#include "../includes/prototype.h"
void printPsi(){
    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    for(int ii=0;ii<occupied_electrons;ii++){
	if(id==0) printf("\n%d\teig=%1.4f\tm=%d\n",ii,Psi_1.wf[ii].eig,Psi_1.wf[ii].m);
	int Nk=(2*coulomb_expand_b_l+1)*coulomb_expand_b_n;

	for(int i=0;i<Nk;i++){
	    if(id==0) printf("b[%d]={%1.4f,%1.4f}\n",i,Psi_1.Re_b_[i],Psi_1.Im_b_[i]);
	}

    }

} 
