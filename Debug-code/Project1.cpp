// ------ Project1 - ������� ������, ��������� ������� �����     ----------
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", UserForm); // ����� �������� ����
USEFORM("Unit2.cpp", FAboutProg); // ����� ���� � ���������
USEFORM("Unit3.cpp", FormHelp); // ����� ���� �������
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
