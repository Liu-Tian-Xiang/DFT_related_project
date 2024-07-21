#include "../includes/global.h"
#include "../includes/prototype.h"
void PoissonCylinder(double *F,double tol,int n1,int n2,int n3,double FF[]){
    //n1=n1;n2=n2;n3=3
//+++++++++++++++++++++++++++++++++++++++++
//Z//M//D_inv//T//////////////////////////     n3
//+++++++++++++++++++++++++++++++++++++++++
    double dsub[n3];
    double dsup[n3];
    double d[n3];
    double dd[3*n3];
    spMatrix M,M2,MD,Mr;
    for(int i=0;i<=n3-1;i++){
	dsub[i]=-1.0/(2.0*(i+3.0/2))*(i+1)*(i+2)*1.0/2/(1.0/2+i+2);
	dsup[i]=-1.0/(2.0*(i+3.0/2))*(i+1)*(i+2)*1.0/2/(1.0/2+i);
	d[i]=-dsub[i]-dsup[i];
    }
    int shift[3]={-2,0,2};
    for(int i=0;i<n3;i++){
	dd[i]=dsub[i];
	dd[i+n3]=d[i];
	dd[i+2*n3]=dsup[i];
    }
    M.Create_spMatrix2(dd,shift,3,n3);
    //M.Print_spMatrix();
    double *D_inv=(double *)calloc(n3*n3,sizeof(double));
    double *T=(double *)calloc(n3*n3,sizeof(double));
    for(int i=0;i<n3;i++){
	D_inv[i*n3+i]=-1.0/(i*(i+3)+2);
    }
    //print_matrix(n3,D_inv);
    for(int i=0;i<n3;i++){
	for(int j=0;j<n3;j++){
	    ////////////////////
	    for(int k=0;k<n3;k++){
		T[i*n3+j]+=D_inv[i*n3+k]*M.element(k,j);
	    }
	    ////////////////////
	}
    }
    double *I3=(double *)calloc(n3*n3,sizeof(double));
    for(int i=0;i<n3;i++){
	for(int j=0;j<n3;j++){
	    I3[i*n3+j]=0;
	}
	I3[i*n3+i]=1.0;
    }
    //print_matrix(n3,T);
//+++++++++++++++++++++++++++++++++++++++++
    //R/D_inv2///M2//I1//Mr2//Mr2_bak//Mr//A//A_2///     n1
//+++++++++++++++++++++++++++++++++++++++++
    double dd2[3*n1];
    for(int i=0;i<=n1-1;i++){
	dsub[i]=-1.0/(2.0*(i+3.0/2))*(i+1)*(i+2)*1.0/2/(1.0/2+i+2);
	dsup[i]=-1.0/(2.0*(i+3.0/2))*(i+1)*(i+2)*1.0/2/(1.0/2+i);
	d[i]=-dsub[i]-dsup[i];
    }
    int shift2[3]={-2,0,2};
    for(int i=0;i<n1;i++){
	dd2[i]=dsub[i];
	dd2[i+n1]=d[i];
	dd2[i+2*n1]=dsup[i];
    }
    M2.Create_spMatrix2(dd2,shift2,3,n1);
    //M2.Print_spMatrix();
    double *D_inv2=(double *)calloc(n1*n1,sizeof(double));
    for(int i=0;i<n1;i++){
	D_inv2[i*n1+i]=-1.0/(i*(i+3)+2);
    }
    //print_matrix(n1,D_inv2);
    double *I1=(double *)calloc(n1*n1,sizeof(double));
    for(int i=0;i<n1;i++){
	I1[i*n1+i]=1.0;
    }
    double *Mr2=(double *)calloc(n1*n1,sizeof(double));
    double *Mr2_bak=(double *)calloc(n1*n1,sizeof(double));
    for(int i=0;i<n1;i++){
	for(int j=0;j<n1;j++){
	    Mr2[i*n1+j]=I1[i*n1+j]-M.element(i,j);
	    Mr2_bak[i*n1+j]=Mr2[i*n1+j];
	}
    }
    //print_matrix(n1,Mr2);
    double vv[2*n1];
    for(int j=0;j<n1;j++){
	vv[j]=-1.0*j*(j+1.0)/(2.0*j+3.0);
	vv[j+n1]=(j+2.0)*(j+3.0)/(2.0*j+3.0);
    }
    int shift3[2]={-1,1};
    MD.Create_spMatrix2(vv,shift3,2,n1);
    //MD.Print_spMatrix();

    double vv2[2*n1];
    for(int j=0;j<n1;j++){
	vv2[j]=1.0*(j+1)/(2.0*j+3.0);
	vv2[j+n1]=(j+2.0)/(2.0*j+3.0);
    }
    Mr.Create_spMatrix2(vv2,shift3,2,n1);
    //Mr.Print_spMatrix();
    int info;
    double R[n1];
    int rank;
    info = LAPACKE_dgelss( LAPACK_COL_MAJOR, n1, n1,n1, D_inv2, n1, Mr2,n1,R,
	    tol, &rank );
    //print_matrix(n1,Mr2);
    double *A_2;
    A_2=(double *)calloc(n1*n1,sizeof(double));
    for(int i=0;i<n1;i++){
	for(int j=0;j<n1;j++){
	    A_2[i*n1+j]=0;
	    ////////////////////
	    for(int k=0;k<n1;k++){
		A_2[i*n1+j]+=5*Mr.element(i,k)*MD.element(k,j);
	    }
	    ////////////////////
	}
    }
    //print_matrix(n1,A_2);
    double *A;
    A=(double *)calloc(n1*n1,sizeof(double));
    for(int i=0;i<n1;i++){
	for(int j=0;j<n1;j++){
	    A[i*n1+j]=Mr2[i*n1+j]+A_2[i*n1+j]+14*M2.element(i,j)-10*I1[i*n1+j];
	}
    }
    //print_matrix(n1,A);
//+++++++++++++++++++++++++++++++++++++++++
    //Z*R//Fk//Xk////////////////////////////    loop 
    //Z//BB
    //R///M2
//+++++++++++++++++++++++++++++++++++++++++
    int Shift=floor((n2-1)*0.5)+1;

    for(int k=-Shift;k<=Shift;k++){
	int jjj=k+Shift;
	if(k!=0 & abs(k)!=1 & jjj<n2){
	    //cout<<"i="<<i<<endl;
	    double *Fk=(double *)calloc(n1*n3,sizeof(double));
	    for(int i=0;i<n1;i++){
		for(int l=0;l<n3;l++){
		    Fk[i*n3+l]=F[i*n2*n3+jjj*n3+l];
		}
	    }

	    double *Fk_temp;
	    Fk_temp=cheb2ultra(Fk,n1,n3);
	    for(int i=0;i<n1;i++){
		for(int j=0;j<n3;j++){
		    Fk[j*n1+i]=Fk_temp[i*n3+j];
		}
	    }
	    free(Fk_temp);
	    Fk_temp=cheb2ultra(Fk,n3,n1);
	    for(int i=0;i<n3;i++){
		for(int j=0;j<n1;j++){
		    Fk[j*n3+i]=Fk_temp[i*n1+j];
		}
	    }
	    free(Fk_temp);
	    ///////n3///////////////////////////////////////////////
	    double *BB=(double *)calloc(n3*n3,sizeof(double));
	    for(int i=0;i<n3;i++){
		for(int j=0;j<n3;j++){
		BB[i*n3+j]=-T[j*n3+i];
		}
	    }
	    for(int i=0;i<n3;i++){
		for(int j=i;j<n3;j++){
		    double temp=D_inv[i*n3+j];
		    D_inv[i*n3+j]=D_inv[j*n3+i];
		    D_inv[j*n3+i]=temp;
		}
	    }
	    ///////n1Xn3///////////////////////////////////////////////
	    Fk_temp=Multiply(Fk,n1,n3,D_inv,n3);
	    for(int i=0;i<n1*n3;i++){
		Fk[i]=Fk_temp[i];
	    }
	    free(Fk_temp);

	    //print_matrix(n3,Fk);
	    double a=-min(0.05,1.0/pow(k,2));
	    double b=(1.0*k<=0.5*n1?-(4e-4/pow(n1,2)):2.0/pow(k,2)/pow(n1,2));
	    double c=39*pow(n3,-4.0);
	    double d=4/pow(PI,2.0);
	    //cout<<"a="<<a<<"\tb="<<b<<"\tc="<<c<<"\td="<<d<<endl;
	    int size=ADIshifts(a,b,c,d,tol,NULL,NULL);
	    double p[size];
	    double q[size];
	    p[0]=1;
	    q[0]=1;
	    size=ADIshifts(a,b,c,d,tol,p,q);

	    /////n1/////////////////////////////////////////////////
	    double *A_Fk=(double *)calloc(n1*n1,sizeof(double));
	    double *A_Fkbak=(double *)calloc(n1*n1,sizeof(double));
	    for(int i=0;i<n1;i++){
		for(int j=0;j<n1;j++){
		    A_Fk[i*n1+j]=A[i*n1+j]-pow(k,2)*M2.element(i,j);
		}
	    }
	    for(int i=0;i<n1*n1;i++){
		A_Fkbak[i]=A_Fk[i];
	    }
	    int ipiv[n1];
	    info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR,n1,n1,A_Fk,n1,ipiv);
	    info = LAPACKE_dgetri(LAPACK_ROW_MAJOR,n1,A_Fk,n1,ipiv);
	    double MM[n1*n1];
	    Fk_temp=Multiply(Mr2_bak,n1,n1,&M2,n1);
	    for(int i=0;i<n1*n1;i++){
		MM[i]=Fk_temp[i];
	    }
	    free(Fk_temp);
	    //////////////////////////////////////////////////////
	    Fk_temp=Multiply(A_Fk,n1,n1,Fk,n3);
	    for(int i=0;i<n1*n3;i++){
		Fk[i]=Fk_temp[i];
	    }
	    free(Fk_temp);
	    double *Xk=(double *)calloc(n1*n3,sizeof(double));
	    //+++++++++++++++++++++++++++++++++++++++++
	    /////////////////core///loop/////////////////
	    //+++++++++++++++++++++++++++++++++++++++++
	    for(int s=0;s<size;s++){
		double *MMpA=(double*)calloc(n1*n1,sizeof(double));
		double *MMqA=(double*)calloc(n1*n1,sizeof(double));
		double *AMMpA=(double*)calloc(n1*n1,sizeof(double));
		double *BBpI=(double*)calloc(n3*n3,sizeof(double));
		double *BBqI=(double*)calloc(n3*n3,sizeof(double));
		for(int i=0;i<n1;i++){
		    for(int j=0;j<n1;j++){
			MMpA[i*n1+j]=MM[i*n1+j]-p[s]*A_Fkbak[i*n1+j];
			MMqA[i*n1+j]=MM[i*n1+j]-q[s]*A_Fkbak[i*n1+j];
		    }
		}
		for(int i=0;i<n3;i++){
		    for(int j=0;j<n3;j++){
			BBpI[i*n3+j]=BB[i*n3+j]-p[s]*I3[i*n3+j];
			BBqI[i*n3+j]=BB[i*n3+j]-q[s]*I3[i*n3+j];
		    }
		}
		Fk_temp=Multiply(A_Fk,n1,n1,MMpA,n1);
		for(int i=0;i<n1*n1;i++){
		    AMMpA[i]=Fk_temp[i];
		}
		free(Fk_temp);
		Fk_temp=Multiply(AMMpA,n1,n1,Xk,n3);
		for(int i=0;i<n1*n3;i++){
		    Xk[i]=Fk[i]-Fk_temp[i];
		}
		free(Fk_temp);
		info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR,n3,n3,BBpI,n3,ipiv);
		info = LAPACKE_dgetri(LAPACK_ROW_MAJOR,n3,BBpI,n3,ipiv);
		Fk_temp=Multiply(Xk,n1,n3,BBpI,n3);
		for(int i=0;i<n1*n3;i++){
		    Xk[i]=Fk_temp[i];
		}
		free(Fk_temp);
		/////////////////1/2////////////////////
		Fk_temp=Multiply(Xk,n1,n3,BBqI,n3);
		for(int i=0;i<n1*n3;i++){
		    Xk[i]=Fk[i]-Fk_temp[i];
		}
		free(Fk_temp);
		Fk_temp=Multiply(A_Fkbak,n1,n1,Xk,n3);
		for(int i=0;i<n1*n3;i++){
		    Xk[i]=Fk_temp[i];
		}
		free(Fk_temp);
		info = LAPACKE_dgetrf(LAPACK_ROW_MAJOR,n1,n1,MMqA,n1,ipiv);
		info = LAPACKE_dgetri(LAPACK_ROW_MAJOR,n1,MMqA,n1,ipiv);
		Fk_temp=Multiply(MMqA,n1,n1,Xk,n3);
		for(int i=0;i<n1*n3;i++){
		    Xk[i]=Fk_temp[i];
		}
		free(Fk_temp);
		free(MMpA);
		free(MMqA);
		free(AMMpA);
		free(BBpI);
		free(BBqI);
	    } 

	    free(A_Fkbak);
	    free(BB);
	    free(A_Fk);

	    double tXk[n1*n3];
	    for(int i=0;i<n1;i++){
		for(int j=0;j<n3;j++){
		    tXk[j*n1+i]=Xk[i*n3+j];
		}
	    }
	    for(int i=0;i<n1*n3;i++){
		Xk[i]=tXk[i];
	    }

	    ///////ult1mx2////////////////
	    double *Xk_temp;
	    Xk_temp=ultra1mx2cheb(Xk,n3,n1);
	    for(int i=0;i<n3;i++){
		for(int j=0;j<n1;j++){
		    Xk[j*n3+i]=Xk_temp[i*n1+j];
		}
	    }
	    free(Xk_temp);
	    Xk_temp=ultra1mx2cheb(Multiply(Mr2_bak,n1,n1,Xk,n3),n1,n3);

	    for(int i=0;i<n1*n3;i++){
		Xk[i]=Xk_temp[i];
	    }
	    free(Xk_temp);

	    for(int i=0;i<n1;i++){
		for(int l=0;l<n3;l++){
		    FF[i*n2*n3+jjj*n3+l]=Xk[i*n3+l];
		}
	    }
	    //////////////////////endl/////////////////////
	    free(Xk);
	    free(Fk);
	}
    }

   //////////////////////caseII////////////////////
   //////////////////////caseII////////////////////
   //////////////////////caseII////////////////////
   //////////////////////caseII////////////////////

    for(int i=0;i<n1;i++){
	D_inv2[i*n1+i]=-1.0/(i*(i+3)+2);
    }

    double *AMrD2;
    AMrD2=(double*)calloc(n1*n1,sizeof(double));
    for(int i=0;i<n1;i++){
	for(int j=0;j<n1;j++){
	    AMrD2[i*n1+j]=Mr.element(i,j);
	}
    }
    info = LAPACKE_dgelss(LAPACK_COL_MAJOR, n1, n1,n1, D_inv2, n1, AMrD2,n1,R,
	    tol, &rank);

    double *Acase2;
    Acase2=(double*)calloc(n1*n1,sizeof(double));
    for(int i=0;i<n1;i++){
	for(int j=0;j<n1;j++){
	    Acase2[i*n1+j]=AMrD2[i*n1+j]+3*MD.element(i,j)-6*Mr.element(i,j);
	}
    }

