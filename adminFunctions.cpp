#include<iostream>
#include "studentFunctions.cpp"
using namespace std;

int code() {
    int a;
    ifstream in("code.dat",ios::in | ios::binary);
    if(!in) {
        cout<<"File Dosen't exist";
        return 0;
    }
    in.read((char *)&a,sizeof(int));
    if(a==0) {
        a=11111;
    }
    a++;
    in.close();
    ofstream out("code.dat", ios::out | ios::binary);
    out.write((char*)&a,sizeof(int));
    out.close();
    return a;
}

int insertBook() {
    system("cls");
    char ch;
    int j=0;
    book b[10];
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,80,"%d-%m-%Y",timeinfo);
    string date(buffer);
    Table t("book.csv",1);
    int i=t.getNumberOfRows();
    do {

        string name=b[j].rettitle();
        string author=b[j].retauthor();
        string edition = b[j].retedition();
        string sub=b[j].retsub();
        int n=b[j].retcop();
        if(name==""||author==""||edition==""||sub=="") {
            return 0;
        }
        for(int k=0; k<n; k++) {
            int a;
            a=code();
            string s="";
            while(a>0) {
                s=((char)((a%10)+'0'))+s;
                a/=10;
            }
            t[i]["Name"]=name;
            t[i]["Author"]=author;
            t[i]["Edition"]=edition;
            t[i]["Code"]=s;
            t[i]["Subject"]=sub;
            t[i]["DOP"]=date;
            t[i]["Availability"]=b[j].retavail();
            i++;
        }

        cout<<"\n\tDo u want to enter one more book[y/n]:";
        cin>>ch;
        j++;
    } while(ch=='y'||ch=='Y');
    t.save();
    return 1;
}


int deleteBook() {
    system("cls");
    char ch;
    int flag=0;
    book b1[10];
    int j=0;
    Table t("book.csv",1);
    int n=t.getNumberOfRows();
    do {
        string book_code=b1[j].retcode();
        for(int i=0; i<n; i++) {
            if(t[i]["Code"]==book_code  && t[i]["Availability"]=="yes") {
                flag=1;
                t.deleteRow(i);
                break;
            }
        }
        if(flag==1) {
            cout<<"\n\tBOOK IS DELETED FROM THE LIST";
        } else {
            cout<<"\n\tBOOK WITH CODE"<<book_code<<" NOT FOUND";
        }
        j++;
        cout<<"\n\t DO YOU WANT TO DELETE ONE MORE BOOK[y/n]: ";
        cin>>ch;
    } while(ch=='Y' || ch=='y');
    t.save();
    return 0;
}

void displayWhoHaveBorrowed() {
    system("cls");
    Table stud("student_record.csv",1);
    Table temp;
    temp.setHeader(new Header);
    for(int i=0,j=0; i<stud.getNumberOfRows(); i++) {
        if(stud[i]["book1"]!="" || stud[i]["book2"]!="" || stud[i]["book3"]!="") {
            temp[j]["Name"]=stud[i]["Name"];
            temp[j]["USN"]=stud[i]["USN"];
            temp[j]["Dept."]=stud[i]["Department"];
            temp[j]["Sem."]=stud[i]["Semester"];
            temp[j]["Sec."]=stud[i]["Section"];
            //temp[j]["Phone"]=stud[i]["Phone"];
            //temp[j]["Email Id"]=stud[i]["Email"];
            int bookCounter=1;
            string bookPrefix("Book ");
            string dobPrefix("Date ");
            //char a[20];
            if(stud[i]["book1"]!="") {
                temp[j][bookPrefix+(char)(bookCounter+'0')]=stud[i]["book1"];
                temp[j][dobPrefix+(char)(bookCounter+'0')]=stud[i]["dob1"];
                bookCounter++;
            }
            if(stud[i]["book2"]!="") {
                temp[j][bookPrefix+(char)(bookCounter+'0')]=stud[i]["book2"];
                temp[j][dobPrefix+(char)(bookCounter+'0')]=stud[i]["dob2"];
                bookCounter++;
            }
            if(stud[i]["book3"]!="") {
                temp[j][bookPrefix+(char)(bookCounter+'0')]=stud[i]["book3"];
                temp[j][dobPrefix+(char)(bookCounter+'0')]=stud[i]["dob3"];
                bookCounter++;
            }
            if(bookCounter==2)temp[j]["Color"]="14";
            else if(bookCounter==3)temp[j]["Color"]="9";
            else temp[j]["Color"]="12";
            j++;
        }
    }
    string columns[]= {string("Name"),string("USN"),string("Dept."),string("Sem."),string("Sec."),string("Book 1"),string("Date 1"),string("Book 2"),string("Date 2"),string("Book 3"),string("Date 3")};
    int widths[]= {20,10,5,4,4,6,10,6,10,6,10};
    displayTable(temp,columns,widths,11);
    getch();
}

