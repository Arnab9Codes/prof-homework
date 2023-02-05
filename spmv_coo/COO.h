#include<stdio.h>
#include<stdlib.h>

typedef struct COO{
    int rows;
    int clmns;
    int nzeros;
    double *vals;
    int *rptrs;
    int *clmnptrs;
}COO;

COO coo_generation(int rs, int cols, int non_zeros, double v[][cols]){

    COO coo;
    coo.rows=rs;
    coo.clmns=cols;
    coo.nzeros=non_zeros;

    //allocating memory and initializing to 0
    coo.vals=calloc(non_zeros, sizeof(double));
    coo.rptrs=calloc(non_zeros, sizeof(int));
    coo.clmnptrs=calloc(non_zeros, sizeof(int));

    int nzc_in_rows=0;

    for(int i=0;i<rs;i++){
        //coo->rptrs[i]=nzc_in_rows;
        for(int j=0;j<cols;j++){
            if(v[i][j]!=0){//v[i*rs+j]!=0

                coo.rptrs[nzc_in_rows]=i;
                coo.vals[nzc_in_rows]=(double)v[i][j];
                coo.clmnptrs[nzc_in_rows]=j;

                nzc_in_rows=nzc_in_rows+1;
            }
        }
    }

    return coo;
}

void print_coo(COO coo){

    int nzc=0;

    for(int i=0;i<coo.nzeros;i++){
        printf("row index: %d, column index: %d, value: %lf\n", coo.rptrs[i], coo.clmnptrs[i], coo.vals[i]);
    }


    free(coo.rptrs);
    free(coo.vals);
    free(coo.clmnptrs);

}
