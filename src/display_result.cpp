
#include "../includes/global.h"
#include "../includes/prototype.h"
void display_result(int i,double delta){

    ///--3D--//
    //surfdensity(i,"rho",&Psi_1);
    //surf(i,"V",&Coulomb_potential);
    //InterpSurf(i,"Fst",&FstPoisson);
    //InterpSurf(i,"cy",&cylinder);
    //InterpSurf(i,"vxc",&spline_vxc);

    ///--2D--//
    //surfdensity2D(i,"rho",&Psi_1);
    //surf2D(i,"V",&Coulomb_potential);
    //InterpSurf2D(i,"Fst",&FstPoisson);
    //InterpSurf2D(i,"cy",&cylinder);
    //InterpSurf2D(i,"vxc",&spline_vxc);
    //InterpSurf2D(i,"vxc",&Rho);

    ///--1D--//
    //surfdensity1D(i,"rho",&Psi_1);


    //display_rho(i);
    display_Coulomb_potential(i);
    if(print_mode) printf("DisplayResult_%d\n",i);
}
