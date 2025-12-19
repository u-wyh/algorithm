#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int fa[MAXN];
int a,b,p;
bool vis[MAXN];
int prime[MAXN];
int cnt=0;
int ans;

int find(int i){
    return i==fa[i]?i:fa[i]=find(fa[i]);
}

void un(int x,int y){
    //cout<<666<<endl;
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

int main()
{
    cin>>a>>b>>p;
    ans=0;
    for(int i=1;i<=b;i++){
        fa[i]=i;
    }
    for (int i = 2; i*i<= b; i++) {
        if (!vis[i]) {
            for (int j = i*i; j <= b; j += i) {
                vis[j] = 1; // 标记为合数
            }
        }
    }
    for(int i=p;i<=b;i++){
        if(!vis[i]){
            prime[++cnt]=i;
        }
    }
    for(int i=1;i<=cnt;i++){
        int t=0;
        while(t*prime[i]<a){
            t++;
        }
        int pre=t*prime[i];
        while(t*prime[i]<=b){
            un(pre,t*prime[i]);
            t++;
        }
    }
    for(int i=a;i<=b;i++){
        if(fa[i]==i){
            ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
