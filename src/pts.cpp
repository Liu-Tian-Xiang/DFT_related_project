#include "../includes/global.h"
#include "../includes/prototype.h"

void chebpts(int n,double r[]){
    double pi=4*atan(1.0);
    if(n<=1) {cout<<"chebpts fail"<<endl;}
    else{
	int m=n-1;
	int o=0;
	for(int i=-m;i<=m;i+=2){
	    r[o]=sin(pi*i*0.5/m);
	    o=o+1;
	}
    }
}
void trigpts(int n,double th[],double coeffs){
    double pi=4*atan(1.0);
    if(n<=1) {cout<<"chebpts fail"<<endl;}
    else{
	double x[n+1];
	for(int i=0;i<=n;i++){
	    x[i]=2.0*i/(n)-1.0;
	}
	/*
	   for(int i=0;i<=n;i++){
	   x[i]=(x[i]-2.0*(n-i)/(n)+1.0)*0.5;
	   }
	 *///enforce symmetry
	for(int i=0;i<n;i++){
	    th[i]=coeffs*x[i];
	}
    }
}


