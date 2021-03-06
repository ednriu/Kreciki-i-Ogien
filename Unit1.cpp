//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"



TKreciki *Kreciki;
        int speed = 1;
        int x=5;
        int y=5;
        int a=1;int b=2,c=3;
        int punkty = 0;

        int random(int from, int to){
                return rand() % (to - from + 1) + from;
        }


        bool kolizja(TImage * Pilka, TImage * kret, TImage * kretZastepczy, TLabel * wyswietlPunkty)
        {
                if (kret->Visible==true)
                {
                        if ((Pilka->Top < kret->Top) && (Pilka->Top > kret->Top-30) && (Pilka->Left<kret->Left+20) && (Pilka->Left>kret->Left-20))
                                {
                                        kret->Visible = false;
                                        kretZastepczy->Visible = true;
                                        int temp = wyswietlPunkty->Caption.ToInt()+1;
                                        wyswietlPunkty->Caption = temp;
                                        if(wyswietlPunkty->Caption<0) wyswietlPunkty->Font->Color = clRed;
                                        if(wyswietlPunkty->Caption>00) wyswietlPunkty->Font->Color = clGreen;
                                        return true;
                                };
                } else if (kret->Visible==false) return false;
                return false;
        };


//---------------------------------------------------------------------------
__fastcall TKreciki::TKreciki(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TKreciki::Timer_paletka_lewoTimer(TObject *Sender)
{
        if (Paletka->Top<1) Paletka->Top = 320;
        Paletka->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TKreciki::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        //paletka1
        if(Key == 'E') Timer_paletka_lewo->Enabled=true;
        if(Key == 'X') Timer_paletka_prawo->Enabled=true;

        //paletka2
        if(Key == VK_UP) Timer_paletka2_lewo->Enabled=true;
        if(Key == VK_DOWN) Timer_paletka2_prawo->Enabled=true;


}
//---------------------------------------------------------------------------
void __fastcall TKreciki::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        //paletka1
        if(Key == 'E') Timer_paletka_lewo->Enabled=false;
        if(Key == 'X') Timer_paletka_prawo->Enabled=false;

        //paletka2
        if(Key == VK_UP) Timer_paletka2_lewo->Enabled=false;
        if(Key == VK_DOWN) Timer_paletka2_prawo->Enabled=false;

}
//---------------------------------------------------------------------------
void __fastcall TKreciki::Timer_pilkaTimer(TObject *Sender)
{

        Pilka->Left+=x;
        Pilka->Top+=y;

        //wersja jednego gracza
        if (Paletka2->Visible==false)
        {
                 //odbijanie od scian
                if (Pilka->Top<5) if(y<0) y = -y;
                if (Pilka->Top>400-Pilka->Height) if(y>0) y = -y;
                if (Pilka->Left>550-Pilka->Width) if(x>0) x = -x;
                if (Pilka->Left<2 && Kolory->Brush->Color==clGreen) if (x<0) x=-x;

                //odbijanie od paletki 1
                if(Pilka->Left<Paletka->Left+Paletka->Width+5 && Pilka->Left>Paletka->Left+Paletka->Width-5 && Pilka->Top>Paletka->Top-Pilka->Height/2 && Pilka->Top<Paletka->Top+Paletka->Height+Pilka->Height)
                {
                        if (x<0)
                        {
                           x=-x;
                           if (Kolory->Brush->Color==clGreen)
                           {
                             sndPlaySound("wav/beep-10.wav", SND_ASYNC);
                             int temp = Punkty->Caption.ToInt()-5;
                             Punkty->Caption = temp;
                             if(Punkty->Caption<0) Punkty->Font->Color = clRed;
                             if(Punkty->Caption>00) Punkty->Font->Color = clGreen;
                           };
                        };
                } else if(Pilka->Left<-5)    //Skucha
                {
                        Pilka->Visible = false;
                        Timer_pilka->Enabled = false;
                        Timer_krety ->Enabled = false;
                        Timer_paletka_lewo->Enabled = false;
                        Timer_paletka_prawo->Enabled = false;
                        TimerOgien->Enabled = false;
                        TimerKolory->Enabled = false;
                        Start->Caption = "Nowa Gra";
                        Start->Enabled = true;
                        Pauza->Enabled = false;
                        Ogien->Visible = false;
                        IleGraczy->Enabled = true;
                        ShowMessage("Koniec Gry! \nTwoje Punkty:" + Punkty->Caption + "\n Czy dasz rad� osi�gn�c lepszy wynik?");
                };
        };


        //wersja dw�ch graczy
        if (Paletka2->Visible==true)
        {
                //odbijanie od scian
                if (Pilka->Top<5) if(y<0) y = -y;
                if (Pilka->Top>400-Pilka->Height) if(y>0) y = -y;
                if (Pilka->Left>550-Pilka->Width && Kolory->Brush->Color==clRed ) if(x>0) x = -x;
                if (Pilka->Left<2 && Kolory->Brush->Color==clGreen) if (x<0) x=-x;


                //Skucha
                if((Pilka->Left<-5) || (Pilka->Left>Paletka2->Left+Paletka2->Width+5))
                {
                        Pilka->Visible = false;
                        Timer_pilka->Enabled = false;
                        Timer_krety ->Enabled = false;
                        Timer_paletka_lewo->Enabled = false;
                        Timer_paletka_prawo->Enabled = false;
                        Timer_paletka2_lewo->Enabled = false;
                        Timer_paletka2_prawo->Enabled = false;
                        TimerKolory->Enabled=false;
                        TimerOgien->Enabled = false;
                        Start->Caption = "Nowa Gra";
                        Start->Enabled = true;
                        Pauza->Enabled = false;
                        IleGraczy->Enabled = true;
                        Ogien->Visible = false;
                        ShowMessage("Koniec Gry! \nTwoje Punkty:" + Punkty->Caption + "\n Czy dasz rad� osi�gn�c lepszy wynik?");
                };
                //odbijanie od paletki 1
                if(Pilka->Left<Paletka->Left+Paletka->Width+5 && Pilka->Left>Paletka->Left+Paletka->Width-5 && Pilka->Top>Paletka->Top-Pilka->Height && Pilka->Top<Paletka->Top+Paletka->Height+Pilka->Height)
                {
                        if (x<0)
                        {
                        x=-x;
                        if (Kolory->Brush->Color==clGreen)
                           {
                             sndPlaySound("wav/beep-10.wav", SND_ASYNC);
                             int temp = Punkty->Caption.ToInt()-5;
                             Punkty->Caption = temp;
                             if(Punkty->Caption<0) Punkty->Font->Color = clRed;
                             if(Punkty->Caption>00) Punkty->Font->Color = clGreen;
                           };
                        };
                }

                //odbijanie od paletki 2
                if(Pilka->Left>Paletka2->Left-Pilka->Width-5 && Pilka->Left<Paletka2->Left-Pilka->Width+5 && Pilka->Top>Paletka2->Top-Pilka->Height && Pilka->Top<Paletka2->Top+Paletka2->Height+Pilka->Height)
                {
                        if (x>0)
                        {
                        x=-x;
                        if (Kolory->Brush->Color==clRed)
                           {
                             sndPlaySound("wav/beep-10.wav", SND_ASYNC);
                             int temp = Punkty->Caption.ToInt()-5;
                             Punkty->Caption = temp;
                             if(Punkty->Caption<0) Punkty->Font->Color = clRed;
                             if(Punkty->Caption>00) Punkty->Font->Color = clGreen;
                           };
                        };
                }
        };


        //odbijanie od ognia
        if (Ogien->Visible == true)
        {
                if(Pilka->Top-Pilka->Height>Ogien->Top && Pilka->Top < Ogien->Top+Ogien->Height && Pilka->Left+Pilka->Width>Ogien->Left && Pilka->Left<Ogien->Left+Ogien->Width)
                {
                        y=-y;
                        x=-x;
                };
        };


        //zbijanie krecikow
        if ((kolizja(Pilka, Krecik, Krecik4, Punkty)==true))
        {
                x=-x;
                y=-y;
                sndPlaySound("wav/crash.wav", SND_ASYNC);

         };

         if ((kolizja(Pilka, Krecik2, Krecik5, Punkty)==true))
        {
                x=-x;
                y=-y;
                sndPlaySound("wav/crash.wav", SND_ASYNC);

         };

         if ((kolizja(Pilka, Krecik3, Krecik6, Punkty)==true))
        {
                x=-x;
                y=-y;
                sndPlaySound("wav/crash.wav", SND_ASYNC);

         };
         if ((kolizja(Pilka, Krecik4, Krecik7, Punkty)==true))
        {
                x=-x;
                y=-y;
                sndPlaySound("wav/crash.wav", SND_ASYNC);

         };
         if ((kolizja(Pilka, Krecik5, Krecik8, Punkty)==true))
        {
                x=-x;
                y=-y;
                sndPlaySound("wav/crash.wav", SND_ASYNC);

         };
         if ((kolizja(Pilka, Krecik6, Krecik9, Punkty)==true))
        {
                x=-x;
                y=-y;
                sndPlaySound("wav/crash.wav", SND_ASYNC);

         };
         if ((kolizja(Pilka, Krecik7, Krecik10, Punkty)==true))
        {
                x=-x;
                y=-y;
                sndPlaySound("wav/crash.wav", SND_ASYNC);

         };
         if ((kolizja(Pilka, Krecik8, Krecik11, Punkty)==true))
        {
                x=-x;
                y=-y;
                sndPlaySound("wav/crash.wav", SND_ASYNC);

         };
         if ((kolizja(Pilka, Krecik9, Krecik12, Punkty)==true))
        {
                x=-x;
                y=-y;
                sndPlaySound("wav/crash.wav", SND_ASYNC);

         };
         if ((kolizja(Pilka, Krecik10, Krecik, Punkty)==true))
        {
                x=-x;
                y=-y;
                sndPlaySound("wav/crash.wav", SND_ASYNC);

         };
         if ((kolizja(Pilka, Krecik11, Krecik2, Punkty)==true))
        {
                x=-x;
                y=-y;
                sndPlaySound("wav/crash.wav", SND_ASYNC);

         };
         if ((kolizja(Pilka, Krecik12, Krecik3, Punkty)==true))
        {
                x=-x;
                y=-y;
                sndPlaySound("wav/crash.wav", SND_ASYNC);

         };

}
//---------------------------------------------------------------------------
void __fastcall TKreciki::PredkoscChange(TObject *Sender)
{
        Timer_pilka->Interval-=speed;        
}
//---------------------------------------------------------------------------

