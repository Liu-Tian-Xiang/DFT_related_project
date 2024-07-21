
#include "../includes/global.h"
#include "../includes/prototype.h"
void Arrange_Psi(){
    Wave_function::_wave temp;
    for(int i=0;i<occupied_electrons;i++){
        for(int j=0;j<occupied_electrons-i-1;j++){
            if(Psi_1.wf[j].eig>Psi_1.wf[j+1].eig){
                temp=Psi_1.wf[j];Psi_1.wf[j]=Psi_1.wf[j+1];Psi_1.wf[j+1]=temp;
            }
        }
    }
}
