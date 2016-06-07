//---------------------------------------------------------------------------

#include <vcl.h>
#include <fstream.h>
#include "iostream.h"
#pragma hdrstop

#include "Unit1.h" // подкючение классов TUserForm, TCell, TGameMatrix реализующих логику игры
#include "Unit2.h" // подключение класса "О программе"
#include "Unit3.h" // подключение класса "Справка"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TUserForm *UserForm; // создание объекта игрового поля (UI)
typedef TCell (*TPtrFuncFromDLL)(int,int**,int,int,int,int,int);  // создание своего типа
HINSTANCE  PtrToDLL;
TPtrFuncFromDLL AIFunction;//переменная создаданного типа, загружаемый ИИ
const int CellSize=50;
const int FSize=500;
TPicture *PZero,*PCross;
TRect Source,Dest;
TGameMatrix MatrixBoard; // создание объекта отвечающего за логику

//---------------------------------------------------------------------------
__fastcall TUserForm::TUserForm(TComponent* Owner)
        : TForm(Owner)
{
   IsComputer=false; // по умолчанию второй игрок тоже пользователь
}
//---------------------------------------------------------------------------
/****************************************************************************
 *               Создаем игровое поле                                       *
*****************************************************************************/
void TUserForm::ToNormLabelLocation(void)
{
   SocerBoard->Left=ImField->Left+(ImField->Width - SocerBoard->Width)/2;
}
//---------------------------------------------------------------------------
void TUserForm::NetGame(void)
{

   if(MtgSea->Checked==true)
   {
     ImField->Picture->LoadFromFile("Темы игры/Океан4.bmp");
     PZero->LoadFromFile("Темы игры/Морской еж1.bmp");
     PZero->Graphic->Transparent=true;
     PCross->LoadFromFile("Темы игры/морская звезда1.bmp");
     PCross->Graphic->Transparent=true;
     SocerBoard->Font->Color=clWhite;
   }
   else if(MtgFootball->Checked==true)
   {
     ImField->Picture->LoadFromFile("Темы игры/газон1.bmp");
     PZero->LoadFromFile("Темы игры/Мяч.bmp");
     PZero->Graphic->Transparent=true;
     PCross->LoadFromFile("Темы игры/Биты2.bmp");
     PCross->Graphic->Transparent=true;
     SocerBoard->Font->Color=clYellow;
     
   }
   ImField->Canvas->Pen->Color=clWhite;
   ImField->Canvas->Pen->Width=2;
   for(int i=0;i<=FSize;i+=CellSize)
   {
      ImField->Canvas->MoveTo(i,0);
      ImField->Canvas->LineTo(i,FSize);
   }
   for(int i=0;i<=FSize;i+=CellSize)
   {
      ImField->Canvas->MoveTo(0,i);
      ImField->Canvas->LineTo(FSize,i);
   }

}
//--------------------------------------------------------------------------
void TUserForm::ToPaint(void)
{

   int n=MatrixBoard.N;
   for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
      {
         if(MatrixBoard.GetElement(i,j)==MatrixBoard.GetZero())
            ImField->Canvas->Draw(i*CellSize,j*CellSize,PZero->Graphic);
        else if (MatrixBoard.GetElement(i,j)==MatrixBoard.GetCross())
             ImField->Canvas->Draw(i*CellSize,j*CellSize,PCross->Graphic);

      }
      DrawLine();
}
//---------------------------------------------------------------------------
void __fastcall TUserForm::MExitClick(TObject *Sender)
{
   Close();        
}
//---------------------------------------------------------------------------

void __fastcall TUserForm::FormCreate(TObject *Sender)
{
   DoubleBuffered=true;
   Left=(Screen->Width-Width)/2;// центральное положение формы
   Top=(Screen->Height-Height)/2;
   ClientHeight=FSize+60;
   ClientWidth=FSize+60;
   ImField->Height=FSize;
   ImField->Width=FSize;
   ImField->Top=30;
   ImField->Left=30;
   PZero=new TPicture();
   PCross=new TPicture();
   IBoder->Canvas->Brush->Color=clBlack;
   IBoder->Canvas->FloodFill(0,0,clWhite,fsSurface);

   NetGame();
}
//---------------------------------------------------------------------------

