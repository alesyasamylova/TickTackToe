<<<<<<< HEAD
//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <ActnList.hpp>
#include <ActnCtrls.hpp>
#include <ActnMan.hpp>
#include <ToolWin.hpp>
#include "math.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
//-- TUserForm  - класс, реализующий пользовательский интерфейс
//---------------------------------------------------------------------------

class TUserForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *MGame;
        TMenuItem *MOptions;
        TMenuItem *MHelp;
        TMenuItem *MNewGame;
        TMenuItem *MExit;
        TMenuItem *MAboutRules;
        TMenuItem *MAboutProgram;
        TMenuItem *MTopicGame;
        TMenuItem *MSave;
        TMenuItem *MLoad;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TImage *ImField;
        TImage *IBoder;
        TMenuItem *MtgSea;
        TMenuItem *MtgFootball;
  TLabel *SocerBoard;
  TMenuItem *NGKomp;
  TMenuItem *NGUser;
  TSaveDialog *SaveDialog1;
  TOpenDialog *OpenDialog1;
        void __fastcall MExitClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall MAboutProgramClick(TObject *Sender);
        void __fastcall ImFieldMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall MAboutRulesClick(TObject *Sender);
        void __fastcall MtgSeaClick(TObject *Sender);
        void __fastcall MtgFootballClick(TObject *Sender);
  void __fastcall NGUserClick(TObject *Sender);
  void __fastcall NGKompClick(TObject *Sender);
  void __fastcall MSaveClick(TObject *Sender);
  void __fastcall MLoadClick(TObject *Sender);
private:	// User declarations
public:
	void NetGame(void);
  void ToPaint(void);
  void ToNormLabelLocation(void);
  void DrawLine (void);
  bool IsComputer;
  void IFSomeoneWin(int MX,int MY);// функци€ проверки и приветстви€ победител€
        __fastcall TUserForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TUserForm *UserForm;

//---------------------------------------------------------------------------
//-----  TCell Цкласс €чейки, содержит пол€ x, y и value --------------------
//---------------------------------------------------------------------------
class TCell
{
public:
   int x,y,value;
   TCell()
   {
      randomize();
      x=random(10);
      y=random(10);
      value=0;
   }
   void ToSetAll(int i,int j,int val)
   {
     x=i;
     y=j;
     value=val;
   }

};
//---------------------------------------------------------------------------
//-- TMatrixGame - класс, описывающий логику игры
//---------------------------------------------------------------------------
class TGameMatrix
{
private:

