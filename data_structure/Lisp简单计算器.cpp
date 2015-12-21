#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
using namespace std;

const int maxlen=100;
char str[maxlen];

template<class T>
class Stack{
    struct Node{
        T val;
        Node *nex;
    };

    private:
        Node *head;
        int _sz;

    public:
        Stack();
        ~Stack();
        void del();
        void push(T _val);
        T top();
        void pop();
        int size();
};

template<class T>
void Stack<T>::del(){
    if(head==NULL)
        return ;
    _sz--;
    Node *tmp=head;
    head=head->nex;
    delete tmp;
}

template<class T>
Stack<T>::Stack(){
    head=NULL;
    _sz=0;
}

template<class T>
Stack<T>::~Stack(){
    Node *tmp;
    while(head!=NULL){
        (*this).del();
    }
}

template<class T>
T Stack<T>::top(){
    return head->val;
}

template<class T>
void Stack<T>::pop(){
    (*this).del();
}

template<class T>
void Stack<T>::push(T _val){
    _sz++;
    Node *tmp=new Node;
    tmp->val=_val;
    tmp->nex=head;
    head=tmp;
}
template<class T>
int Stack<T>::size(){
    return _sz;
}

int cal(){
    Stack<char> op;
    Stack<int> val;
    for(int i=0,sz=strlen(str);i<sz;i++){
        if(isdigit(str[i]))
            val.push(str[i]-'0');
        else{
            switch(str[i]){
                case ')':{
                    char opt=op.top();
                    op.pop();op.pop();
                    int y=val.top();val.pop();
                    int x=val.top();val.pop();
                    int ans;
                    switch(opt){
                        case '+':
                            ans=x+y;break;
                        case '-':
                            ans=x-y;break;
                        case '*':
                            ans=x*y;break;
                        case '/':
                            ans=x/y;break;
                        default:
                            break;
                    }
                    val.push(ans);
                }break;
                default:
                    op.push(str[i]);break;
            }
        }
    }
    return val.top();
}
int main(){
    freopen("in.txt","r",stdin);
    while(cin>>str){
        cout<<cal()<<endl;
    }
}
