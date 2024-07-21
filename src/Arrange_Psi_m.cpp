#include "../includes/global.h"
#include "../includes/prototype.h"
void Arrange_Psi_m(){
    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);


    Wave_function::_wave tp[2*occupied_electrons];
    int k=0;
    for(int j=0;j<occupied_electrons;j++){
	if(Psi_1.wf[j].m==0){
	    tp[k]=Psi_1.wf[j];
	    k=k+1;
	}else{
	    tp[k]=Psi_1.wf[j];	
	    tp[k+1]=Psi_1.wf[j];	
	    k=k+2;
	}
    }

    for(int i=0;i<occupied_electrons;i++){
	Psi_1.wf[i]=tp[i];
    }
}
