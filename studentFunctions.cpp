#include<iostream>
#include<conio.h>
#include<ctime>
#include<math.h>
#include "utilities.cpp"

Table searchField(Table t, string str, int a) {
    int b=0,c=0,d=0,e=0,f=0;
    Table temp;
    for(int i=0; i<t.getNumberOfRows(); i++) {
        if(a==1) {
            if(myMatch(t[i]["Name"].getString(),str)){
                temp[b]=t[i];
                b++;
            }
        } else if(a==2) {
            if(myMatch(t[i]["Author"].getString(),str)) {
                temp[c]=t[i];
                c++;
            }
        } else if(a==3) {
            if(myMatch(t[i]["Edition"].getString(),str)) {
                temp[d]=t[i];
                d++;
            }
        } else if(a==4) {
            if(myMatch(t[i]["Code"].getString(),str)) {
                temp[e]=t[i];
                e++;
            }
        } else if(a==5) {
            if(myMatch(t[i]["Subject"].getString(),str)) {
                temp[f]=t[i];
                f++;
            }
        }
    }
    //cout<<"Required data is"<<endl;
    //cout<<temp<<endl;
    return temp;
}

int viewBorrowedBooks(string);

int bookReturn(string usn) {
    //student st;
    //st.getd();
    // string name=st.retname();
    //string usn=st.retusn();
    if(!viewBorrowedBooks(usn)) {
        getch();
        return 0;
    }
    cout<<endl;
    //system("cls");
    string code;
    cout<<"\n\tEnter Book Code: ";
    cin>>code;
    Table s("student_record.csv",1);
    int m=s.getNumberOfRows();
    for(int i=0; i<m; i++) {
        if(s[i]["USN"]==usn) {
            if(s[i]["book1"]==code) {
                s[i]["book1"]="";
                s[i]["dob1"]="";
            } else if(s[i]["book2"]==code) {
                s[i]["book2"]="";
                s[i]["dob2"]="";
            } else if(s[i]["book3"]==code) {
                s[i]["book3"]="";
                s[i]["dob3"]="";
            } else {
                cout<<"\n\tYou did not borrow this!!!"<<endl;
                getch();
                return 0;
            }
            break;
        }
    }
    s.save();

    Table t("book.csv",1);
    int n=t.getNumberOfRows();
    for(int i=0; i<n; i++) {
        if(t[i]["Code"]==code) {
            t[i]["Availability"]="yes";
            cout<<"\t"<<t[i]["Name"]<<" by "<<t[i]["Author"]<<" has been returned";
            getch();
            break;
        }
    }
    t.save();
    return 1;
}

int bookBorrow(string usn) {
    system("cls");
    string code;
    int coun=0;
    int flag=0;
    int pos=0;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,80,"%d-%m-%Y",timeinfo);
    string date(buffer);
    Value v(STRING);
    v=date;
    v.toDate();
    Table s("student_record.csv",1);
    Table stud("student_record.csv",1);//this has stuff converted to date and all
    Table t("book.csv",1);
    int m=s.getNumberOfRows();//m is the number of rows
    for(int i=0; i<m; i++) {
        if(s[i]["USN"]==usn) {
            coun++;
            pos=i;
            break;
        }
    }

    stud[pos]["dob1"].toDate();
    stud[pos]["dob2"].toDate();
    stud[pos]["dob3"].toDate();

    if((v-stud[pos]["dob1"]>(86400*15)) || (v-stud[pos]["dob2"]>(86400*15)) || (v-stud[pos]["dob3"]>(86400*15))) {
        cout<<"\t\tYou have overdues : \n";
        if(v-stud[pos]["dob1"]>(86400*15))cout<<"\t\t"<<stud[pos]["book1"]<<"\t"<<(v-stud[pos]["dob1"])/(86400)<<"days"<<endl;
        if(v-stud[pos]["dob2"]>(86400*15))cout<<"\t\t"<<stud[pos]["book2"]<<"\t"<<(v-stud[pos]["dob2"])/(86400)<<"days"<<endl;
        if(v-stud[pos]["dob3"]>(86400*15))cout<<"\t\t"<<stud[pos]["book3"]<<"\t"<<(v-stud[pos]["dob3"])/(86400)<<"days";
        coun=0;
        getch();
    }
    if(coun) {
        if(s[pos]["book1"]!="" && s[pos]["book2"]!="" && s[pos]["book3"]!="") {
            cout<<"\n\tMaximum limit is reached";
            getch();
            return 1;
        }

        if(s[pos]["book1"]=="" || s[pos]["book2"]=="" || s[pos]["book3"]=="") {

            int n=t.getNumberOfRows();
            string code;
            cout<<"\n\tBook code:";
            cin>>code;
            for(int i=0; i<n; i++) {
                if(t[i]["Code"]==code && t[i]["Availability"]=="yes") {
                    flag=1;
                    t[i]["Availability"]="no";
                    break;
                }
            }
            if(flag==1) {
                if(s[pos]["book1"]=="") {
                    s[pos]["book1"]=code;
                    s[pos]["dob1"]=date;
                } else if(s[pos]["book2"]=="") {
                    s[pos]["book2"]=code;
                    s[pos]["dob2"]=date;
                } else {
                    s[pos]["book3"]=code;
                    s[pos]["dob3"]=date;
                }
                s.save();
                cout<<"\n\t"<<searchTable(t,string("Code"),code)[0]["Name"]<<" by "<<searchTable(t,string("Code"),code)[0]["Author"]<<" has been borrowed";
                getch();
            } else {
                cout<<"\n\tBook not found";
                getch();
            }
            t.save();//saving the file explicitly
        }
    }
}

