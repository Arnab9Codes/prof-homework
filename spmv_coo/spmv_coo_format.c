#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "COO.h"


//#define NUM_THREADS 4 // same as number of rows
#define R1 4
#define C1 4
//#define R2 4
//#define C2 4


 double* spmv(COO coo, double V[C1]){

    static double res[R1];

    #pragma omp parallel for
    for(int i=0;i<coo.nzeros;i++){
        int r=coo.rptrs[i];
        int c=coo.clmnptrs[i];

        double m_val=coo.vals[i];
        double v=V[c];

        #pragma omp atomic
        res[r]+=m_val*v;
    }
    return res;
}

int main()
{
    double m[R1][C1]={{1,0,0,0},
            {0,1,0,0},
            {0,0,0,1},
            {1,0,0,1}};

    double v[C1]={1,1,1,1};
    double* product;

    for(int i=0;i<R1;i++){
            product[i]=0.0;
    }

    COO coo_object1, coo_object2;
    coo_object1=coo_generation(4,4,5,m);
    product=spmv(coo_object1,v);
    //print_coo(coo_object1);
    for(int i=0;i<R1;i++){
        printf("%lf ", *(product+i));
    }

    return 0;
}
    
