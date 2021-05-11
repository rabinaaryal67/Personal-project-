//***********************************************************

//
// Program: Postfix Calculator
// This program evaluates postfix expressions.
//***********************************************************


//include directives
//for cout and cin
#include <iostream>
#include <iomanip>
//for file input and output
#include <fstream>
//for handling stacks
#include<stack>
#include "mystack.h"

using namespace std;
//this function evaluates our postfix expression
void evaluateExpression(ifstream& inpF, ofstream& outF,
                        stackType<double>& stack,
                        char& ch, bool& isExpOk);
                        //this function evaluates our operators from the postfix expression

void evaluateOpr(ofstream& out, stackType<double>& stack,
                 char& ch, bool& isExpOk);
//This expression removes our postfix expression
void discardExp(ifstream& in, ofstream& out, char& ch);

//Print the results of the evaluation of our postfix expression
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk);

int main()
{
    bool expressionOk;
    char ch;
    //declare our stack wich can hold 100 values of type double
    stackType<double> stack(100);
    ifstream infile;
    ofstream outfile;
//open our RpnData file for reading
    infile.open("RpnData.txt");
// the file opening fail throw an appropriate exception
    if (!infile)
    {
        cout << "Cannot open the input file. "
             << "Program terminates!" << endl;
        return 1;
    }
   //open our file RpnFile for writing
    outfile.open("RpnOutput.txt");
   //set appropriate flags to makes sure our values are in correct format
   //before loaded into the output file
    outfile << fixed << showpoint;
    outfile << setprecision(2);

    infile >> ch;
    //while theres content to read in the input file keep reading until theres none
    while (infile)
    {
        stack.initializeStack();
        expressionOk = true;
        outfile << ch;

        evaluateExpression(infile, outfile, stack, ch,
                           expressionOk);
        printResult(outfile, stack, expressionOk);
        infile >> ch; //begin processing the next expression
    } //end while
// when we're done reading the file to make sure we save our computer resources
//and make is available for other resources to use it we have to close the streams
    infile.close();
    outfile.close();

    return 0;

} //end main


void evaluateExpression(ifstream& inpF, ofstream& outF, stackType<double>& stack,char& ch, bool& isExpOk)
{
    double num;
//while our charactor is not an equal sign then execute the loop body
    while (ch != '=')
    {
        switch (ch)
        {
            //Case ch is requal to our hashtag charactor execute the following case statements
        case '#':
            inpF >> num;
            outF << num << " ";
            // if our stack is not full, not equal 100 please load our value num
            //into the statck
            if (!stack.isFullStack())
                stack.push(num);
            else
            {
                //if the stack is full display the following message to the screen
                cout << "Stack overflow. "
                     << "Program terminates!" << endl;
                exit(0);  //terminate the program
            }

            break;
        default:
            evaluateOpr(outF, stack, ch, isExpOk);
        }//end switch
         //If our expression is good to go enter our ifstatement body and
         //read our charactor and store it into the file
        if (isExpOk) //if no error
        {
            inpF >> ch;
            outF << ch;

            if (ch != '#')
                outF << " ";
        }
        else
            //discard our postfix expression
            discardExp(inpF, outF, ch);
    } //end while (!= '=')
} //end evaluateExpression

//The following code checks if the stack is not empty
//if the stack is not empty then pop appropriate values and check our expression
// look for operators such as plus then evaluate our poped out values
void evaluateOpr(ofstream& out, stackType<double>& stack,
              char& ch, bool& isExpOk)
{
    double op1, op2;

    if (stack.isEmptyStack())
    {
        out << " (Not enough operands)";
        isExpOk = false;
    }
    else
    {
        op2 = stack.top();
        stack.pop();

        if (stack.isEmptyStack())
        {
            out << " (Not enough operands)";
            isExpOk = false;
        }
        else
        {
            op1 = stack.top();
            stack.pop();

            switch (ch)
            {
            case '+':
                //Evaluate the operand op1 and op2, and then push them into the stack
                stack.push(op1 + op2);
                break;
            case '-':
                stack.push(op1 - op2);
                break;
            case '*':
                stack.push(op1 * op2);
                break;
            case '/':
                if (op2 != 0)
                    stack.push(op1 / op2);
                else
                {
                    out << " (Division by 0)";
                    isExpOk = false;
                }
                break;
            default:
                out << " (Illegal operator)";
                isExpOk = false;
            }//end switch
        } //end else
    } //end else
} //end evaluateOpr

//check our charactor if it matches the equal sign charactor then discard it
void discardExp(ifstream& in, ofstream& out, char& ch)
{
    while (ch != '=')
    {
        in.get(ch);
        out << ch;
    }
} //end discardExp
//print the results if  expression validation is ok and is good to go and the stack is not empty
void printResult(ofstream& outF, stackType<double>& stack,
                 bool isExpOk)
{
    double result;

    if (isExpOk) //if no error, print the result
    {
        if (!stack.isEmptyStack())
        {
            result = stack.top();
            stack.pop();

            if (stack.isEmptyStack())
                outF << result << endl;
            else
                outF << " (Error: Too many operands)" << endl;
        } //end if
        else
            outF << " (Error in the expression)" << endl;
    }
    else
        outF << " (Error in the expression)" << endl;

    outF << "_________________________________"
         << endl << endl;
} //end printResult AZsxdc fvkl.kjhgfd saASE DRFGHJKL;
