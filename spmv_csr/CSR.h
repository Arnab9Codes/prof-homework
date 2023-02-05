#include<stdio.h>
#include<stdlib.h>

typedef struct CSR{
    int rows;
    int clmns;
    int nzeros;
    double *vals;
    int *rptrs;
    int *clmnptrs;
}CSR;

CSR csr_generation(int rs, int cols, int non_zeros, double v[][cols]){

    CSR csr;
    csr.rows=rs;
    csr.clmns=cols;
    csr.nzeros=non_zeros;

    //allocating memory and initializing to 0
    csr.vals=calloc(non_zeros, sizeof(double));
    csr.rptrs=calloc((rs+1), sizeof(int));
    csr.clmnptrs=calloc(non_zeros, sizeof(int));

    int nzc_in_rows=0;

    for(int i=0;i<rs;i++){
        csr.rptrs[i]=nzc_in_rows;
        for(int j=0;j<cols;j++){
            if(v[i][j]!=0){//v[i*rs+j]!=0

               // coo.rptrs[nzc_in_rows]=i;
                csr.vals[nzc_in_rows]=(double)v[i][j];
                csr.clmnptrs[nzc_in_rows]=j;

                nzc_in_rows=nzc_in_rows+1;
            }
        }
    }
    csr.rptrs[rs]=nzc_in_rows;

    return csr;
}

void print_csr(CSR csr){

    int nzc=0;

    for(int i=0; i<(csr.rows+1);i++){
        printf("row %d",i);printf("\n");
        for(int j=csr.rptrs[i];j<csr.rptrs[i+1];j++){
            printf("column index: %d", csr.clmnptrs[nzc]);printf("\n");
            printf("value: %lf", csr.vals[nzc]);printf("\n");
            nzc++;
        }
        printf("------------\n");
    }

    free(csr.rptrs);
    free(csr.vals);
    free(csr.clmnptrs);

}