void __fastcall TKreciki::FormCreate(TObject *Sender)
{
        Predkosc->Items->Add("1");
        Predkosc->Items->Add("2");
        Predkosc->Items->Add("3");
        Predkosc->Items->Add("4");
        Predkosc->Items->Add("5");
        Predkosc->Items->Add("6");
        Predkosc->Items->Add("7");
        Application->MessageBox("Klawisze:\n\n Zielona Paletka:\nUP,DOWN\nCzerwona Paletka:\nE,X\n\nZasady:\n +1pkt za zbicie kreta \n -5pkt za odbicie pi�ki gdy wskazany kolor jest taki sam jak kolor paletki",
				"Instrukcja", NULL);
}
//---------------------------------------------------------------------------

void __fastcall TKreciki::StartClick(TObject *Sender)
{
        Sleep(500);
        srand(time(0));
        if ((Start->Caption=="Start") || (Start->Caption=="Nowa Gra"))
        {

                Punkty->Caption="0";
                Pilka->Visible = true;
                Krecik->Visible = true;
                Krecik2->Visible = true;
                Krecik3->Visible = true;
                Krecik4->Visible = false;
                Krecik5->Visible = false;
                Krecik6->Visible = false;
                Krecik7->Visible = false;
                Krecik8->Visible = false;
                Krecik9->Visible = false;
                Krecik10->Visible = false;
                Krecik11->Visible = false;
                Krecik12->Visible = false;
                Pilka->Left = random(150, 400);
                Pilka->Top = random(0, 400-Pilka->Height);
        };
       
        speed= StrToInt(Predkosc->Text);
        Timer_pilka->Interval = 25-3*speed;
        Timer_pilka->Enabled = true;
        Start->Enabled = false;
        Pauza->Enabled = true;
        Predkosc->Enabled = false;
        IleGraczy->Enabled = false;
        Timer_krety->Enabled = true;
        TimerOgien->Enabled = true;
        TimerKolory->Enabled = true;
        //Paletka2 Widocznosc
        if (IleGraczy->Checked == true) Paletka2->Visible = true;
        if (IleGraczy->Checked == false) Paletka2->Visible = false;

}
//---------------------------------------------------------------------------

