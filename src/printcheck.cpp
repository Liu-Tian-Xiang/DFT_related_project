
#include "../includes/global.h"
#include "../includes/prototype.h"

void Wave_function::printcheck(char name){
if(name=='v'){
    cout<<"name==vxc----"<<endl;
    int o=0;
    for(int n=1;n<=coulomb_expand_b_n;n++){
	for(int l=-coulomb_expand_b_l;l<=coulomb_expand_b_l;l++){
	    printf("checkVXC[%d][%d]=%1.4f\t%1.4f\n",n,l,Re_vxc_[o],Im_vxc_[o]);
	    //printf("checkB[%d][%d]=%1.4f\t%1.4f\n",n,l,Re_b_[o],Im_b_[o]);
	    o=o+1; 
	}
    }
}

if(name=='b'){
    cout<<"name==b----"<<endl;
    int o=0;
    for(int n=1;n<=coulomb_expand_b_n;n++){
	for(int l=-coulomb_expand_b_l;l<=coulomb_expand_b_l;l++){
	    //printf("checkVXC[%d][%d]=%1.4f\t%1.4f\n",n,l,Re_vxc_[o],Im_vxc_[o]);
	    printf("checkB[%d][%d]=%1.4f\t%1.4f\n",n,l,Re_b_[o],Im_b_[o]);
	    o=o+1; 
	}
    }
}


}
