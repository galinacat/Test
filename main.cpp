#include "TXLib.h"
#include <fstream>

using namespace std;

struct Form
{
    string text_question;
    string text_answer1;
    int cost_answer1;
    string text_answer2;
    int cost_answer2;
};

void draw_answer(int y, string text)
{
    Win32::RoundRect(txDC(),150, y, 200,y+50,30,30 );
    txTextOut(250,y, text.c_str() );
}

bool click_answer (int y)
 {
  return  (txMouseButtons() == 1 &&
           txMouseX() >= 150 &&
           txMouseY() >= y &&
           txMouseX() <= 200 &&
           txMouseY() <= y+50);
}

int main()
{
    txCreateWindow (1200,900);
    txTextCursor (false);
    int n_question = 1;
    int result=0;
    HDC Fon = txLoadImage ("test.bmp");
    Form form;
    Form form_list[50];
    string page = "start";
    string str;
    int n = 0;
    ifstream  file("вопросы.txt");

    while(file.good())
     {
        getline(file,str);

        int pos1 = str.find(";");
        string text_question  =  str.substr(0,pos1);
        form_list[n].text_question = text_question;

        int pos2 = str.find(";", pos1+1);
        string text_answer1 =  str.substr(pos1+1,pos2 -(pos1+1));
        form_list[n].text_answer1 = text_answer1;

        int pos3 = str.find(";", pos2+1);
        string cost_answer1 =  str.substr(pos2+1,pos3 -(pos2+1));
        form_list[n].cost_answer1 = atoi(cost_answer1.c_str());

        int pos4 = str.find(";", pos3+1);
        string text_answer2 =  str.substr(pos3+1,pos4 -(pos3+1));
        form_list[n].text_answer2 = text_answer2 ;

        int pos5 = str.find(";", pos4+1);
        string cost_answer2 =  str.substr(pos4+1,pos5 -(pos4+1));
        form_list[n].cost_answer2 = atoi(cost_answer2.c_str());

        n++;
    }
   file.close();

    while(n_question<= n)
{
     if(page == "start")
     {
        txBegin();
        txSetColor (TX_WHITE);
        txSetFillColor (TX_BLACK);
        txClear();
        txBitBlt(txDC(), 0, 0, 1200, 900, Fon);

        txDrawText(0, 100, 1200, 200, "Психологический тест");

        txRectangle(450, 450, 750, 500);
        txDrawText(450, 450, 750, 500, "Пройти тест");
        if(txMouseButtons() == 1 &&
           txMouseX() >= 450 &&
           txMouseY() >= 450 &&
           txMouseX() <= 750 &&
           txMouseY() <= 500)
           {
                page = "test";
           }


        txSleep(50);
        txEnd();
     }

     if(page == "test")
     {
        txBegin();
        txSetFillColor (TX_BLACK);
        txClear();
        txBitBlt(txDC(), 0, 0, 1200, 900, Fon);
        form = form_list[n_question - 1];
        txSelectFont("Arial", 40);
        txSetColor (TX_WHITE);
        txDrawText(0 , 50, 1200, 250, form.text_question.c_str());
        draw_answer(250,form.text_answer1 );
        draw_answer(350,form.text_answer2 );

        char stroka[10];
        sprintf(stroka, "вопрос %d/%d",n_question,n);
        txDrawText(0 , 0, 1200, 50,stroka );
        //Клик на ответ 1
        if(click_answer (250))
        {
             txSleep(400);
             n_question++;
             result = result + form.cost_answer1;

        }
        //Клик на ответ 2
        if(click_answer (350))
        {
             txSleep(400);
             n_question++;
             result = result + form.cost_answer2;
        }
      txSleep(50);
      txEnd();
    }
}
    txSetFillColor (TX_BLACK);
    txClear();
    txDrawText(0 , 50, 1200, 250, "ВАШ РЕЗУЛЬТАТ");
    char stroka [10];
    sprintf(stroka,"%d",result);
     txDrawText(0 , 150, 1200, 350,stroka);
     if(result<30)
    txDrawText(0 , 350, 1200, 550, "ВЫ АГРЕССИВНЫЙ ЧЕЛОВЕК");
    else if((  result<=40 )&& (result>= 30))
    txDrawText(0 , 350, 1200, 550, "ВЫ  БОЛЕЕ  СПОКОЙНЫЙ ЧЕЛОВЕК ");
   else if ( result > 40)
    txDrawText(0 , 350, 1200, 550, "ВЫ  СПОКОЙНЫЙ ЧЕЛОВЕК ");

    return 0;
}

