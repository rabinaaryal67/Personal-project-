
#include <windows.h>
#include <iostream>
#include <fstream>
#include <stack>
#include "PrefixStack.h"


using namespace std;


int main()
{
    //declare our Datastack
    stack<int> DataStack;

    string PreExpression;
    cout<<"Note a prefix Expression must start with an operator from its left"<<endl;
    cout <<"E.g *454+78 is called a prefix Expression because the operator * is at the left"<<endl;
    cout<<"Now enter any prefix Expression you can think of and press enter:"<<endl;
    getline(cin,PreExpression);


    if (IsValidPrefix(PreExpression))
    {


        int result;
        //We reverse the string to turn it into a PostFix Expression
        //Remember PostFix expression is just an opposite of prefix expression
        ReverseString(PreExpression);



        int nLength=PreExpression.length();
        //if our charactor is a number then convert it to a number and push it down
        //our stack.
        //if the PreExpression charactor matches the operand pop the stack
        //and assign values to our operator variables x and y then
        // add to result and push the sum of our variable values to
        //to our stack
        //repeat the process until all the charactors are read from our string
        for( int i = 0; i < nLength; i++)
        {

            if(isdigit(PreExpression[i])==true)
            {
                char c = PreExpression[i];

                //convert any char to integer type
                int n = c-'0';
                DataStack.push(n);
            }

            if (!(DataStack.empty()))
            {

                if(PreExpression[i]=='+')
                {

                    int x = DataStack.top();

                    DataStack.pop();
                    int y = DataStack.top();

                    DataStack.pop();
                    result = x+y;
                    cout<<"operator "<< PreExpression[i]<<" operand x:"<<x<<"operand:y"<<y<< " After evaluation:"<<result<<endl;
                    DataStack.push(result);
                }
                if(PreExpression[i]=='-')
                {
                    //get the value at the top of the stack
                    int x = DataStack.top();

                    DataStack.pop();
                    int y = DataStack.top();

                    result = y-x;
                    cout<<"operator "<< PreExpression[i]<<" operand x:"<<x<<"operand:y"<<y<< " After evaluation:"<<result<<endl;
                    DataStack.push(result);
                }
                if(PreExpression[i]=='*')
                {
                    int x = DataStack.top();

                    DataStack.pop();
                    int y = DataStack.top();

                    result = x*y;
                    cout<<"operator "<< PreExpression[i]<<" operand x:"<<x<<"operand:y"<<y<< " After evaluation:"<<result<<endl;
                    DataStack.push(result);
                }
                if(PreExpression[i]=='/')
                {
                    int x = DataStack.top();

                    DataStack.pop();
                    int y = DataStack.top();

                    result = y/x;
                    cout<<"operator "<< PreExpression[i]<<" operand x:"<<x<<"operand:y"<<y<< " After evaluation:"<<result<<endl;
                    DataStack.push(result);
                }
            }
        }
        //The display our final results here
        cout<<"Final evaluation:"<<DataStack.top()<<endl;;
    }
    else
    {
        cout <<"Expression:'"<<PreExpression<<"' is not a valid prefix expression"<<endl;
    }
    cout<<"press any key to continue"<<endl;

    cin.ignore();
    return 0;
}


