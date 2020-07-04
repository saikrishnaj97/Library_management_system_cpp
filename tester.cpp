#define _WIN32_WINNT 0x0502
#include<iostream>
#include<fstream>
#include<windows.h>
#include<conio.h>
#include<string>
using namespace std;
//HWND hwnd = GetConsoleWindow();
int myMatch(string s, string p) {
    int pos=0;
    for(int i=0; i<p.length(); i++) {
        pos=s.find(p[i],pos);
        cout<<pos<<endl;
        if(pos==-1)return 0;
    }
    return 1;
}
int main() {
    //if( hwnd != NULL ){ MoveWindow(hwnd ,340,550 ,680,150 ,TRUE); }
    /*if( hwnd != NULL ){ SetWindowPos(hwnd ,0,0,0 ,1000,300 ,SWP_SHOWWINDOW|SWP_NOMOVE); }
    HANDLE buff = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD sizeOfBuff;
    sizeOfBuff.X=150;
    sizeOfBuff.Y=100;
    SetConsoleScreenBufferSize(buff,sizeOfBuff);*/
    /*SMALL_RECT rect;

    rect.Left=0;
    rect.Top=0;
    rect.Bottom=10;
    rect.Right=10;
    SetConsoleWindowInfo(buff,FALSE,&rect);
    int a=11130;
    cin>>a;
    ofstream out("code.dat", ios::out | ios::binary);
    out.write((char*)&a,sizeof(int));
    out.close();*/

    /*HANDLE  hConsole;
    int k;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // you can loop k higher to see more color choices
    for(k = 1; k <=255; k++)
    {
     // pick the colorattribute k you want
     SetConsoleTextAttribute(hConsole, k);
     cout << k << " I want to be nice today!" << endl;
    }

    cin.get(); // wait
    return 0;*/
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,7 );
    /*string s("This is some text please work . time up . ");
    string pattern("isz");
    if(myMatch(s,pattern)) {
        cout<<"matched"<<endl;
    } else {
        cout<<"collapse"<<endl;
    }*/
    char a[20];
    itoa(1,a,19);
    cout<<a<<"zdfddd";
    itoa(2,a,19);
    cout<<string(a)<<"Sd";
}

