//a.Read the input file from the beginning of the file to the end of file,  character by character using one character array for storing the characters with maximum array size of 32 (regardless of input file size).// b.Read the input file in reverse, that is, backwards from the end of the file, character by character.
//using one character array for storing the characters with maximum array size of 32 (regardless of input file size), Comparing each character read from part (a) with that from part (b). If they are the same then print to the screen a zero, otherwise print 1. 


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <stack>

using namespace std;

#define ReadSize 32 // max Characters to read
char ForwardArray[ReadSize], BackwardArray[ReadSize];

void Reset_Arrays()
{
    // We need to clear array before reading next 32 bytes
    for (int i = 0; i < ReadSize; i++)
    {
        ForwardArray[i] = '\0';
        BackwardArray[i] = '\0';
    }
}

void print_int(int Num)
{
    // This fuction will print int using write system call

    stack<char> S;
    while (Num > 0)
    {
        char c = (Num % 10) + '0'; //casting int to char
        Num /= 10;
        S.push(c);
    }

    while (!S.empty())
    {
        char c = S.top();
        S.pop();
        write(STDOUT_FILENO, &c, 1);
    }

    write(STDOUT_FILENO, " ", 1);
}

// A packet will contain data of a single mismatch
class Packet
{

public:
    char a, b;     //Both the chars the differ
    int Dif_Index; // The index at which they differ

    Packet(char A, char B, int Index)
    {
        a = A;
        b = B;
        Dif_Index = Index;
    }

    void Print()
    {
        print_int(Dif_Index); // we have to start counting from 1
        write(STDOUT_FILENO, &a, 1);
        write(STDOUT_FILENO, " ", 1);
        write(STDOUT_FILENO, &b, 1);
        write(STDOUT_FILENO, "\n", 1);
    }
};

int GetData(int fd, char *Array, int Chars_to_Read, int chars_to_skip, short int Side);
void Compare(char *A, char *B, vector<Packet> &List, int base);

int main(int argc, char *argv[])
{
    if (argc<2)
    {
        // Provide File to Read
        write(STDOUT_FILENO,"FILE TO READ NOT PROVIDED\n",26);
        return -1;
    }
    

    vector<Packet> Datalist; // This will be used to keep track of all the data (Mismatchs) that we print in the end

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1 )
    {
        return -1;
        write(STDOUT_FILENO,"Cant Open File\n", 20);
    }
    
    //open file in ReadOnly mode

    int Start_offset = 0, End_Offset = 1; // Doing some random intization so that our loop executes

    //for (int i = 0; End_Offset > Start_offset; i += ReadSize)

    for (int i = 0; End_Offset!=0; i += ReadSize)
    {
        Start_offset = GetData(fd, ForwardArray, ReadSize, i, 0);
        End_Offset = GetData(fd, BackwardArray, ReadSize, i, 1);

        Compare(ForwardArray, BackwardArray, Datalist, i);

        if (Start_offset == End_Offset)
        {
            write(STDOUT_FILENO, "\n\n", 2);
            break;
            // file is Exhausted
        }
        Reset_Arrays();
    }

    write(STDOUT_FILENO, "\n\n", 2);
    for (int i = 0; i < Datalist.size(); i++)
    {
        Datalist[i].Print();
    }

    write(STDOUT_FILENO, "\nTotal: ", 8);
    print_int(Datalist.size());
    write(STDOUT_FILENO, "Characters positions Differ in Position \n", 42);
    return 0;
    // we want to read untill both we reach file's middle from both ends
}

/* The fuction will be used by both part a just the parameters will be different
This function will return the current offset from where data is read, referenced from file's start
Side" will tell the function to read the data from beginning or end 
Side = 0 will read from start while Side = 1 will read from end 
*/
int GetData(int fd, char *Array, int Chars_to_Read, int chars_to_skip, short int Side)
{
    //Seek to offset
    int ret_val = 0;
   
    if (Side == 0)
    {
        //skip un-required chars
        ret_val = lseek(fd, chars_to_skip, SEEK_DATA);
        int BytesRead = read(fd, Array, ReadSize);

        //reset the file offset
        lseek(fd, ret_val, SEEK_SET);
    }
    else
    {
        
        //Save Current offset
        int Curret_offset = lseek(fd,0,SEEK_CUR);

        // Move to the last byte of file
        int END = lseek(fd, 0, SEEK_END);
        chars_to_skip = chars_to_skip * -1; //Covert the number to neg in order to move back

        int val = lseek(fd,chars_to_skip,SEEK_CUR);
        
        if (val < ReadSize)
        {
            ret_val = lseek(fd, - val, SEEK_CUR);
            int BytesRead = read(fd, Array, val);
        }
        else
        {
            ret_val = lseek(fd, - ReadSize, SEEK_CUR);
            int BytesRead = read(fd, Array, ReadSize);
        }

        
    
        //reset back the offset
        lseek(fd,Curret_offset,SEEK_SET);
    }

    
    return ret_val;
}

void Compare(char *A, char *B, vector<Packet> &List, int base)
// The base will added to Index to get right value of index
{
    int j = ReadSize - 1;

    //skip NULLs of Backward array if any
    for (j; B[j] == '\0'; j--)
    {
    }

    for (int i = 0; j >= 0; i++, j--)
    {
        if (A[i] != B[j])
        {
            List.emplace_back(A[i], B[j], i + base + 1);
            // Different match write 1
            write(STDOUT_FILENO, "1", 1);
        }
        else
        {

            write(STDOUT_FILENO, "0", 1); // Same Match write 0
        }
    }
}