void __fastcall TKreciki::PauzaClick(TObject *Sender)
{
        Timer_pilka->Enabled = false;
        Timer_krety->Enabled = false;
        TimerOgien->Enabled = false;
        TimerKolory->Enabled = false;
        Pauza->Enabled = false;
        Start->Enabled = true;
        Start->Caption = "Wznow";
}
//---------------------------------------------------------------------------

void __fastcall TKreciki::Timer_paletka_prawoTimer(TObject *Sender)
{
        if (Paletka->Top>320) Paletka->Top = 1;
        Paletka->Top+=10;
}
//---------------------------------------------------------------------------

void __fastcall TKreciki::Timer_kretyTimer(TObject *Sender)
{
        //wielokrotnosci 1,4,7,10
        if (Krecik->Visible)
        {
                Krecik->Top+=a;
                if (Krecik->Top<=5) a=-a;
                if (Krecik->Top>=375) a=-a;
        };


        if (Krecik4->Visible)
        {
                Krecik4->Top+=a;
                if (Krecik4->Top<=5) a=-a;
                if (Krecik4->Top>=375) a=-a;
        };

        if (Krecik7->Visible)
        {
                Krecik7->Top+=a;
                if (Krecik7->Top<=5) a=-a;
                if (Krecik7->Top>=375) a=-a;
        };

        if (Krecik10->Visible)
        {
                Krecik10->Top+=a;
                if (Krecik10->Top<=5) a=-a;
                if (Krecik10->Top>=375) a=-a;
        };

        //wielokrotnosci 2,5,8,11
        if (Krecik2->Visible)
        {
                Krecik2->Top+=b;
                if (Krecik2->Top<=5) b=-b;
                if (Krecik2->Top>=375) b=-b;
        };

        if (Krecik5->Visible)
        {
                Krecik5->Top+=b;
                if (Krecik5->Top<=5) b=-b;
                if (Krecik5->Top>=375) b=-b;
        };

        if (Krecik8->Visible)
        {
                Krecik8->Top+=b;
                if (Krecik8->Top<=5) b=-b;
                if (Krecik8->Top>=375) b=-b;
        };

        if (Krecik11->Visible)
        {
                Krecik11->Top+=b;
                if (Krecik11->Top<=5) b=-b;
                if (Krecik11->Top>=375) b=-b;
        };

        //wielokrotnosci 3,6,9,12
        if (Krecik3->Visible)
        {
                Krecik3->Top+=c;
                if (Krecik3->Top<=5) c=-c;
                if (Krecik3->Top>=375) c=-c;
        };

                if (Krecik6->Visible)
        {
                Krecik6->Top+=c;
                if (Krecik6->Top<=5) c=-c;
                if (Krecik6->Top>=375) c=-c;
        };

                if (Krecik9->Visible)
        {
                Krecik9->Top+=c;
                if (Krecik9->Top<=5) c=-c;
                if (Krecik9->Top>=375) c=-c;
        };

                if (Krecik12->Visible)
        {
                Krecik12->Top+=c;
                if (Krecik12->Top<=5) c=-c;
                if (Krecik12->Top>=375) c=-c;
        };


}
//---------------------------------------------------------------------------