int viewBorrowedBooks(string usn) {
    system("cls");
    fflush(stdin);
    string code;
    int coun=0;
    int flag=0;
    int pos=0;
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,80,"%d-%m-%Y",timeinfo);
    string date(buffer);
    Value v(STRING);
    v=date;
    v.toDate();
    //Table s("student_record.csv",1);
    Table stud("student_record.csv",1);
    Table t("book.csv",1);
    int m=stud.getNumberOfRows();//m is the number of rows
    for(int i=0; i<m; i++) {
        if(stud[i]["USN"]==usn) {
            coun++;
            pos=i;
            break;
        }
    }

    stud[pos]["dob1"].toDate();
    stud[pos]["dob2"].toDate();
    stud[pos]["dob3"].toDate();

    if(stud[pos]["book1"]!="" || stud[pos]["book2"]!="" || stud[pos]["book3"]!="") {
        int temp;
        if(stud[pos]["book1"]!="") {
            cout<<"\t\t"<<stud[pos]["book1"]<<endl;
            Table oneRow;
            oneRow = searchTable(t,string("Code"),stud[pos]["book1"].getString());
            cout<<"\t\t"<<oneRow[0]["Name"]<<" by "<<oneRow[0]["Author"]<<endl<<"\t\tEdition:"<<oneRow[0]["Edition"]<<endl;
            cout<<"\t\t"<<abs(temp=(15-(v-stud[pos]["dob1"])/86400))<<" days";
            if(temp>0)cout<<" remaining"<<endl;
            else cout<<" overdue"<<endl;
            cout<<"\t\t________________________________________________"<<endl;
        }
        if(stud[pos]["book2"]!="") {
            cout<<"\t\t"<<stud[pos]["book2"]<<endl;
            Table oneRow;
            oneRow = searchTable(t,string("Code"),stud[pos]["book2"].getString());
            cout<<"\t\t"<<oneRow[0]["Name"]<<" by "<<oneRow[0]["Author"]<<endl<<"\t\tEdition:"<<oneRow[0]["Edition"]<<endl;
            cout<<"\t\t"<<abs(temp=(15-(v-stud[pos]["dob2"])/86400))<<" days";
            if(temp>0)cout<<" remaining"<<endl;
            else cout<<" overdue"<<endl;
            cout<<"\t\t________________________________________________"<<endl;
        }
        if(stud[pos]["book3"]!="") {
            cout<<"\t\t"<<stud[pos]["book3"]<<endl;
            Table oneRow;
            oneRow = searchTable(t,string("Code"),stud[pos]["book3"].getString());
            cout<<"\t\t"<<oneRow[0]["Name"]<<" by "<<oneRow[0]["Author"]<<endl<<"\t\tEdition:"<<oneRow[0]["Edition"]<<endl;
            cout<<"\t\t"<<abs(temp=(15-(v-stud[pos]["dob3"])/86400))<<" days";
            if(temp>0)cout<<" remaining"<<endl;
            else cout<<" overdue"<<endl;
            cout<<"\t\t________________________________________________"<<endl;
        }
        return 1;//meaning atleast one book
    } else {
        cout<<"\t\tYou haven't borrowed any books";
    }
    return 0;//meaning zero books
    //getch();
}

int studentsBookSearch() {

    //cout<<"Welcome to Search\n\n\n";
    string value;
    Table t("book.csv",1);
    Table temp;
    for(int i=0; i<t.getNumberOfRows(); i++) {
        if(t[i]["Availability"]=="no") {
            t[i]["Color"]="12";
        } else {
            t[i]["Color"]="10";
        }
    }
    do {
        system("cls");
        temp=t;
        string cols[]= {string("Name"),string("Author"),string("Edition"),string("Subject"),string("Code"),string("Availability")};
        int sizes[]= {25,15,7,12,6,12};
        displayTable(temp,cols,sizes,6);
        do {
            cout<<"\n\tAdd another filter[y/n]:";
            if(getche()!='y')break;
            /*cout<<"\n\n\tEnter key value: ";
            cin.clear();
            fflush(stdin);
            getline(cin,value);
            temp = searchTable(temp, value);
            system("cls");
            cout<< "\n\n";*/
            cout<<"\r                                  \r\tSearch By:"<<endl;
            cout<<"\t\t1.Name\n\t\t2.Author\n\t\t3.Edition\n\t\t4.Code\n\t\t5.Subject"<<endl;
            cout<<"\t\tChoice:";
            int ch;
            cin>>ch;
            cout<<"\t\t";
            switch(ch) {
            case 1:
                cout<<"Name:";
                cin.clear();
                fflush(stdin);
                getline(cin,value);
                temp=searchField(temp, value, ch);
                break;
            case 2:
                cout<<"Author:";
                cin.clear();
                fflush(stdin);
                getline(cin,value);
                temp = searchField(temp, value, ch);
                break;
            case 3:
                cout<<"Edition:";
                cin.clear();
                fflush(stdin);
                getline(cin,value);
                temp = searchField(temp, value, ch);
                break;
            case 4:
                cout<<"Code:";
                cin.clear();
                fflush(stdin);
                getline(cin,value);
                temp = searchField(temp, value, ch);
                break;
            case 5:
                cout<<"Subject:";
                cin.clear();
                fflush(stdin);
                getline(cin,value);
                temp = searchField(temp, value, ch);
                break;
            case 6:
                exit(1);
            default:
                cin.clear();
                fflush(stdin);
                break;
            }
            system("cls");
            displayTable(temp,cols,sizes,6);
        } while(1);
        system("cls");
        cout<<"\n\tSearch for another book[y/n]:";
    } while(getche()=='y');
}

