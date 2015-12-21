#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

class MST{
    struct Edge{
        int u,v,w;
        bool operator <(const Edge &a)const{
            return w<a.w;
        };
    };
    private:
        static const int maxn=1000;
        static const int maxm=4000;
        Edge edge[maxm];
        int par[maxn];
        int n,m,ans;
    public:
        void read(const int & _n,const int & _m);
        int find(int _val);
        bool Kruskal();

        void solve(const int & _n,const int & _m);
};

void MST::read(const int & _n,const int & _m){
    n=_n;m=_m;ans=0;
    for(int i=0;i<maxn;i++)
        par[i]=i;
    for(int i=0;i<n;i++)
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
}

int MST::find(int _val){
    return par[_val]==_val?_val:par[_val]=find(par[_val]);
}

bool MST::Kruskal(){
    sort(edge,edge+m);
    int cnt=0;
    for(int i=0;i<m;i++){
        int u=(*this).find(edge[i].u);
        int v=(*this).find(edge[i].v);
        if(u!=v){
            cnt++;par[v]=u;
            ans+=edge[i].w;
        }
    }
    return cnt==n-1;
}

void MST::solve(const int & _n,const int & _m){
    (*this).read(_n,_m);
    if((*this).Kruskal())
        cout<<"The MST expense: "<<ans<<endl;
    else
        cout<<"This graph is disconnected"<<endl;
}
int main(){
    //freopen("in.txt","r",stdin);
    int n,m;
    while(cin>>n>>m){
        MST G;
        if(n!=0)
            G.solve(n,m);
    }
    return 0;
}
