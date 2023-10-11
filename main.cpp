#include "TXLib.h"

struct Button
{
    int x;
    const char* name;
    string category;

    void draw()
    {
        txSetColor (TX_GRAY);
        txSetFillColor (TX_GRAY);
        Win32::RoundRect (txDC(), x+3, 33, x+140, 63, 20, 20);
        txSetColor (TX_BLACK, 2);
        txSetFillColor (TX_WHITE);
        Win32::RoundRect (txDC(), x, 30, x+140, 60, 20, 20);
        txSetColor (TX_BLACK);
        txSelectFont("Times New Roman", 25);
        txDrawText(x, 30, x+140, 60, name);
    }

    bool click()
    {
        return (txMouseButtons() == 1 &&
                txMouseX() > x && txMouseX() < x+140 &&
                txMouseY() > 30 && txMouseY() < 60);
    }
};

struct Picture
{
    int x;
    int y;
    int w_scr;
    int h_scr;
    HDC pic;
    int w;
    int h;
    bool visible;
    string category;

    void draw()
    {
        if(visible) Win32::TransparentBlt (txDC(), x, y, w_scr, h_scr, pic, 0, 0, w, h, TX_WHITE);
    }

    bool click()
    {
        return (txMouseButtons() == 1 &&
                txMouseX() > x && txMouseX() < x+w_scr &&
                txMouseY() > y && txMouseY() < y+h_scr);
    }
};




int main()
{
txTextCursor (false);
txDisableAutoPause();

    txCreateWindow (1200, 700);

    int count_btn = 3;
    int count_pic = 9;

    //Область инициализации объектов
    //Кнопка
    Button btn[count_btn];
    btn[0] = {30, "Вид одежды", "Одежда"};
    btn[1] = {200, "Эмблемы", "Эмблема"};
    btn[2] = {370, "Логотипы", "Логотип"};

    //Картинка-меню
    Picture menu_pic[count_pic];
    menu_pic[0] = {10, 100,  94, 110, txLoadImage ("Pictures/Одежда/Майка.bmp"), 470, 550, false, "Одежда"};
    menu_pic[1] = {10, 250,  94, 110, txLoadImage ("Pictures/Одежда/Футболка.bmp"), 470, 550, false, "Одежда"};
    menu_pic[2] = {10, 100, 100, 100, txLoadImage ("Pictures/Эмблемы/Эмблема1.bmp"), 100, 100, false, "Эмблема"};
    menu_pic[3] = {10, 250, 100, 100, txLoadImage ("Pictures/Эмблемы/Эмблема2.bmp"), 100, 100, false, "Эмблема"};
    menu_pic[4] = {10, 400, 100, 100, txLoadImage ("Pictures/Эмблемы/Эмблема3.bmp"), 100, 100, false, "Эмблема"};
    menu_pic[5] = {10, 100, 100, 100, txLoadImage ("Pictures/Логотипы/logo1.bmp"), 100, 100, false, "Логотип"};
    menu_pic[6] = {10, 250, 100, 100, txLoadImage ("Pictures/Логотипы/logo2.bmp"), 100, 100, false, "Логотип"};
    menu_pic[7] = {10, 400, 100, 100, txLoadImage ("Pictures/Логотипы/logo3.bmp"), 100, 100, false, "Логотип"};
    menu_pic[8] = {10, 550, 100, 100, txLoadImage ("Pictures/Логотипы/logo4.bmp"), 100, 100, false, "Логотип"};

    //Картинка в центре
    Picture centr_pic[count_pic];
    centr_pic[0] = {430, 100, 470, 550, menu_pic[0].pic, menu_pic[0].w, menu_pic[0].h, false};
    centr_pic[1] = {430, 100, 470, 550, menu_pic[1].pic, menu_pic[1].w, menu_pic[1].h, false};
    centr_pic[2] = {600, 100, 100, 100, menu_pic[2].pic, menu_pic[2].w, menu_pic[2].h, false};
    centr_pic[3] = {600, 200, 100, 100, menu_pic[3].pic, menu_pic[3].w, menu_pic[3].h, false};
    centr_pic[4] = {600, 300, 100, 100, menu_pic[4].pic, menu_pic[4].w, menu_pic[4].h, false};
    centr_pic[5] = {600, 400, 100, 100, menu_pic[5].pic, menu_pic[5].w, menu_pic[5].h, false};
    centr_pic[6] = {600, 500, 100, 100, menu_pic[6].pic, menu_pic[6].w, menu_pic[6].h, false};
    centr_pic[7] = {600, 600, 100, 100, menu_pic[7].pic, menu_pic[7].w, menu_pic[7].h, false};
    centr_pic[8] = {700, 600, 100, 100, menu_pic[8].pic, menu_pic[8].w, menu_pic[8].h, false};


    while(!txGetAsyncKeyState (VK_ESCAPE))
    {

        txSetColor (TX_YELLOW);
        txSetFillColor (TX_YELLOW);
        txClear();

        txBegin();
        //Область рисования
        for(int i=0; i<count_btn; i++)
        {
            btn[i].draw();
        }

        for(int i=0; i<count_pic; i++)
        {
            menu_pic[i].draw();
        }

        for(int i=0; i<count_pic; i++)
        {
            centr_pic[i].draw();
        }

        //Область взаимодействия
        for (int ib=0; ib<count_btn; ib++)
        {
            if(btn[ib].click())
            {
                  for (int ip=0; ip<count_pic; ip++)
                  {
                        menu_pic[ip].visible = false;
                        if (menu_pic[ip].category == btn[ib].category)
                        {
                            menu_pic[ip].visible = true;
                        }
                  }
            }
        }


        for (int i=0; i<count_pic; i++)
        {
            if(menu_pic[i].click() && menu_pic[i].visible)
            {
                centr_pic[i].visible = true;
            }
        }



        txEnd();
        txSleep(50);
    }

    for(int i=0; i<count_pic; i++)
    {
        txDeleteDC (menu_pic[i].pic);
        txDeleteDC (centr_pic[i].pic);
    }


return 0;
}

