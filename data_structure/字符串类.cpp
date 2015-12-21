#include<iostream>
#include<cstring>

using namespace std;

class SString{
    private:
        char *str;
        int len;
        const static int ok=1;
        const static int npos=-1;
    public:
    //constructors and other methods
        SString();
        SString(const char *s);
        SString(const SString &s);
        ~SString();
        int & size();
        int find(const SString &s);
        void replace(const SString &s,const SString &re);
    //overload operator methods
        SString & operator =(const SString &s);
        SString & operator =(const char * s);
        char & operator[](int idx);
        const char & operator[](int idx) const;
    //overload operator friends
        friend bool operator <(const SString &s1,const SString &s2);
        friend bool operator >(const SString &s1,const SString &s2);
        friend bool operator ==(const SString &s1,const SString &s2);
        friend bool operator !=(const SString &s1,const SString &s2);
        friend SString operator +(const SString &s1,const SString &s2);
        friend SString operator +=(const SString &s1,const SString &s2);
        friend ostream & operator <<(ostream & os,const SString &s);
        friend istream & operator >>(istream & is,SString &s);

};

//constructors and other methods
SString::SString(){
    len=0;
    str=new char[1];
    str[0]='\0';
}

SString::SString(const char *s){
    len=strlen(s);
    str=new char[len+1];
    strcpy(str,s);
}

SString::SString(const SString &s){
    len=s.len;
    str=new char[len+1];
    strcpy(str,s.str);
}

SString::~SString(){
    delete [] str;
}

int & SString::size(){
    return len;
}

int SString::find(const SString &s){
    int *nex=new int[s.len];
    nex[0]=0;
    for(int i=0,j=0;i<s.len;){
        j=nex[i];
        while(j&&s.str[i]!=s.str[j])
            j=nex[j];
        if(s.str[i]==s.str[j])
            nex[++i]=j+1;
        else
            nex[++i]=0;
    }
    int pos=npos;
    for(int i=0,j=0;i<len;){
        if(str[i]==s.str[j]){
            i++,j++;
            if(j==s.len){
                pos=i-s.len;
                break;
            }
        }
        else
            j?j=nex[j]:i++;
    }
    delete [] nex;
    return pos;
}

void SString::replace(const SString &s,const SString &re){
    int *nex=new int[s.len];
    nex[0]=0;
    for(int i=0,j;i<s.len;){
        j=nex[i];
        while(j&&s.str[i]!=s.str[j])
            j=nex[j];
        if(s.str[i]==s.str[j])
            nex[++i]=j+1;
        else
            nex[++i]=0;
    }

    int length=0;
    char *tt=new char[(len/s.len+1)*re.len+1];

    for(int i=0,j=0;i<len;){
        if(str[i]==s.str[j]){
            tt[length++]=str[i];
            i++,j++;
            if(j==s.len){
                length-=s.len;
                for(int t=0;t<re.len;)
                    tt[length++]=re[t++];
                j=0;
            }
        }
        else
            j?j=nex[j]:tt[length++]=str[i++];

    }
    len=length;
    delete [] str;
    str=new char[len+1];
    for(int i=0;i<len;i++)
        str[i]=tt[i];
    str[len]='\0';
    delete [] tt;
    delete [] nex;
}
//overload operator methods
SString & SString::operator =(const SString &s){
    if(this==&s)
        return *this;
    delete [] str;
    len=s.len;
    str=new char[len+1];
    strcpy(str,s.str);
    return *this;
}

SString & SString::operator =(const char *s){
    delete [] str;
    len=strlen(s);
    str=new char[len+1];
    strcpy(str,s);
    return *this;
}

char & SString::operator [](int idx){
    return str[idx];
}

const char & SString::operator [](int idx) const{
    return str[idx];
}

//overload operator friends
bool operator <(const SString &s1,const SString &s2){
    return strcmp(s1.str,s2.str)<0;
}

bool operator >(const SString &s1,const SString &s2){
    return s2<s1;
}

SString operator +(const SString &s1,const SString &s2){
    SString tmp;
    delete [] tmp.str;
    tmp.len=s1.len+s2.len;
    tmp.str=new char[tmp.len+1];
    strcpy(tmp.str,s1.str);
    strcat(tmp.str,s2.str);
    return tmp;
}

SString operator +=(const SString &s1,const SString &s2){
    return s1+s2;
}

bool operator ==(const SString &s1,const SString &s2){
    return strcmp(s1.str,s2.str)==0;
}

bool operator !=(const SString &s1,const SString &s2){
    return !(s1==s2);
}

ostream & operator <<(ostream & os,const SString &s){
    os<<s.str;
    return os;
}

istream & operator >>(istream & is,SString &s){
    is>>s.str;
    s.len = strlen(s.str);
    return is;
}

int main(){
    SString s1,s2,s3;
    cin>>s1>>s2;
    cout<<"s1="<<s1<<endl;
    cout<<"s2="<<s2<<endl;
    if(s1==s2)
        cout<<"s1==s2"<<endl;
    else
        cout<<"s1!=s2"<<endl;
    cout<<"s2= ";
    cin>>s2;
    cout<<"The position of s2 in si: "<<s1.find(s2)+1<<endl;
    cout<<"s3= ";
    cin>>s3;
    s1.replace(s2,s3);
    cout<<"replace s2 in s1 with s3: "<<s1<<endl;
    return 0;
}
