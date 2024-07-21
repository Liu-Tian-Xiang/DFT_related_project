
#include "../includes/global.h"
#include "../includes/prototype.h"

int transform(int i,int tot){
    for(int j=0;j<tot;j++){
	int test=tot*(j+1)-(j+1)*j/2; 
	if((test-tot+j+1)<=i & i<=test){
	    /* int result=i+(j+1)*j/2; 
	       if(result%2==(1+(tot+1)*j)%2){
	       return result;
	       }else{
	       return 0;
	       }*/
	    return i+(j+1)*j/2; 
	}
    }
    return 0;
}

void Hamiltonian(int m,int loop_number){
    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    int *p; 
    int index,o; 
    //FuncPtr integrand=(rs>1?&Get_V_xc2:&Get_V_xc1); 
    int Nmax=index_basis[m].Nmax;
    int tot=index_basis[m].Tot;
    int dim=(tot+1)*tot/2;
    int period=(dim%numprocs?dim/numprocs+1:dim/numprocs);
    double *H;	
    double *H_final;
    H_final=(double*)calloc(numprocs*period,sizeof(double));
    //H_last=(double*)calloc(tot*tot,sizeof(double));
    //ht[m].h=(double*)calloc(tot*tot,sizeof(double));
    H=(double*)calloc(period,sizeof(double));
    if(loop_number>1){

	for(int i=1;i<=period;i++){			
	    index=transform(id*period+i,tot); 
	    p=get_param(m,index,p); 
	    if(/*index &&*/ id*period+i<=dim){
		H[i-1]=0.0
		    +kenetic(index,m,p[0],p[1])
		    +E_g*Integral(p[0],p[1],p[2],p[3],m,Get_V_xc2,NULL)
		    //+E_g*Integral(p[0],p[1],p[2],p[3],m,interpV,&spline_vxc)
		    //+E_g*IntegralMonte(p[0],p[1],p[2],p[3],m,interpV,&spline_vxc)

		    //+V_divide*Integral(p[0],p[1],p[2],p[3],m,interpV,&MixV)
		    //+V_divide*IntegralMonte(p[0],p[1],p[2],p[3],m,interpV,&MixV)
		    +V_divide*V_Coulomb(p[0],p[1],p[2],p[3],m)
		    //+V_divide*Integral(p[0],p[1],p[2],p[3],m,interpV,&FstPoisson)
		    //+Integral(p[0],p[1],p[2],p[3],m,interpV,&cylinder)
		    ;
	    } 
	}
	MPI_Gather(H,period,MPI_DOUBLE,H_final,period,MPI_DOUBLE,0,MPI_COMM_WORLD);
	if(id==0){ 
	    o=0;  
	    for(int i=0;i<tot;i++){
		for(int j=i;j<tot;j++){
		    //H_last[i*tot+j]=H_final[o];
		    ht[m].h[i*tot+j]=H_final[o];
		    o=o+1; 
		}
	    }	
	} 
	free(H);		
	free(p); 
	free(H_final);
	//return H_last;       
    }else{
	////////////////////////////////////////////////
	for(int i=1;(i<=period);i++){
	    index=transform(id*period+i,tot); 
	    p=get_param(m,index,p);
	    if(/*index &&*/ id*period+i<=dim){
		H[i-1]=kenetic(index,m,p[0],p[1])
		    +Integral(p[0],p[1],p[2],p[3],m,Init_V,NULL)
		    //+IntegralMonte(p[0],p[1],p[2],p[3],m,Init_V,NULL)
		    ;
	    }
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Gather(H,period,MPI_DOUBLE,H_final,period,MPI_DOUBLE,0,MPI_COMM_WORLD);
	if(id==0){ 
	    o=0;  
	    for(int i=0;i<tot;i++){
		for(int j=i;j<tot;j++){
		    //H_last[i*tot+j]=H_final[o];
		    ht[m].h[i*tot+j]=H_final[o];
		    o=o+1; 
		}
	    }	
	}
	free(H);
	free(p); 
	free(H_final);
	//return H_last;       
    } 
}

