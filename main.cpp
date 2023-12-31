#include "TXLib.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <dirent.h>

using namespace std;

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
    string adress;
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

int get_w(string adress)
{
    char header[54];
    ifstream bmp;
    bmp.open(adress, ios::in | ios::binary);
    bmp.read(header, 54);
    int w = *(int *)&header[18];

    return w;
}

int get_h(string adress)
{
    char header[54];
    ifstream bmp;
    bmp.open(adress, ios::in | ios::binary);
    bmp.read(header, 54);
    int h = *(int *)&header[22];

    return h;
}

int readFolders(string adressDir, Picture menu_pic[], int count_pic)
{
    DIR *dir;
    struct dirent *ent;
    int X = 10;
    int Y = 100;
    if ((dir = opendir (adressDir.c_str())) != NULL)
    {
      while ((ent = readdir (dir)) != NULL)
      {
        if((string)ent->d_name != "." && (string)ent->d_name != "..")
        {
            menu_pic[count_pic].y = Y;
            menu_pic[count_pic].x = X;
            menu_pic[count_pic].adress = adressDir + (string)ent->d_name;
            count_pic++ ;
            Y += 150;
        }
      }
      closedir (dir);
    }
    return count_pic;
}


int main()
{
txTextCursor (false);
txDisableAutoPause();

    txCreateWindow (1200, 700);

    int count_btn = 4;
    int count_pic = 0;
    int vybor = -1;
    bool mousefree = true;
    char str[20];
    int nCenrtPic = 0;

    //������� ������������� ��������
    //������
    Button btn[count_btn];
    btn[0] = {30, "��� ������", "������"};
    btn[1] = {200, "�������", "�������"};
    btn[2] = {370, "��������", "��������"};
    btn[3] = {540, "�������", "�������"};

    //��������-����
    Picture menu_pic[100];

    count_pic = readFolders("Pictures/������/", menu_pic, count_pic);
    count_pic = readFolders("Pictures/�������/", menu_pic, count_pic);
    count_pic = readFolders("Pictures/��������/", menu_pic, count_pic);
    count_pic = readFolders("Pictures/�������/", menu_pic, count_pic);

    for(int i=0; i<count_pic; i++)
    {
        menu_pic[i].pic = txLoadImage (menu_pic[i].adress.c_str());

        menu_pic[i].w = get_w(menu_pic[i].adress);
        menu_pic[i].h = get_h(menu_pic[i].adress);

        menu_pic[i].visible = false;

        string str = menu_pic[i].adress;
        int pos1 = str.find("/");
        int pos2 = str.find("/", pos1+1);
        menu_pic[i].category = str.substr(pos1+1, pos2-(pos1+1));

        if(menu_pic[i].category == "������" || menu_pic[i].category == "�������")
        {
            menu_pic[i].w_scr = menu_pic[i].w/5;
            menu_pic[i].h_scr = menu_pic[i].h/5;
        }
        else if(menu_pic[i].category == "�������" || menu_pic[i].category == "��������")
        {
            menu_pic[i].w_scr = menu_pic[i].w;
            menu_pic[i].h_scr = menu_pic[i].h;
        }
    }

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
                                        menu_pic[i].adress,
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

