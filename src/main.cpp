#include "../includes/global.h"
#include "../includes/prototype.h"
int occupied_electrons,Mmax;
double Ec,R,L,N,R_sys,L_sys,BoxMag,rs,PI,Ef0,n0,kf,lf;
INDEX_JELLIUM_ROD *index_basis;
HAMILTONIAN *ht;
Wave_function Psi_1;
spline_space cylinder,spline_vxc,FstPoisson,Mix,MixV;
int coulomb_expand_b_l,coulomb_expand_b_n;
double erf_eigen,BoxMag_R;
double *trip_integrate_bessel; 
double *bessel_zero;
double *bessel_Jn;
double E_g,delta_rho,delta;
double E_divide,V_divide;
int print_mode;
int calc_mode,instr;
std::vector<int> i_stack;
int flag,loop_number=0;

group_creat *group; 
MPI_Group world_group,group_gather;
MPI_Comm gather_comm;

int main(int argc,char *argv[]){

    int id,numprocs;
    int namelen; 
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Get_processor_name(processor_name,&namelen);
    fprintf(stderr,"Process %d on %s\t%d\n",id,processor_name,numprocs);
    MPI_Barrier(MPI_COMM_WORLD);

    char inputfile[18]="./inputs/para2.in";
    if(id==0) print_mode=1;
    /////seting//////
    int Multcore=0;
    //MPI_Bcast(&Multcore,1,MPI_INT,0,MPI_COMM_WORLD);
    /////////////////
    //if(id==3) printf("multcore=%d\n",Multcore);
    double MPIelapsed;
    double MPIt2;
    double MPIt1;
    //gsl_set_error_handler_off();
    MPIt1=MPI_Wtime();

    run();

    //if(id==1 | id==2) Py_Finalize();
    MPI_Finalize();
    return 0;
}
