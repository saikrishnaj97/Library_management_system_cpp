#define _WIN32_WINNT 0x0502
#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include "adminFunctions.cpp"
using namespace std;
HANDLE buff = GetStdHandle(STD_OUTPUT_HANDLE);

string usn;

void intro() { //INTRODUCTION
    cout<<"\t\t\t\tLIBRARY MANAGEMENT SYSTEM\n";
}

void insert_delete() {
    system ("cls");
    int ch;
    cout<<"\n\n\t1.INSERT  BOOK";
    cout<<"\n\n\t2.DELETE PARTICULAR BOOK";
    cout<<"\n\n\t3.BACK";
    cout<<"\n\n\tENTER YOUR CHOICE:";
    cin>>ch;
    switch(ch) {
    case 1:
        insertBook();
        break;
    case 2:
        deleteBook();
        break;
    case 3:
        return;
    default:
        cin.clear();
        fflush(stdin);
        break;
    }
}


void display_student() {
    system ("cls");
    intro();
    int ch;
    cout<<"\n\n\t1.DISPLAY STUDENTS WHO HAVE BORROWED";
    cout<<"\n\n\t2.DISPLAY STUDENTS WHO HAVE OVERDUE";
    cout<<"\n\n\t3.BACK";
    cout<<"\n\n\tENTER YOUR CHOICE:";
    cin>>ch;
    switch(ch) {
    case 1:
        displayWhoHaveBorrowed();
        break;
    case 2:
        displayWhoHaveOverdue();
        break;
    case 3:
        return;
    default:
        cout<<ch;
        cin.clear();
        fflush(stdin);
        break;
    }
}


void student_menu() { //Student menu
    //system ("cls");
    int ch;
    while(1) {
        system("cls");
        intro();
        cout<<"\n\n\t1.Borrow Book";//done
        cout<<"\n\n\t2.Return Book";//done
        cout<<"\n\n\t3.Search for a book";
        cout<<"\n\n\t4.View borrowed books";//done
        cout<<"\n\n\t5.Logout";//epic done
        cout<<"\n\n\tPlease Enter Your Choice (1-5)\n\n\t";
        SetConsoleTextAttribute(buff,14);
        cin>>ch;
        SetConsoleTextAttribute(buff,7);
        switch(ch) {
        case 1:
            bookBorrow(usn);
            break;
        case 2:
            bookReturn(usn);
            break;
        case 3:
            studentsBookSearch();
            break;
        case 4:
            viewBorrowedBooks(usn);
            getch();
            break;
        case 5:
            return;
            break;
        default:
            cin.clear();
            fflush(stdin);
            break;
        }
    }
}


void admin_menu() {  //ADMIN MENU
    system ("cls");
    intro();
    int ch2;
    cout<<"\n\n\n\tADMINISTRATOR MENU";
    cout<<"\n\n\t1.Insert Or Delete Books";//done
    cout<<"\n\n\t2.Check Availability";//done
    cout<<"\n\n\t3.Display Borrower's Details";//done
    cout<<"\n\n\t4.Display All Books";
    cout<<"\n\n\t5.Search Book";
    cout<<"\n\n\t6.Search Student";
    cout<<"\n\n\t7.Display Old Books";
    cout<<"\n\n\t8.Logout";
    cout<<"\n\n\tPlease Enter Your Choice (1-6)\n\n\t ";
    SetConsoleTextAttribute(buff,14);
    cin>>ch2;
    SetConsoleTextAttribute(buff,7);
    switch(ch2) {
    case 1:
        insert_delete();
        break;
    case 2:
        checkAvailability();//don
        break;
    case 3:
        display_student();//ppl with overdue , ppl who have just borrowed
        break;
    case 4:
        displayAllBooks();
        break;
    case 5:
        adminSearchBook();
        break;
    case 6:
        adminSearchStudent();
        break;
    case 7:
        adminDisplayOldBooks();
        return;
    case 8:
        return;
    default:
        cin.clear();
        fflush(stdin);
        break;
    }
    admin_menu();

}


void studentLogin() {
    string password;
    string stars="";
    usn="";
    password="";
    char temp;
    system("cls");
    intro();
    cout<<"\tUSN:";
    cin>>usn;
    cout<<"\tPassword:";
    while((temp=getch())!=13) {
        if(temp==8) {
            stars = stars.substr(0,stars.length()-1);
            password = password.substr(0,password.length()-1);
        } else {
            stars += '*';
            password += temp;
        }
        cout<<"\r\t\t\t\t\t\t\t\r\tPassword:";
        SetConsoleTextAttribute(buff,14);
        cout<<stars;
        SetConsoleTextAttribute(buff,7);
    }
    //password.pop_back();
    //cout<<password;
    Table t("student_record.csv",1);
    int flag=0;
    for(int i=0; i<t.getNumberOfRows(); i++) {
        if(t[i]["USN"]==usn&&t[i]["Password"]==password) {
            student_menu();
            flag=1;
            break;
        }
    }
    if(!flag) {
        cout<<"Incorrect usn or password"<<endl;
        getch();
    }
}

void adminLogin() {
    system("cls");
    intro();
    string password;
    password="";
    string stars="";
    char temp;
    cout<<"\n\n\tPassword:";
    while((temp=getch())!=13) {
        if(temp==8) {
            stars = stars.substr(0,stars.length()-1);
            password = password.substr(0,password.length()-1);
        } else {
            stars += '*';
            password += temp;
        }
        cout<<"\r\t\t\t\t\t\t\t\r\tPassword:";
        SetConsoleTextAttribute(buff,14);
        cout<<stars;
        SetConsoleTextAttribute(buff,7);
    }
    if(password=="superuser") {
        admin_menu();
    } else {
        cout<<endl<<"\n\t\tWrong password!";
        getch();
    }
}

int main() {
    int ch;
    COORD sizeOfBuff;
    sizeOfBuff.X=170;
    sizeOfBuff.Y=100;
    SetConsoleScreenBufferSize(buff,sizeOfBuff);
    SetConsoleTextAttribute(buff,7);
    while(1) {
        system("cls");
        intro();
        cout<<"\n\n\tLogin as:";
        cout<<"\n\n\t\t1.Admin";
        cout<<"\n\n\t\t2.Student";
        cout<<"\n\n\t\t3.Exit";
        cout<<endl<<"\tChoice:";
        fflush(stdin);
        cin>>ch;
        switch(ch) {
        case 2:
            studentLogin();
            break;
        case 1:
            adminLogin();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout<<ch;
            cin.clear();
            fflush(stdin);
            break;
        }
    }

    return 0;
}


