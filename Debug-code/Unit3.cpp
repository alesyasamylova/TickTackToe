//---- Unit3 �������� ���� ������� -----------
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormHelp *FormHelp;
//---------------------------------------------------------------------------
__fastcall TFormHelp::TFormHelp(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormHelp::FormClose(TObject *Sender, TCloseAction &Action)
{
    UserForm->Enabled=true;
}
//---------------------------------------------------------------------------



