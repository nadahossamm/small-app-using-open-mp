#include <stdio.h>
#include <stdlib.h>

#define THREADS 4

int main()
{
    int row,col,id,np;
    printf("Enter number of row and column ");
    scanf("%d %d", &row,&col);
    int i,j;
    char ** arr= (char**)malloc(row * sizeof(char *));
    for(i=0; i<row; i++)
    {
        arr[i]= (char*)malloc(col* sizeof(char ));
    }

    for( i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            printf("Enter 'X' or 'O' ");
            scanf(" %c", & arr[i][j] );
        }
    }
    printf("\n");
    for( i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }


    printf("\n");
    printf("\n");
    #pragma omp parallel private(j) num_threads(THREADS)
    {
        #pragma omp for schedule(static)
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < col; j++)
            {
		printf("%d %d",i,j);
                if(  arr[i][j] =='o' && arr[i][j-1] =='x' && arr[i][j+1] =='x')
                {

                    arr[i][j] ='x';
		     

                }
                np = omp_get_num_threads();
                id = omp_get_thread_num();

                printf ("hello from thread %d out of %d threads\n", id, np);


            }

        }

    }
    for( i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}
