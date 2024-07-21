#include "../includes/global.h"
#include "../includes/prototype.h"
int Diagonal_Hamiltonian(double *H,int m,int flag){
    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    clock_t start,finish;
    start=clock(); 
    int n=index_basis[m].Tot;
    double LWORKOPT;
    int LWORK=-1; 
    int IWORK[5*n]; 
    double dZERO=0.0;
    int iONE=1;
    int iMONE=-1;
    double w[n];                
    double z[n*n];              
    int lda=n;
    int mm=-1;                   
    double abstol=0.0;     
    int ldz=n;               
    int ifail[5*n];
    int info;

    if(id==0){
	int Eselect=min(occupied_electrons,n);
	printf(RED "Eselect=%d" RESET "\n",Eselect);    dsyevx_("V","I","L",&n,H,&lda,&dZERO,&dZERO,&iONE,&Eselect,&abstol,&mm,w,z,&ldz,&LWORKOPT,&LWORK,IWORK,ifail,&info); LWORK=(int)LWORKOPT; double WORK[LWORK]; 

	dsyevx_("V","I","L",&n,H,&lda,&dZERO,&dZERO,&iONE,&Eselect,&abstol,&mm,w,z,&ldz,WORK,&LWORK,IWORK,ifail,&info);
    }

    MPI_Bcast(w,n,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(z,n*n,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Bcast(&info,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    if(info==0){
	flag=renew_Psi(m,w,z,flag);
    }

    finish=clock();

    if((id==0) & print_mode){
	double duration=(double)(finish-start)/CLOCKS_PER_SEC;
	printf("\nDiagonal_Hamiltonian take " GREEN "%f" RESET " seconds\n",duration);
	printf(YELLOW "w[0]=%1.6f" RESET,w[0]);
    }    
    return flag;
}
