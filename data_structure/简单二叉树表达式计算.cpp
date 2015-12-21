#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class Calculator{
    struct Node{
        Node *l,*r;
        char ch;
    };

    private:
        int tmp;
        Node *root;
    public:
        Calculator();
        ~Calculator();
        void del(Node * _root);
        void bulid(const char *s);
        void add(Node * _root,const char *s);
        double solve();
        double cal(const Node * _root);
        void show();
        void print(const Node * _root);

};

Calculator::Calculator(){
    root=new Node;
    root->l=root->r=NULL;
    root->ch='\0';
    tmp=0;
}

Calculator::~Calculator(){
    (*this).del(root);
}

void Calculator::del(Node * _root){
    if(_root->l)
        del(_root->l);
    if(_root->r)
        del(_root->r);
    delete _root;
}

void Calculator::bulid(const char *s){
    (*this).add(root,s);
}

void Calculator::add(Node * _root,const char *s){
    _root->ch=s[tmp++];
    if(isdigit(s[tmp-1])||tmp==strlen(s))
        return ;
    _root->l=new Node;
    _root->l->l=_root->l->r=NULL;
    (*this).add(_root->l,s);
    _root->r=new Node;
    _root->r->l=_root->r->r=NULL;
    (*this).add(_root->r,s);
}

double Calculator::solve(){
    return (*this).cal(root);
}

double Calculator::cal(const Node * _root){
    if(_root->l==NULL&&_root->r==NULL)
        return _root->ch-'0';
    else{
        double x=cal(_root->l);
        double y=cal(_root->r);
        switch(_root->ch){
            case '+':
                return x+y;
            case '-':
                return x-y;
            case '*':
                return x*y;
            case '/':
                return x/y;
            case '^':
                return pow(x,y);
        }
    }
}

void Calculator::show(){
    (*this).print(root);
}

void Calculator::print(const Node * _root){
    if(_root->l){
        cout<<"(";
        (*this).print(_root->l);
    }
    cout<<_root->ch;
    if(_root->r){
        (*this).print(_root->r);
        cout<<")";
    }
}
int main(){
    //freopen("in.txt","r",stdin);
    Calculator E;
    char str[20];
    cin>>str;
    cout<<str<<endl;
    E.bulid(str);
    E.show();
    cout<<"="<<E.solve()<<endl;
    return 0;
}
