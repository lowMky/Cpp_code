#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>

using namespace std;

class Joseph{
    struct Node{
        int num,val;
        Node *nex;
    };

    private:
        Node *head;
        int _n,_m;

    public:
        Joseph();
        Joseph(int n,int m,int tag);
        ~Joseph();
        void del();
        void print();
};



Joseph::Joseph(){
    head==NULL;
    _n=_m=0;
}

Joseph::Joseph(int n,int m,int tag){
    int maxn;
    if(tag)
        scanf("%d",&maxn);
    _n=n;
    _m=m;
    head=NULL;
    Node *pre=NULL;
    for(int i=1;i<=_n;i++){
        Node *tmp=new Node;
        tmp->nex=NULL;
        tmp->num=i;
        if(tag)
            tmp->val=rand()%maxn+1;
        else
            scanf("%d",&(tmp->val));
        if(head==NULL){
            head=pre=tmp;
        }
        else{
            pre->nex=tmp;
            pre=pre->nex;
        }
    }
    pre->nex=head;
}

Joseph::~Joseph(){
    Node *tmp;
    while(_n>0){
        tmp=head;
        head=head->nex;
        delete tmp;
        _n--;
    }
}

void Joseph::del(){
    Node *tmp=head;
    Node *pre=head;
    while(_n--){
        while(--_m){
            pre=tmp;
            tmp=tmp->nex;
        }
        pre->nex=tmp->nex;
        printf("%d ",tmp->num);
        _m=tmp->val;
        delete tmp;
        pre=pre->nex;
        tmp=pre;
    }
}

void Joseph::print(){
    Node *tmp=head;
    printf("n=%d m=%d\n",_n,_m);
    do{
        printf("%d %d\n",tmp->num,tmp->val);
        tmp=tmp->nex;
    }while(head!=tmp);
}

int main(){
    int n,m,tag;

    srand((unsigned)time(0)); //设定时间种子
    printf("请依次输入人数 (N) 初始位置 (M) :\n");
    scanf("%d%d",&n,&m);

    printf("模式1：输入各个节点的密码值:\n");
    printf("模式2：输入随机生成密码值的上界:\n");
    scanf("%d",&tag);
    Joseph test(n,m,tag-1);
    test.del();
    return 0;
}
