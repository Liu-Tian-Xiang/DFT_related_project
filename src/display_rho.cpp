/*************************************************************************
  > File Name: display_rho.c
  > Author: 
  > Mail: 
  > Created Time: 
 ************************************************************************/

#include "../includes/global.h"
#include "../includes/prototype.h"
void display_rho(int i){
    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    double R_rho=R_sys;
    double L_rho=L_sys;
    double h=20;
    char name[30];    

    int section=L_rho*h/numprocs+1;
    sprintf(name,"./data/out_rho%d_%d.m",i,id); 
    ofstream outfile;
    outfile.open(name);

    //freopen((const char*)name,"w",stdout);
    for(int z=id*section;z<(id+1)*section && z<=L_rho*h;z++){  

        outfile<<z+1<<"\t"<<Psi_1.rho(0,(z)/h)<<endl;
     //   printf("%d\t%1.3f\n",z+1,Psi_1.rho(0,(z)/h));
    }

    outfile.close();
    //fclose(stdout);
    //freopen("/dev/tty","w",stdout);
    
}
