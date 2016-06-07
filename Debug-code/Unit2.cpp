<<<<<<< HEAD
// ----------- Unit2 создание окна о программе ----------
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"                                       
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFAboutProg *FAboutProg;
//---------------------------------------------------------------------------
__fastcall TFAboutProg::TFAboutProg(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFAboutProg::FormClose(TObject *Sender,
      TCloseAction &Action)
{
     UserForm->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFAboutProg::FormCreate(TObject *Sender)
{
  Position=poScreenCenter;
}
//---------------------------------------------------------------------------

=======
// ----------- Unit2 создание окна о программе ----------
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"                                       
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFAboutProg *FAboutProg;
//---------------------------------------------------------------------------
__fastcall TFAboutProg::TFAboutProg(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFAboutProg::FormClose(TObject *Sender,
      TCloseAction &Action)
{
     UserForm->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TFAboutProg::FormCreate(TObject *Sender)
{
  Position=poScreenCenter;
}
//---------------------------------------------------------------------------

>>>>>>> 443dcff40d1411906ff5a5c002787e717b2b8aab