void __fastcall TUserForm::MAboutProgramClick(TObject *Sender)
{
   FAboutProg->Show();
   UserForm->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TUserForm::ImFieldMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
                                                  
   int MX,MY;
   MX=X/CellSize;
   MY=Y/CellSize;
   if(MatrixBoard.PossibleMotion(MX,MY))
   {
     if((Shift.Contains(ssLeft)==true)&&(Shift.Contains(ssRight)==false))
     {
        if(!MatrixBoard.IsNextCross())
        {
           if(!IsComputer)
           {
             MatrixBoard.SetElement(MX,MY,MatrixBoard.GetZero());
             ImField->Canvas->Draw(MX*CellSize,MY*CellSize,PZero->Graphic);
             SocerBoard->Caption="Ход: крестика";
             ToNormLabelLocation();
           }
           else goto m;
        }

       else
        {
        m: MatrixBoard.SetElement(MX,MY,MatrixBoard.GetCross());
           ImField->Canvas->Draw(MX*CellSize,MY*CellSize,PCross->Graphic);
           SocerBoard->Caption="Ход: нолика";
           ToNormLabelLocation();
           IFSomeoneWin(MX,MY);

           if((IsComputer)&&(ImField->Enabled==true))
           {
             TCell Choise=AIFunction(MatrixBoard.GetZero(),MatrixBoard.GMatrix,MatrixBoard.N,MatrixBoard.win_number,MatrixBoard.GetCross(),MatrixBoard.GetZero(),MatrixBoard.count_of_free);
             MX=Choise.x;
             MY=Choise.y;
             MatrixBoard.SetElement(MX,MY,MatrixBoard.GetZero());
             ImField->Canvas->Draw(MX*CellSize,MY*CellSize,PZero->Graphic);
             SocerBoard->Caption="Ход: крестика";
             ToNormLabelLocation();
           }
        }
        IFSomeoneWin(MX,MY);
     }
   }
}
//---------------------------------------------------------------------------
void TUserForm::DrawLine(void)
{
       if(MatrixBoard.BegPoint.value==0)
          return;
       ImField->Canvas->Pen->Color=clBlue;
       ImField->Canvas->Pen->Width=3;
       TCell MBeg,MEnd;
       MBeg.ToSetAll(MatrixBoard.BegPoint.x*CellSize,MatrixBoard.BegPoint.y*CellSize,0);
       MEnd.ToSetAll(MatrixBoard.EndPoint.x*CellSize,MatrixBoard.EndPoint.y*CellSize,0);
       int direct=MatrixBoard.BegPoint.value;
       switch(direct)
       {
         case 1:
         {
            MBeg.y=MBeg.y+CellSize/2;
            MEnd.x=MEnd.x+CellSize;
            MEnd.y=MEnd.y+CellSize/2;
            break;
         }
         case 2:
         {
            MBeg.x=MBeg.x+CellSize/2;
            MEnd.x= MEnd.x+CellSize/2;
            MEnd.y=MEnd.y+CellSize;
            break;
         }
         case 3:
         {
            MEnd.x= MEnd.x+CellSize;
            MEnd.y=MEnd.y+CellSize;
            break;
         }
         case 4:
         {
            MBeg.y=MBeg.y+CellSize;
            MEnd.x=MEnd.x+CellSize;


            break;
         }
       }
       ImField->Canvas->MoveTo(MBeg.x,MBeg.y);
       ImField->Canvas->LineTo(MEnd.x,MEnd.y);

}
//---------------------------------------------------------------------------
void TUserForm::IFSomeoneWin(int MX,int MY)
{
    if(MatrixBoard.GetElement(MX,MY)==MatrixBoard.IsWinner(MX,MY,MatrixBoard.GetZero())\
    ||MatrixBoard.GetElement(MX,MY)==MatrixBoard.IsWinner(MX,MY,MatrixBoard.GetCross())\
    &&(ImField->Enabled==true))
   {
       AnsiString Con="Выиграли";
       if(MatrixBoard.GetElement(MX,MY)==MatrixBoard.GetCross())
           Con+=" крестики";
       else Con+=" нолики";
       Application->MessageBoxA(Con.c_str(),"Win",MB_OK);
       ImField->Enabled=false;
       Con+=". Game over.";
       SocerBoard->Caption=Con;
       ToNormLabelLocation();
       DrawLine();
   }
   else if(MatrixBoard.IsFull())
      Application->MessageBoxA("Мир"," Ничья ",MB_OK);
}

//---------------------------------------------------------------------------
void __fastcall TUserForm::FormDestroy(TObject *Sender)
{
  PZero->Free();
  PCross->Free();
}
//---------------------------------------------------------------------------


