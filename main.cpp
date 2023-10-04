#include "TXLib.h"

struct Button
{
    int x;
    const char* name;

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

    void draw()
    {
        if(visible) Win32::TransparentBlt (txDC(), x, y, w_scr, h_scr, pic, 0, 0, w, h, TX_WHITE);
    }

    bool click()
    {
        return (txMouseButtons() == 1 &&
                txMouseX() > 10 && txMouseX() < 480 &&
                txMouseY() > y && txMouseY() < y+550);
    }
};




int main()
{
txTextCursor (false);
txDisableAutoPause();

    txCreateWindow (1200, 700);

    int count_btn = 3;
    int count_pic = 6;

    //Область инициализации объектов
    //Кнопка
    Button btn[count_btn];
    btn[0] = {30, "Вид одежды"};
    btn[1] = {200, "Эмблемы"};
    btn[2] = {370, "Логотипы"};

    //Картинка-меню
    Picture menu_pic[count_pic];
    menu_pic[0] = {10, 100, 94, 110, txLoadImage ("Pictures/Одежда/Майка.bmp"), 470, 550, false};
    menu_pic[1] = {10, 250, 94, 110, txLoadImage ("Pictures/Одежда/Футболка.bmp"), 470, 550, false};
    menu_pic[2] = {10, 100, 100, 100, txLoadImage ("Pictures/Эмблемы/Эмблема1.bmp"), 100, 100, false};
    menu_pic[3] = {10, 250, 100, 100, txLoadImage ("Pictures/Эмблемы/Эмблема2.bmp"), 100, 100, false};
    menu_pic[4] = {10, 400, 100, 100, txLoadImage ("Pictures/Эмблемы/Эмблема3.bmp"), 100, 100, false};
    menu_pic[5] = {10, 100, 100, 100, txLoadImage ("Pictures/Логотипы/logo1.bmp"), 100, 100, false};

    //Картинка в центре
    Picture centr_pic[count_pic];
    centr_pic[0] = {430, 100, 470, 550, txLoadImage ("Pictures/Одежда/Майка.bmp"), 470, 550, false};
    centr_pic[1] = {430, 100, 470, 550, txLoadImage ("Pictures/Одежда/Футболка.bmp"), 470, 550, false};
    centr_pic[2] = {10, 100, 100, 100, txLoadImage ("Pictures/Эмблемы/Эмблема1.bmp"), 100, 100, false};
    centr_pic[3] = {10, 250, 100, 100, txLoadImage ("Pictures/Эмблемы/Эмблема2.bmp"), 100, 100, false};
    centr_pic[4] = {10, 400, 100, 100, txLoadImage ("Pictures/Эмблемы/Эмблема3.bmp"), 100, 100, false};
    centr_pic[5] = {10, 100, 100, 100, txLoadImage ("Pictures/Логотипы/logo1.bmp"), 100, 100, false};


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
        if(btn[0].click())
        {
            menu_pic[0].visible = true;
            menu_pic[1].visible = true;
        }

        if(menu_pic[0].click())
        {
            centr_pic[0].visible = true;
        }

        if(menu_pic[1].click())
        {
            centr_pic[1].visible = true;
        }

        if(btn[1].click())
        {
            menu_pic[2].visible = true;
            menu_pic[3].visible = true;
            menu_pic[4].visible = true;
        }

        if(btn[2].click())
        {
            menu_pic[5].visible = true;
        }

        txEnd();
        txSleep(50);
    }

    for(int i=0; i<count_pic; i++)
    {
        txDeleteDC (menu_pic[i].pic);
    }
    for(int i=0; i<count_pic; i++)
    {
        txDeleteDC (centr_pic[i].pic);
    }


return 0;
}