void __fastcall TKreciki::Timer_paletka2_lewoTimer(TObject *Sender)
{
        if (Paletka2->Top<1) Paletka2->Top = 320;
        Paletka2->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TKreciki::Timer_paletka2_prawoTimer(TObject *Sender)
{
        if (Paletka2->Top>320) Paletka2->Top = 1;
        Paletka2->Top+=10;
}
//---------------------------------------------------------------------------

void __fastcall TKreciki::TimerOgienTimer(TObject *Sender)
{
        int losowa1, losowa2;
        bool kolizja = false;
        losowa1 =  random(75,400-Ogien->Height-75);
        losowa2 =  random(50,550-Ogien->Width-50);
        Ogien->Enabled  =true;
        Ogien->Visible = true;

        if ((losowa1<Pilka->Top-Pilka->Height) && (losowa1+Ogien->Height>Pilka->Top) && (Pilka->Left+Pilka->Width>losowa2) && (Pilka->Left<losowa2+Ogien->Width))
        {
                kolizja = true;
        };

        if (kolizja == false)
        {
                Ogien->Top = losowa1;
                Ogien->Left= losowa2;
        };

}




void __fastcall TKreciki::TimerKoloryTimer(TObject *Sender)
{
        int numerKoloru = random(1, 24);
        
        if (numerKoloru>=1 && numerKoloru<=4) if((x>0 || Pilka->Left>Paletka->Left+Paletka->Width+70) && (x<0 || Pilka->Left<Paletka2->Left-70)) Kolory->Brush->Color = clRed;
        if (numerKoloru>=5 && numerKoloru<=8) if((x>0 || Pilka->Left>Paletka->Left+Paletka->Width+70) && (x<0 || Pilka->Left<Paletka2->Left-70)) Kolory->Brush->Color = clGreen;
        if (numerKoloru>=9 && numerKoloru<=12) if((x>0 || Pilka->Left>Paletka->Left+Paletka->Width+70) && (x<0 || Pilka->Left<Paletka2->Left-70)) Kolory->Brush->Color = clGray;
        if (numerKoloru>=13 && numerKoloru<=16) if((x>0 || Pilka->Left>Paletka->Left+Paletka->Width+70) && (x<0 || Pilka->Left<Paletka2->Left-70)) Kolory->Brush->Color = clAqua;
        if (numerKoloru>=17 && numerKoloru<=20) if((x>0 || Pilka->Left>Paletka->Left+Paletka->Width+70) && (x<0 || Pilka->Left<Paletka2->Left-70)) Kolory->Brush->Color = clFuchsia;
        if (numerKoloru>=21 && numerKoloru<=24) if((x>0 || Pilka->Left>Paletka->Left+Paletka->Width+70) && (x<0 || Pilka->Left<Paletka2->Left-70))
        {
                if (Paletka2->Visible) Kolory->Brush->Color = clYellow;
                if (!Paletka2->Visible) Kolory->Brush->Color = clGreen;
        };
}
//---------------------------------------------------------------------------


