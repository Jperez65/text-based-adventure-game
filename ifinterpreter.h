#ifndef __IFINTERPRETER__H
#define __IFINTERPRETER__H
#include"storytokenizer.h"
#include"unordered_map"
//#include"store.h"
#include<vector>
#include<string>
#include<stack>
#include"map"

using namespace std;
class Store;
class Pieces;



class Store {
    private:
    vector<Pieces*> parts;
    //vector<Test> parts;
    public:
    Store();  //Default constructor
    Store(vector<Pieces*>&); //Contructor with vectors
    void addparts(Pieces&);
    void print();
    void getSize();
    int static_global;
    
};


class Pieces {
    protected:
    string str;
    public:
    //Pieces();
    Pieces(string line): str(line) {};
    virtual string getLine()const final { return str; }
    virtual void test() const =0;
    virtual void print() const =0;
};

class Text: public Pieces{
    public:
    Text(string);
    virtual void print() const override;
    virtual void test() const override;
};

class Link: public Pieces{
    private:
    string name;
    bool indicator;
    public: 
    Link(string);
    virtual void print() const override;
    virtual void test() const override;
    //string getLink();
};

class Else: public Pieces{
    public:
    Else(string);
    virtual void print() const override;
    virtual void test() const override;
    //bool vcheck(string, unordered_map<string, bool>);
};

class Block: public Pieces{
    public:
    Block(string);
    void searchblock(string, unsigned int);
    virtual void test() const override;
    virtual void print() const override;
};

class Set: public Pieces{
    private:
    string name;
    bool value;

    public:
    Set(string);
    virtual void test() const override;
    virtual void print() const override;
    //add function to set up boolean value of set to condition
};

class If: public Pieces{
    private:
    string name;
    bool value;

    public:
    If(string);
   // bool v1check(string, unordered_map<string, bool>); //change name later
    virtual void print() const override;
    virtual void test() const override;
};

class Goto: public Pieces{
    private:
    string name;
    
    public: 
    Goto(string);
    //string direction();
    virtual void print() const override;
    virtual void test() const override;
    //add function to set up boolean vlaue of set to condition
};

class ElseIf: public Pieces{
    private:
    string name;    
    bool value;

    public:
    ElseIf(string);
    //bool v2check(string, unordered_map<string, bool>);//change name later
    virtual void print() const override;
    virtual void test() const override;
    //add function to set up boolean value to condition unorder map
};

class IFInterpreter{
    private:
    string line;
    //Store collec;
    vector<Store*> partpassage;
    vector<string> passagename;

    Link* slink;
    Text* stext;
    Block* sblock;
    If* sif;
    Else* selse;
    ElseIf* selseif;
    Goto* sgoto;
    Set* sset;
    map<string, Store*> passage;

    protected:
   // unordered_map<string, Store*> passage;
    unordered_map<string, bool> condition;
    public:
    IFInterpreter(string);
    //IFInterpreter(const IFInterpreter& copy);
    //IFInterpreter(IFInterpreter&& move);
    //IFInterpreter& operator=(IFInterpreter&&);
   // IFInterpreter& operator=(IFInterpreter&);
    void print();
    void play();
    ~IFInterpreter();
};


#endif