    const int cross,zero,vacant; //vacant -пустой
    bool is_next_cross;
public:
    int  **GMatrix;
    const int N;   // размер пол€
    const int win_number;
    int count_of_free;
    TCell BegPoint,EndPoint; //выигрышные точки
    TGameMatrix():N(10),cross(1),zero(2),vacant(0),win_number(5)
    {
       GMatrix=new int*[N];
       for (int i=0;i<N;i++)
       {
          GMatrix[i]=new int[N];
          for(int j=0;j<N;j++)
             GMatrix[i][j]=vacant;
       }
       is_next_cross=true;
       count_of_free=N*N;
       BegPoint.ToSetAll(-1,-1,-1);
       EndPoint.ToSetAll(-1,-1,-1);// пока нет выигрышной линии
    }
    ~TGameMatrix()
    {
      for(int i=0;i<N;i++)
        delete[]GMatrix[i];
      delete[]GMatrix;
    }
    void SetElement(int x,int y,const int symbol)
    {
       if((x<N)&&(y<N))
       {
          switch(symbol)
          {
          case 1 : GMatrix[x][y]=cross; is_next_cross=false;count_of_free--; break;
          case 2:  GMatrix[x][y]=zero;is_next_cross=true;count_of_free--; break;
          default: GMatrix[x][y]=vacant;break;
          }
       }
    }
    int GetElement( int x,int y)
    {
        if((x<N)&&(y<N))
           return GMatrix[x][y];
        return -1;
    }
    int GetZero()
    {
      return zero;
    }
    int GetCross()
    {
      return cross;
    }
    int f_empty ()
    {
       return vacant;
    }
    bool IsFull()
    {
       if(count_of_free!=0)
           return false;
       return true;
    }
    bool PossibleMotion(int x,int y)
    {
       int El=GetElement(x,y);
       if(El==vacant)
          return true;
       return false;
    }
    void Reset ()
    {
      for (int i=0;i<N;i++)
          for(int j=0;j<N;j++)
             GMatrix[i][j]=vacant;
      is_next_cross=true;
      count_of_free=N*N;
      BegPoint.ToSetAll(-1,-1,-1);
      EndPoint.ToSetAll(-1,-1,-1);
    }
    bool IsNextCross()
    {
        return is_next_cross;
    }
    void SetIsNextCross(bool pr)
    {
        is_next_cross=pr;
    }
    int IsWinner(int x,int y,int symbol)
    {
       int ccount=0;// количество  идущих подр€д символов данного типа
       int dlcount=0;// по левой диагонали
       int drcount=0;// по правой диагонали
       for(int i=x-win_number;i<x+win_number;i++)
       {
           if((i>=0)&&(i<N))
           {
             if(GMatrix[i][y]==symbol)
             {
                if(ccount==0)
                  BegPoint.ToSetAll(i,y,1);
                ccount++;
                if(ccount==win_number)
                {
                    EndPoint.ToSetAll(i,y,1);
                    return symbol;
                }
             }
             else
             {
               ccount=0;
               BegPoint.ToSetAll(-1,-1,0);
             }
           }
       }
       ccount=0;
       for(int j=y-win_number;j<y+win_number;j++)
       {
          if((j>=0)&&(j<N))
          {
             if(GMatrix[x][j]==symbol)
             {
                 if(ccount==0)
                  BegPoint.ToSetAll(x,j,2);
                 ccount++;
                 if(ccount==win_number)
                 {
                    EndPoint.ToSetAll(x,j,2);
                    return symbol;
                 }
             }
             else
             {
                ccount=0;
                BegPoint.ToSetAll(-1,-1,0);
             }
          }
       }

       int i,j,r;
       i=x-win_number;
       j=y-win_number;
       r=y+win_number;
       TCell BegDiag1;
       BegDiag1.ToSetAll(-1,-1,0);
       int k=0;
       int control=2*win_number;
       while(k<control)
       {
          if((i+k>=0)&&(i+k<N)&&(j+k>=0)&&(j+k<N))
          {
              if(GMatrix[i+k][j+k]==symbol)
              {
                    if(dlcount==0)
                       BegDiag1.ToSetAll(i+k,j+k,3);
                    dlcount++;
                    if(dlcount==win_number)
                    {
                       BegPoint=BegDiag1;
                       EndPoint.ToSetAll(i+k,j+k,3);
                       return symbol;
                    }
              }
              else
              {
                  dlcount=0;
                  BegDiag1.ToSetAll(-1,-1,0);
              }
          }
          if((i+k>=0)&&(i+k<N)&&(r-k>=0)&&(r-k<N))
          {
              if(GMatrix[i+k][r-k]==symbol)
              {
                  if(drcount==0)
                    BegPoint.ToSetAll(i+k,r-k,4);
                  drcount++;
                  if(drcount==win_number)
                  {
                     EndPoint.ToSetAll(i+k,r-k,4);
                     return symbol;
                  }
              }
              else
              {
                drcount=0;
                BegPoint.ToSetAll(-1,-1,0);
              }
          }
          k++;
       }
       return -1;

    }

};
#endif
=======
//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <ActnList.hpp>
#include <ActnCtrls.hpp>
#include <ActnMan.hpp>
#include <ToolWin.hpp>
#include "math.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
//-- TUserForm  - класс, реализующий пользовательский интерфейс
//---------------------------------------------------------------------------

class TUserForm : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *MGame;
        TMenuItem *MOptions;
        TMenuItem *MHelp;
        TMenuItem *MNewGame;
        TMenuItem *MExit;
        TMenuItem *MAboutRules;
        TMenuItem *MAboutProgram;
        TMenuItem *MTopicGame;
        TMenuItem *MSave;
        TMenuItem *MLoad;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TImage *ImField;
        TImage *IBoder;
        TMenuItem *MtgSea;
        TMenuItem *MtgFootball;
  TLabel *SocerBoard;
  TMenuItem *NGKomp;
  TMenuItem *NGUser;
  TSaveDialog *SaveDialog1;
  TOpenDialog *OpenDialog1;
        void __fastcall MExitClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall MAboutProgramClick(TObject *Sender);
        void __fastcall ImFieldMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall MAboutRulesClick(TObject *Sender);
        void __fastcall MtgSeaClick(TObject *Sender);
        void __fastcall MtgFootballClick(TObject *Sender);
  void __fastcall NGUserClick(TObject *Sender);
  void __fastcall NGKompClick(TObject *Sender);
  void __fastcall MSaveClick(TObject *Sender);
  void __fastcall MLoadClick(TObject *Sender);
private:	// User declarations
public:
	void NetGame(void);
  void ToPaint(void);
  void ToNormLabelLocation(void);
  void DrawLine (void);
  bool IsComputer;
  void IFSomeoneWin(int MX,int MY);// функци€ проверки и приветстви€ победител€
        __fastcall TUserForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TUserForm *UserForm;

//---------------------------------------------------------------------------
//-----  TCell Цкласс €чейки, содержит пол€ x, y и value --------------------
//---------------------------------------------------------------------------
class TCell
{
public:
   int x,y,value;
   TCell()
   {
      randomize();
      x=random(10);
      y=random(10);
      value=0;
   }
   void ToSetAll(int i,int j,int val)
   {
     x=i;
     y=j;
     value=val;
   }

};
//---------------------------------------------------------------------------
//-- TMatrixGame - класс, описывающий логику игры
//---------------------------------------------------------------------------
class TGameMatrix
{
private:

