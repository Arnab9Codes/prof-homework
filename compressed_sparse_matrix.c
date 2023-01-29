#include<stdio.h>
#include<stdlib.h>

typedef struct CSR{
    int rows;
    int clmns;
    int nzeros;
    int *vals;
    int *rptrs;
    int *clmnptrs;
}CSR;

void csr_generation(int rs, int cols, int non_zeros,const int *v, CSR *csr){

    csr->rows=rs;
    csr->clmns=cols;
    csr->nzeros=non_zeros;

    //allocating memory and initializing to 0
    csr->vals=calloc(non_zeros, sizeof(int));
    csr->rptrs=calloc((rs+1), sizeof(int));
    csr->clmnptrs=calloc(non_zeros, sizeof(int));

    int nzc_in_rows=0;

    for(int i=0;i<rs;i++){
        csr->rptrs[i]=nzc_in_rows;
        for(int j=0;j<cols;j++){
            if(v[i*rs+j]!=0){//v[i*rs+j]!=0
                csr->vals[nzc_in_rows]=v[i*rs+j];
                csr->clmnptrs[nzc_in_rows]=j;

                nzc_in_rows=nzc_in_rows+1;
            }
        }
    }
    csr->rptrs[rs]=nzc_in_rows;// row pointers are 1 more than the row

}

void print_csr(CSR *csr){

    int nzc=0;

    for(int i=0; i<(csr->rows+1);i++){
        printf("row %d",i);printf("\n");
        for(int j=csr->rptrs[i];j<csr->rptrs[i+1];j++){
            printf("column index: %d", csr->clmnptrs[nzc]);printf("\n");
            printf("value: %d", csr->vals[nzc]);printf("\n");
            nzc++;
        }
        printf("------------\n");
    }

    free(csr->rptrs);
    free(csr->vals);
    free(csr->clmnptrs);

}

int main()
{
    int r=4;
    int c=4;
    int non_zero_vals=5;
    int v[]={
           0,1,2,0,
           0,0,2,0,
           1,0,0,0,
           0,0,5,2};
    
   /*int v[4][4]={
           {0,1,2,0},
           {0,0,2,0},
           {1,0,0,0},
           {0,0,5,2}};*/
    CSR csr;
    csr_generation(r,c,non_zero_vals,v,&csr);
    print_csr(&csr);

    return 0;

}
