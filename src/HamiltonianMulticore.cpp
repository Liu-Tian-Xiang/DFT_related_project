
#include "../includes/global.h"
#include "../includes/prototype.h"

int transformCore(int i,int tot){
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


void HamiltonianMulticore(int m,int loop_number){

   int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    int *p; 
    int index,o;
    //FuncPtr integrand=(rs>1?&Get_V_xc2:&Get_V_xc1); 
    int Nmax=index_basis[m].Nmax;
    int tot=index_basis[m].Tot;
    int dim=(tot+1)*tot/2;

    int period=(dim%(numprocs/4)?dim/(numprocs/4)+1:dim/(numprocs/4));
    double *H;	
    double *H_final;
    H_final=(double*)calloc(numprocs*period,sizeof(double));
    //H_last=(double*)calloc(tot*tot,sizeof(double));
    ht[m].h=(double*)calloc(tot*tot,sizeof(double));
    H=(double*)calloc(period,sizeof(double));

    /////////////////////////define the groups//////////////////////////////////////    
    MPI_Group world_group;
    MPI_Comm_group(MPI_COMM_WORLD,&world_group);
    int group_head[numprocs/4];
    int parts[4]={id/4*4,1+id/4*4,2+id/4*4,3+id/4*4};
    for(int i=0;i<numprocs/4;i++){
	group_head[i]=4*i;
    } 
    MPI_Group_incl(world_group, 4, parts, &group[id/4].group_parts);
    MPI_Comm_create(MPI_COMM_WORLD, group[id/4].group_parts, &group[id/4].group_parts_comm);

    MPI_Group group_gather;
    MPI_Comm gather_comm;
    MPI_Group_incl(world_group, numprocs/4, group_head, &group_gather);
    MPI_Comm_create(MPI_COMM_WORLD, group_gather, &gather_comm);
    ////////////////////////////////////////////////////////////////////////////////    

    if(loop_number>1){
	for(int i=1;i<=period;i++){			
	    index=transformCore(id/4*period+i,tot); 
	    p=get_param(m,index,p); 
	    if(id/4*period+i<=dim){
		H[i-1]=kenetic(index,m,p[0],p[1])
		    +E_g*IntegralMulticore(p[0],p[1],p[2],p[3],m,interpV,&spline_vxc)
		    +V_divide*V_Coulomb(p[0],p[1],p[2],p[3],m)
		    ;
	    } 
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if(MPI_COMM_NULL!=gather_comm){
	    MPI_Gather(H,period,MPI_DOUBLE,H_final,period,MPI_DOUBLE,0,gather_comm);
	    MPI_Comm_free(&gather_comm);
	} 
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

	if(MPI_GROUP_NULL!=group_gather) MPI_Group_free(&group_gather);
	if(MPI_GROUP_NULL!=group[id/4].group_parts) MPI_Group_free(&group[id/4].group_parts);
	if(MPI_COMM_NULL!=group[id/4].group_parts_comm) MPI_Comm_free(&group[id/4].group_parts_comm);   
	free(H);		
	free(p); 
	free(H_final);

	//return H_last;       
    }else{

	////////////////////////////////////////////////
	for(int i=1;i<=period;i++){
	    index=transformCore(id/4*period+i,tot); 
	    p=get_param(m,index,p);
	    if(id/4*period+i<=dim){
		H[i-1]=kenetic(index,m,p[0],p[1])
		    +IntegralMulticore(p[0],p[1],p[2],p[3],m,Init_V,NULL)
		    ;
	    }
	}
	MPI_Barrier(MPI_COMM_WORLD);

	if(MPI_COMM_NULL!=gather_comm){
	    MPI_Gather(H,period,MPI_DOUBLE,H_final,period,MPI_DOUBLE,0,gather_comm);
	    MPI_Comm_free(&gather_comm); 
	} 
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
	if(MPI_GROUP_NULL!=group_gather) MPI_Group_free(&group_gather);
	if(MPI_GROUP_NULL!=group[id/4].group_parts) MPI_Group_free(&group[id/4].group_parts);
	if(MPI_COMM_NULL!=group[id/4].group_parts_comm) MPI_Comm_free(&group[id/4].group_parts_comm);   
	free(H);
	free(p); 
	free(H_final);
	//return H_last;   
    } 
}

