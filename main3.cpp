#include <iostream>
#include <cstring>
#include <fstream>
#include "MyStackh.h"
using namespace std;
struct Pair
{
    char variable;
    int value;
};

class Calculator
{
private:
    Stack<char> expressionStack;
    Pair p[32];//array for the 32 letters in the alphabet and the 32 values respectively
    int nr;
    bool ok;// to stop other methods from overwriting some errors that are already printed

public:
    void readInput()
    {
        char x,y;
        int z;

        ifstream fin("input.txt");
        ofstream fout("output.txt");

        while(fin>>x)
        {
            //cout<<x<<y<<z<<" ";
            if(x=='(')
            {
                expressionStack.push(x);
                break;
            }

            if(!(x >= 'A' && x <= 'Z'))
            {
                fout<<"Invalid variable name";
                ok=0;
                return;
            }
            p[nr].variable=x;
        fin>>y;

            if(y!='=')
            {
                fout<<"The operator "<<y<<" is invalid";
                ok=0;
                return;
            }
        fin>>z;

            p[nr].value=z;// i have to take it as integer if it has >1 digits
            nr++;

        }

        while(fin>>x)
                    expressionStack.push(x);//push the rest of the expression to the stack

        fin.close();
        fout.close();
    }

    void inverseStack()//left to right
    {
        Stack<char> auxStack;
        while(expressionStack.isEmpty()==0)
        {
            auxStack.push(expressionStack.pop());
        }
        expressionStack=auxStack;
    }

    int execute()
    {
        ofstream fout("output.txt");

        inverseStack();// evaluate the expression from left to right

        Stack<int> operandStack;/// for numbers
        Stack<char> operatorStack;/// for parenthesis and operators

        char t;
        int v;//integer for the operand stack obtained from t

        while(expressionStack.isEmpty()==0)
        {
            t=expressionStack.pop();
            //t is the value extracted from the stack that we will further analyze
            if(t=='(' || t =='+'||t =='-'||t =='*'||t =='/'||t =='%')
            {
                operatorStack.push(t);
            }
            else if(t==')')
            {
                //while(operatorStack.isEmpty()==0 && operatorStack.peek()!='(')
                char aux=operatorStack.pop(); // get the operator
                operatorStack.pop();
            if(operandStack.getTopLevel()>=1)//from 0!
                {int op2 = operandStack.pop();
                int op1 = operandStack.pop();
                int op;
                switch (aux) {
                    case '+':
                        op= op1+op2;
                        break;
                    case '-':
                        op= op1-op2;
                        break;
                    case '*':
                        op= op1*op2;
                        break;
                    case '/':
                        if(op2==0)
                        {
                            fout<<"Division by 0!";
                            ok=0;
                            return 0;
                        }
                        op= op1/op2;
                        break;
                    case '%':
                        op= op1%op2;
                        break;
                }
                operandStack.push(op);
                }
                else {
                    fout<<"Not enough elements to perform computations!";
            ok=0;
            return 0;
                }
            }
            else if(t>='A' && t<='Z')
            {
                bool isgood=0;//for verifying variables

                for(int i=0;i<32;i++)
                    if(p[i].variable==t)
                    {
                        v=p[i].value;
                        operandStack.push(v);
                        isgood=1;
                        break;
                    }
                    if(isgood==0)
                        {
                            fout<<"Variable used in expression is not defined!";
                            ok=0;
                            return 0;
                        }
            }

        }

        if(operatorStack.isEmpty()==0)
        {
            fout<<"Declaration of the formula is not clear! (parentheses not closed properly)";
            ok=0;
            return 0;
        }

        if(ok==1)
        return operandStack.peek();

        fout.close();
    }

    void writeOutput()
    {
        int i;


        if(ok==1)
         i=execute(); //to update the data ( the value "ok" )
        if(ok==1){
        //to not overwrite fake results over errors

        ofstream fout("output.txt");
        fout<<"Result="<<i;

        fout.close();
        }
    }

    Calculator()
    {
        p[32]={NULL};
        nr=0;
        ok=1;

    }

};

int main()
{
    Calculator c;
    c.readInput();
    c.writeOutput();

    return 0;
}
