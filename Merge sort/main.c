#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
int arr[50];
char buf[1024];


int flag =0;
pthread_t *threads ;
int thread_id =0;
struct arg_struct //int arr[], int l, int r
{
    int l;
    int r;
};
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }


    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(void *vargp)//int arr[], int l, int r
{
pthread_t *threads_inside = malloc( (2) * sizeof(pthread_t) );;

    struct arg_struct *args = vargp;
    struct arg_struct my_arg, arg1, arg2;
    memcpy(&my_arg, args, sizeof (*args));

    int thread_idA[2];

    int trash =0;
    if (my_arg.l < my_arg.r)
    {
        int m = my_arg.l+(my_arg.r-my_arg.l)/2;
        arg1.l = my_arg.l;
        arg1.r = m;

        thread_idA[0] = thread_id;
        pthread_create(&threads_inside[ 0], NULL, mergeSort, (void*)(&arg1)) ;                    //mergeSort(arr, my_arg.l, m);


        //pthread_join(threads[thread_id], NULL);
        //printf("%d " , thread_id);

        arg2.l =m+1;
        arg2.r = my_arg.r;
        thread_idA[1] = thread_id;
        pthread_create(&threads_inside[ 1], NULL, mergeSort, (void*)(&arg2)) ;          //mergeSort(arr, m+1, my_arg.r);

           pthread_join(threads_inside[0], NULL);
    pthread_join(threads_inside[1], NULL);


        merge(arr, my_arg.l, m, my_arg.r);


    }
    pthread_exit(NULL);
}
int main()
{

//     char ch, file_name[25];
    FILE *fp;



    fp = fopen("input.txt", "r"); // read mode

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    // printf("The contents of %s file are:\n", file_name);
    int last, ArrayNum, AI =0, flag =0;
    char ch;

    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        buf[strlen(buf) - 1] = '\0'; // eat the newline fgets() stores
        if(flag ==0)
            ArrayNum = atoi(buf);
        flag++;
    }

    const char s[2] = " ";
    char *token;

    /* get the first token */
    token = strtok(buf, s);

    /* walk through other tokens */
    while( token != NULL )
    {

        arr[AI] = atoi(token);
        AI++;
        token = strtok(NULL, s);
    }

//printf("%d"  , ArrayNum);

    fclose(fp);



    threads = malloc( (ArrayNum) * sizeof(pthread_t) );
    struct arg_struct args;
    args.l = 0;  //0
    args.r = ArrayNum-1;  //max-1
    pthread_create(&threads[thread_id], NULL, mergeSort, (void*)(&args)) ;



    pthread_join(threads[0], NULL);


    for(int loop = 0; loop < 10; loop++)
        printf("%d ", arr[loop]);

    // printf("Hello world!\n");
    return 0;
}
