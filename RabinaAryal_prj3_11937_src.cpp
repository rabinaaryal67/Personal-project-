//Compilation Instructions

//g++.exe RabinaAryal_prj3_11937_src.cpp -o RabinaAryal_prj3_11937_src.exe
///RabinaAryal_prj3_11937_src.exe  prj2inp1.txt
///RabinaAryal_prj3_11937_src.exe  prj2inp2.txt

#define _XOPEN_SOURCE 500
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
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
#include<stack>

#define INT_STR_SIZE (sizeof(int)*CHAR_BIT/3 + 3)
using namespace std;

stack <char>_Stack;
pthread_mutex_t _mutex;
int globalIntegers[10];

int CharToInt(char c);
int ComputeMin(char filechunk[1000]);
int Minimum(int array1[],int itemsCount);
char *toCharArray(int number);

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
//Convert integer into a string of chars


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
//Compute the minimum number
int Minimum(int array1[],int itemsCount)
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
//Gets the minimum number from a string of 1000 integers
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
//Convert char to integer
int CharToInt(char c)
{
    int h=c-'0';
    return h;
}

int ChunkCounter1=0;
//keep track of the current file position variable
int CurrentPos=0;

//First read 1000 chunk of numbers from file
//Then push a 100 chunk into a stack one char at a time
//When we have reached a maximum of 100 chars then
//Then unlock the mutex
//then call thread two and lock the mutex so that the current thread wont read any data
//until thread 2 the consumer is done popping all 100 chars from the stack
//repeat this procedure until we're done reading all 10000 characters from the file

void * v1(void *arguments)

{
    int fd=*(int*)arguments;

    char buff[1000];
//seek the current position of our
    lseek(fd,CurrentPos,SEEK_SET);

    int results=read(fd,&buff,sizeof(buff));

    if(results==-1)
    {
        write(STDOUT_FILENO,"Failed to read from file\n",25);
        exit(-1);
    }



    if(pthread_mutex_lock(&_mutex)!=0)
    {

        exit(-1);
    }


    if(ChunkCounter1==1000)
    {
        lseek(fd,CurrentPos,SEEK_SET);
        int results=read(fd,&buff,sizeof(buff));

        if(results==-1)
        {
            write(STDOUT_FILENO,"Failed to read from file\n",25);
            exit(-1);
        }
        CurrentPos+=1000;

        ChunkCounter1=0;
    }

    while(_Stack.size()<100 && ChunkCounter1<1000)
    {
sched_yield();
         if(buff[ChunkCounter1]=='\n')
         {
             _Stack.push('0');
         }else
         {
            _Stack.push(buff[ChunkCounter1]);
         }

        ChunkCounter1++;
    }


    if(pthread_mutex_unlock(&_mutex)!=0)
    {

        exit(-1);
    }


    return NULL;
}

int bufferCounter=0;
int ChunkCounter=0;
//buffer for storing 1000 integers from the producer thread
char buff1[1000];
//Our consumer thread
void * v2(void *arguments)
{
    // lock the mutex
    if(pthread_mutex_lock(&_mutex)!=0)
    {
        exit(-1);
    }
//pop the values form stack until the size is zero and make sure buffer counter
// Does not exceed buffer1 array maximum index to avoid index out of bounds error
    while(_Stack.size()>0 && bufferCounter<1000)
    {
         sched_yield();

        buff1[bufferCounter]=_Stack.top();
        _Stack.pop();
        bufferCounter++;

    }
  // if our buffer has 1000 chunks of chars
  //then compute the minimum and store it in our array
    if(bufferCounter==1000)
    {
        globalIntegers[ChunkCounter]=ComputeMin(buff1);
        ChunkCounter++;
        bufferCounter=0;
    }

    //release our lock
    if(pthread_mutex_unlock(&_mutex)!=0)
    {

        exit(-1);
    }

    return NULL;

}



     int main(int argc,char*argv[])
   {

char*filename;

  if (argc==2)
    {
        filename=argv[1];
    }else
    {
       write(STDOUT_FILENO,"Usage:",6);
        write(STDOUT_FILENO,argv[0],strlen(argv[0]));
         write(STDOUT_FILENO,".exe Filename\n",14);
     exit(-1);
    }

    // open our file for reading
    int fd=open(filename,O_RDONLY,0644);
    //initialize our mutex
    _mutex=(pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;




    if(fd!=-1)
    {

        pthread_t t1,t2;
        //while we're not done reading 10 chunks of 1000 chars each keep looping
        while(ChunkCounter<10)
        {
             //Create the thread and pass the file descriptor as argument
            pthread_create(&t1,NULL,&v1,(void*)&fd);
            pthread_create(&t2,NULL,&v2,NULL);
            //join threads
            pthread_join(t1,NULL);
            pthread_join(t2,NULL);
        }
        write(STDOUT_FILENO,"Data",4);
        write(STDOUT_FILENO,"\n",1);
        write(STDOUT_FILENO,"----------\n",11);

        //Display our data
        for(int i=0; i<9; i++)
        {
            write(STDOUT_FILENO,"Minimum integer after ",22);

            write(STDOUT_FILENO, toCharArray((i+1)*1000),5);
            write(STDOUT_FILENO," integers =\t",12);

            write(STDOUT_FILENO, my_itoa(globalIntegers[i]),1);
            write(STDOUT_FILENO,"\n",1);
        }

        write(STDOUT_FILENO,"Minimum integer after 10 000 integers =\t",40);

        write(STDOUT_FILENO,my_itoa(Minimum(globalIntegers,10)),1);
        write(STDOUT_FILENO,"\n",1);
    }
    else
    {
        write(STDOUT_FILENO,"error while opening the file\n",29);

    }

   close(fd);

    return 0;
}
