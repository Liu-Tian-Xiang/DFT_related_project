
#include "../includes/global.h"
#include "../includes/prototype.h"
void print_wave_function(int flag,int loop_number){
    if(loop_number>0){ 
	for(int i=0;i<flag;i++){
	    int m=Psi_1.wf[i].m;
	    int mm=Psi_1.wf[i].m;
	    printf("__________________________________________\n");
	    printf("|" CYAN"electron[%d]==" RED"<<old>>" RESET"\n",i+1);
	    printf("|-----" BLUE"[m]=%d" RESET"\n",m);
	    printf("|-----" YELLOW"[Nmax]=%d" RESET"\n",index_basis[m].Nmax);
	    printf("|-----" RED"tot=%d" RESET"\n",index_basis[m].Tot);
	    printf("|-----" GREEN"eig=%1.6e" RESET"\n",Psi_1.wf[i].eig);
	    printf("=========================================\n");
	    printf("|" CYAN"electron[%d]==" GREEN"<<new>>" RESET"\n",i+1);
	    printf("|-----" BLUE"[m]=%d" RESET"\n",mm);
	    printf("|-----" YELLOW"[Nmax]=%d" RESET"\n",index_basis[mm].Nmax);
	    printf("|-----" RED"tot=%d" RESET"\n",index_basis[mm].Tot);
	    printf("|-----" GREEN"eig=%1.6e" RESET"\n",Psi_1.wf[i].eig);
	    printf("|\\\\\\\\\\\\" YELLOW"Lmax_collection" RESET"\\\\\\\\\\\\\\\\\\\n");


	    for(int n=1;n<=max(index_basis[m].Nmax,index_basis[mm].Nmax);n++){
		printf("|" RED"[old]" CYAN"electron" YELLOW"[n]=%d" RESET"->" MAGENTA"[Lmax]=%d" RESET"------",n,index_basis[m].Lmax[n-1]);
		printf("|" GREEN"[new]" CYAN"electron" YELLOW"[n]=%d" RESET"->" MAGENTA"[Lmax]=%d" RESET"---",n,index_basis[mm].Nmax);
		printf("\n------------------------------------------");
		for(int l=1;l<=max(index_basis[m].Lmax[n-1],index_basis[mm].Lmax[n-1]);l++){
			if(l<=index_basis[m].Lmax[n-1] & n<=index_basis[m].Nmax){
				printf("\n\tA_" CYAN"n" YELLOW"l" RESET"[" CYAN"%d" RESET"-" YELLOW"%d" RESET"]->%1.3e  ",n,l,Psi_1.wf[i].A_nl[find_A_index_basis(m,n,l)]); 
			}//else{printf("\t\t\t\t");}
			if(l<=index_basis[mm].Lmax[n-1] & n<=index_basis[mm].Nmax){
				printf("\t\t\tA_" CYAN"n" YELLOW"l" RESET"[" CYAN"%d" RESET"-" YELLOW"%d" RESET"]->%1.3e \n ",n,l,Psi_1.wf[i].A_nl[find_A_index_basis(mm,n,l)]); 
			}else{printf("\t\t\t\t");}
		}printf("\n");
	    }printf("------------------------------------------>>>" RED"%d\tPsi_p" RESET"\n",i+1);
	}



	printf("\n");
	printf("\n");
    }
}