void displayWhoHaveOverdue() {
    system("cls");
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,80,"%d-%m-%Y",timeinfo);
    string today(buffer);
    Value v(STRING);
    v=today;
    v.toDate();
    Table temp;
    temp.setHeader(new Header);
    Table stud("student_record.csv",1);
    for(int i=0,j=0; i<stud.getNumberOfRows(); i++) {
        stud[i]["dob1"].toDate();
        stud[i]["dob2"].toDate();
        stud[i]["dob3"].toDate();
        if( (v-stud[i]["dob1"]>(86400*15)) || (v-stud[i]["dob2"]>(86400*15)) || (v-stud[i]["dob3"]>(86400*15))) {
            /*cout<<"\n\n\t\tName:"<<stud[i]["Name"]<<endl;
            cout<<"\t\tUSN:"<<stud[i]["USN"]<<endl;
            cout<<"\t\tPhone:"<<stud[i]["Phone"]<<endl;
            cout<<"\t\tEmail:"<<stud[i]["Email"]<<endl;
            cout<<"\t\tOverdue books:";
            if(v-stud[i]["dob1"]>(86400*15))cout<<stud[i]["book1"]<<"\t\t";
            if(v-stud[i]["dob2"]>(86400*15))cout<<stud[i]["book2"]<<"\t\t";
            if(v-stud[i]["dob3"]>(86400*15))cout<<stud[i]["book3"]<<"\t\t";
            cout<<endl<<endl<<"\t\t______________________________________________________________________________";*/
            temp[j]["Name"]=stud[i]["Name"];
            temp[j]["USN"]=stud[i]["USN"];
            temp[j]["Dept."]=stud[i]["Department"];
            temp[j]["Sem."]=stud[i]["Semester"];
            temp[j]["Sec."]=stud[i]["Section"];
            temp[j]["Phone"]=stud[i]["Phone"];
            temp[j]["Email Id"]=stud[i]["Email"];
            int bookCounter=1;
            string bookPrefix("Book ");
            string dobPrefix("Over.");
            //char a[20];
            if(v-stud[i]["dob1"]>(86400*15)) {
                temp[j][bookPrefix+(char)(bookCounter+'0')]=stud[i]["book1"];
                temp[j][dobPrefix+(char)(bookCounter+'0')]=(v-stud[i]["dob1"])/(86400)-15;
                temp[j][dobPrefix+(char)(bookCounter+'0')]+="days";
                bookCounter++;
            }
            if(v-stud[i]["dob2"]>(86400*15)) {
                temp[j][bookPrefix+(char)(bookCounter+'0')]=stud[i]["book2"];
                temp[j][dobPrefix+(char)(bookCounter+'0')]=(v-stud[i]["dob2"])/(86400)-15;
                temp[j][dobPrefix+(char)(bookCounter+'0')]+="days";
                bookCounter++;
            }
            if(v-stud[i]["dob3"]>(86400*15)) {
                temp[j][bookPrefix+(char)(bookCounter+'0')]=stud[i]["book3"];
                temp[j][dobPrefix+(char)(bookCounter+'0')]=(v-stud[i]["dob3"])/(86400)-15;
                temp[j][dobPrefix+(char)(bookCounter+'0')]+="days";
                bookCounter++;
            }
            if(bookCounter==2)temp[j]["Color"]="11";
            else if(bookCounter==3)temp[j]["Color"]="13";
            else temp[j]["Color"]="12";
            j++;
        }

    }
    string columns[]= {string("Name"),string("USN"),string("Dept."),string("Sem."),string("Sec."),string("Phone"),string("Email Id"),string("Book 1"),string("Over.1"),string("Book 2"),string("Over.2"),string("Book 3"),string("Over.3")};
    int widths[]= {20,10,5,4,4,10,30,6,10,6,10,6,10};
    displayTable(temp,columns,widths,13);
    getch();
}

void checkAvailability() {
    system("cls");
    string s;
    cout<<"\n\t\tCode:";
    cin>>s;
    Table t("book.csv",1);
    Table temp;
    temp = searchTable(t,string("Code"),s);
    //cout<<temp;
    if(temp.getNumberOfRows()==1) {
        cout<<"\tFound!"<<endl;
        cout<<"\t\t"<<temp[0]["Name"]<<" by "<<temp[0]["Author"]<<endl<<"\t\tEdition:"<<temp[0]["Edition"]<<endl;
        cout<<"\t\tDate Of Purchase"<<temp[0]["DOP"]<<endl;
        if(temp[0]["Availability"]=="yes"){
            cout<<"\t\tIn stock";
        }else{
            Table stud("student_record.csv",1);
            temp = searchTable(stud,s);
            cout<<"\t\tBorrowed By "<<temp[0]["Name"]<<endl;
            cout<<"\t\tUSN:"<<temp[0]["USN"];
        }
    } else cout<<"Wrong Code";
    getch();
}

