// 2 level nested thread implementation
// do not use Complex Coodinate Matrix Format
// do not use Compressed Sparsed Matrix Format

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4 // same as number of rows
#define R1 4
#define C1 4
#define R2 4
#define C2 4

void print_mat(double v[][C2]){
    for(int i=0;i<R1;i++){
        for(int j=0;j<C2;j++){
            printf("%lf ", v[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    double m[R1][C1]={{1,1,1,1},
            {1,1,1,1},
            {1,1,1,1},
            {1,1,1,1}};

    double v[R2][C2]={{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
    double product[R1][C2];

    for(int i=0;i<R1;i++){
        for(int j=0;j<C2;j++){
            product[i][j]=0.0;
        }
    }

    int num_threads_req=0;

    omp_set_num_threads(NUM_THREADS);// assuming will get as the required number of threads
    omp_set_nested(1);
    #pragma omp parallel num_threads(R1)
    {
       // double temp_add=0.0;
        int row_nthreads=omp_get_num_threads();
        int row_no=omp_get_thread_num();

        for(int i=row_no;i<NUM_THREADS;i=i+row_nthreads){
            
            #pragma omp parallel num_threads(C2)
            {
                int col_nthreads=omp_get_num_threads();
                int col_no=omp_get_thread_num();
                double temp_add=0.0;

                for(int j=col_no;j<C2;j+=col_nthreads){
                    for (int k=0;k<C1;k++){
                        temp_add+=m[row_no][k]*v[k][col_no];
                        product[row_no][col_no]=temp_add;
                    }
                }    
            }
                
        }
    }

    print_mat(product);
    return 0;
}
