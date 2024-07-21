#include "../includes/global.h"
#include "../includes/prototype.h"

extern lapack_logical select(const lapack_complex_double *a, const lapack_complex_double *b);
extern lapack_logical cselect(const lapack_complex_float *a, const lapack_complex_float *b);
extern lapack_logical dselect(const double *a, const double *b,const double *c);

void BartelsStewart(lapack_complex_double *A,lapack_complex_double *B,lapack_complex_double *C,lapack_complex_double *D,lapack_complex_double *E,bool xsplit,bool ysplit,int n1,MKL_Complex16 XX[],int n3){
    /*
       int id,numprocs;
       MPI_Comm_rank(MPI_COMM_WORLD,&id);
       MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
     */

    double tol=1e-1;
    int info;

    char Method='z';

    int rldvsl=n1;
    int rldvsr=n1;
    int rsdim[n1];

    int zldvsl=n3;
    int zldvsr=n3;
    int zsdim[n3];
    lapack_complex_double ralpha[n1];
    lapack_complex_double rbeta[n1];
    lapack_complex_double zalpha[n3];
    lapack_complex_double zbeta[n3];

    MKL_Complex16 *Q1=(MKL_Complex16*)calloc(n1*n1,sizeof(MKL_Complex16));
    MKL_Complex16 *Z1=(MKL_Complex16*)calloc(n1*n1,sizeof(MKL_Complex16));

    MKL_Complex16 *Q2=(MKL_Complex16*)calloc(n3*n3,sizeof(MKL_Complex16));
    MKL_Complex16 *Z2=(MKL_Complex16*)calloc(n3*n3,sizeof(MKL_Complex16));

    //    int ldvsl=n1;
    //    int ldvsr=n1;
    //    int sdim[n1];
    //    lapack_complex_double alpha[n1];
    //    lapack_complex_double beta[n1];

    /*
       if(Method=='d'){
    ///////////real condition....
    double dalphai[n1];
    double dalphar[n1];
    double dbeta[n1];
    double dQ1[n1*n1];
    double dQ2[n1*n1];
    double dZ1[n1*n1];
    double dZ2[n1*n1];
    double dA[n1*n1];
    double dB[n1*n1];
    double dC[n1*n1];
    double dD[n1*n1];
    for(int i=0;i<n1*n1;i++){
    dQ1[i]=0;
    dQ2[i]=0;
    dZ1[i]=0;
    dZ2[i]=0;
    dA[i]=A[i].real;
    dB[i]=B[i].real;
    dC[i]=C[i].real;
    dD[i]=D[i].real;
    }

    //	   double work[1000000];
    //	   int lwork=1000000;
    //	   lapack_logical bwork=0;

    for(int i=0;i<n1;i++){dalphai[i]=0;dalphar[i]=1;}
    for(int i=0;i<n1;i++){dbeta[i]=1;}
    info=LAPACKE_dgges(LAPACK_ROW_MAJOR,'V','V','S',dselect,n1,dA,n1,dC,n1,sdim,dalphar,dalphai,dbeta,dQ1,ldvsl,dZ1,ldvsr);
    //dgges("V","V","S",ddselect,&n1,dA,&n1,dC,&n1,sdim,dalphar,dalphai,dbeta,dQ1,&ldvsl,dZ1,&ldvsr,work,&lwork,&bwork,&info);
    for(int i=0;i<n1;i++){dalphai[i]=0;dalphar[i]=1;}
    for(int i=0;i<n1;i++){dbeta[i]=1;}
    info=LAPACKE_dgges(LAPACK_ROW_MAJOR,'V','V','S',dselect,n1,dD,n1,dB,n1,sdim,dalphar,dalphai,dbeta,dQ2,ldvsl,dZ2,ldvsr);
    //dgges("V","V","S",ddselect,&n1,dD,&n1,dB,&n1,sdim,dalphar,dalphai,dbeta,dQ2,&ldvsl,dZ2,&ldvsr,work,&lwork,&bwork,&info);
    for(int i=0;i<n1*n1;i++){

    A[i].real=dA[i];
    A[i].imag=0;
    B[i].real=dB[i];
    B[i].imag=0;
    C[i].real=dC[i];
    C[i].imag=0;
    D[i].real=dD[i];
    D[i].imag=0;

    Q1[i].real=dQ1[i];
    Q1[i].imag=0;
    Q2[i].real=dQ2[i];
    Q2[i].imag=0;
    Z1[i].real=dZ1[i];
    Z1[i].imag=0;
    Z2[i].real=dZ2[i];
    Z2[i].imag=0;

    }
    }

    if(Method=='c'){
    lapack_complex_float cA[n1*n1];
    lapack_complex_float cB[n1*n1];
    lapack_complex_float cC[n1*n1];
    lapack_complex_float cD[n1*n1];

    for(int i=0;i<n1*n1;i++){

    cA[i].real=A[i].real;
    cB[i].real=B[i].real;
    cC[i].real=C[i].real;
    cD[i].real=D[i].real;

    cA[i].imag=A[i].imag;
    cB[i].imag=B[i].imag;
    cC[i].imag=C[i].imag;
    cD[i].imag=D[i].imag;

}

lapack_complex_float calpha[n1];
lapack_complex_float cbeta[n1];
lapack_complex_float cQ1[n1*n1];
lapack_complex_float cQ2[n1*n1];
lapack_complex_float cZ1[n1*n1];
lapack_complex_float cZ2[n1*n1];


///////complex condition....
for(int i=0;i<n1;i++){calpha[i]={1,0};}
for(int i=0;i<n1;i++){cbeta[i]={1,0};}
info=LAPACKE_cgges(LAPACK_ROW_MAJOR,'V','V','S',cselect,n1,cA,n1,cC,n1,sdim,calpha,cbeta,cQ1,ldvsl,cZ1,ldvsr);
for(int i=0;i<n1;i++){calpha[i]={1,0};}
for(int i=0;i<n1;i++){cbeta[i]={1,0};}
info=LAPACKE_cgges(LAPACK_ROW_MAJOR,'V','V','S',cselect,n1,cD,n1,cB,n1,sdim,calpha,cbeta,cQ2,ldvsl,cZ2,ldvsr);
for(int i=0;i<n1*n1;i++){

    A[i].real=cA[i].real;
    B[i].real=cB[i].real;
    C[i].real=cC[i].real;
    D[i].real=cD[i].real;

    A[i].imag=cA[i].imag;
    B[i].imag=cB[i].imag;
    C[i].imag=cC[i].imag;
    D[i].imag=cD[i].imag;


    Q1[i].real=cQ1[i].real;
    Q2[i].real=cQ2[i].real;
    Z1[i].real=cZ1[i].real;
    Z2[i].real=cZ2[i].real;

    Q1[i].imag=cQ1[i].imag;
    Q2[i].imag=cQ2[i].imag;
    Z1[i].imag=cZ1[i].imag;
    Z2[i].imag=cZ2[i].imag;

}
///A=P;C=S;
///D=T;B=R;
//triu();
}
*/

if(Method=='z'){
    ///////complex condition....
    info=LAPACKE_zgges(LAPACK_ROW_MAJOR,'V','V','S',select,n1,A,n1,C,n1,rsdim,ralpha,rbeta,Q1,rldvsl,Z1,rldvsr);

    info=LAPACKE_zgges(LAPACK_ROW_MAJOR,'V','V','S',select,n3,D,n3,B,n3,zsdim,zalpha,zbeta,Q2,zldvsl,Z2,zldvsr);
    ///A=P;C=S;
    ///D=T;B=R;
    //triu();
}

for(int i=0;i<n1;i++){
    for(int j=i+1;j<n1;j++){
	C[j*n1+i]={0,0};
    }
}
for(int i=0;i<n1;i++){
    for(int j=i+1;j<n1;j++){
	A[j*n1+i]={0,0};
    }
}

for(int i=0;i<n1*n1;i++){
    Q1[i].imag=-Q1[i].imag;
}


for(int i=0;i<n3*n3;i++){
    Q2[i].imag=-Q2[i].imag;
}

/*
   print_matrix( "P", n1, n1, A, n1 );
   print_matrix( "S", n1, n1, C, n1 );
   print_matrix( "Q1", n1, n1, Q1, n1 );
   print_matrix( "Z1", n1, n1, Z1, n1 );
   print_matrix( "T", n1, n1, D, n1 );
   print_matrix( "R", n1, n1, B, n1 );
   print_matrix( "Q2", n1, n1, Q2, n1 );
   print_matrix( "Z2", n1, n1, Z2, n1 );
 */    
lapack_complex_double F_temp[n1*n3];
lapack_complex_double F[n1*n3];

MKL_Complex16 One={1,0};
MKL_Complex16 Zero={0,0};
MKL_Complex16 Mone={-1,0};

//if(id==0) print_matrix( "Q1", n1, n1, Q1, n1 );
//if(id==0) print_matrix( "F", n1, n3, E, n3 );
cblas_zgemm(CblasRowMajor, CblasTrans, CblasNoTrans, n1, n3, n1, &One, Q1, n1, E, n3, &Zero, F_temp, n3);
//if(id==0) print_matrix( "Ft", n1, n3, F_temp, n3 );
cblas_zgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n1, n3, n3, &One, F_temp, n3, Q2, n3, &Zero, F, n3);