//////////////////////////////////
    for(int k=-1;k<=1;k+=2){
	int jjj=k+Shift;
	//double Fk[n3*n1];
	double *Fk;
	Fk=(double *)calloc(n3*n1,sizeof(double));
	double *Fk_temp;
	for(int i=0;i<n1;i++){
	    for(int l=0;l<n3;l++){
		Fk[i*n3+l]=F[i*n2*n3+jjj*n3+l];
	    }
	}
	Fk_temp=cheb2ultra(Fk,n1,n3);
	for(int i=0;i<n1;i++){
	    for(int j=0;j<n3;j++){
		Fk[j*n1+i]=Fk_temp[i*n3+j];
	    }
	}
	free(Fk_temp);
	Fk_temp=cheb2ultra(Fk,n3,n1);
	for(int i=0;i<n3;i++){
	    for(int j=0;j<n1;j++){
		Fk[j*n3+i]=Fk_temp[i*n1+j];
	    }
	}
	free(Fk_temp);

	for(int i=0;i<n3;i++){
	    for(int j=i;j<n3;j++){
		double temp=D_inv[i*n3+j];
		D_inv[i*n3+j]=D_inv[j*n3+i];
		D_inv[j*n3+i]=temp;
	    }
	}
	for(int i=0;i<n3;i++){
	    for(int j=0;j<n3;j++){
		////////////////////
		T[i*n3+j]=0;
		for(int kk=0;kk<n3;kk++){
		    T[i*n3+j]+=D_inv[i*n3+kk]*M.element(kk,j);
		}
	    }
	}

	//print_matrix(n3,D_inv);
	Fk_temp=Multiply(Fk,n1,n3,D_inv,n3);
	for(int i=0;i<n1*n3;i++){
	    Fk[i]=Fk_temp[i];
	}
	free(Fk_temp);
	//print_matrix(n3,Fk);
	double *MM2=(double *)calloc(n1*n1,sizeof(double));

	Fk_temp=Multiply(&Mr,n1,n1,&M2,n1);
	for(int i=0;i<n1*n1;i++){
	    MM2[i]=Fk_temp[i];
	}
	free(Fk_temp);
//+++++++++++++++++++++++++++++++++++++++++
/////bartel///////////////
//+++++++++++++++++++++++++++++++++++++++++
	MKL_Complex16 *Xk_temp;

	double *Xk=(double *)calloc(n3*n1,sizeof(double));

	MKL_Complex16 *I3c;
	MKL_Complex16 *MM2c;
	MKL_Complex16 *Acase2c;
	MKL_Complex16 *Tc;
	MKL_Complex16 *Fkc;
	/////Z
	I3c=(MKL_Complex16*)calloc(n3*n3,sizeof(MKL_Complex16));
	Tc=(MKL_Complex16*)calloc(n3*n3,sizeof(MKL_Complex16));
	/////R
	MM2c=(MKL_Complex16*)calloc(n1*n1,sizeof(MKL_Complex16));
	Acase2c=(MKL_Complex16*)calloc(n1*n1,sizeof(MKL_Complex16));
	////Z*R
	Fkc=(MKL_Complex16*)calloc(n1*n3,sizeof(MKL_Complex16));
	for(int i=0;i<n3;i++){
	    for(int j=0;j<n3;j++){
		I3c[i*n3+j].real=I3[i*n3+j];
		I3c[i*n3+j].imag=0.0;
		Tc[i*n3+j].real=T[i*n3+j];
		Tc[i*n3+j].imag=0.0;
	    }
	}
	for(int i=0;i<n1;i++){
	    for(int j=0;j<n1;j++){
		MM2c[i*n1+j].real=MM2[i*n1+j];
		MM2c[i*n1+j].imag=0.0;
		Acase2c[i*n1+j].real=Acase2[i*n1+j];
		Acase2c[i*n1+j].imag=0.0;
	    }
	}
	for(int i=0;i<n1;i++){
	    for(int j=0;j<n3;j++){
		Fkc[i*n3+j].real=Fk[i*n3+j];
		Fkc[i*n3+j].imag=0.0;
	    }
	}
	free(MM2);

	MKL_Complex16 *XX;
	XX=(MKL_Complex16*)calloc(n1*n3,sizeof(MKL_Complex16));
	//cout<<"crack"<<endl;
	BartelsStewart(MM2c,I3c,Acase2c,Tc,Fkc,0,0,n1,XX,n3);
	//print_matrix("Fk",n1,n3,Fkc,n3);//3333

	free(I3c);
	free(MM2c);
	free(Acase2c);
	free(Tc);
	free(Fkc);
	for(int i=0;i<n1;i++){
	    for(int j=0;j<n3;j++){
		Xk[j*n1+i]=XX[i*n3+j].real;
	    }
	}
	free(XX);
	double *Xkk_temp;
	Xkk_temp=ultra1mx2cheb(Xk,n3,n1);
	for(int i=0;i<n3;i++){
	    for(int j=0;j<n1;j++){
		Xk[j*n3+i]=Xkk_temp[i*n1+j];
	    }
	}
	free(Xkk_temp);
	Xkk_temp=ultra1mx2cheb(Multiply(&Mr,n1,n1,Xk,n3),n1,n3);
	for(int i=0;i<n3*n1;i++){
	    Xk[i]=Xkk_temp[i];
	}
	free(Xkk_temp);
	for(int i=0;i<n1;i++){
	    for(int l=0;l<n3;l++){
		FF[i*n2*n3+jjj*n3+l]=Xk[i*n3+l];
	    }
	}

	free(Fk);
	free(Xk);
    }
