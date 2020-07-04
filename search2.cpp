
#include<iostream>
using namespace std;
#include "tableobject.cpp"
Table search_record(Table t, string value)
{
    int k=0;
    Table temp;
    int n = t.getNumberOfRows();
    int flag=0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<t[i].getNumberOfColumns(); j++)
        {
            if(t[i][j]==value)
            {
                flag=1;
                temp[k]=t[i];
                k++;
                }
        }
    }
    return temp;

}
int main()
{
    cout<<"Welcome to Search\n\n\n";
    Table t("check_h.csv",1);
    Table temp;
    temp = search_record(t, "CompRef");
    cout<<temp;
    temp = t;
    int ch;
    string val;
    do{

    cout<<"Do u want to enter another key to search(1 or 0)"<<endl;
    cin>>ch;
    if(ch==1)
    {
        cout<<"Enter New Key"<<endl;
        cin>>val;
        temp=search_record(temp, val);
    }
    else{
    break;
    }
    }while(1);
    cout<<temp;
}
