#include "ifinterpreter.h"
#include "storytokenizer.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

IFInterpreter::IFInterpreter(string str)
{
    string story;
    ifstream file(str);
    if (!file.is_open())
    {
        throw "Could not open file";
    }

    getline(file, line);
    while (file && line != "</html>")
    {
        story += line + '\n';
        getline(file, line);
    }
    int x=0;
    StoryTokenizer st(story);

    while (st.hasNextPassage())
    {
        Store* collec = new Store();

        PassageToken ptok = st.nextPassage();
        PassageTokenizer pt(ptok.getText());
        


        while (pt.hasNextPart())
        {

            PartToken stok = pt.nextPart();

            if (stok.getType() == LINK)
            {
                slink = new Link(stok.getText());
                collec->addparts(*slink);
            }
            else if (stok.getType() == BLOCK)
            {
               sblock= new Block(stok.getText());
                collec->addparts(*sblock);
            }
            else if (stok.getType() == TEXT)
            {
                stext=  new Text(stok.getText());
                collec->addparts(*stext);
            }
            else if (stok.getType() == IF)
            {
                sif = new If(stok.getText());
                collec->addparts(*sif);
            }
            else if (stok.getType() == ELSE)
            {
                selse = new Else(stok.getText());
                collec->addparts(*selse);
            }
            else if (stok.getType() == ELSEIF)
            {
                selseif = new ElseIf(stok.getText());
                collec->addparts(*selseif);
            }
            else if (stok.getType() == SET)
            {
                sset = new Set(stok.getText());
                collec->addparts(*sset);
            }
            else if (stok.getType() == GOTO)
            {
                sgoto = new Goto(stok.getText());
                collec->addparts(*sgoto);
            }
        }

        partpassage.push_back(collec);
        passagename.push_back(ptok.getName());
        passage[ptok.getName()]=collec;
    }

}

void IFInterpreter::print()
{
    
     for(int i= 0; i<passagename.size(); i++){
        cout<<"\nPassage "<<passagename[i]<<": "<<endl;
        //partpassage[i]->print();
        passage[passagename[i]]->print();
        
    }

}

IFInterpreter::~IFInterpreter(){
    delete slink;
    delete stext;
    delete sblock;
    delete selse;
    delete selseif;
    delete sgoto;
    delete sset;
}