#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>

using namespace std;

struct Node{
    int val;
    Node *nex;
};

struct Queue{
    Node *head;
    Node *tail;
    int sz;
};

void init(Queue *A);
void add(Queue *A,int val);
void clear(Queue *A);
void del(Queue *A);
int size(Queue *A);
int front(Queue *A);
void init_maze();
bool solve(Queue *A);
void print(int flag);

static const int MAXN=100;
static const int MAXM=100;

int maze[MAXN][MAXM];
int vis[MAXN][MAXM];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
int n,m,s,e;
Queue Que;


void init(Queue *A){
    A->head=A->tail=NULL;
    A->sz=0;
}
void add(Queue *A,int _val){
    A->sz++;
    Node *tmp=new Node;
    tmp->val=_val;
    tmp->nex=NULL;
    if(A->head==NULL)
        A->head=A->tail=tmp;
    else{
        A->tail->nex=tmp;
        A->tail=tmp;
    }
}

void clear(Queue *A){
    Node *tmp;
    while(A->head!=NULL){
        del(A);
    }
}

void del(Queue *A){
    if(A->head==NULL)
        return ;
    A->sz--;
    Node *tmp=A->head;
    A->head=A->head->nex;
    delete tmp;
}

int size(Queue *A){
    return A->sz;
}

int front(Queue *A){
    return A->head->val;
}

void init_maze(){
    srand((unsigned)time(0));
    s=rand()%20+20;
    do{
        e=rand()%20+(n*m-21);
    }while(e==s);
    maze[s/m][s%m]=2;
    maze[e/m][e%m]=3;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            vis[i][j]=-1;
            if(maze[i][j]==2||maze[i][j]==3)
                continue;
            maze[i][j]=rand()%10;
            maze[i][j]=maze[i][j]<7?1:0;
        }
    }
}

bool solve(){
    vis[s/m][s%m]=2;
    add(&Que,s);
    while(size(&Que)){
        int z=front(&Que);
        del(&Que);
        if(z==e)
            return true;
        int x=z%m;
        int y=z/m;

        for(int i=0;i<4;i++){
            int tx=x+dx[i];
            int ty=y+dy[i];
            if(vis[ty][tx]!=-1||!maze[ty][tx]||(tx<0||tx>=m||ty<0||ty>=n))
                continue;
            add(&Que,ty*m+tx);
            vis[ty][tx]=z;
        }

    }
    return false;
}

void print(int flag){
    vis[s/m][s%m]=2;
    vis[e/m][s%m]=3;
    if(flag)
        for(int k=vis[e/m][e%m];k!=s;k=vis[k/m][k%m])
            maze[k/m][k%m]=-1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            switch(maze[i][j]){
                case -1:
                    printf("*");break;
                case 0:
                    printf("#");break;
                case 1:
                    printf(".");break;
                case 2:
                    printf("@");break;
                case 3:
                    printf("^");break;
                default:
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
}


int main(){
    printf("请输入迷宫的行数和列数: ");
    scanf("%d%d",&n,&m);
    init(&Que);
    init_maze();
    printf("\n符号代表的意义:\n'.'=空地 '#'=墙 '*'=答案 '@'=起点 '^'=终点\n");
    print(0);
    if(solve())
        print(1);
    else
        printf("There is no answer\n");
}
