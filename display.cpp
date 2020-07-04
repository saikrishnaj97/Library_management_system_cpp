#include<iostream>
#include "tableobject.cpp"
using namespace std;
void display1(Table t, string column_name)
{
    for(int q=0;q<t.getNumberOfRows();q++)
    {
        cout<<t[q][column_name]<<endl;
    }
}
void display1(Table t, string column_name1, string column_name2)
{
    for(int q=0;q<t.getNumberOfRows();q++)
    {
        cout<<t[q][column_name1]<<"\t"<<t[q][column_name2]<<endl;
    }
}
void display1(Table t, string column_name1, string column_name2, string column_name3)
{
    for(int q=0;q<t.getNumberOfRows();q++)
    {
        cout<<t[q][column_name1]<<"\t"<<t[q][column_name2]<<"\t"<<t[q][column_name3]<<endl;
    }
}
/*int main()
{
    Table t("check_h.csv",1);
    cout<<(*(t.getHeader())).revTranslate(1)<<endl;
    cout<<endl;
    display1(t,"DOP");
    cout<<endl;
    display1(t,"Edition","Availability");
    cout<<endl;
    display1(t,"Name","Edition","Subject");
}*/
