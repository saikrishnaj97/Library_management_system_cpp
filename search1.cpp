#include<iostream>
#include<cstdlib>
#include "tableobject.cpp"
using namespace std;
void searchField(Table, string, int);
void searchUI(Table t) {
    string value;
    int ch;
    int a;
    cout<<"Search By:"<<endl;
    cout<<"1.Name\n2.Author\n3.Edition\n4.Code\nSubject"<<endl;
    while(1) {
        a=0;
        cout<<"Choice:"<<endl;
        cin>>ch;
        //cout<<"Enter Value of the String to be searched"<<endl;
        //cin>>value;
        switch(ch) {
        case 1:
            a=1;
            cout<<"Name:";
            cin.clear();
            fflush(stdin);
            getline(cin,value);
            searchField(t, value, a);
            break;
        case 2:
            a=2;
            cout<<"Author:";
            cin.clear();
            fflush(stdin);
            getline(cin,value);
            searchField(t, value, a);
            break;
        case 3:
            a=3;
            cout<<"Edition:";
            cin.clear();
            fflush(stdin);
            getline(cin,value);
            searchField(t, value, a);
            break;
        case 4:
            a=4;
            cout<<"Code:";
            cin.clear();
            fflush(stdin);
            getline(cin,value);
            searchField(t, value, a);
            break;
        case 5:
            a=5;
            cout<<"Subject:";
            cin.clear();
            fflush(stdin);
            getline(cin,value);
            searchField(t, value, a);
            break;
        case 6:
            exit(1);
        default:
            cin.clear();
            fflush(stdin);
            break;
        }
    }
}

Table searchField(Table t, string str, int a) {
    int b=0,c=0,d=0,e=0,f=0;
    Table temp;
    for(int i=0; i<t.getNumberOfRows(); i++) {
        if(a==1) {
            if(t[i]["Name"]==str) {
                temp[b]=t[i];
                b++;
            }
        } else if(a==2) {
            if(t[i]["Author"]==str) {
                temp[c]=t[i];
                c++;
            }
        } else if(a==3) {
            if(t[i]["Edition"]==str) {
                temp[d]=t[i];
                d++;
            }
        } else if(a==4) {
            if(t[i]["Code"]==str) {
                temp[e]=t[i];
                e++;
            }
        } else if(a==5) {
            if(t[i]["Subject"]==str) {
                temp[f]=t[i];
                f++;
            }
        }
    }
    //cout<<"Required data is"<<endl;
    //cout<<temp<<endl;
    return temp;
}

int main() {
    Table t("book.csv",1);
    searchUI(t);
    return 0;
}
