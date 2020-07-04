#include<iostream>
#include "values.cpp"
#include "header.cpp"

class Row {

    int numberOfColumns;
    ValueNode firstNode;
    int usingHeader;//if header is being used or not is specified by this
    Header * header;

public:
    Row() {
        firstNode=*(new ValueNode());
        firstNode.setLink(NULL);
        numberOfColumns=0;
        usingHeader = 0;
    }

    Value & operator [] (int n) {
        ValueNode * curr = &firstNode;
        int j=-1;
        while(j!=n&&curr->next()!=NULL) {
            curr = curr->next();
            j++;
        }
        if(j!=n) {
            numberOfColumns=n+1;
            while(j!=n) {
                ValueNode * temp=new ValueNode();
                temp->thisValue().setDataType(STRING);
                curr->setLink(temp);
                curr = curr->next();
                curr->setLink(NULL);
                j++;
            }
        }
        return curr->thisValue();
    }

    Value & operator [] (char * s) {
        return (*this)[string(s)];
    }

    Value & operator [] (string s) {
        int result = header->translate(s);
        if(result!=-1) {
            return (*this)[result];
        } else {
            (*header)+=s;
            result = header->translate(s);
            return (*this)[result];
        }
    }

    int getNumberOfColumns() {
        return numberOfColumns;
    };

    void setHeader(Header * h) { // we are actually storing the starting address of the header used by this row
        header = h;
        if(header != NULL)usingHeader = 1;
        else usingHeader = 0;
    }

    friend ostream & operator << (ostream & , Row & r);
};

ostream & operator << (ostream & os , Row & r) {
    for(int i=0; i<r.numberOfColumns; i++) {
        cout<<r[i]<<'\t';
    }
    return os;
}

class RowNode {
    Row r;
    RowNode * link;
public:
    RowNode() {
        r=*(new Row());
        link=NULL;
    }
    RowNode * next() {
        return link;
    }
    Row & thisRow() {
        return r;
    }
    void setLink(RowNode * l) {
        link=l;
    }
};

/*int main() {
    Row r;
    r[0].setDataType(INTEGER);
    r[0]=1;
    r[12].setDataType(INTEGER);
    r[12]=125;
    cout<<r[0]<<r[2]<<r[12];
    cout<<endl<<r.getNumberOfColumns();
}*/
