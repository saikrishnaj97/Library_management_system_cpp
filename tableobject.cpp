#include<iostream>
#include<fstream>
#include "rowobj.cpp"
using namespace std;

class Table {

    RowNode firstNode;

    Header * header;
    int usingHeader;//this is a flag variable telling if header is  being used or not

    int numberOfRows;
    string fileName;


public:
    Table() {
        firstNode=*(new RowNode());
        firstNode.setLink(NULL);
        numberOfRows=0;
        header = NULL;
        usingHeader = 0;
    }

    Table(char * fname , int headerFlag=0) {
        fileName=string(fname);
        firstNode=*(new RowNode());
        firstNode.setLink(NULL);
        numberOfRows=0;
        usingHeader=0;
        header=NULL;
        if(headerFlag==1) {
            header = new Header();
            usingHeader = 1;
        }
        parseAndStoreFile(fname);
    }

    Row & operator [] (int n) {
        RowNode * curr = &firstNode;
        int j=-1;
        while(j!=n&&curr->next()!=NULL) {
            curr = curr->next();
            j++;
        }
        if(j!=n) {
            numberOfRows=n+1;
            while(j!=n) {
                RowNode * temp=new RowNode();
                curr->setLink(temp);
                curr = curr->next();
                curr->setLink(NULL);
                (curr->thisRow()).setHeader(header);
                j++;
            }
        }
        return curr->thisRow();
    }

    int getNumberOfRows() {
        return numberOfRows;
    }

    void addCSVParseableRow(int rowNum, string line) {
        (*this)[rowNum].setHeader(header);
        int colNum=0;
        int i=0;//this the traveling pointer
        string out;
        int j=0;//this is the out pointer
        char symbol;
        int dqflag=0;//1 means inside a double quotes
        while((symbol=line[i])!='\0') {
            switch(symbol) {
            case '\"':
                if(!dqflag) {
                    dqflag=1;
                    i++;
                } else {
                    //check if the next is double quotes or not
                    if(line[i+1]=='\"') {
                        //if the next one is also double quotes the add it to the output
                        out+='\"';
                        i++;
                        i++;
                    } else if(line[i+1]==',') {
                        dqflag=0;
                        (*this)[rowNum][colNum].setDataType(STRING);
                        (*this)[rowNum][colNum++]=out;
                        out="";
                        i++;
                        i++;
                    } else {
                        dqflag=0;//end of double quotes
                        i++;
                    }
                }
                break;
            case ',':
                if(dqflag) {
                    out+=',';
                    i++;
                } else {
                    (*this)[rowNum][colNum].setDataType(STRING);
                    (*this)[rowNum][colNum++]=out;
                    out="";
                    i++;
                }
                break;

            default:
                out+=symbol;
                i++;
                break;
            }
        }
        if(out.length()) {
            (*this)[rowNum][colNum].setDataType(STRING);
            (*this)[rowNum][colNum++]=out;
        }
    }

    void addCSVParseableHeader(string line) {
        int colNum=0;
        int i=0;//this the traveling pointer
        string out;
        int j=0;//this is the out pointer
        char symbol;
        int dqflag=0;//1 means inside a double quotes
        while((symbol=line[i])!='\0') {
            switch(symbol) {
            case '\"':
                if(!dqflag) {
                    dqflag=1;
                    i++;
                } else {
                    //check if the next is double quotes or not
                    if(line[i+1]=='\"') {
                        //if the next one is also double quotes the add it to the output
                        out+='\"';
                        i++;
                        i++;
                    } else if(line[i+1]==',') {
                        dqflag=0;
                        (*header)+=out;
                        out="";
                        i++;
                        i++;
                    } else {
                        dqflag=0;//end of double quotes
                        i++;
                    }
                }
                break;
            case ',':
                if(dqflag) {
                    out+=',';
                    i++;
                } else {
                    (*header)+=out;
                    out="";
                    i++;
                }
                break;

            default:
                out+=symbol;
                i++;
                break;
            }
        }
        if(out.length()) {
            (*header)+=out;
        }
    }

    void parseAndStoreFile(char * name) {
        int usingHeaderFlag = usingHeader;
        int rowNumber=0;
        ifstream file(name,ios::in);
        string s;
        char ch;
        while(ch!=EOF) {
            s="";
            while((ch=file.get())!='\n'&&ch!=EOF) {
                s+=ch;
            }
            if(usingHeaderFlag) {
                usingHeaderFlag=0;
                addCSVParseableHeader(s);
            } else {
                addCSVParseableRow(rowNumber,s);
                rowNumber++;
            }
        }
        //here the deleting will happen
        (*this).deleteRow(numberOfRows-1);
        file.close();
    }

    void save() {
        ofstream out;
        out.open(fileName.data());
        if(usingHeader==1) {
            for(int i=0; i<header->length(); i++) {
                out<<'\"'<<header->revTranslate(i)<<'\"';
                if(i!=header->length()-1) {
                    out<<',';
                }
            }
            out<<'\n';
        }
        for(int i=0; i<numberOfRows; i++) {
            Row r = (*this)[i];
            for(int j=0; j<r.getNumberOfColumns(); j++) {
                out<<'\"'<<r[j]<<'\"';
                if(j!=r.getNumberOfColumns()-1) {
                    out<<',';
                }
            }
            out<<'\n';

        }
        out.close();
    }

    ~Table() {
        //save();
    }

    Header * getHeader() {
        return header;
    }

    int setHeader(Header * newHeader) {
        header=newHeader;
        if(header)usingHeader=1;
        else usingHeader=0;
    }

    int deleteRow(int rowIndex) {
        if(rowIndex<numberOfRows) {
            RowNode *curr,*prev;
            curr = &firstNode;
            prev = &firstNode;
            int j=-1;
            while(j!=rowIndex) {
                prev=curr;
                curr = curr->next();
                j++;
            }
            prev->setLink(curr->next());
            //free(curr);
            numberOfRows--;
            return 1;
        }
        return 0;
    }

    friend ostream & operator << (ostream & , Table &);
};

ostream & operator << (ostream & os , Table & t) {
    if(t.usingHeader==1) {
        for(int i=0; i<t.header->length(); i++) {
            cout<<t.header->revTranslate(i);
            cout<<"\t";
        }
        cout<<endl;
    }
    for(int i=0; i<t.numberOfRows; i++) {
        os<<t[i]<<endl;
    }
    return os;
}

