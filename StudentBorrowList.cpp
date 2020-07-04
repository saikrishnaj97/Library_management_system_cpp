#include<iostream>
#include "tableobject.cpp"
using namespace std;

//int StudentBorrowList()
int main()
{
    cout<<"\tStudent"<<"\tUSN"<<"\tPhone"<<endl;
    Table n("student_record.csv",1);
    for(int i=0;i<n.getNumberOfRows();i++)
    {
        if(n[i]["book1"]!="" && n[i]["book2"]!="" && n[i]["book3"]!="")
        {
            cout<<n[i]["Name"]<<n[i]["USN"]<<n[i]["Phone"]<<n[i]["Email"]<<endl;
        }
    }
}
