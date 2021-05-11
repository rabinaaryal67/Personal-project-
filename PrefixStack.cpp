
#include "PrefixStack.h"
//Reverse our prefix string
void ReverseString(string &data)
{
    int lastIndex = data.length()-1;
    int start = 0;
    char temp;
    while(start < lastIndex)
    {
        temp = data[start];
        data[start] = data[lastIndex];
        data[lastIndex] = temp;
        start++;
        lastIndex--;
        cout<<data<<endl;
    }
}
//check if the string is a valid prefix string
bool IsValidPrefix(string & data)
{
    bool isvalid=false;
 string operands ="+*/-";
 int length_=operands.length();
     for (int i=0;i<length_;i++)
    {
       if(data[0]==operands[i])
       {
           isvalid=true;
       }
    }
    return isvalid;
}
