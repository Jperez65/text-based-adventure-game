#ifndef __STORYTOKENIZER_H
#define __STORYTOKENIZER_H
#include<string>
#include"ifinterpreter.h"

using namespace std;
enum type{LINK, SET, GOTO, IF, ELSEIF, ELSE, BLOCK, TEXT};

class PartToken{
    private:
        int level;
        type tType;
        string tpart;
    public:
        PartToken(string, type);
        string getText() const;
        type getType()const;
};
class PassageTokenizer{
    private:
        string passage;
        string parts;
        bool button=false;
        
    public:
        PassageTokenizer(string);
        PartToken nextPart();
        bool hasNextPart();
};

class PassageToken{
    public:
        string getName() const;
        string getText() const;
        PassageToken(string, string);
    private:
        string pName;
        string pText;
};

class StoryTokenizer{
    public:
        bool hasNextPassage();
        PassageToken nextPassage();
        StoryTokenizer(string);
    private:
    string tPassage;
    int loc;
    int tempv;
    int endingv;


};

#endif