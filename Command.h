#ifndef COMMAND_H
#define COMMAND_H
#include "MVC.h"

#include <vector>
#include <string>



//*********************************************************************************************
//create a command/command history interface



class Command
{

public:
    virtual ~Command(){}  
    Command(int x, int y): x(x), y(y) {}
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;

    int GetX() const { return x; }
    int GetY() const { return y; }

protected:
    int x;
    int y;
};



class CommandHistory
{
public:
    CommandHistory();
    virtual ~CommandHistory();

    bool Undo();
    bool Redo();

    void ExecuteCMD(Command * pCmd);
    int GetCurrCMD(){return c_Undo;}

protected:
    //support undo/redo commands
    std::vector<Command *> listCmd;
    std::vector<Command *> undone;
    int c_Undo;

};


//********************************************************************************************




//************************************************************************************



#endif