#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>

using namespace std;

class Set{
    struct Node{
        int val;
        Node *nex;
    };

    private:
        int _sz;
        Node *head;

    public:
        Set();
        Set(int _sz);
        ~Set();
        Set& operator = (const Set &A);
        bool find(const int &val);
        void sort();
        void quick_sort(Node *L,Node *R);
        Set inter(Set &A);
        Set unio(Set &A);
        Set comple(Set &A);
        void add(int val);
        void print();

};

Set::Set(){
    head=NULL;
    _sz=0;
}

Set& Set::operator = (const Set &A){
    Node *tA=A.head;
    while(tA!=NULL){
        (*this).add(tA->val);
        tA=tA->nex;
    }
    return *this;
}

bool Set::find(const int &val){
    Node *tmp=head;
    while(tmp!=NULL){
        if((tmp->val)==val)
            break;
        tmp=tmp->nex;
    }
    return tmp!=NULL;
}

void Set::add(int val){
    _sz++;
    Node *pnew=new Node;
    pnew->val=val;
    pnew->nex=NULL;
    if(head==NULL){
        head=pnew;
    }
    else{
        Node *tmp=head;
        while((tmp->nex)!=NULL){
            tmp=tmp->nex;
        }
        tmp->nex=pnew;
    }
}

Set::Set(int sz){
    _sz=0;
    head=NULL;
    while(_sz<sz){
        int tmp=rand()%26;
        while((*this).find(tmp)){
            tmp=rand()%26;
        }
        (*this).add(tmp);
    }
    (*this).sort();
}

Set::~Set(){
    Node *tmp;
    while(_sz--){
        tmp=head;
        head=head->nex;
        delete tmp;
    }
}

void Set::sort(){
    quick_sort(head,NULL);
}

void Set::quick_sort(Node *L,Node *R){
    if(L==R)
        return;
    Node *p=L;
    Node *q=L->nex;
    int key=L->val;
    while(q!=R){
        if((q->val)<key){
            p=p->nex;
            swap(p->val,q->val);
        }
        q=q->nex;
    }
    swap(p->val,L->val);

    if(L!=R){
        quick_sort(L,p);
        quick_sort(p->nex,R);
    }
}

Set Set::inter(Set &A){
    A.sort();
    (*this).sort();
    Set tmp;
    Node *tA=A.head;
    Node *tB=this->head;

    while(tA!=NULL&&tB!=NULL){
        if((tA->val)==tB->val){
            tmp.add(tA->val);
            tA=tA->nex;
            tB=tB->nex;
        }
        else if((tA->val)<tB->val){
            tmp.add(tA->val);
            tA=tA->nex;
        }
        else{
            tmp.add(tB->val);
            tB=tB->nex;
        }
    }
    while(tA!=NULL){
        tmp.add(tA->val);
        tA=tA->nex;
    }
    while(tB!=NULL){
        tmp.add(tB->val);
        tB=tB->nex;
    }
    return tmp;
}

Set Set::unio(Set &A){
    A.sort();
    (*this).sort();

    Set tmp;
    Node *tA=A.head;
    Node *tB=this->head;

    while(tA!=NULL&&tB!=NULL){
        if((tA->val)==tB->val){
            tmp.add(tA->val);
            tA=tA->nex;
            tB=tB->nex;
        }
        else if((tA->val)<tB->val)
            tA=tA->nex;
        else
            tB=tB->nex;
    }
    return tmp;
}

Set Set::comple(Set &A){
    A.sort();
    (*this).sort();

    Set tmp;
    Node *tA=A.head;
    Node *tB=this->head;

    while(tB!=NULL){
        if(!A.find(tB->val))
            tmp.add(tB->val);
        tB=tB->nex;
    }
    return tmp;
}

void Set::print(){
    Node *tmp=head;
    while(tmp!=NULL){
        printf("%c ",(tmp->val)+'a');
        tmp=tmp->nex;
    }
    printf("\n");
}

int main(){
    srand((unsigned)time(0));
    int t1,t2;
    printf("请分别输入两个集合的元素个数:\n");
    scanf("%d %d",&t1,&t2);
    Set a(t1);
    Set b(t2);
    printf("集合A：");
    a.print();
    printf("集合B: ");
    b.print();
    Set c=a.inter(b);
    printf("交集: ");
    c.print();
    Set d=a.unio(b);
    printf("并集：");
    d.print();
    Set e=a.comple(b);
    printf("差集：");
    e.print();
    return 0;
}
