#include<iostream>
#include<cstring>
using namespace std;

class SString{
    private:
        char *str;
        int len;

    public:
        SString();
        SString(const char *s);
        ~sstring();
}

SString::SString(){
    len=0;
    str=new char[1];
    str[0]=0;
}

SString::SString(const char *s){
    len=strlen(s)+1;
    str=new char[len];
    strcpy(str,s);
}

SString::~SString(){
    delete str[];
}
