<<<<<<< HEAD
//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFAboutProg : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFAboutProg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFAboutProg *FAboutProg;
//---------------------------------------------------------------------------
#endif
=======
//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFAboutProg : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFAboutProg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFAboutProg *FAboutProg;
//---------------------------------------------------------------------------
#endif
>>>>>>> 443dcff40d1411906ff5a5c002787e717b2b8aab
