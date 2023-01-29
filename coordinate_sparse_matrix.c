#include<stdio.h>
#include<stdlib.h>

typedef struct COO{
    int rows;
    int clmns;
    int nzeros;
    int *vals;
    int *rptrs;
    int *clmnptrs;
}COO;

void coo_generation(int rs, int cols, int non_zeros,const int *v, COO *coo){

    coo->rows=rs;
    coo->clmns=cols;
    coo->nzeros=non_zeros;

    //allocating memory and initializing to 0
    coo->vals=calloc(non_zeros, sizeof(int));
    coo->rptrs=calloc(non_zeros, sizeof(int));
    coo->clmnptrs=calloc(non_zeros, sizeof(int));

    int nzc_in_rows=0;

    for(int i=0;i<rs;i++){
        //coo->rptrs[i]=nzc_in_rows;
        for(int j=0;j<cols;j++){
            if(v[i*rs+j]!=0){//v[i*rs+j]!=0

                coo->rptrs[nzc_in_rows]=i;
                coo->vals[nzc_in_rows]=v[i*rs+j];
                coo->clmnptrs[nzc_in_rows]=j;

                nzc_in_rows=nzc_in_rows+1;
            }
        }
    }
}

void print_coo(COO *coo){

    int nzc=0;

    for(int i=0;i<coo->nzeros;i++){
        printf("row index: %d, column index: %d, value: %d\n", coo->rptrs[i], coo->clmnptrs[i], coo->vals[i]);
    }


    free(coo->rptrs);
    free(coo->vals);
    free(coo->clmnptrs);

}

int main()
{
    int r=4;
    int c=4;
    int non_zero_vals=6;
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
    COO coo;
    coo_generation(r,c,non_zero_vals,v,&coo);
    print_coo(&coo);

    return 0;

}
