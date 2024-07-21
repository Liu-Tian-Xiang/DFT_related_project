#include "../includes/global.h"
#include "../includes/prototype.h"

void spMatrix::Create_spMatrix2(double v[],int shift[],int lds,int dim){
    dimStruct=lds*dim;
    dimMatrix=dim;
    for(int i=0;i<lds;i++){
	dimStruct=dimStruct-fabs(shift[i]);
    }
    spdiags=(struct _spdiags*)malloc(dimStruct*sizeof(struct _spdiags));
    int o=0;
    for(int i=0;i<lds;i++){
	for(int j=0;j<dim-fabs(shift[i]);j++){
	    if(shift[i]<0){
	    spdiags[o].i=j+abs(shift[i]);
	    spdiags[o].j=j;
	    spdiags[o].eval=v[i*dim+j];
	    }else{
	    spdiags[o].i=j;
	    spdiags[o].j=j+abs(shift[i]);
	    spdiags[o].eval=v[i*dim+j+shift[i]];
	    }
	    o+=1;
	}
    }

}

void spMatrix::Create_spMatrix(double v[],double w[],int shift[],int dim){
    dimStruct=2*dim-shift[1];
    dimMatrix=dim;
    spdiags=(struct _spdiags*)malloc(dimStruct*sizeof(struct _spdiags));
    for(int i=0;i<dimStruct;i++){
	if(i<dimMatrix){
	    spdiags[i].i=i;
	    spdiags[i].j=i;
	    spdiags[i].eval=v[i];
	}else{
	    spdiags[i].i=i-dimMatrix;
	    spdiags[i].j=i-dimMatrix+shift[1];
	    spdiags[i].eval=w[i-dimMatrix+shift[1]];
	}
    }
}

double spMatrix::element(int i,int j){
    for(int k=0;k<dimStruct;k++){
	if(spdiags[k].i==i & spdiags[k].j==j){
	    return spdiags[k].eval;
	}
    }
    return 0;
}


void spMatrix::destroy_spMatrix(){
    free(spdiags);
}


void spMatrix::Print_spMatrix(){
    printf("S=[\n");
    int flag=0;
    for(int i=0;i<dimMatrix;i++){
	for(int j=0;j<dimMatrix;j++){
	    if(j!=dimMatrix-1){

		cout<<element(i,j)<<",\t";

	    }else{
		if(i!=dimMatrix-1){
		    cout<<element(i,j)<<";"<<endl;
		}else{
		    cout<<element(i,j)<<"]"<<endl;
		}
	    }
	}

    }

}
