
#include "../includes/global.h"
#include "../includes/prototype.h"

void scf(){
    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    //while(delta>erf_eigen){

    //while(loop_number<2){
        loop_number=loop_number+1;
        delta_rho=0.0;
        flag=0;
        delta=0;

        if(loop_number>1){
            //Mix.points=1;//spline_vxc.points;
            //Mix.set();

            //MixV.points=1;
            //MixV.setV();
        }

        if(!Psi_1.wf){
            Psi_1.wf=(Wave_function::_wave*)calloc(occupied_electrons,sizeof(Wave_function::_wave));
        }

        for(int m=0;m<=Mmax;m++){
            if((id==0) & print_mode){  
                printf("\n\n\n\t\t--" CYAN"[%d]" RESET"--" BLUE"loop[%d]" RESET"\t\t\n\n\n",m+1,loop_number);
                printf("\n\n\n=================================");
                printf("\n___generate_Hamiltonian_begin____");
                printf("\n==========================================\n");
            } 

            Hamiltonian(m,loop_number);        ////-----<<<1>>>

            MPI_Reduce(&delta_rho,&delta,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);
            MPI_Bcast(&delta,1,MPI_DOUBLE,0,MPI_COMM_WORLD); 

            if((id==0) & print_mode){
                //print_matrix(m,H); 
                print_matrix(m,ht[m].h); 
            }
            MPI_Barrier(MPI_COMM_WORLD);

            if(numprocs>=index_basis[m].Tot){
                //flag=Diagonal_Hamiltonian(H,m,flag); ////-----<<<2>>>
                flag=Diagonal_Hamiltonian(ht[m].h,m,flag); ////-----<<<2>>>
            }else{
                //flag=Diagonal_parallel(H,m,flag);
                flag=Diagonal_parallel(ht[m].h,m,flag);
            }
            //free(ht[m].h);
            //free(H);	
        }

        if((id==0) & (loop_number>10) & print_mode){
            //check_orthogonal();
            print_wave_function(flag,loop_number); 
            //print_Psi_eig(flag,loop_number); 
            //printf("---------------------------------------free[H]--m--[%d]\n\n",m);
        }

        if(loop_number<3) delta=2.0;

        if((id==0) & print_mode){	
            printf("\n\n\t\t\t\t\t*******************"); 
            printf("\n********************************************loop__end%d   **\n",loop_number); 
            printf("\t\t\t\t\t*******************\n\n"); 
            printf("__display_result__\n"); 
            cout<<"delta_out="<<delta_rho<<endl;
        }

        MPI_Barrier(MPI_COMM_WORLD);
        Arrange_Psi_m();
        Psi_1.points=1;
        Psi_1.pcreateb();
        //printPsi();
        //Psi_1.create_b();
        //Psi_1.pcreatevxc();
        //Psi_1.stRHO();
        //Psi_1.stV();

        /*
        //if(id==0) Psi_1.printcheck('b');
        //////check_vxc//
        if(id==0) cout<<"*************************************************"<<endl;
        Psi_1.SetVxc();
        if(id==3) Psi_1.printcheck('v');
        MPI_Barrier(MPI_COMM_WORLD);
        if(id==0) cout<<"*************************************************"<<endl;
        //Psi_1.create_vxc();
        Psi_1.pcreatevxc();
        if(id==3) Psi_1.printcheck('v');
        MPI_Barrier(MPI_COMM_WORLD);
        ///////
        */


        //spline_vxc.points=1;
        //spline_vxc.vxc();

        //FstPoisson.points=10;
        //FstPoisson.FstPs(loop_number);

        //cylinder.points=20;
        //cylinder.solve_pde(loop_number);
        //if(id==0){
        //}

        if((id==0) & print_mode){
            double rho_integral=Integral_rho(&rho_test);
            double rho_n=PI*pow(R,2.0)*L;
            printf("display_rho_%d->Integral_rho=%1.6e[%1.5e]\n",loop_number,rho_integral,rho_n*n0);
        }

        display_result(loop_number,delta); 
        MPI_Barrier(MPI_COMM_WORLD);
        //python_draw(loop_number);
        MPI_Barrier(MPI_COMM_WORLD);
        if(id==0) cout<<CYAN"delta("<<loop_number<<")="<<delta<< RESET<<endl;
    //}



}