////////////////////
    free(AMrD2);
    free(Acase2);

    //////////////////////caseIII////////////////////
    //////////////////////caseIII////////////////////
    //////////////////////caseIII////////////////////
    //////////////////////caseIII////////////////////


    //double A3[n3*n1];
    double *A3;
    A3=(double *)calloc(n1*n1,sizeof(double));

    for(int i=0;i<n1;i++){
	D_inv2[i*n1+i]=-1.0/(i*(i+3)+2);
    }

    double A31[n1*n1];
    for(int i=0;i<n1*n1;i++){
	    A31[i]=Mr2_bak[i];
    }
    info = LAPACKE_dgelss(LAPACK_COL_MAJOR, n1, n1,n1, D_inv2, n1, A31,n1,R,
	    tol, &rank);
    double *A32;
    A32=Multiply(&Mr,n1,n1,&MD,n1);
    for(int i=0;i<n1*n1;i++){
	    A3[i]=A31[i]+A32[i]-2*Mr2_bak[i];
    }
    free(A32);
    //print_rmatrix("A3",n1,n3,A3,n3);
    /////////////////////////k=0////////////////
    double Fk[n1*n3];
    for(int i=0;i<n1;i++){
	for(int l=0;l<n3;l++){
	    Fk[i*n3+l]=F[i*n2*n3+Shift*n3+l];
	}
    }

    double *Fk_temp;

    Fk_temp=cheb2ultra(Fk,n1,n3);
    for(int i=0;i<n1;i++){
	for(int j=0;j<n3;j++){
	    Fk[j*n1+i]=Fk_temp[i*n3+j];
	}
    }
    free(Fk_temp);
    Fk_temp=cheb2ultra(Fk,n3,n1);
    for(int i=0;i<n3;i++){
	for(int j=0;j<n1;j++){
	    Fk[j*n3+i]=Fk_temp[i*n1+j];
	}
    }
    free(Fk_temp);

    for(int i=0;i<n3;i++){
	for(int j=i;j<n3;j++){
	    double temp=D_inv[i*n3+j];
	    D_inv[i*n3+j]=D_inv[j*n3+i];
	    D_inv[j*n3+i]=temp;
	}
    }

    for(int i=0;i<n3;i++){
	for(int j=0;j<n3;j++){
	    ////////////////////
	    T[i*n3+j]=0;
	    for(int k=0;k<n3;k++){
		T[i*n3+j]+=D_inv[i*n3+k]*M.element(k,j);
	    }
	}
    }

    //print_matrix(n3,D_inv);
    Fk_temp=Multiply(Fk,n1,n3,D_inv,n3);
    for(int i=0;i<n1*n3;i++){
	Fk[i]=Fk_temp[i];
    }
    free(Fk_temp);

    //double MM22[n3*n1];
    double *MM22;
    MM22=(double *)calloc(n1*n1,sizeof(double));
    Fk_temp=Multiply(Mr2_bak,n1,n1,&M2,n1);
    for(int i=0;i<n1*n1;i++){
	MM22[i]=Fk_temp[i];
    }
    free(Fk_temp);

    MKL_Complex16 *Xk_temp;
    double *Xk;
    Xk=(double *)calloc(n1*n3,sizeof(double));

    MKL_Complex16 *I3c;
    MKL_Complex16 *MM2c;
    MKL_Complex16 *A3c;
    MKL_Complex16 *Tc;
    MKL_Complex16 *Fkc;
    I3c=(MKL_Complex16*)calloc(n3*n3,sizeof(MKL_Complex16));
    Tc=(MKL_Complex16*)calloc(n3*n3,sizeof(MKL_Complex16));

    MM2c=(MKL_Complex16*)calloc(n1*n1,sizeof(MKL_Complex16));
    A3c=(MKL_Complex16*)calloc(n1*n1,sizeof(MKL_Complex16));

    Fkc=(MKL_Complex16*)calloc(n1*n3,sizeof(MKL_Complex16));
    double *MFK=Multiply(Mr2_bak,n1,n1,Fk,n3);
    for(int i=0;i<n3;i++){
	for(int j=0;j<n3;j++){
	    I3c[i*n3+j].real=I3[i*n3+j];
	    I3c[i*n3+j].imag=0.0;
	    Tc[i*n3+j].real=T[i*n3+j];
	    Tc[i*n3+j].imag=0.0;
	}
    }
    for(int i=0;i<n1;i++){
	for(int j=0;j<n1;j++){
	    MM2c[i*n1+j].real=MM22[i*n1+j];
	    MM2c[i*n1+j].imag=0.0;
	    A3c[i*n1+j].real=A3[i*n1+j];
	    A3c[i*n1+j].imag=0.0;
	}
    }
    for(int i=0;i<n1;i++){
	for(int j=0;j<n3;j++){
	    Fkc[i*n3+j].real=MFK[i*n3+j];
	    Fkc[i*n3+j].imag=0.0;
	}
    }

    free(MM22);
    free(A3);
    free(MFK);
    MKL_Complex16 *XX;
    XX=(MKL_Complex16*)calloc(n1*n3,sizeof(MKL_Complex16));
    BartelsStewart(MM2c,I3c,A3c,Tc,Fkc,0,0,n1,XX,n3);
    //print_matrix("XX",n1,n3,XX,n3);///3333

    free(I3c);
    free(MM2c);
    free(A3c);
    free(Tc);
    free(Fkc);

    for(int i=0;i<n1;i++){
	for(int j=0;j<n3;j++){
	    Xk[j*n1+i]=XX[i*n3+j].real;
	}
    }

    double *Xkk_temp;
    Xkk_temp=ultra1mx2cheb(Xk,n3,n1);
    for(int i=0;i<n3;i++){
	for(int j=0;j<n1;j++){
	    Xk[j*n3+i]=Xkk_temp[i*n1+j];
	}
    }
    free(Xkk_temp);
    Xkk_temp=ultra1mx2cheb(Xk,n1,n3);
    for(int i=0;i<n3*n1;i++){
	Xk[i]=Xkk_temp[i];
    }
    free(Xkk_temp);

    for(int i=0;i<n1;i++){
	for(int l=0;l<n3;l++){
	    FF[i*n2*n3+Shift*n3+l]=Xk[i*n3+l];
	}
    }


    free(Xk);
    free(XX);
    //////////////////
    free(A_2);
    free(A);
    free(I3);
    free(I1);
    free(D_inv);
    free(T);
    free(D_inv2);
    free(Mr2);
    free(Mr2_bak);

}


