#include<stdio.h>
#include "sharedspice.h"
#include "myspice.h"
#include <pthread.h>
void* hello(void* arg)
{
    printf("Hello World! in Thread of NgSpice.\n");
    spiceInit();
    return 0;
}
int main(int argc, char const *argv[])
{
    pthread_t thread_ngspice;
    int ifSPICE_RUN = pthread_create(&thread_ngspice, NULL, hello, NULL);
    printf("Hello NGspice! in main Thread\n");
    pthread_exit(NULL);
    
    return 0;
}
