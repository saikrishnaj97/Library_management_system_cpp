#include "search.cpp"

class student {
    string name;
    string usn;
    string contact;
public:
    void getd() {
        cout<<"\n\tEnter Your Name: ";
        cin.clear();
        fflush(stdin);
        getline(cin,name);
        cout<<"\n\tEnter Your USN: ";
        cin.clear();
        fflush(stdin);
        getline(cin,usn);
    }

    string retname() {
        return name;
    }
    string retusn() {
        return usn;
    }


};


class book {

    string title;
    string author;
    string edition;
    string code;
    string subject;
    int copies;
    string availability;
public:
    book() {
        availability="yes";
    }

    string rettitle() {
        cout<<"\n\tEnter Title of the book:";
        cin.clear();
        fflush(stdin);
        getline(cin,title);
        return title;
    }
    int retcop() {
        cout<<"\n\tEnter no. of copies: ";
        cin>>copies;
        return copies;
    }

    string retauthor() {
        cout<<"\n\tEnter Author of the book:";
        cin.clear();
        fflush(stdin);
        getline(cin,author);
        return author;
    }

    string retedition() {
        cout<<"\n\tEnter Edition:";
        cin>>edition;
        return edition;
    }
    string retcode() {
        cout<<"\n\tenter code:";
        cin>>code;
        return code;
    }
    string retsub() {
        cout<<"\n\tEnter subject to which the book belongs:";
        cin.clear();
        fflush(stdin);
        getline(cin,subject);
        return subject;
    }

    string retavail() {

        return availability;
    }
};
