#include "../includes/global.h"
#include "../includes/prototype.h"
void display_Coulomb_potential(int i){
    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    char name[30];    
    double h=20;
    int section=L_sys*h/numprocs+1;
    sprintf(name,"./data/out_V%d_%d.m",i,id);

    ofstream outfile;
    outfile.open(name);
    //freopen((const char*)name,"w",stdout);

    for(int x=id*section;x<=(id+1)*section && x<=L_sys*h;x++){
	///cout<<x<<"\t"<<0<<endl;
        outfile<<x<<"\t"<<Coulomb_potential(0,(x/*-L_sys*40*/)/h)<<endl;
      //      printf("%d\t%f\n",x,
// 		    Coulomb_potential(0,(x/*-L_sys*40*/)/h)
//                   Get_V_xc2(0.0,0.025*(x))
		    //(sqrt(pow(R,2+pow(fabs(x/h-0.5*L_sys),2)))-fabs(x/h-0.5*L_sys))
/*		    (fabs(0.1*V_Cpde(0,(x)/h)
		    /Coulomb_potential(0,(x)/h))-1<10?fabs(0.1*V_Cpde(0,(x)/h)
		    /Coulomb_potential(0,(x)/h))-1:0.0)*/
//		    V_Cpde(0,(x)/h)/Coulomb_potential(0,(x/*-L_sys*40*/)/h)
		    //rho_psi_old(0.0,(x)/h)-n0
//		    -V_Cpde(0,(x)/h)
     //             );                                 
        //}printf("\n");                                          
    }
/*
    if(id==numprocs-1){
	    //printf("\nsurf(v)\n");
//        printf("pause(4)\n");
//	    printf("\nplot(v(1,:),'linewidth',%d)\n",i%5+1);
    }
*/
    outfile.close();
    //fclose(stdout);
    //freopen("/dev/tty","w",stdout);
}

