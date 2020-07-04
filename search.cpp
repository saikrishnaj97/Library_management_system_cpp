#include<iostream>
using namespace std;
#include "tableobject.cpp"

int myMatch(string s, string p){
    int pos=0;
    for(int i=0;i<p.length();i++){
        pos=s.find(p[i],pos);
        if(pos==-1)return 0;
    }
    return 1;
}

Table searchTable(Table t,string col, string value) {
    int k=0;
    Table temp1;
    int n = t.getNumberOfRows();
    int flag=0;
    for(int i=0; i<n; i++) {
        if(t[i][col]==value) {
            flag=1;
            temp1[k]=t[i];
            k++;
        }
    }
    temp1.setHeader(t.getHeader());
    return temp1;
}

Table searchTable(Table t, string value) {
    int k=0;
    Table temp;
    int n = t.getNumberOfRows();
    int flag=0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<t[i].getNumberOfColumns(); j++) {
            if(t[i][j]==value) {
                flag=1;
                temp[k]=t[i];
                k++;
            }
        }
    }
    temp.setHeader(t.getHeader());
    return temp;
}

Table searchTableAll(Table t, string value) {
    int k=0;
    Table temp;
    int n = t.getNumberOfRows();
    int flag=0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<t[i].getNumberOfColumns(); j++) {
            if(myMatch(t[i][j].getString(),value)) {
                flag=1;
                temp[k]=t[i];
                k++;
                break;
            }
        }
    }
    temp.setHeader(t.getHeader());
    return temp;
}

void displayTable(Table t,string * listOfCols,int * sizeOfCols,int n) {
    int *spaces = new int[n];
    int color;
    spaces[0] = 1;
    HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i=1; i<n; i++) {
        spaces[i] = spaces[i-1] + 3 +sizeOfCols[i-1];
    }

    //print end of table
    for(int i=0; i<spaces[n-1]+sizeOfCols[n-1]; i++) {
        cout<<" ";
    }
    cout<<(char)219;

    for(int i=n-1; i>=0; i--) {
        cout<<"\r";
        for(int j=0; j<spaces[i]-2; j++) {
            cout<<" ";
        }
        cout<<(char)219<<" "<<((listOfCols[i]).substr(0,sizeOfCols[i]));
    }

    //just a mid divider long line
    cout<<endl;
    for(int i=0; i<spaces[n-1]+sizeOfCols[n-1]; i++) {
        cout<<(char)220;
    }
    cout<<(char)219;

    //content
    cout<<endl;
    for(int k=0; k<t.getNumberOfRows(); k++) {
        //print end of table
        for(int i=0; i<spaces[n-1]+sizeOfCols[n-1]; i++) {
            cout<<" ";
        }
        SetConsoleTextAttribute(h,7);
        cout<<(char)219;
        color=atoi(((t[k]["Color"]).getString()).data());
        if(((t[k]["Color"]).getString())=="")color=7;
        //SetConsoleTextAttribute(h,12);
        for(int i=n-1; i>=0; i--) {
            cout<<"\r";
            for(int j=0; j<spaces[i]-2; j++) {
                cout<<" ";
            }
            cout<<(char)221<<" ";
            SetConsoleTextAttribute(h,color);
            cout<<((string*)(t[k][listOfCols[i]].getData()))->substr(0,sizeOfCols[i]);
            SetConsoleTextAttribute(h,7);
        }
        cout<<endl;
    }
    for(int i=0; i<spaces[n-1]+sizeOfCols[n-1]; i++) {
        cout<<(char)223;
    }
    cout<<(char)223<<endl;
}
