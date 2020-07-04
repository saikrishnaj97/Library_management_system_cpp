#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

enum Type {NOTHING,INTEGER,FRACTION,STRING,MDATE};
class Date {
public:
    int day,month,year;
    Date() {
        day=1;
        month=1;
        year=1970;
    }
    void setDate(int d,int m,int y) {
        day=d;
        month=m;
        year=y;
    }

    friend ostream & operator << (ostream & os,Date & d);
};
ostream & operator << (ostream & os,Date & d) {
    os<<d.day<<'-'<<d.month<<'-'<<d.year;
    return os;
}

class Value {
    Type dataType;
    void * data;
public:
    Value() {//default constructor
        dataType=NOTHING;
        data=NULL;
    }

    Value(Type t) {
        dataType = t;
        switch(dataType) {
        case NOTHING:
            data=NULL;
            break;
        case INTEGER:
            data=new int;
            break;
        case FRACTION:
            data=new double;
            break;
        case MDATE:
            data = new Date();
            break;
        case STRING:
            data = new string();
            break;
        default:
            data=NULL;
            break;
        }
    }

    Value(const Value & v) {
        dataType = v.dataType;
        switch(dataType) {
        case NOTHING:
            data=NULL;
            break;
        case INTEGER:
            data=new int;
            *(int*)data = *((int *)v.data);
            break;
        case FRACTION:
            data=new float;
            *(float*)data = *((float *)v.data);
            break;
        case MDATE:
            data = new Date();
            *(Date*)data = *((Date *)v.data);
            break;
        case STRING:
            data = new string();
            *(string*)data = *((string *)v.data);
            break;
        default:
            data=NULL;
            break;
        }
    }

    void setDataType(Type t) {
        if(dataType==t)
            return;
        if(dataType!=NOTHING)
            delete data;
        dataType=t;
        switch(dataType) {
        case NOTHING:
            data=NULL;
            break;
        case INTEGER:
            data=new int;
            break;
        case FRACTION:
            data=new double;
            break;
        case MDATE:
            data = new Date();
            break;
        case STRING:
            data = new string();
            break;
        default:
            data=NULL;
            break;
        }
    }

    void operator += (string s){
        if(dataType==STRING){
            *((string*)data) = *((string*)data) + s;
        }
    }

    Value operator = (int);

    Value operator = (double);

    Value operator = (string);

    friend ostream & operator << (ostream & os,Value v);

    int operator - (Date & d2){
        if(dataType==MDATE){
            Date d1;
            d1 = *((Date*)data);
            //cout<<d2.day<<" "<<d2.month<<" "<<d2.year<<endl;
            struct tm * t1,*t2;
            struct tm temp1,temp2;
            t1 = & temp1;
            t2 = & temp2;
            t1->tm_sec=0;
            t1->tm_min=0;
            t1->tm_hour=0;
            t1->tm_mday=d1.day;
            t1->tm_mon=d1.month-1;
            t1->tm_year=d1.year-1900;
            t2->tm_sec=0;
            t2->tm_min=0;
            t2->tm_hour=0;
            t2->tm_mday=d2.day;
            t2->tm_mon=d2.month-1;
            t2->tm_year=d2.year-1900;
            time_t time1 = mktime(t1);
            time_t time2 = mktime(t2);
            //cout<<time1<<" "<<time2<<endl;
            return time1-time2;
        }
    }

    int operator - (Value & v){
        if(dataType==v.dataType){
            switch(dataType){
            case MDATE:
                return (*this)-*((Date*)(v.data));
            }
        }
    }

    int operator == (string s) {
        if(*((string*)data)==s) {
            return 1;
        } else {
            return 0;
        }
    }

    int operator == (char * ch) {
        return operator == (string(ch));
    }

    int operator == (const Value & v) {
        if(dataType==v.dataType) {
            switch (dataType) {
            case INTEGER:
                break;
            case FRACTION:
                break;
            case STRING:
                return (*this)==*((string*)v.data);
                break;
            case MDATE:
                Date d1,d2;
                d1=*((Date*)data);
                d2=*((Date*)v.data);
                if(d1.day==d2.day&&d1.month==d2.month&&d1.year==d2.year)
                    return 1;
                else return 0;
                break;
                //default:
                //     return 0;
                //    break;
            }

        }
        return 0;
    }

    int operator == (Date d2) {
        if(dataType==MDATE) {
            Date d1;
            d1=*((Date*)data);
            if(d1.day==d2.day&&d1.month==d2.month&&d1.year==d2.year)
                return 1;
            else return 0;
        }
    }

    int operator !=(string s) {
        return !((*this)==(s));
    }

    int operator != (char * ch) {
        return !((*this)==(ch));
    }

    int toDate() {
        if(dataType==STRING) {
            string s;
            if((s=*((string*)data))!="") {
                setDataType(MDATE);
                Date * ptr = (Date*)data;
                int d,m,y;
                int loc1,loc2;
                loc1 = s.find("-");
                loc2 = s.find("-",loc1+1);
                d=atoi(s.substr(0,loc1).data());
                m=atoi(s.substr(loc1+1,loc2-loc1-1).data());
                y=atoi(s.substr(loc2+1).data());
                ptr->setDate(d,m,y);
            }
        }
        return 0;
    }

    void * getData(){
        return data;
    }

    string getString(){
        if(dataType==STRING){
            return *((string*)data);
        }else{
            return string("");
        }
    }
};

Value Value::operator = (int n) {
    string tempS("");
    switch(dataType) {
    case INTEGER:
        *((int*)data)=n;
        break;
    case FRACTION:
        *((float*)data)=n;
        break;
    case STRING:
        while(n>0){
            tempS = ((char)(n%10+'0'))+tempS;
            n/=10;
        }
        *((string*)data)=tempS;
        break;
    default:
        return *this;
        break;
    }
    return *this;
}

Value Value::operator = (double f) {
    switch (dataType) {
    case INTEGER:
        *((int*)data)=f;
        break;
    case FRACTION:
        *((float*)data)=f;
        break;
    case STRING:
        return *this;
        break;
    case MDATE:
        return *this;
        break;
    default:
        break;
    }
    return *this;
}

Value Value::operator = (string s) {
    switch (dataType) {
    case INTEGER:
        return *this;
        break;
    case FRACTION:
        return *this;
        break;
    case STRING:
        *((string*)data)=s;
        break;
    case MDATE:
        return *this;
        break;
    default:
        break;
    }
    return *this;
}

ostream & operator << (ostream & os,Value v) {
    switch (v.dataType) {
    case INTEGER:
        os<<*(int*)v.data;
        break;
    case FRACTION:
        os<<*(float*)v.data;
        break;
    case STRING:
        os<<*(string*)v.data;
        break;
    case MDATE:
        os<<*(Date*)v.data;
        break;
    default:
        break;
    }
    return os;
}

int operator - (Date & d , Value & v){
    return v-d;
}

class ValueNode {
    Value v;
    ValueNode * link;
public:
    ValueNode() {
        v=(*new Value());
    }
    ValueNode * next() {
        return link;
    }
    Value & thisValue() {
        return v;
    }
    void setLink(ValueNode * l) {
        link=l;
    }
};










