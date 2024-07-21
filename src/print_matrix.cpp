#include "../includes/global.h"
#include "../includes/prototype.h"
void print_matrix(int m,double *z){
int n=index_basis[m].Tot;
int o=0;
printf("\n----------" RED "m=[%d]" RESET "--" CYAN "dim-[%d]" RESET "--------\n",m,n);
printf("H=\n[");
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        printf("%1.9f",z[o]);
        if(j!=n-1){printf(",\t");} 
        o=o+1; 
    }
if(i!=n-1){printf(";\n");}else{printf(";]\n");}
}
printf("\n+++++++++++++++++++++++++++++++++\n");
}
