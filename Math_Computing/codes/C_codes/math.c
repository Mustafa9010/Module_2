#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libs/matfun.h"


int  main()
{

FILE *fp; //file pointer
double **A,**B,**D,**e1;//declaring matrices names
int m = 3, n = 4;
double **vert;

// creating Matrix MAT and loading MATRIX from file
vert = createMat(m,n);
vert = loadMat("Mat.dat",m,n);

//Extracting vertices
A = Matcol(vert,m,0);
B = Matcol(vert,m,1);
D = Matcol(vert,m,2);
e1 = Matcol(vert,m,3);

double **n1, **n2, **n3, **n4, **d1, **d2, **d3, **num, **den;
n1 = Matmul(transposeMat(B,m,1),B,1,m,1);
n2 = Matmul(transposeMat(B,m,1),D,1,m,1);
n3 = Matmul(transposeMat(D,m,1),D,1,m,1);
n4 = Matmul(transposeMat(A,m,1),Matadd(B,D,3,1),1,m,1);
d1 = Matmul(transposeMat(A,m,1),e1,1,m,1);
d2 = Matmul(transposeMat(B,m,1),e1,1,m,1);
d3 = Matmul(transposeMat(e1,m,1),D,1,m,1);
num = Matadd(Matsub(Matadd(n1,n3,1,1),Matmul(n4,n4,1,1,1),1,1),Matscale(n2,1,1,2),1,1);
den = Matscale(Matsub(Matsub(Matmul(d1,n4,1,1,1),d2,1,1),d3,1,1),1,1,2);
double lambda = Matdiv(num,den);
printf("lambda = %lf \n",lambda);
return 0;
}
