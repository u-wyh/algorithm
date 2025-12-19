#include<bits/stdc++.h>
using namespace std;
const int BASE = 499;
const int MAXD = 205;
const int MAXN = 5e3+5;

int d,n,m;
int ans;
int root[MAXD][MAXN];
vector<int>vec[MAXD][MAXN];
long long h[MAXN];
long long p[MAXD];
unordered_map<long long,int>cnt;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
        x=x*10+ch-'0',ch=getchar();
    return x*f;
}

void add(long long val){
    int x=cnt[val];
    ans+=2*x+1;
    cnt[val]++;
}

void del(long long val){
    int x=cnt[val];
    ans-=2*x-1;
    cnt[val]--;
}

int main()
{
    d=read(),n=read(),m=read();
    p[0]=1;
    for(int i=1;i<=d;i++){
        p[i]=p[i-1]*BASE;
    }
    for(int k=1;k<=d;k++){
        for(int i=1;i<=n;i++){
            root[k][i]=i;
            h[i]+=i*p[k];
            vec[k][i].push_back(i);
        }
    }
    for(int i=1;i<=n;i++){
        add(h[i]);
    }
    while(m--){
        int u,v,k;
        u=read(),v=read(),k=read();
        int fx=root[k][u];
        int fy=root[k][v];
        if(fx==fy){
            printf("%d\n",ans);
            continue;
        }
        if(vec[k][fx].size()<vec[k][fy].size()){
            swap(fx,fy);
        }
        for(int i=0;i<(int)vec[k][fy].size();i++){
            int v=vec[k][fy][i];
            vec[k][fx].push_back(v);
            root[k][v]=fx;
            del(h[v]);
            h[v]+=1ll*(fx-fy)*p[k];
            add(h[v]);
        }
        printf("%d\n",ans);
    }
    return 0;
}