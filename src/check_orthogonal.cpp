#include "../includes/global.h"
#include "../includes/prototype.h"

void check_orthogonal(){
    cout<<"check Psi_1:"<<endl;
    for(int i=0;i<occupied_electrons;i++){
	int m=Psi_1.wf[i].m;
	double p=0.0;
	for(int j=0;j<index_basis[m].Tot;j++){
	    p=p+pow(Psi_1.wf[i].A_nl[j],2.0);
	}
	cout<<"Psi_1="<<p<<endl;
    }

if(Psi_1.wf!=NULL){
cout<<"check Psi_1:"<<endl;
    for(int i=0;i<occupied_electrons;i++){
	int m=Psi_1.wf[i].m;
	double p=0.0;
	for(int j=0;j<index_basis[m].Tot;j++){
	    p=p+pow(Psi_1.wf[i].A_nl[j],2.0);
	}
	cout<<"Psi_1="<<p<<endl;
    }
}

if(Psi_1.wf!=NULL){
cout<<"check Psi_1:"<<endl;
    for(int i=0;i<occupied_electrons;i++){
	int m=Psi_1.wf[i].m;
	double p=0.0;
	for(int j=0;j<index_basis[m].Tot;j++){
	    p=p+pow(Psi_1.wf[i].A_nl[j],2.0);
	}
	cout<<"Psi_1="<<p<<endl;
    }
}

}
