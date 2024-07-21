#include "../includes/global.h"
#include "../includes/prototype.h"
void surf(int i,char *prename,FuncPtr pV){

    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    char name[30];    
    double h=30;
    double hth=30;
//    int fl=floor(h*(BoxMag+L*0.5))+1;
    int section=L_sys*h/numprocs+1;
    sprintf(name,"./data/Out_%s%d_%d.m",prename,i,id);
    freopen((const char*)name,"w",stdout);
    for(int x=id*section;x<=(id+1)*section && x<=(L_sys)*h;x++){
	//if(x/h>=BoxMag+L*0.5 & x/h<=L_sys-BoxMag-L*0.5){
for(int th=0;th<=2*PI*hth;th++){
	    for(int r=0;r<=(R_sys)*h;r++){
		//printf("%s(%d,%d,%d)=%1.4e;\n",prename,r+1,th+1,x+1,pV(r/h,x/h)); 
		//printf("%s(%d,%d,%d)=%1.4e;\n",prename,floor(r*cos(th/h))+1,floor(r*sin(th/h))+1,x+1,pV(r/h,x/h)); 
		cout<<prename<<"("<<floor(R_sys*h+r*cos(th/hth))+1<<","<<floor(R_sys*h+r*sin(th/hth))+1<<","<<x+1<<")="<<pV(r/h,x/h)<<";"<<endl; 
		//printf("%s(%1.5e,%1.5e)=%1.4e;\n",prename,r*1.0/h,x*1.0/h,pV(1.0*r/h,1.0*x/h)); 
	//	printf("%s(%d,%d)=%1.4e;\n",prename,r+1,x+1-fl,pV(r/h,x/h)); 
}printf("\n");                                          
	    }printf("\n");                                          
	//}
    }


    if(id==numprocs-1){
//	    printf("\nsurf(%s)\n",prename);
	    printf("\nff=%s;\n",prename);
//        printf("pause(4)\n");
//	    printf("\nplot(%s(%d,:),'linewidth',%d)\n",prename,1,i%5+1);
    }

    fclose(stdout);
    freopen("/dev/tty","w",stdout);
    //double U=Coulomb_potential(0,BoxMag+L*0.5)-Coulomb_potential(0,L_sys-BoxMag-L*0.5);
    //if(id==0) printf("\nU=%1.5f\tE=%1.5f\tE_theory=%1.5f\tmismatch=%1.5f\n",U,U/(N+L),U/((N+L)*n0),floor(h*(BoxMag+L*0.5)));

}

