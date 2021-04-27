#define _XOPEN_SOURCE 500

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <cmath>
#include<cstring>
#include<algorithm>
#include <limits.h>
#include<stdint.h>

#define INT_STR_SIZE (sizeof(int)*CHAR_BIT/3 + 3)

using namespace std;

struct tArguments
{
   pthread_t t;
   int filedescriptor;
};


int globalMinimum[10];
int  offsets[10][2];
char filechunks[10][1000];

//Convert an integer char to integer
//e.g char l='7'
// int seven=l-'0';
int CharToInt(char c)
{
    int h=c-'0';

    return h;
}
char *my_itoa(int x) {
    char dest[1000];
    size_t size1=INT_STR_SIZE;
  char buf[INT_STR_SIZE];
  char *p = &buf[INT_STR_SIZE - 1];
  *p = '\0';
  int i = x;

  do {
    *(--p) = abs(i%10) + '0';
    i /= 10;
  } while (i);

  if (x < 0) {
    *(--p) = '-';
  }
  size_t len = (size_t) (&buf[INT_STR_SIZE] - p);
  if (len > size1) {
    return NULL;
  }
  return (char*)memcpy(dest, p, len);
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

      for (i=n-1;i>=0;--i,number/=10)
    {

        numberArray[i]=(number%10)+'0';
    }



    return numberArray;
}



//Calculate  the minimum number from our chunk
int ComputeMin(int ChunkIndex,char filechunks[][1000])
{
    int maximumValue=0;

    for(int j=0;j<1000;j++)
    {
        if(CharToInt(filechunks[ChunkIndex][j])>maximumValue)
        {
            maximumValue=CharToInt(filechunks[ChunkIndex][j]);
        }
    }

    int minN=maximumValue;

        for (int j=0;j<1000;j++)
        {
             if (CharToInt(filechunks[ChunkIndex][j])<minN)
             {
            minN=CharToInt(filechunks[ChunkIndex][j]);
             }
        }

    return minN;
}
//Compute our global minimum from  generated minimums by our 10 threads
void ComputeGlobalMin()
{
     int maximumValue=0;

    for(int j=0;j<10;j++)
    {
        if(globalMinimum[j]>maximumValue)
        {
            maximumValue=globalMinimum[j];
        }
    }

    int minN=maximumValue;

        for (int j=0;j<10;j++)
        {
             if (globalMinimum[j]<minN)
             {
            minN=globalMinimum[j];
             }
        }

    printf("Global Minimum = \t %d",minN);
}
uint64_t _IntThreadId()
{
     pthread_t ptid=pthread_self();
      uint64_t threadId=0;
    memcpy(&threadId,&ptid,std::min(sizeof(threadId),sizeof(ptid)));
    return threadId;
}
uint64_t _IntThreadId(pthread_t ptid)
{

      uint64_t threadId=0;
    memcpy(&threadId,&ptid,std::min(sizeof(threadId),sizeof(ptid)));
    return threadId;
}
void * v1(void * arguments)
{
int result= ComputeMin(0,filechunks);
pthread_t ptid=pthread_self();
globalMinimum[0]=result;
 printf("%s \t %d \t %d \t %d\n",toCharArray(_IntThreadId(ptid)),offsets[0][0],offsets[0][1],result);
 return NULL;
}
void * v2(void * arguments)
{

int result= ComputeMin(1,filechunks);
pthread_t ptid=pthread_self();
globalMinimum[1]=result;
printf("%s \t %d \t %d \t %d\n",toCharArray(_IntThreadId(ptid)),offsets[1][0],offsets[1][1],result);
 return NULL;
}
void * v3(void * arguments)
{
 int result= ComputeMin(2,filechunks);
 pthread_t ptid=pthread_self();
 globalMinimum[2]=result;
 printf("%s \t %d \t %d \t %d\n",toCharArray(_IntThreadId(ptid)),offsets[2][0],offsets[2][1],result);
 return NULL;
}
void * v4(void * arguments)
{
  int result= ComputeMin(3,filechunks);
  pthread_t ptid=pthread_self();
  globalMinimum[3]=result;
  printf("%s \t %d \t %d \t %d\n",toCharArray(_IntThreadId(ptid)),offsets[3][0],offsets[3][1],result);
  return NULL;
}
void * v5(void * arguments)
{
 int result= ComputeMin(4,filechunks);
 pthread_t ptid=pthread_self();
  globalMinimum[4]=result;


 printf("%s \t %d \t %d \t %d\n",toCharArray(_IntThreadId(ptid)),offsets[4][0],offsets[4][1],result);
 return NULL;
}
void * v6(void * arguments)
{
 int result= ComputeMin(5,filechunks);
 pthread_t ptid=pthread_self();
  globalMinimum[5]=result;
printf("%s \t %d \t %d \t %d\n",toCharArray(_IntThreadId(ptid)),offsets[5][0],offsets[5][1],result);
return NULL;
}
void * v7(void * arguments)
{
 int result= ComputeMin(6,filechunks);
  pthread_t ptid=pthread_self();
    globalMinimum[6]=result;
printf("%s \t %d \t %d \t %d\n",toCharArray(_IntThreadId(ptid)),offsets[6][0],offsets[6][1],result);
return NULL;
}
void * v8(void * arguments)
{
 int result= ComputeMin(7,filechunks);
   pthread_t ptid=pthread_self();
     globalMinimum[7]=result;
printf("%s \t %d \t %d \t %d\n",toCharArray(_IntThreadId(ptid)),offsets[7][0],offsets[7][1],result);
return NULL;
}
void * v9(void * arguments)
{
 int result= ComputeMin(8,filechunks);
    pthread_t ptid=pthread_self();
     globalMinimum[8]=result;
printf("%s \t %d \t %d \t %d\n",toCharArray(_IntThreadId(ptid)),offsets[8][0],offsets[8][1],result);
return NULL;
}