    const int cross,zero,vacant; //vacant -пустой
    bool is_next_cross;
public:
    int  **GMatrix;
    const int N;   // размер пол€
    const int win_number;
    int count_of_free;
    TCell BegPoint,EndPoint; //выигрышные точки
    TGameMatrix():N(10),cross(1),zero(2),vacant(0),win_number(5)
    {
       GMatrix=new int*[N];
       for (int i=0;i<N;i++)
       {
          GMatrix[i]=new int[N];
          for(int j=0;j<N;j++)
             GMatrix[i][j]=vacant;
       }
       is_next_cross=true;
       count_of_free=N*N;
       BegPoint.ToSetAll(-1,-1,-1);
       EndPoint.ToSetAll(-1,-1,-1);// пока нет выигрышной линии
    }
    ~TGameMatrix()
    {
      for(int i=0;i<N;i++)
        delete[]GMatrix[i];
      delete[]GMatrix;
    }
    void SetElement(int x,int y,const int symbol)
    {
       if((x<N)&&(y<N))
       {
          switch(symbol)
          {
          case 1 : GMatrix[x][y]=cross; is_next_cross=false;count_of_free--; break;
          case 2:  GMatrix[x][y]=zero;is_next_cross=true;count_of_free--; break;
          default: GMatrix[x][y]=vacant;break;
          }
       }
    }
    int GetElement( int x,int y)
    {
        if((x<N)&&(y<N))
           return GMatrix[x][y];
        return -1;
    }
    int GetZero()
    {
      return zero;
    }
    int GetCross()
    {
      return cross;
    }
    int f_empty ()
    {
       return vacant;
    }
    bool IsFull()
    {
       if(count_of_free!=0)
           return false;
       return true;
    }
    bool PossibleMotion(int x,int y)
    {
       int El=GetElement(x,y);
       if(El==vacant)
          return true;
       return false;
    }
    void Reset ()
    {
      for (int i=0;i<N;i++)
          for(int j=0;j<N;j++)
             GMatrix[i][j]=vacant;
      is_next_cross=true;
      count_of_free=N*N;
      BegPoint.ToSetAll(-1,-1,-1);
      EndPoint.ToSetAll(-1,-1,-1);
    }
    bool IsNextCross()
    {
        return is_next_cross;
    }
    void SetIsNextCross(bool pr)
    {
        is_next_cross=pr;
    }
    int IsWinner(int x,int y,int symbol)
    {
       int ccount=0;// количество  идущих подр€д символов данного типа
       int dlcount=0;// по левой диагонали
       int drcount=0;// по правой диагонали
       for(int i=x-win_number;i<x+win_number;i++)
       {
           if((i>=0)&&(i<N))
           {
             if(GMatrix[i][y]==symbol)
             {
                if(ccount==0)
                  BegPoint.ToSetAll(i,y,1);
                ccount++;
                if(ccount==win_number)
                {
                    EndPoint.ToSetAll(i,y,1);
                    return symbol;
                }
             }
             else
             {
               ccount=0;
               BegPoint.ToSetAll(-1,-1,0);
             }
           }
       }
       ccount=0;
       for(int j=y-win_number;j<y+win_number;j++)
       {
          if((j>=0)&&(j<N))
          {
             if(GMatrix[x][j]==symbol)
             {
                 if(ccount==0)
                  BegPoint.ToSetAll(x,j,2);
                 ccount++;
                 if(ccount==win_number)
                 {
                    EndPoint.ToSetAll(x,j,2);
                    return symbol;
                 }
             }
             else
             {
                ccount=0;
                BegPoint.ToSetAll(-1,-1,0);
             }
          }
       }

       int i,j,r;
       i=x-win_number;
       j=y-win_number;
       r=y+win_number;
       TCell BegDiag1;
       BegDiag1.ToSetAll(-1,-1,0);
       int k=0;
       int control=2*win_number;
       while(k<control)
       {
          if((i+k>=0)&&(i+k<N)&&(j+k>=0)&&(j+k<N))
          {
              if(GMatrix[i+k][j+k]==symbol)
              {
                    if(dlcount==0)
                       BegDiag1.ToSetAll(i+k,j+k,3);
                    dlcount++;
                    if(dlcount==win_number)
                    {
                       BegPoint=BegDiag1;
                       EndPoint.ToSetAll(i+k,j+k,3);
                       return symbol;
                    }
              }
              else
              {
                  dlcount=0;
                  BegDiag1.ToSetAll(-1,-1,0);
              }
          }
          if((i+k>=0)&&(i+k<N)&&(r-k>=0)&&(r-k<N))
          {
              if(GMatrix[i+k][r-k]==symbol)
              {
                  if(drcount==0)
                    BegPoint.ToSetAll(i+k,r-k,4);
                  drcount++;
                  if(drcount==win_number)
                  {
                     EndPoint.ToSetAll(i+k,r-k,4);
                     return symbol;
                  }
              }
              else
              {
                drcount=0;
                BegPoint.ToSetAll(-1,-1,0);
              }
          }
          k++;
       }
       return -1;

    }

};
#endif
>>>>>>> 443dcff40d1411906ff5a5c002787e717b2b8aab
