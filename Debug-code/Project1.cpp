// ------ Project1 - главный модуль, создающий игровую среду     ----------
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", UserForm); // форма игрового поля
USEFORM("Unit2.cpp", FAboutProg); // форма окна о программе
USEFORM("Unit3.cpp", FormHelp); // форма окна справки
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TUserForm), &UserForm);
                 Application->CreateForm(__classid(TFAboutProg), &FAboutProg);
                 Application->CreateForm(__classid(TFormHelp), &FormHelp);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
