#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1<<20;

int n,k;
int f[MAXN];
vector<int>g[21];
bool vis[MAXN];

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

int main()
{
    n=read(),k=read();
    for(int i=1;i<=n;i++){
        int val=read();
        vis[val]=true;
    }
    int maxval=(1<<k)-1;
    for(int i=0;i<=maxval;i++){
        for(int j=i;j;j-=(j&-j)){
            f[i]=max(f[i],f[i-(j&-j)]);
        }
        if(vis[i]){
            f[i]++;
            g[f[i]].push_back(i);
        }
    }
    cout<<1<<endl;
    cout<<f[maxval]<<endl;

    for(int i=1;i<=f[maxval];i++){
        cout<<g[i].size()<<' ';
        for(int j=0;j<(int)g[i].size();j++){
            cout<<g[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}