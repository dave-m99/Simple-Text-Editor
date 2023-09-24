#ifndef CONCRETEOBSERVER_H
#define CONCRETEOBSERVER_H

#include "ECTextViewImp.h"
#include "ECObserver.h"
#include <fstream>
#include "MVC.h"
#include <string>
#include <vector>


//observer that changes the modes

class Observer_Mode: public ECObserver
{

public:
    Observer_Mode(ECTextViewImp &sub, Controller &c): subject(sub), ctrl(c)
    {
        subject.Attach(this);
    }

    ~Observer_Mode(){ subject.Detach(this); }


    //switch between modes
    virtual void Update()
    {
        //switch to edit if i is pressed
        if(subject.GetPressedKey() == 105)
        {
            subject.ClearStatusRows();
            ctrl.ChangeMode(1);

           //update the status bar from the controller to get the proper x and y axis relative to the model
            ctrl.UpdateStatusBar();
            //increment the session number, for undo/redo function
            ctrl.IncSession();
    
        }

        //else if ESC or CTRL A are pressed, change to command mode
        else if(subject.GetPressedKey() == KEY_ACTION::ESC || subject.GetPressedKey() == KEY_ACTION::CTRL_A)
        {
            subject.ClearStatusRows();
            ctrl.ChangeMode(0);
            
            //same as above
            ctrl.UpdateStatusBar();
         
        }
    }



private:
    ECTextViewImp &subject;
    Controller &ctrl;
};



//*************************************************************************************************************************************************
//Observer for redo/undo


class Observer_Command: public ECObserver
{

public:
    Observer_Command(ECTextViewImp &sub, Controller &c): subject(sub), ctrl(c)
    {
        subject.Attach(this);
    }
    ~Observer_Command(){ subject.Detach(this); }


    virtual void Update()
    {
        //ctrl+z is undo, ctrl+y is redo
        if(subject.GetPressedKey() == KEY_ACTION::CTRL_Z)
        {
            ctrl.Undo();
        }

        else if(subject.GetPressedKey() == KEY_ACTION::CTRL_Y)
        {
            ctrl.Redo();
        }
    }
    
private:
    ECTextViewImp &subject;
    Controller &ctrl;
};



//observer for editing 
class Observer_Edit: public ECObserver
{


public:
    Observer_Edit(ECTextViewImp &sub, Controller &c): subject(sub), ctrl(c)
    {
        subject.Attach(this);
    }

    ~Observer_Edit() { subject.Attach(this); }


    virtual void Update()
    {   
        int key = subject.GetPressedKey();
        if(key >= 32 && key <= 126 && ctrl.GetMode())
        {
            char c = static_cast<char> (key);
            ctrl.AddChar(c);
        }
        else if(key == KEY_ACTION::BACKSPACE && ctrl.GetMode())
        {
            ctrl.DeleteChar();
        }
        else if(key == KEY_ACTION::ENTER && ctrl.GetMode())
        {
            ctrl.Enter();
        }
    } 

private:
    ECTextViewImp &subject;
    Controller & ctrl;
};


//CONCRETE OBSERVERS ********************************************************************************
//whenever we hit enter, we start a new row 
//we treat observers as the controller in this case 




class Observer_Cursor: public ECObserver
{

public:
    Observer_Cursor(ECTextViewImp &sub, Controller &c): subject(sub),ctrl(c)
    {
        subject.Attach(this);
    }
    ~Observer_Cursor(){ subject.Detach(this) ;}

    virtual void Update()
    {
        if(subject.GetPressedKey() == KEY_ACTION::ARROW_LEFT){ ctrl.MoveCurLeft(); }
        
        else if(subject.GetPressedKey() == KEY_ACTION::ARROW_RIGHT){ ctrl.MoveCurRight(); }

        else if(subject.GetPressedKey() == KEY_ACTION::ARROW_UP) {ctrl.MoveCurUp();}

        else if(subject.GetPressedKey() == KEY_ACTION::ARROW_DOWN) { ctrl.MoveCurDown(); }
    }

private:
    ECTextViewImp &subject;
    Controller &ctrl;    
};




#endif
