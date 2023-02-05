#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "CSR.h"


//#define NUM_THREADS 4 // same as number of rows
#define R1 4
#define C1 4
//#define R2 4
//#define C2 4


 double* spmv(CSR csr, double V[C1]){

    static double res[R1];
    int nzc=0;
    int row_count=0;
    #pragma omp parallel for
    for(int i=0;i<csr.rptrs[csr.rows];i++){
        int r_start=csr.rptrs[i];
        int r_end=csr.rptrs[i+1];
        //int c=csr.clmnptrs[i];
        //printf("\nrstart %d, rend: %d\n",r_start,r_end);

        for(int j=r_start;j<r_end;j++){
            int c=csr.clmnptrs[nzc];
            double mat_row_val=csr.vals[nzc];
            double v=V[c];
            //printf("\nmat_val %lf, vector val: %lf\n",mat_row_val,v);
            # pragma omp atomic
            res[i]+=mat_row_val*v;// i maintains individual rows
            nzc++;
        }
        
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

    CSR csr_object1, csr_object2;
    csr_object1=csr_generation(4,4,5,m);
    product=spmv(csr_object1,v);
    //print_csr(csr_object1);
    for(int i=0;i<R1;i++){
        printf("%lf ", *(product+i));
    }

    return 0;
}
    