//multiply(Q1,E,F_temp,n1,n3);
//multiply(F_temp,Q2,F,n1,n3);

//print_matrix( "F", n1, n1, F, n1 );

lapack_complex_double Y[n1*n3];
for(int i=0;i<n1*n3;i++){Y[i]={0,0};}

lapack_complex_double M[n1*n1];
lapack_complex_double PY[n1*n3];
lapack_complex_double SY[n1*n3];
lapack_complex_double cPY[n1*n3];
lapack_complex_double cSY[n1*n3];

for(int i=0;i<n1*n1;i++){M[i]={0,0};}
for(int i=0;i<n1*n3;i++){PY[i]={0,0};}
for(int i=0;i<n1*n3;i++){SY[i]={0,0};}
for(int i=0;i<n1*n3;i++){cPY[i]={0,0};}
for(int i=0;i<n1*n3;i++){cSY[i]={0,0};}



lapack_complex_double rhs[n1];
for(int i=0;i<n1;i++){rhs[i]={0,0};}
int k=n3;

while(k>1){
    double check=sqrt(pow(D[(k-1)*n3+k-2].real,2)+pow(D[(k-1)*n3+k-2].imag,2));

    if(check==0){

	for(int i=0;i<n1;i++){
	    rhs[i]=F[i*n3+k-1];//rhs=F(:,K)
	}
	if(k<n3){
	    //multiply(A,Y,cPY,n1,n3);
	    //multiply(C,Y,cSY,n1,n3);
	    cblas_zgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n1, n3, n1, &One, A, n1, Y, n3, &Zero, cPY, n3);
	    cblas_zgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n1, n3, n1, &One, C, n1, Y, n3, &Zero, cSY, n3);

	    for(int i=0;i<n1;i++){
		PY[i*n3+k]=cPY[i*n3+k];
		SY[i*n3+k]=cSY[i*n3+k];
	    }//rhs=F(:,K)
	    for(int jj=k+1;jj<=n3;jj++){
		for(int i=0;i<n1;i++){
		    MKL_Complex16 Res={0,0};
		    cblas_zaxpy(1,&B[(k-1)*n3+jj-1],&PY[i*n3+jj-1],1,&Res,1);
		    cblas_zaxpy(1,&D[(k-1)*n3+jj-1],&SY[i*n3+jj-1],1,&Res,1);
		    cblas_zaxpy(1,&Mone,&Res,1,&rhs[i],1);
		}
	    }
	}
	for(int i=0;i<n1;i++){
	    for(int j=0;j<n1;j++){
		MKL_Complex16 Res={0,0};
		cblas_zaxpy(1,&B[(k-1)*n3+k-1],&A[i*n1+j],1,&Res,1);
		cblas_zaxpy(1,&D[(k-1)*n3+k-1],&C[i*n1+j],1,&Res,1);
		M[i*n1+j]=Res;
	    }
	}
	int ipiv[n1];
	info = LAPACKE_zgetrf(LAPACK_ROW_MAJOR,n1,n1,M,n1,ipiv);
	info = LAPACKE_zgetri(LAPACK_ROW_MAJOR,n1,M,n1,ipiv);
	lapack_complex_double YRes[n1];
	for(int i=0;i<n1;i++){YRes[i]={0,0};}
	cblas_zgemv(CblasRowMajor,CblasNoTrans,n1,n1,&One,M,n1,rhs,1,&Zero,YRes,1);
	for(int j=0;j<n1;j++){
	    Y[j*n3+k-1]=YRes[j];
	}

	k=k-1;    

    }else{

	lapack_complex_double rhs1[n1];
	lapack_complex_double rhs2[n1];
	for(int i=0;i<n1;i++){
	    rhs1[i]=F[i*n3+k-2];
	    rhs2[i]=F[i*n3+k-1];
	}
	//cout<<endl;
	//for(int i=0;i<n1;i++){
	//	printf("rhs1[%d]=(%6.6f,%6.6f)\n",i, rhs1[i].real, rhs1[i].imag);
	//   }cout<<endl;
	//  for(int i=0;i<n1;i++){
	//	printf("rhs2[%d]=(%6.6f,%6.6f)\n",i, rhs2[i].real, rhs2[i].imag);
	///   }

	lapack_complex_double yj[n1];
	for(int jj=k+1;jj<=n3;jj++){
	    for(int i=0;i<n1;i++){
		yj[i]=Y[i*n3+jj-1];
	    }

	    lapack_complex_double rhs1Res[n1];
	    for(int i=0;i<n1;i++){rhs1Res[i]={0,0};}
	    lapack_complex_double rhs2Res[n1];
	    for(int i=0;i<n1;i++){rhs2Res[i]={0,0};}
	    lapack_complex_double Eye[n1*n1];
	    for(int i=0;i<n1*n1;i++){Eye[i]={0,0};}
	    for(int i=0;i<n1;i++){Eye[i*n1+i]={1,0};}
	    cblas_zgemv(CblasRowMajor,CblasNoTrans,n1,n1,&B[(k-2)*n3+jj-1],A,n1,yj,1,&Zero,rhs1Res,1);
	    cblas_zgemv(CblasRowMajor,CblasNoTrans,n1,n1,&D[(k-2)*n3+jj-1],C,n1,yj,1,&One,rhs1Res,1);
	    cblas_zgemv(CblasRowMajor,CblasNoTrans,n1,n1,&Mone,Eye,n1,rhs1Res,1,&One,rhs1,1);
	    ///
	    cblas_zgemv(CblasRowMajor,CblasNoTrans,n1,n1,&B[(k-1)*n3+jj-1],A,n1,yj,1,&Zero,rhs2Res,1);
	    cblas_zgemv(CblasRowMajor,CblasNoTrans,n1,n1,&D[(k-1)*n3+jj-1],C,n1,yj,1,&One,rhs2Res,1);
	    cblas_zgemv(CblasRowMajor,CblasNoTrans,n1,n1,&Mone,Eye,n1,rhs2Res,1,&One,rhs2,1);
	}
	lapack_complex_double SMuu[n1*n1];
	lapack_complex_double SMud[n1*n1];
	lapack_complex_double SMdu[n1*n1];
	lapack_complex_double SMdd[n1*n1];

	for(int i=0;i<n1;i++){
	    for(int j=0;j<n1;j++){
		MKL_Complex16 Res={0,0};
		cblas_zaxpy(1,&B[(k-2)*n3+k-2],&A[i*n1+j],1,&Res,1);
		cblas_zaxpy(1,&D[(k-2)*n3+k-2],&C[i*n1+j],1,&Res,1);
		SMuu[i*n1+j]=Res;

		Res={0,0};
		cblas_zaxpy(1,&B[(k-2)*n3+k-1],&A[i*n1+j],1,&Res,1);
		cblas_zaxpy(1,&D[(k-2)*n3+k-1],&C[i*n1+j],1,&Res,1);
		//SMud[i*n1+j]=Res;
		SMdu[i*n1+j]=Res;

		Res={0,0};
		cblas_zaxpy(1,&B[(k-1)*n3+k-2],&A[i*n1+j],1,&Res,1);
		cblas_zaxpy(1,&D[(k-1)*n3+k-2],&C[i*n1+j],1,&Res,1);
		//SMdu[i*n1+j]=Res;
		SMud[i*n1+j]=Res;

		Res={0,0};
		cblas_zaxpy(1,&B[(k-1)*n3+k-1],&A[i*n1+j],1,&Res,1);
		cblas_zaxpy(1,&D[(k-1)*n3+k-1],&C[i*n1+j],1,&Res,1);
		SMdd[i*n1+j]=Res;
	    }
	}

	//    print_matrix( "SMuu", n1, n1, SMuu, n1 );
	//    print_matrix( "SMud", n1, n1, SMud, n1 );
	//    print_matrix( "SMdu", n1, n1, SMdu, n1 );
	//    print_matrix( "SMdd", n1, n1, SMdd, n1 );

	lapack_complex_double Spermuted[4*n1*n1];
	for(int i=0;i<4*n1*n1;i++){Spermuted[i]={0,0};}
	for(int i=0;i<2*n1;i+=2){
	    for(int j=0;j<2*n1;j+=2){
		Spermuted[i*n1*2+j]=SMuu[(i/2)*n1+j/2];
		Spermuted[(i+1)*n1*2+j+1]=SMdd[(i/2)*n1+j/2];
	    }
	}
	//	    print_matrix( "Sper", 2*n1, 2*n1, Spermuted, 2*n1 );

	lapack_complex_double rhs12[2*n1];
	for(int i=0;i<n1*2;i++){rhs12[i]={0,0};}
	for(int i=0;i<n1;i++){
	    rhs12[i]=rhs1[i];
	    rhs12[i+n1]=rhs2[i];
	}
	int ipiv2[2*n1];
	info = LAPACKE_zgesv( LAPACK_ROW_MAJOR, 2*n1, 1, Spermuted, 2*n1, ipiv2,rhs12 , 1 );
	for(int j=0;j<n1;j++){
	    Y[j*n3+k-2]=rhs12[j];
	    Y[j*n3+k-1]=rhs12[j+n1];
	}
	//	    print_matrix( "Y", n1, n1, Y, n1 );

	//multiply(A,Y,cPY,n1,n3);
	//multiply(C,Y,cSY,n1,n3);
	cblas_zgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n1, n3, n1, &One, A, n1, Y, n3, &Zero, cPY, n3);
	cblas_zgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n1, n3, n1, &One, C, n1, Y, n3, &Zero, cSY, n3);
	for(int i=0;i<n1;i++){
	    //for(int j=0;j<n1;j++){
	    //if(j==k-1 | j==k-2){
	    PY[i*n3+k-1]=cPY[i*n3+k-1];
	    SY[i*n3+k-1]=cSY[i*n3+k-1];

	    PY[i*n3+k-2]=cPY[i*n3+k-2];
	    SY[i*n3+k-2]=cSY[i*n3+k-2];
	    //}
	    //}
	}//rhs=F(:,K)
	//print_matrix( "PY", n1, n1, PY, n1 );
	//print_matrix( "SY", n1, n1, SY, n1 );
	k=k-2;    

    }

    //getchar();
}