void __fastcall TUserForm::MAboutRulesClick(TObject *Sender)
{
    FormHelp->Show();
    UserForm->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TUserForm::MtgSeaClick(TObject *Sender)
{

   MtgSea->Checked=true;
   NetGame();
   ToPaint();
}
//---------------------------------------------------------------------------

void __fastcall TUserForm::MtgFootballClick(TObject *Sender)
{
   MtgFootball->Checked=true;
   NetGame();
   ToPaint();
}
//---------------------------------------------------------------------------

void __fastcall TUserForm::NGUserClick(TObject *Sender)
{
    NGUser->Checked=true;
    MatrixBoard.Reset();
    ImField->Enabled=true;
    if(PtrToDLL!=NULL)
       FreeLibrary(PtrToDLL);
    NetGame();
    ToPaint();
    SocerBoard->Caption="Ход: крестика";
    ToNormLabelLocation();
    IsComputer=false;

}
//---------------------------------------------------------------------------

void __fastcall TUserForm::NGKompClick(TObject *Sender)
{

   NGKomp->Checked=true;
   MatrixBoard.Reset();
   ImField->Enabled=true;
   PtrToDLL=NULL;
   if(PtrToDLL==NULL)
   {  AnsiString WayToDLL=GetCurrentDir()+"\\DLL\\MyDLL.dll";
      PtrToDLL=LoadLibrary(WayToDLL.c_str()); //загружаем DLL
      if(PtrToDLL==NULL)
         Application->MessageBoxA("Невозможно загрузить DLL","Ошибка",MB_OK+MB_ICONERROR);
      AIFunction =(TPtrFuncFromDLL)GetProcAddress(PtrToDLL,"_AnalyseMove");
      if(AIFunction==NULL)
        Application->MessageBoxA("Функция не существует","Ошибка",MB_OK+MB_ICONERROR);
   }

   NetGame();
   ToPaint();
   SocerBoard->Caption="Ход: крестика";
   ToNormLabelLocation();
   IsComputer=true;
}
//---------------------------------------------------------------------------

void __fastcall TUserForm::MSaveClick(TObject *Sender)
{
  if(MatrixBoard.BegPoint.value!=0)
  {
    Application->MessageBoxA("Игра окончена","Нет смысла сохранять",MB_OK+MB_ICONWARNING);
    return;
  }
  SaveDialog1->InitialDir=GetCurrentDir()+"\\Сохраненные игры";
  SaveDialog1->Title="Сохранение сеанса игры";
  SaveDialog1->DefaultExt="*.crz";
  AnsiString MyFileName="Игра 0";
  SaveDialog1->FileName=MyFileName;

  if(SaveDialog1->Execute())
  {
    MyFileName=SaveDialog1->FileName;
    ofstream SWrite (MyFileName.c_str());
    SWrite<<MatrixBoard.IsNextCross()<<endl;
    for(int i=0;i<MatrixBoard.N;i++)
    {
       for(int j=0;j<MatrixBoard.N;j++)
         SWrite<<MatrixBoard.GetElement(i,j)<<" ";   // транспонируемa
       SWrite<<endl;
    }
    SWrite.close();

  }


}
//---------------------------------------------------------------------------

void __fastcall TUserForm::MLoadClick(TObject *Sender)
{
   OpenDialog1->InitialDir=GetCurrentDir()+"\\Сохраненные игры";
   OpenDialog1->Title="Загрузка сеанса игры";
   OpenDialog1->DefaultExt="*.crz";
   AnsiString MyFileName="Игра 0";
   OpenDialog1->FileName=MyFileName;
   if(OpenDialog1->Execute())
   {
      MyFileName=OpenDialog1->FileName;
      ifstream FRead(MyFileName.c_str());

      bool pr;
      MatrixBoard.Reset();
      int z=1;
      int i=0;
      char str[255];
      AnsiString Stroka,Dop;
      while(FRead.getline(str,255)!=0)
      {
        Stroka=str;
        Stroka=Stroka.Trim();
        if(z==1)
        {
          pr=StrToInt(Stroka);
          MatrixBoard.SetIsNextCross(pr);
          if(pr==true)
             SocerBoard->Caption="Ход: крестика";
          else SocerBoard->Caption="Ход: нолика";

        }
        else
        {
          int j=0,vh;
          Stroka=Stroka+" ";
          vh=Stroka.Pos(" ");
          while(vh!=0)
          {
            Dop=Stroka.SubString(1,vh-1);
            int el=Dop.ToInt();
            MatrixBoard.SetElement(j,i,el);
            Stroka.Delete(1,vh);
            vh=Stroka.Pos(" ");
            j++;
          }
          i++;

        }
        z++;
      }
       FRead.close();
   }
    ImField->Enabled=true;
    NetGame();
    ToPaint();
    ToNormLabelLocation();



}
//---------------------------------------------------------------------------

