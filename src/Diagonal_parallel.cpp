
#include "../includes/global.h"
#include "../includes/prototype.h"
extern "C" {
    int numroc_(const int*, const int*, const int*, const int*, const int*);
    void descinit_(int *, const int *, const int *, const int *, const int *, const int *, const int *,const int *, const int *,int *);
}

int Diagonal_parallel(double *H,int m,int flag){

    int tot=index_basis[m].Tot; 

    int ZEROi = 0;
    int MONEi=-1; 
    int ONEi=1;    
    double ONEd=1.0;
    double ZEROd=0.0;
    double ORFAC=0.0;

    int N=tot; 
    int M=tot; 
    int Nb=20; 
    int Mb=20; 
    int descA[20];
    int descZ[20];

    int MM=-1,NZ=-1; 
    int *IFAIL;
    IFAIL=(int*)calloc(N,sizeof(int));

    double *GAP;
    double *W;
    GAP=(double*)calloc(N,sizeof(double));
    W=(double*)calloc(N,sizeof(double));

    int *ICLUSTER; 
    ICLUSTER=(int*)calloc(N*M,sizeof(int));

    double MPIelapsed;
    double MPIt2;
    double MPIt1;

    int id,numprocs;
    int ctxt, myrow, mycol;

    blacs_pinfo_(&id, &numprocs);
    blacs_get_(&MONEi, &ZEROi, &ctxt);
    bool mpiroot = (id == 0);
    double *A=NULL , *A_loc;
    double *Z=NULL,*Z_loc;  
    int info; 
    Z=(double *)calloc(N*M,sizeof(double));

    if (mpiroot) {
	A=H;	
    }
    MPIt1=MPI_Wtime();
    int procrows = sqrt(numprocs), proccols = sqrt(numprocs);
    blacs_gridinit_(&ctxt, "R", &procrows, &proccols);  
    blacs_gridinfo_(&ctxt, &procrows, &proccols, &myrow, &mycol );  
    int nrows = numroc_(&N, &Nb, &myrow, &ZEROi, &procrows);
    int lda = max(1,nrows);
    int ncols = numroc_(&M, &Mb, &mycol, &ZEROi, &proccols);
    double abstol=pdlamch(&ctxt,"U");
    descinit_(descA, &N, &M, &Nb, &Mb,&ZEROi,&ZEROi,&ctxt, &lda, &info);
    descinit_(descZ, &N, &M, &Nb, &Mb,&ZEROi,&ZEROi,&ctxt, &lda, &info);
    A_loc=(double *)calloc(nrows*ncols,sizeof(double));
    Z_loc=(double *)calloc(nrows*ncols,sizeof(double));

    /* Scatter matrix */
    int sendr = 0, sendc = 0, recvr = 0, recvc = 0;
    for (int r = 0; r < N; r += Nb, sendr=(sendr+1)%procrows) {
	sendc = 0;
	int nr = Nb;
	if (N-r < Nb)
	    nr = N-r;
	for (int c = 0; c < M; c += Mb, sendc=(sendc+1)%proccols) {
	    int nc = Mb;
	    if (M-c < Mb)
		nc = M-c;
	    if (mpiroot) {
		dgesd2d_(&ctxt, &nr, &nc, A+N*c+r, &N, &sendr, &sendc);
	    }
	    if (myrow == sendr && mycol == sendc) {
		dgerv2d_(&ctxt, &nr, &nc, A_loc+nrows*recvc+recvr, &nrows,&ZEROi,&ZEROi);
		recvc = (recvc+nc)%ncols;
	    }
	}
	if (myrow == sendr)
	    recvr = (recvr+nr)%nrows;
    }
    MPIt2=MPI_Wtime();
    MPIelapsed=MPIt2-MPIt1;    
    MPIt1=MPI_Wtime(); 
    blacs_barrier_(&ctxt,"A");

    int LWORK;

    double LWORKOPT;
    int LIWORKOPT; 
    int Eselect=min(occupied_electrons,N);
    if(mpiroot) printf(RED"Eselect=%d" RESET"\n",Eselect);    
    pdsyevx_("V","I","L",&N, A_loc, &ONEi , &ONEi, descA, &ZEROd, &ZEROd, &ONEi,&Eselect, &abstol, &MM, &NZ, W, &ORFAC, Z_loc, &ONEi, &ONEi, descZ, &LWORKOPT,&MONEi, &LIWORKOPT, &MONEi, IFAIL, ICLUSTER, GAP, &info );

    LWORK=(int)LWORKOPT;
    double *WORK=(double*)calloc(LWORKOPT,sizeof(double));

    int IWORK[LIWORKOPT];
    blacs_barrier_(&ctxt,"A");
    pdsyevx_("V","I","L",&N, A_loc, &ONEi , &ONEi, descA, &ZEROd, &ZEROd, &ONEi,&Eselect, &abstol, &MM, &NZ, W, &ORFAC, Z_loc, &ONEi, &ONEi, descZ, WORK,&LWORK, IWORK, &LIWORKOPT, IFAIL, ICLUSTER, GAP, &info );



    MPIt2=MPI_Wtime();
    MPIelapsed=MPIt2-MPIt1;
    if(mpiroot & print_mode){
	cout<<"timepdsyevx("<<MM<<")"<<"="<<MPIelapsed<<";"<<endl;
	cout<<YELLOW"w(0)"<<"="<<W[0]<<RESET<<";"<<endl;
    }
    //Gather matrix 
    sendr = 0;
    for (int r = 0; r < N; r += Nb, sendr=(sendr+1)%procrows) {
	sendc = 0;
	int nr = Nb;
	if (N-r < Nb)
	    nr = N-r;
	for (int c = 0; c < M; c += Mb, sendc=(sendc+1)%proccols) {
	    int nc = Mb;
	    if (M-c < Mb)
		nc = M-c;
	    if (myrow == sendr && mycol == sendc) {
		dgesd2d_(&ctxt, &nr, &nc, Z_loc+nrows*recvc+recvr, &nrows,&ZEROi,&ZEROi);
		recvc = (recvc+nc)%ncols;
	    }
	    if (mpiroot) {
		dgerv2d_(&ctxt, &nr, &nc, Z+N*c+r, &N, &sendr, &sendc);
	    }
	}
	if (myrow == sendr)
	    recvr = (recvr+nr)%nrows;
    }


    MPI_Bcast(Z,N*M,MPI_DOUBLE,0,MPI_COMM_WORLD);
    if(info==0){
	flag=renew_Psi(m,W,Z,flag);
    }


    free(WORK);
    free(IFAIL);
    free(GAP);
    free(W);
    free(ICLUSTER);
    free(Z);
    free(A_loc);
    free(Z_loc);
    blacs_gridexit_(&ctxt);
    return flag;
}
