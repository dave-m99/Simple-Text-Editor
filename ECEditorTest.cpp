// Test code for editor
#include "ECTextViewImp.h"
#include "ConcreteObserver.h"
#include "MVC.h"
#include <iostream>
#include <fstream>

using namespace  std;

int myCounter = 0;

int main(int argc, char *argv[])
{
    if(argc > 2)
    {
      throw std::string("Too many arguments given!");
      exit(0);
    }


    ECTextViewImp wndTest;
    std::string name = "";
    if(argc == 2)
    {
      name = argv[1];
    }
    Model model(name);
    //model takes reads from givene file 
    model.ReadFile();

    Controller ctr(model, wndTest); 
    //cursor observers and edit observers
    Observer_Cursor cursor(wndTest, ctr);
    Observer_Edit edit(wndTest, ctr);

    //observer for command mode to be able to do redo/undo
    Observer_Command command(wndTest, ctr);

    //observer to change modes
    Observer_Mode mode(wndTest, ctr);

    
    //add to the view
    ctr.AddView();

    std::string msg = "Current Mode: Command    ";
    msg += "Column = ";
    msg+= std::to_string(wndTest.GetCursorX());
    msg+= ", Row = ";
    msg+= std::to_string(wndTest.GetCursorY());

    wndTest.AddStatusRow(msg, "Press i for Edit Mode", true);

  
    wndTest.Show();

    return 0;
}
