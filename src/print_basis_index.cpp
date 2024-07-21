
#include "../includes/global.h"
#include "../includes/prototype.h"
void print_basis_index(){
    //printf("occupied_electrons=%d----nt_index_basis=%d\n",occupied_electrons,Mmax); 
    printf("----------index_basis---------------\n"); 
    printf("-------------" RED "Mmax=%d" RESET "----------------\n",Mmax); 
    printf("------------------------------------\n"); 
    for(int m=0;m<=Mmax;m++){
        printf("index_basis__" RED "Mmax[%d]__" CYAN "Nmax[%d]___" RED "tot=%d" RESET "\n",m,index_basis[m].Nmax,index_basis[m].Tot);
        for(int n=1;n<=index_basis[m].Nmax;n++){
            printf("\tMmax[%d]---" GREEN "Nmax[%d]" RESET "--->" YELLOW "Lmax[%d]" RESET "\n",m,n,index_basis[m].Lmax[n-1]);
        }printf("\n");
    }
    printf("-------------------------------------------------\n");
    printf("_________________________________________________\n\n");
}
