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

    int count_btn = 4;
    int count_pic = 11;
    int vybor = -1;
    bool mousefree = true;
    char str[20];
    int nCenrtPic = 0;

    //������� ������������� ��������
    //������
    Button btn[count_btn];
    btn[0] = {30, "��� ������", "������"};
    btn[1] = {200, "�������", "�������"};
    btn[2] = {370, "��������", "�������"};
    btn[3] = {540, "�������", "�������"};

    //��������-����
    Picture menu_pic[count_pic];
    menu_pic[0] = {10, 100,  94, 110, txLoadImage ("Pictures/������/�����.bmp"), 470, 550, false, "������"};
    menu_pic[1] = {10, 250,  94, 110, txLoadImage ("Pictures/������/��������.bmp"), 470, 550, false, "������"};
    menu_pic[2] = {10, 100, 100, 100, txLoadImage ("Pictures/�������/�������1.bmp"), 100, 100, false, "�������"};
    menu_pic[3] = {10, 250, 100, 100, txLoadImage ("Pictures/�������/�������2.bmp"), 100, 100, false, "�������"};
    menu_pic[4] = {10, 400, 100, 100, txLoadImage ("Pictures/�������/�������3.bmp"), 100, 100, false, "�������"};
    menu_pic[5] = {10, 100, 100, 100, txLoadImage ("Pictures/��������/logo1.bmp"), 100, 100, false, "�������"};
    menu_pic[6] = {10, 250, 100, 100, txLoadImage ("Pictures/��������/logo2.bmp"), 100, 100, false, "�������"};
    menu_pic[7] = {10, 400, 100, 100, txLoadImage ("Pictures/��������/logo3.bmp"), 100, 100, false, "�������"};
    menu_pic[8] = {10, 550, 100, 100, txLoadImage ("Pictures/��������/logo4.bmp"), 100, 100, false, "�������"};
    menu_pic[9] = {10, 100, 70, 60, txLoadImage ("Pictures/�������/�������1.bmp"), 350, 300, false, "�������"};
    menu_pic[10] = {10, 200, 70, 60, txLoadImage ("Pictures/�������/�������2.bmp"), 350, 300, false, "�������"};

    //�������� � ������
    Picture centr_pic[100];

    while(!txGetAsyncKeyState (VK_ESCAPE))
    {

        txSetColor (TX_YELLOW);
        txSetFillColor (TX_YELLOW);
        txClear();

        txBegin();
        //������� ���������
        //������
        for(int i=0; i<count_btn; i++)
        {
            btn[i].draw();
        }

        //�������� ����
        for(int i=0; i<count_pic; i++)
        {
            menu_pic[i].draw();
        }

        //�������� � ������
        for(int i=0; i<nCenrtPic; i++)
        {
            centr_pic[i].draw();
        }

        //������� ��������������
        //��������� �������� ���� �� ���������
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

        //��������� �������� � ������
        for (int i=0; i<count_pic; i++)
        {
            if(menu_pic[i].click() && menu_pic[i].visible)
            {
                while (txMouseButtons()==1)   txSleep(10);
                centr_pic[nCenrtPic] = {200,
                                        100,
                                        menu_pic[i].w, menu_pic[i].h,
                                        menu_pic[i].pic,
                                        menu_pic[i].w, menu_pic[i].h,
                                        menu_pic[i].visible};
                nCenrtPic++;
            }
        }

        //����� �������� � ������
        for (int npic=0; npic<nCenrtPic; npic++)
        {
            if(centr_pic[npic].click() && centr_pic[npic].visible)
            {
                 vybor = npic;
                 mousefree = false;
            }

        }

        /*
        sprintf(str, "����� =  %d", vybor);
        txTextOut(10, 550, str);
        sprintf(str, "nCenrtPic =  %d", nCenrtPic);
        txTextOut(10, 600, str);
        sprintf(str, "������ =  %d ������ = %d", centr_pic[vybor].w_scr, centr_pic[vybor].h_scr);
        txTextOut(10, 600, str);
        */

        //������������ �������� � ������ �� �������� � +/- ������
        if(vybor>=0)
        {
            if(txGetAsyncKeyState (VK_UP))
            {
                centr_pic[vybor].y -= 3;
            }
            if(txGetAsyncKeyState (VK_DOWN))
            {
                centr_pic[vybor].y += 3;
            }
            if(txGetAsyncKeyState (VK_RIGHT))
            {
                centr_pic[vybor].x += 3;
            }
            if(txGetAsyncKeyState (VK_LEFT))
            {
                centr_pic[vybor].x -= 3;
            }
            if(txGetAsyncKeyState (VK_ADD) || txGetAsyncKeyState (VK_OEM_PLUS))
            {
                centr_pic[vybor].w_scr = centr_pic[vybor].w_scr*1.02;
                centr_pic[vybor].h_scr = centr_pic[vybor].h_scr*1.02;
            }
            if(txGetAsyncKeyState (VK_SUBTRACT) || txGetAsyncKeyState (VK_OEM_MINUS))
            {
                centr_pic[vybor].w_scr = centr_pic[vybor].w_scr*0.98;
                centr_pic[vybor].h_scr = centr_pic[vybor].h_scr*0.98;
            }
        }

        //������������ �������� � ������ ������
        if(vybor>=0 && txMouseButtons() == 1 && !mousefree)
        {
            centr_pic[vybor].x = txMouseX() - centr_pic[vybor].w_scr/2;
            centr_pic[vybor].y = txMouseY() - centr_pic[vybor].h_scr/2;
        }
        if(vybor>=0 && !txMouseButtons() == 1 && !mousefree)
        {
            mousefree = true;
        }

        //�������� �������� � ������
        if(vybor>=0 && txGetAsyncKeyState (VK_DELETE))
        {
            centr_pic[vybor]  = centr_pic[nCenrtPic - 1];
            nCenrtPic--;
            vybor = -1;
        }


        txEnd();
        txSleep(50);
    }

    for(int i=0; i<count_pic; i++)
    {
        txDeleteDC (menu_pic[i].pic);
    }

    for(int i=0; i<nCenrtPic; i++)
    {
        txDeleteDC (centr_pic[i].pic);
    }

return 0;
}