void displayAllBooks() {
    system("cls");
    Table book("book.csv",1);
    Table student("student_record.csv",1);
    for(int i=0; i<book.getNumberOfRows(); i++) {
        if(book[i]["Availability"]=="no") {
            book[i]["USN"]=searchTable(student,book[i]["Code"].getString())[0]["USN"];
            book[i]["Section"]=searchTable(student,book[i]["Code"].getString())[0]["Section"];
            book[i]["Semester"]=searchTable(student,book[i]["Code"].getString())[0]["Semester"];
            book[i]["Dept."]=searchTable(student,book[i]["Code"].getString())[0]["Department"];
            book[i]["Color"]="12";
        } else {
            book[i]["Color"]="10";
        }
    }
    string cols[]= {string("Name"),string("Author"),string("Edition"),string("Subject"),string("Code"),string("Availability"),string("USN"),string("Dept."),string("Semester"),string("Section")};
    int sizes[]= {25,15,7,12,6,12,10,5,8,7};
    displayTable(book,cols,sizes,10);
    getch();
}

void adminSearchBook() {

    Table t("book.csv",1);
    Table temp;
    Table student("student_record.csv",1);
    int ch;
    string value;
    for(int i=0; i<t.getNumberOfRows(); i++) {
        if(t[i]["Availability"]=="no") {
            t[i]["USN"]=searchTable(student,t[i]["Code"].getString())[0]["USN"];
            t[i]["Borrower"]=searchTable(student,t[i]["Code"].getString())[0]["Name"];
            t[i]["Section"]=searchTable(student,t[i]["Code"].getString())[0]["Section"];
            t[i]["Semester"]=searchTable(student,t[i]["Code"].getString())[0]["Semester"];
            t[i]["Dept."]=searchTable(student,t[i]["Code"].getString())[0]["Department"];
            t[i]["Color"]="12";

        } else {
            t[i]["Color"]="10";
        }
    }
    do {
        system("cls");
        temp=t;
        string cols[]= {string("Name"),string("Author"),string("Edition"),string("Subject"),string("Code"),string("Availability"),string("USN"),string("Borrower"),string("Dept."),string("Semester"),string("Section")};
        int sizes[]= {25,15,7,12,6,12,10,15,5,8,7};
        displayTable(temp,cols,sizes,10);
        do {
            cout<<"\n\tAdd another filter[y/n]:";
            if(getche()!='y')break;
            cout<<"\n\n\tEnter key value: ";
            cin.clear();
            fflush(stdin);
            getline(cin,value);
            temp = searchTableAll(temp, value);
            system("cls");
            cout<< "\n\n";
            displayTable(temp,cols,sizes,10);
        } while(1);
        system("cls");
        cout<<"\n\tSearch for another book[y/n]:";
    } while(getche()=='y');
}

void adminSearchStudent() {
    Table student("student_record.csv",1);
    Table temp;
    int ch;
    string value;
    do {
        system("cls");
        temp=student;
        string cols[]= {string("Name"),string("USN"),string("Department"),string("Semester"),string("Section"),string("Phone"),string("Email")};
        int sizes[]= {25,10,10,8,7,10,30};
        displayTable(temp,cols,sizes,7);
        do {
            cout<<"\n\tAdd another filter[y/n]:";
            if(getche()!='y')break;
            cout<<"\n\n\tEnter key value: ";
            cin.clear();
            fflush(stdin);
            getline(cin,value);
            temp = searchTableAll(temp, value);
            system("cls");
            cout<< "\n\n";
            displayTable(temp,cols,sizes,7);
        } while(1);
        system("cls");
        cout<<"\n\tSearch for another book[y/n]:";
    } while(getche()=='y');
}

void adminDisplayOldBooks() {
    system("cls");
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer,80,"%d-%m-%Y",timeinfo);
    string today(buffer);
    Value v(STRING);
    v=today;
    v.toDate();
    Table book("book.csv",1);
    Table book2("book.csv",1);
    Table temp;
    temp.setHeader(new Header);
    for(int i=0,j=0; i<book.getNumberOfRows(); i++) {
        book2[i]["DOP"].toDate();
        if((v-book2[i]["DOP"])/(86400*365*5)>0) {
            temp[j]["Name"]=book[i]["Name"];
            temp[j]["Author"]=book[i]["Author"];
            temp[j]["Edition"]=book[i]["Edition"];
            temp[j]["Subject"]=book[i]["Subject"];
            temp[j]["Code"]=book[i]["Code"];
            temp[j]["DOP"]=book[i]["DOP"];
        }
    }
    string cols[]= {string("Name"),string("Author"),string("Edition"),string("Subject"),string("Code"),string("DOP")};
    int sizes[]= {25,15,7,15,6,11};
    cout<<temp.getNumberOfRows();
    if(temp.getNumberOfRows()>0)
        displayTable(temp,cols,sizes,6);
    else cout<<"No Books are older than 5 Years :)";
    getch();
}
