#include<iostream>
using namespace std;
struct HeaderNode {
    string name;
    struct HeaderNode * link;
};

class Header {
    int numberOfNodes;
    struct HeaderNode headerHead;
public:
    Header() {
        numberOfNodes=0;
        headerHead.name="this is the head";
        headerHead.link=NULL;
    }

    void operator += (string s) {
        numberOfNodes++;
        struct HeaderNode * curr;
        curr=&headerHead;
        while(curr->link!=NULL) {
            curr=curr->link;
        }
        curr->link=new HeaderNode;
        curr=curr->link;
        curr->link=NULL;
        curr->name=s;
    }

    void operator += (char * s) {
        (*this)+=*(new string(s));
    }

    void disp() {
        struct HeaderNode * curr = headerHead.link;
        while(curr!=NULL) {
            cout<<curr->name<<endl;
            curr=curr->link;
        }
    }

    int translate (string s) {
        int i=0;
        struct HeaderNode * curr = headerHead.link;
        while(curr!=NULL) {
            if(s!=curr->name) {
                curr = curr->link;
                i++;
            } else {
                return i;
            }
        }
        return -1;
    }

    int translate (char * s) {
        return translate(string(s));
    }

    string revTranslate(int n){
        if(n>=numberOfNodes){
            return string("");
        }else{
            int i=0;
            struct HeaderNode * curr = headerHead.link;
            while(i!=n){
                curr = curr->link;
                i++;
            }
            return curr->name;
        }
    }

    int length(){
        return numberOfNodes;
    }

};
