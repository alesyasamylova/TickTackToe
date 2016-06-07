//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include <math.h>
#pragma hdrstop
//---------------------------------------------------------------------------
//------------------------Искусственный ителлект-----------------------------
//---------------------------------------------------------------------------

#pragma argsused
int win_number,cross,zero,count_of_free;
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
  return 1;
}
//----------------------------------------------------------------------------
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
//----------------------------------------------------------------------------
int GetEstimate (int x,int y,int symbol,int**GMatrix,int N)
{

       int k[8];
       for(int i=0;i<8;i++)
          k[i]=0;
       for(int i=x-1;i>=x-win_number;i--)
       {
          if(i>=0&&i<N)
          {
            if(GMatrix[i][y]==symbol)
              k[0]++;
            else break;
          }
          else break;
       }
       for(int i=x+1;i<x+win_number;i++)
       {
          if(i>=0&&i<N)
          {
            if(GMatrix[i][y]==symbol)
              k[1]++;
            else break;
          }
          else break;
       }
       for(int i=y-1;i>=y-win_number;i--)
       {
          if(i>=0&&i<N)
          {
            if(GMatrix[x][i]==symbol)
               k[2]++;
            else break;
          }
          else break;
       }
       for(int i=y+1;i<y+win_number;i++)
       {
          if(i>=0&&i<N)
          {
            if(GMatrix[x][i]==symbol)
               k[3]++;
            else break;
          }
          else break;
       }
       int i=x;
       int j=y;
       int l=1;
       while(l<win_number)           //left up
       {
         if((i-l>=0)&&(i-l<N)&&(j-l>=0)&&(j-l<N))
         {
            if(GMatrix[i-l][j-l]==symbol)
               k[4]++;
            else break;
         }
         else break;

         l++;
       }
       l=1;
       i=x;
       j=y;
       while(l<win_number)      // right down
       {
         if((i+l>=0)&&(i+l<N)&&(j+l>=0)&&(j+l<N))
         {
            if(GMatrix[i+l][j+l]==symbol)
               k[5]++;
            else break;
         }
         else break;
         l++;

       }
       l=1;
       i=x;
       j=y;
       while(l<win_number)        // right up
       {
         if((i-l>=0)&&(i-l<N)&&(j+l>=0)&&(j+l<N))
         {
            if(GMatrix[i-l][j+l]==symbol)
               k[6]++;
            else break;
         }
         else break;
         l++;
       }
       l=1;
       i=x;
       j=y;
       while(l<win_number)        // left down
       {
         if((i+l>=0)&&(i+l<N)&&(j-l>=0)&&(j-l<N))
         {
            if(GMatrix[i+l][j-l]==symbol)
               k[7]++;
            else break;
         }
         else break;
         l++;
       }

       int M=0;
       for(i=0;i<8;i++)
          M=M+pow(15,k[i]);

       return M;
}
//----------------------------------------------------------------------------

double ComplitWeight(int x, int y,int symbol,int **GMatrix,int n)
{
        int M=GetEstimate(x,y,symbol,GMatrix,n);
        int other_symbol=cross;
        if(other_symbol==symbol)
          other_symbol=zero;
        int N=GetEstimate(x,y,other_symbol,GMatrix,n);
        double Q=0.1;
        double F=M+Q*N;
        return F;
}
//----------------------Основная функция--------------------------------------
extern "C" TCell __export  AnalyseMove(int symbol,int**GMatrix,int N,int uwin_number,int ucross, int uzero, int ucount_of_free)
{
       win_number=uwin_number;
       cross=ucross;
       zero=uzero;
       count_of_free=ucount_of_free;
       if(count_of_free==0)
       {
         TCell Step;
         Step.ToSetAll(-1,-1,-4);
         return Step;

       }
       TCell *ArrayPossibles=new TCell[count_of_free];
       int k=0;
       for(int i=0;i<N;i++)
         for(int j=0;j<N;j++)
         {
             if(GMatrix[i][j]==0)
             {
                ArrayPossibles[k].ToSetAll(i,j,ComplitWeight(i,j,symbol,GMatrix,N));
                k++;
                if(k==count_of_free) break;
             }
         }
         int r=random(count_of_free);
         TCell Max=ArrayPossibles[r];
         for(int i=0;i<count_of_free;i++)
             if(Max.value<ArrayPossibles[i].value)
                Max=ArrayPossibles[i];
         delete[]ArrayPossibles;
        // SetElement(Max.x,Max.y,symbol);   нужно записать из вне
         return Max;       


}



//---------------------------------------------------------------------------