//////////k==1///////////////////////////////////////////////////////////////// 

if(k==1){
    for(int i=0;i<n1;i++){
	rhs[i]=F[i*n3];
	//    printf( " rhs[%d]=(%6.6f,%6.6f)\n",i, rhs[i].real, rhs[i].imag );
    }
    //multiply(A,Y,cPY,n1,n3);
    //multiply(C,Y,cSY,n1,n3);
    cblas_zgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n1, n3, n1, &One, A, n1, Y, n3, &Zero, cPY, n3);
    cblas_zgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n1, n3, n1, &One, C, n1, Y, n3, &Zero, cSY, n3);
    for(int i=0;i<n1;i++){
	PY[i*n3+1]=cPY[i*n3+1];
	SY[i*n3+1]=cSY[i*n3+1];
    }//rhs=F(:,K)
    //	print_matrix( "PY", n1, n1, PY, n1 );
    //	print_matrix( "SY", n1, n1, SY, n1 );

    ///////////////////////
    for(int jj=2;jj<=n3;jj++){
	for(int i=0;i<n1;i++){
	    MKL_Complex16 Res={0,0};
	    cblas_zaxpy(1,&B[jj-1],&PY[i*n3+jj-1],1,&Res,1);
	    cblas_zaxpy(1,&D[jj-1],&SY[i*n3+jj-1],1,&Res,1);
	    //printf( "Res[%d]=(%6.6f,%6.6f)\n",i, Res.real, Res.imag );
	    cblas_zaxpy(1,&Mone,&Res,1,&rhs[i],1);
	}
	//	    printf( "\n");
    }
    for(int i=0;i<n1;i++){
	for(int j=0;j<n1;j++){
	    MKL_Complex16 Res={0,0};
	    cblas_zaxpy(1,&B[0],&A[i*n1+j],1,&Res,1);
	    cblas_zaxpy(1,&D[0],&C[i*n1+j],1,&Res,1);
	    M[i*n1+j]=Res;
	}
    }
    int ipiv[n1];
    info = LAPACKE_zgetrf(LAPACK_ROW_MAJOR,n1,n1,M,n1,ipiv);
    info = LAPACKE_zgetri(LAPACK_ROW_MAJOR,n1,M,n1,ipiv);
    lapack_complex_double YRes[n1];
    for(int i=0;i<n1;i++){YRes[i]={0,0};}
    cblas_zgemv(CblasRowMajor,CblasNoTrans,n1,n1,&One,M,n1,rhs,1,&Zero,YRes,1);
    for(int j=0;j<n1;j++){
	Y[j*n3]=YRes[j];
    }

}
/////////////////////////////////////////////////////////////////////////// 

lapack_complex_double X_temp[n1*n3];

//multiply(Z1,Y,X_temp,n1,n3);
//multiply(X_temp,Z2,XX,n1,n3);
cblas_zgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n1, n3, n1, &One, Z1, n1, Y, n3, &Zero, X_temp, n3);
cblas_zgemm(CblasRowMajor, CblasNoTrans, CblasTrans, n1, n3, n3, &One, X_temp, n3, Z2, n3, &Zero, XX, n3);
//    print_matrix( "X", n1, n1, X, n1 );

free(Q1);
free(Z1);
free(Q2);
free(Z2);
}

lapack_logical select(const lapack_complex_double *a, const lapack_complex_double *b){
    //lapack_complex_double num={6.0};
    return (a<b);
}

lapack_logical cselect(const lapack_complex_float *a, const lapack_complex_float *b){
    //lapack_complex_double num={6.0};
    return (a<b);
}


lapack_logical dselect(const double *a, const double *b,const double *c){
    //lapack_complex_double num={6.0};
    return 1;
}




