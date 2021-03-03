#include "ifinterpreter.h"
#include <iostream>
#include <sstream>

//contructor for Store where it would intiated the class with an empty vector
Store::Store() : parts()
{
    static_global = 0;
}

//
Store::Store(vector<Pieces *> &copy)
{
    parts = copy;
}

//Function that will push back the vector inside Store
void Store::addparts(Pieces &section)
{
    parts.push_back(&section);
}

void Store::print()
{
    for (int i = 0; i < parts.size(); i++)
    {

        parts.at(i)->print();
        parts.at(i)->test();
    }
}

void Store::getSize()
{
    cout << "SIze of the array: " << parts.size() << endl;
}

Text::Text(string line) : Pieces(line)
{
}

void Text::print() const
{
    cout << "Text: " << str << endl;
}
void Text::test() const{}
void Link::test() const{}

Link::Link(string line) : Pieces(line)
{
    int loc= line.find("[[");
    int end= line.find("]]");
    int val= line.find("-&gt;");
    if(val!=string::npos)
    {
        name=line.substr(val+5, end);
    }
    else 
        name= line.substr(loc+2, end-2);

}

void Link::print() const
{
    cout<<"\""<<name<<"\"";
}

Else::Else(string line) : Pieces(line)
{
}
void Else::test() const{}

void Else::print() const
{
    cout << "Else" << endl;
}

Block::Block(string line) : Pieces(line)
{
}

void Block::searchblock(string line, unsigned int pos)
{
}

void Block::test() const{

}

void Block::print() const
{

    unsigned int count = 1;
    unsigned int startpos = str.find("[") + 1;

    string buffer = str.substr(startpos);
    string hold;
    startpos = 0;
    cout << "START BLOCK" << endl;
    int pos;
    int pos2;
    int pos3;
    int pos4;

    while (count != 0)
    {
        
        pos = buffer.find("(");

        if (pos != string::npos)
        {

            if (pos > startpos)
            {
                hold = buffer.substr(startpos, pos - startpos);
                Text tec(hold);
                tec.print();
                buffer = buffer.substr(pos);
            }

            hold = buffer.substr(buffer.find("("), buffer.find(")") + 1 - buffer.find("("));

            if (hold.find("if:") != string::npos)
            {
                If call(hold);
                call.print();
            }
            else if (hold.find("else:") != string::npos)
            {
                Else e2(hold);
                e2.print();
            }
            else if (hold.find("else-if:") != string::npos)
            {
                ElseIf call(hold);
                call.print();
            }
            else if (hold.find("go-to") != string::npos)
            {
                Goto gt(hold);
                gt.print();
            }
            else if (hold.find("set:") != string::npos)
            {
                Set st(hold);
                st.print();
            }
            buffer = buffer.substr(buffer.find(")" + 1));
        }

        pos2 = buffer.find("[");

        if (pos2 != string::npos)
        {
            ++count;
            buffer=buffer.substr(pos2+1);
            cout << "START BLOCK" << endl;
        }

        pos4 = buffer.find("[[");

        if(pos4 != string::npos)
        {
            hold=buffer.substr(buffer.find("[["), buffer.find("]]")+2-buffer.find("[["));
            Link lin(hold);
            lin.print();
            buffer=buffer.substr(buffer.find("]]")+2);
        }

        pos3 = buffer.find("]");

        if (pos3 != string::npos && pos==string::npos)
        {
           
            if (pos3 != startpos)
            {
                hold = buffer.substr(startpos, pos3 - startpos);
                Text tec(hold);
                tec.print();
                buffer = buffer.substr(pos3);
            }
             --count;
            cout<<"END BLOCK"<<endl;
        }

    }
}

//Constructor for set where it will find the name and boolean it has in the passage token
Set::Set(string line) : Pieces(line)
{
    name=line.substr(line.find("$"), line.find("to")-1);
    if(line.find("true")!=string::npos)
        value=true;
    else
        value=false;
}


//Print function for Set class where it would print the target variable and what type of bool it is.
void Set::print() const
{
}

//If class contructor where it is inheriting the string from Pieces class variable
If::If(string line) : Pieces(line)
{
    if(line.find("true")!=string::npos)
        value=true;
    else
        value=false;
}
void If::test() const{}
//Print function for If class where it would print the target variable and what type of bool it is.
void If::print() const
{

    string buffer;
    string target;
    int begin = str.find("$");
    int end = str.find(")");
    if (begin != string::npos && end != string::npos)
    {
        buffer = str.substr(begin, end);
        end = buffer.find(" ");
        target = buffer.substr(0, end);
        if (value)
            cout << "If: var=" << target << ", value=true" << endl;
        else
            cout << "If: var=" << target << ", value=false" << endl;
    }
    else
        throw "Could not find if value";
}

Goto::Goto(string line) : Pieces(line)
{}

void Goto::test() const{}
//A print function for go-to glass where it would print only the value is pointing at.
void Goto::print() const
{
    string buffer;
    int end;
    int begin = str.find(";") + 1;
    if (begin != string::npos)
    {
        buffer = str.substr(begin);
        end = buffer.find("&");
        buffer = buffer.substr(0, end);
        cout << "Go-to: Target=" << buffer << endl;
    }
    else
        throw "Could not find goto value"; //add a try catch later
}

ElseIf::ElseIf(string line) : Pieces(line)
{}

void ElseIf::test() const{}

//Print function for Else-If class where it would print the target variable and what type of bool it is.
void ElseIf::print() const
{
    string buffer;
    string target;
    int begin = str.find("$");
    int end = str.find(")");
    if (begin != string::npos && end != string::npos)
    {
        buffer = str.substr(begin, end);
        end = buffer.find(" ");
        target = buffer.substr(0, end);
        begin = buffer.find("true");
        if (begin != string::npos)
            cout << " Else-if: var=" << target << ", value=true" << endl;
        else
            cout << "Else-if: var=" << target << ", value=false" << endl;
    }
    else
        throw "Could not find if value";
}