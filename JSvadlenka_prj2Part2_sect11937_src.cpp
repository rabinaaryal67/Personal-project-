#define _XOPEN_SOURCE 500
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include<iostream>
#include <math.h>
#include<cstring>
#include<time.h>
#include <limits.h>

#define BUFFER_SIZE 5

#define INT_STR_SIZE (sizeof(int)*CHAR_BIT/3 + 3)


using namespace std;


int in(0),out(0),in1(0),out1(0);

int Buffer[BUFFER_SIZE][3];
int Buffer2[BUFFER_SIZE];

//function converts int to string
char *my_itoa(int x)
{
    char dest[1000];
    size_t size1=INT_STR_SIZE;
    char buf[INT_STR_SIZE];
    char *p = &buf[INT_STR_SIZE - 1];
    *p = '\0';
    int i = x;

    do
    {
        *(--p) = abs(i%10) + '0';
        i /= 10;
    }
    while (i);

    if (x < 0)
    {
        *(--p) = '-';
    }
    size_t len = (size_t) (&buf[INT_STR_SIZE] - p);
    if (len > size1)
    {
        return NULL;
    }
    return (char*)memcpy(dest, p, len);
}




int CharToInt(char c)
{
    int h=c-'0';

    return h;
}
//gets the minimum number from a string of integers
int ComputeMin(char filechunk[1000])
{
    int maximumValue=0;

    for(int j=0; j<1000; j++)
    {
        if(CharToInt(filechunk[j])>maximumValue)
        {
            maximumValue=CharToInt(filechunk[j]);
        }
    }

    int minN=maximumValue;

    for (int j=0; j<1000; j++)
    {
        if (CharToInt(filechunk[j])<minN)
        {
            minN=CharToInt(filechunk[j]);
        }
    }

    return minN;
}

//gets the minimum number from an array of integers
int ComputeMin(int array1[],int itemsCount)
{
    int maximumValue=0;

    for(int j=0; j<itemsCount; j++)
    {
        if(array1[j]>maximumValue)
        {
            maximumValue=array1[j];
        }
    }

    int minN=maximumValue;

    for (int j=0; j<itemsCount; j++)
    {
        if (array1[j]<minN)
        {
            minN=array1[j];
        }
    }

    return minN;
}



//This function converts our integer into a string of chars
char *toCharArray(int number)
{
    int n=1;

    if(number!=0)
    {
        n=log10(number)+1;
    }

    int i;
    char *numberArray=(char*)calloc(n,sizeof(char));

    for (i=n-1; i>=0; --i)
    {

        numberArray[i]=(number%10)+'0';
        number/=10;
    }
    return numberArray;
}

int tThread1Counter=0;
int tThread2Counter=1;
int tThread3Counter=1;
int GlobalMinimums[10];


//This function reads data from the input file
//manipulates the data then stores the results
//inside  the buffer to be consumed by thread 2

