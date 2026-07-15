#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n;
vector<int>vec[MAXN];

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

int find(int st,int v){
    int l=0,r=vec[v].size()-1,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(vec[v][mid]>st){
            ans=vec[v][mid];
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        int u=read();
        vec[u].push_back(i);
    }
    int q=read();
    while(q--){
        int m=read();
        int u=0;
        for(int i=1;i<=m;i++){
            int v=read();
            if(u==-1){
                continue;
            }
            u=find(u,v);
        }
        if(u==-1){
            printf("NIE\n");
        }
        else{
            printf("TAK\n");
        }
    }
    return 0;
}