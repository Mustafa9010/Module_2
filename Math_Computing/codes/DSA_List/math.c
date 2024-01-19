#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libs/listgen.h"
#include "libs/listfun.h"

int  main()
{
avyuh *A,*B,*D,*e1,*vert;
avyuh *n1,*n2,*n3,*n4,*d1,*d2,*d3,*num,*den;
int m =3,n=4; //(mxn) matrices

//load matrix from file
vert = loadList("Mat.dat",m,n);

//printList(vert);
//Triangle vertices
A = Listcol(vert,0);
B = Listcol(vert,1);
D = Listcol(vert,2);
e1 = Listcol(vert,3);

//printing the lists
/*printList(A);
printList(B);
printList(D);
printList(e1);*/

n1 = Listmul(transposeList(B),B);
//printList(n1);
n2 = Listmul(transposeList(B),D);
n3 = Listmul(transposeList(D),D);
n4 = Listmul(transposeList(A),Listadd(B,D));
d1 = Listmul(transposeList(A),e1);
d2 = Listmul(transposeList(B),e1);
d3 = Listmul(transposeList(e1),D);
num = Listadd(Listsub(Listadd(n1,n3),Listmul(n4,n4)),Listscale(n2,2));
//printList(num);
//den = Listscale(Listsub(Listsub(Listmul(d1,n4),d2),d3,2);
den = Listscale(Listsub(Listsub(Listmul(d1,n4),d2),d3),2);	
//printList(den);
double lambda = Listdiv(num,den);
printf("Lambda = %lf\n",lambda);
return 0;

}
