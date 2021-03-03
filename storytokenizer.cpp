#include <string>
#include <sstream>
#include <vector>
#include "storytokenizer.h"
#include"ifinterpreter.h"

//Member functions and contructor for StorytoKenizer class

/**
 * This function will loop through our tPassage string to see if there
 * is a passage with the keyword "<tw-passagedata " and if it cannot find such
 * keyword return a false flag back to main driver
 * it will also create a substring starting at the key word until the reaching
 * the keyword "</tw-passagedata>"
*/
bool StoryTokenizer::hasNextPassage()
{

    string kword("<tw-passagedata");
    unsigned loc = tPassage.find(kword);

    if (loc != string::npos)
    {
        tPassage = tPassage.substr(loc);
        return true;
    }

    if (loc == string::npos)
    {
        return false;
    }
}

/**
 * 
 * This function will take the substring created from hasNextPassage function
 * and parse through it to find keywords such as name and the text body
 * later on return the found keyword to Passagetoken constructor
*/
PassageToken StoryTokenizer::nextPassage()
{

    string name;
    string text;

    tempv = tPassage.find("name=") + 6;

    while (tPassage.at(tempv) != '\"')
    {
        name += tPassage.at(tempv);
        tempv++;
    }

    tempv = tPassage.find(">") + 1;
    endingv = tPassage.find("</tw-passagedata>");

    while (tempv != endingv)
    {
        text += tPassage.at(tempv);
        tempv++;
    }

    tPassage = tPassage.substr(endingv);
    return PassageToken(name, text);
}

/**
 * Contructor for Storytokenizer class that takes a string as a parameter
 * */
StoryTokenizer::StoryTokenizer(string str)
{
    tPassage = str;
}

/**
 * Return pName which contains the name of the passage
*/
string PassageToken::getName() const
{
    return pName;
}

/**
 * Return pText which contains the body tex of the passage
 */
string PassageToken::getText() const
{
    return pText;
}

/**
 * contructor for PassageToken class that when called will assign the 
 * name of the passage to pNam and pText with the passage body text
 * */
PassageToken::PassageToken(string name, string text)
{
    pName = name;
    pText = text;
}

/**
 * 
 * 
 * PART 2
 * 
 * 
 * 
*/

/** 
 * Contructor that will assing the text line from PassageToken
 * */
PassageTokenizer::PassageTokenizer(string text)
{
    passage = text;
}

/**
 * Functions that will parse through the text saved in PassageTokenizer 
 * and return an object to PartToken.
*/
PartToken PassageTokenizer::nextPart()
{
    unsigned int endloc;
    unsigned int count;
    unsigned int startpos = 0;
    parts.clear();

/**
 * If statement that find the first position in passage when it is 
 * a '[' character and start testing wether or not it is a block or
 * links.
**/
    if (passage.find("[") == startpos)
    {

    /**
     * An if statement that finds wether or not '[[' is located in at the 
     * starting position. When found, the ending location will be found
     * and proceed to start a loop through it until reaching the last position 
     * */
        if (passage.find("[[") == startpos)
        {

            endloc = passage.find("]]") + 2;

            while (startpos != endloc)
            {
                parts += passage[startpos];
                startpos++;
            }

            passage = passage.substr(startpos);
            return PartToken(parts, LINK);
        }
    /**
     * whenthe if statement fails the else statement will proceed to copied the 
     * the string as a blocks.
     * 
     * */
        else
        {
            count = 1;
            while (count != 0)
            {

                if (passage[startpos] == ']')
                    count--;

                parts += passage[startpos];
                startpos++;

                if (passage[startpos] == '[')
                    count++;
            }

            passage = passage.substr(startpos);
            return PartToken(parts, BLOCK);
        }
    }

    /**
     * Second if statement that test wether or not a command is found in the 
     * starting position. When found it will find the ending position of it
     * and store each character to parts. Later on it will test which command
     * link is found and return it as a object corresponding with the 
     * command it has.
     * */
    else if (passage.find("(set:") == startpos || passage.find("(else:") == startpos || passage.find("(else-if:") == startpos || passage.find("(go-to:") == startpos || passage.find("(if:") == startpos)
    {

        endloc = passage.find(")") + 1;
        while (startpos != endloc)
        {
            parts += passage[startpos];
            startpos++;
        }

        passage = passage.substr(startpos);
        if (parts.find("set:") != string::npos)
            return PartToken(parts, SET);

        if (parts.find("if:") != string::npos)
            return PartToken(parts, IF);

        if (parts.find("else:") != string::npos)
            return PartToken(parts, ELSE);

        if (parts.find("else-if:") != string::npos)
            return PartToken(parts, ELSEIF);

        if (parts.find("go-to:") != string::npos)
            return PartToken(parts, GOTO);
    }
    /**
     * Third if statement test wether or not a command, link, and a block is not found in the passage 
     * when not found it would proceed to take the passage. past it to parts and return parts as a text 
     * */
    else if (passage.find("[[") == string::npos && passage.find("(set") == string::npos && passage.find("(if") == string::npos && passage.find("(else-if") == string::npos && passage.find("(go-to") == string::npos && passage.find("(else") == string::npos)
    {
        while (passage[startpos] != '\0')
        {
            parts += passage[startpos];
            startpos++;
        }
        passage = passage.substr(startpos);
        return PartToken(parts, TEXT);
    }
    /**
     * When all if statetment fail proceed to each character in passage to parts while 
     * each reading character does not compare to a link, command, and block
    */
    else
    {

        while (startpos != passage.find("[[") && startpos != passage.find("(set:") && startpos != passage.find("(if:") && startpos != passage.find("(else") && startpos != passage.find("(else-if:") && startpos != passage.find("(go-to:"))
        {
            parts += passage[startpos];
            startpos++;
        }

        passage = passage.substr(startpos);
        return PartToken(parts, TEXT);
    }
}

//constructor that assing the text line from PassageToken to
PartToken::PartToken(string parts, type command)
{
    tpart = parts;
    tType = command;
}

//Functions that return the first type inside the passage
type PartToken::getType() const
{
    return tType;
}

//Functions that return the body text that related to the type
string PartToken::getText() const
{
    return tpart;
}

//function test if the passage save in PassageTokenizer contains more
// text.
bool PassageTokenizer::hasNextPart()
{
    if (passage != "\0")
    {
        return true;
    }
    else
    {
        return false;
    }
}