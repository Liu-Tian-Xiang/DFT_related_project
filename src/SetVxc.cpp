#include "../includes/global.h"
#include "../includes/prototype.h"
void Wave_function::SetVxc(){

    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    int Nk=(2*coulomb_expand_b_l+1)*coulomb_expand_b_n;
    int period=(Nk%numprocs?Nk/numprocs+1:Nk/numprocs);
    double* SectionIm=(double *)calloc(period,sizeof(double)); 
    double* SectionRe=(double *)calloc(period,sizeof(double)); 
    if(!Im_vxc_) Im_vxc_=(double *)calloc(numprocs*period,sizeof(double));
    if(!Re_vxc_) Re_vxc_=(double *)calloc(numprocs*period,sizeof(double));
    //srand((int)time(NULL)); 
    srand(0); 
    //int o=0;
    int number=occupied_electrons;
//for(int i=0;i<Nk;i++){
	for(int i=1;i<=period;i++){
	    if(id*period+i<=Nk){
		int n=(id*period+i-1)/(2*coulomb_expand_b_l+1)+1;
		int l=(id*period+i-1)%(2*coulomb_expand_b_l+1)-coulomb_expand_b_l;
		SectionRe[i-1]=n;///*Get_V_xc2(n,l,NULL);*/Psi_1.rho(n,l);
		SectionIm[i-1]=l;///*Get_V_xc2(l,n,NULL);*/Psi_1.rho(l,n);
	    }
	    //Im_vxc_[o]=//Psi_1.rho(n,l);
	    //(double)(rand()%100)/(double)(rand()%10+1);
	    //Re_vxc_[o]=//Psi_1.rho(n,l);
	    //(double)(rand()%100)/(double)(rand()%10+1);
	    //o=o+1; 
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Gather(SectionIm,period,MPI_DOUBLE,Im_vxc_,period,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Gather(SectionRe,period,MPI_DOUBLE,Re_vxc_,period,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Bcast(Re_vxc_,Nk,MPI_DOUBLE,0,MPI_COMM_WORLD); 
	MPI_Bcast(Im_vxc_,Nk,MPI_DOUBLE,0,MPI_COMM_WORLD); 
	MPI_Barrier(MPI_COMM_WORLD);
	free(SectionIm);
	free(SectionRe);
}