void * v10(void * arguments)
{
 int result= ComputeMin(9,filechunks);
   pthread_t ptid=pthread_self();
     globalMinimum[9]=result;

printf("%s \t %d \t %d \t %d\n",toCharArray(_IntThreadId(ptid)),offsets[9][0],offsets[9][1],result);
return NULL;
}

void ReadFile(int fdescriptor,char filechunks[][1000])
{
  int cur=0;
  int chunkIndex=0;
  int endOffset=1000;
 pthread_t ptid=pthread_self();
   printf("Main OutPut\n");
  printf("TID \t S_OffSet \t E_OffSet\n");

   while (cur<=9000)
   {
       //Store our startoffset and our endoffset to be read by our 10 threads later on
       offsets[chunkIndex][0]=cur;
       offsets[chunkIndex][1]=endOffset;

     //read and store our filechunks in a two dimensional array
       lseek(fdescriptor,cur,SEEK_SET);
        int results=read(fdescriptor,&filechunks[chunkIndex],sizeof(filechunks[chunkIndex]));

          printf("%s \t %d \t %d \n",toCharArray(_IntThreadId(ptid)),cur,endOffset);
        cur+=1000;
        chunkIndex=cur/1000;
        endOffset+=1000;

        if(results==-1)
        {
          write(STDOUT_FILENO,"Failed to read from file",24);
        exit(-1);
        }
   }

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

 pthread_t t1[10];

 //Open our test file for reading
int fd=open(filename,O_RDONLY,0644);

if (fd!=-1)
{

ReadFile(fd,filechunks);


write(STDOUT_FILENO,"\n",1);
write(STDOUT_FILENO,"Threads output:",14);
write(STDOUT_FILENO,"\n",1);

//The following code creates our 10 threads
pthread_create(&t1[0],NULL,&v1,NULL);
pthread_create(&t1[1],NULL,&v2,NULL);
pthread_create(&t1[2],NULL,&v3,NULL);
pthread_create(&t1[3],NULL,&v4,NULL);
pthread_create(&t1[4],NULL,&v5,NULL);
pthread_create(&t1[5],NULL,&v6,NULL);
pthread_create(&t1[6],NULL,&v7,NULL);
pthread_create(&t1[7],NULL,&v8,NULL);
pthread_create(&t1[8],NULL,&v9,NULL);
pthread_create(&t1[9],NULL,&v10,NULL);

//This code calls pthread_join when all our threads are done executing
for (int i=0;i<10;i++)
{
   pthread_join(t1[i],NULL);
}

   close(fd);

   }else
   {
       write(STDOUT_FILENO,"error while opening the file",28);
   }

write(STDOUT_FILENO,"\n",1);

ComputeGlobalMin();

    return 0;
}
