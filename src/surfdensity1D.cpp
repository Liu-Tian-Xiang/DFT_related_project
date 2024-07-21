#include "../includes/global.h"
#include "../includes/prototype.h"
void surfdensity1D(int i,char *prename,void *ptr){

    Wave_function *para=(Wave_function *)ptr;
    //FuncPtr *para=(FuncPtr *)ptr;

    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    char name[30];    
    double h=30;
//    int fl=floor(h*(BoxMag+L*0.5))+1;
    int section=L_sys*h/numprocs+1;
    sprintf(name,"./data/Out1D_%s%d_%d.m",prename,i,id);
    freopen((const char*)name,"w",stdout);

    for(int x=id*section;x<=(id+1)*section && x<=(L_sys)*h;x++){
	//if(x/h>=BoxMag+L*0.5 & x/h<=L_sys-BoxMag-L*0.5){
	    for(int r=0;r<=(R_sys)*h;r++){
		cout<<r*1.0/h<<"\t\t\t"<<x*1.0/h<<"\t\t\t"<<para->rho(r*1.0/h,x*1.0/h)<<endl;
	    }printf("\n");                                          
	//}
    }

    if(id==numprocs-1){

	printf("\n\n\n---print__init---\n");  
	printf("\t\tPI=%1.9f\n",PI); 
	printf("\t\tR=%1.4f\n",R); 
	printf("\t\tL=%1.4f\n",L); 
	printf("\t\tN=%1.4f\n",N); 
	printf("\t\tR_sys=%1.4f\n",R_sys); 
	printf("\t\tL_sys=%1.4f\n",L_sys); 
	printf("\t\tE_divide=%1.9f\n",E_divide); 
	printf("\t\tV_divide=%1.9f\n",V_divide); 
	printf("\t\tkf=%1.9f\n",kf); 
	printf("\t\tn0=%1.9f\n",n0); 
	printf("\t\tEf0=%1.9f\n",Ef0); 
	printf("\t\tlf=%1.9f\n",lf); 
	printf("\t\tMmax=%d\n",Mmax); 
	printf("\t\tE_g=%1.3e\n",E_g); 
	printf("\t\toccupied_electrons=%d\n",occupied_electrons);
    }

    fclose(stdout);
    freopen("/dev/tty","w",stdout);
    //double U=Coulomb_potential(0,BoxMag+L*0.5)-Coulomb_potential(0,L_sys-BoxMag-L*0.5);
    //if(id==0) printf("\nU=%1.5f\tE=%1.5f\tE_theory=%1.5f\tmismatch=%1.5f\n",U,U/(N+L),U/((N+L)*n0),floor(h*(BoxMag+L*0.5)));

}

