#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;

class Stack{
    struct Node{
        int val;
        Node *nex;
    };

    private:
        Node *head;
        int _sz;

    public:
        Stack();
        ~Stack();
        void del();
        void push(int _val);
        int top();
        void pop();
        int size();


};

void Stack::del(){
    if(head==NULL)
        return ;
    _sz--;
    Node *tmp=head;
    head=head->nex;
    delete tmp;
}

Stack::Stack(){
    head=NULL;
    _sz=0;
}

Stack::~Stack(){
    Node *tmp;
    while(head!=NULL){
        (*this).del();
    }
}

int Stack::top(){
    return head->val;
}

void Stack::pop(){
    (*this).del();
}

void Stack::push(int _val){
    _sz++;
    Node *tmp=new Node;
    tmp->val=_val;
    tmp->nex=head;
    head=tmp;
}

int Stack::size(){
    return _sz;
}

class Board{
    private:
        static const int MAXN=8;
        static const int MAXM=8;

        int _s,_cnt;
        int vis[MAXN][MAXM];
        bool tag[MAXN][MAXM][8];
        Stack Sta;

    public:
        Board();
        Board(int s,int cnt);
        int solve();
        void print();
};

Board::Board(){
    srand((unsigned)time(0));
    for(int i=0;i<MAXN;i++)
        for(int j=0;j<MAXM;j++){
            vis[i][j]=-1;
            for(int k=0;k<8;k++)
                tag[i][j][k]=false;
        }
    _s=rand()%(MAXN*MAXM-1);
    _cnt=3;
}

Board::Board(int s,int cnt){
    for(int i=0;i<MAXN;i++)
        for(int j=0;j<MAXM;j++){
            vis[i][j]=-1;
            for(int k=0;k<8;k++)
                tag[i][j][k]=false;
        }
    _s=(s-1);
    _cnt=cnt;
}

int Board::solve(){
    int dy[8]={1,-1,2,-2,2,-2,1,-1};
    int dx[8]={-2,-2,-1,-1,1,1,2,2};
    vis[_s/8][_s%8]=1;
    Sta.push(_s);
    int icase=0;
    while(Sta.size()!=0){
        if(Sta.size()==64){
            if(icase<_cnt)
                (*this).print();
            icase++;
        }

        int x=Sta.top()%8;
        int y=Sta.top()/8;
        int flag=-1;
        int maxn=9;
        for(int i=0;i<8;i++){
            int tx=x+dx[i];
            int ty=y+dy[i];
            if(tag[y][x][i]||vis[ty][tx]!=-1||(tx<0||tx>7||ty<0||ty>7))
                continue;

            int cnt=0;
            for(int k=0;k<8;k++){
                int my=ty+dy[k];
                int mx=tx+dx[k];

                if(vis[my][mx]==-1&&(mx>=0&&mx<8&&my>=0&&my<8))
                    cnt++;
            }
            if(cnt<maxn){
                maxn=cnt;
                flag=i;
            }
        }

        if(flag!=-1){
            int ty=y+dy[flag];
            int tx=x+dx[flag];

            Sta.push(ty*8+tx);
            vis[ty][tx]=vis[y][x]+1;
            tag[y][x][flag]=true;
        }
        else{
            vis[y][x]=-1;
            for(int i=0;i<8;i++)
                tag[y][x][i]=false;
            Sta.pop();
        }
    }
    return icase;
}

void Board::print(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            printf("%2d ",vis[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    int n,cnt;
    printf("请输入起始格子(范围1~64)和需要的解的个数：");
    scanf("%d%d",&n,&cnt);
    Board a(n,cnt);
    printf("%d\n",a.solve());
    return 0;
}