void * thread1_Func(void * arguments)
{

    int fd=*(int*)arguments;
    char filechunk[1000];
    int cur=0;
    int endOffset=1000;

//while we haven't read 10 inputs from the file keep reading and manipulating
//The file data
    while(tThread1Counter<10)
    {

        while((in +1)%BUFFER_SIZE==out)sched_yield();
        lseek(fd,cur,SEEK_SET);
        int results=read(fd,filechunk,sizeof(filechunk));

        if(results==-1)
        {
            write(STDOUT_FILENO,"Failed to read from file\n",25);
            exit(-1);
        }
        printf("%d \t %d \t %d \n",cur,endOffset,tThread1Counter+1);

        //write(STDOUT_FILENO,my_itoa(cur),strlen(my_itoa(cur)));
        //write(STDOUT_FILENO,"\t",1);
        //write(STDOUT_FILENO,my_itoa(EndOffset),strlen(my_itoa(EndOffset)));
        //write(STDOUT_FILENO,"\t",1);
        //write(STDOUT_FILENO,my_itoa(tThread1Counter+1),strlen(my_itoa(tThread1Counter+1)));
        //write(STDOUT_FILENO,"\n",1);

        Buffer[in][0]=cur;
        Buffer[in][1]=endOffset;
        Buffer[in][2]=tThread1Counter+1;

        cur+=1000;
        endOffset+=1000;


        in=(in+1)%BUFFER_SIZE;
        tThread1Counter++;

    }
    return NULL;
}
//This thread 2 function consumes the data from thread1 buffer
//and then reads the file using buffer data
//Then manipulates the input file data and store inside second buffer
//to be consumed by thread3
void * thread2_Func(void * arguments)
{
    int fd=*(int*)arguments;

    char filechunk[1000];
    int chunkIndex=0;
    int EndOffset=0;
    int StartOffSet=0;
    while(tThread2Counter<=10)
    {
        while(in==out)sched_yield();
        chunkIndex=Buffer[out][2];
        StartOffSet=Buffer[out][0];
        EndOffset=Buffer[out][1];

        out=(out+1)%BUFFER_SIZE;

        while((in1+1)%BUFFER_SIZE==out1)sched_yield();

        lseek(fd,StartOffSet,SEEK_SET);

        int results=read(fd,filechunk,sizeof(filechunk));

        if(results==-1)
        {
            write(STDOUT_FILENO,"Failed to read from file\n",25);
            exit(-1);
        }
        int localminimum=ComputeMin(filechunk);

        printf("%d \t %d \t %d \t %d \n",chunkIndex,StartOffSet,EndOffset,localminimum);


        //write(STDOUT_FILENO,my_itoa(chunkIndex),strlen(my_itoa(chunkIndex)));
        //write(STDOUT_FILENO,"\t",1);
        //write(STDOUT_FILENO,my_itoa(StartOffSet),strlen(my_itoa(StartOffSet)));
        //write(STDOUT_FILENO,"\t",1);
        //write(STDOUT_FILENO,my_itoa(EndOffset),strlen(my_itoa(EndOffset)));
        //write(STDOUT_FILENO,"\t",1);
        //write(STDOUT_FILENO,my_itoa(localminimum),strlen(my_itoa(localminimum)));
        //write(STDOUT_FILENO,"\n",1);

        //Store our localminimum into our buffer
        Buffer2[in1]=localminimum;
        in1=(in1+1)%BUFFER_SIZE;
        tThread2Counter++;

    }
    return NULL;
}



//This Thread3 function consumes data from thread 2 buffer
//then use the data to computer the global minimum
void * thread3_Func(void * arguments)
{
    while(tThread3Counter<=10)
    {
        while(in1==out1)sched_yield();

        GlobalMinimums[tThread3Counter-1]=Buffer2[out1];
        out1=(out1+1)%BUFFER_SIZE;
        tThread3Counter++;

        if(tThread3Counter==10)
        {
            int globalMin=ComputeMin(GlobalMinimums,10);
            printf("Global Minimum =\t %d \n",globalMin);


            //write(STDOUT_FILENO,"Global Minimum =",16);
            //write(STDOUT_FILENO,"\t",1);
            //write(STDOUT_FILENO,"\n",1);

        }
    }
    return NULL;
}


int main(int argc,char*argv[])
{
    char*filename;
    if (argc==2)
    {
        filename=argv[1];
    }
    else
    {
        write(STDOUT_FILENO,"Usage:",6);
        write(STDOUT_FILENO,argv[0],strlen(argv[0])+1);
        write(STDOUT_FILENO,".exe Filename\n",15);
        write(STDOUT_FILENO,"\n",1);
         exit(-1);
    }

    pthread_t t1,t2,t3;
    int fd=open(filename,O_RDONLY,0644);

    if(fd!=-1)
    {
        pthread_create(&t1,NULL,&thread1_Func,(void*)&fd);
        pthread_create(&t2,NULL,&thread2_Func,(void*)&fd);
        pthread_create(&t3,NULL,&thread3_Func,NULL);
        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        pthread_join(t3,NULL);
    }
    else
    {
        write(STDOUT_FILENO,"error while opening the file\n",29);
    }


    return 0;
}
