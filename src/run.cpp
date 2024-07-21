
#include "../includes/global.h"
#include "../includes/prototype.h"
void run_init(){
    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    calc_mode=1;
    if((calc_mode<1 || calc_mode>9) && calc_mode!=M_STOP){
        if(id==0) printf("CalculationMode Wrong");
    }
    if(calc_mode !=M_STOP){
        init();
    }
}
void define_run_modes(){

    switch(calc_mode){
        case M_START_STATIC_CALC:
            i_stack.clear();
            i_stack.push_back(I_END);
            i_stack.push_back(I_FREE);
            i_stack.push_back(I_SCF);
            i_stack.push_back(I_SETUP_HAMILTONIAN);
            i_stack.push_back(I_PRINT_BASIS);
            break;
            //default:
    }
}
void test(){
    printf("scf_instr=%d\n",instr);
    loop_number+=1;
}
void run(){
    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    string sub_name = "run"; push_sub();
    run_init();
    define_run_modes();
    instr=i_stack.size()-1;

    while(i_stack[instr]!=I_END){
        delta=2.0;

        switch(i_stack[instr]){
            case I_FREE:
                free_everything(); 
                MPI_Barrier(MPI_COMM_WORLD);
                instr=instr-1;
                break;
            case I_PRINT_BASIS:
                if(id==0 /*& print_mode*/){
                    print_basis_index(); 
                }
                MPI_Barrier(MPI_COMM_WORLD);
                instr=instr-1;
                break;
            case I_SCF:
                scf();
                MPI_Barrier(MPI_COMM_WORLD);
                if(loop_number>1){
                    instr=instr-1;
                }
                break;
            default:
                MPI_Barrier(MPI_COMM_WORLD);
                instr=instr-1;
        }


    }


}
