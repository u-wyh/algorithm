#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e5+5;

int n;
int val[MAXN];
int fa[MAXN];

int stk[MAXN];
int top=0;

int ans[MAXN];

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        fa[fx]=fy;
    }
}

void solve(){
    cin>>n;
    for(int i=1;i<=2*n;i++){
        cin>>val[i];
        ans[i]=-1;
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;
    }
    top=0;

    for(int i=1;i<=2*n;i++){
        if(top==0){
            stk[++top]=i;
        }
        else{
            int v=stk[top];
            if(find(val[v])==find(val[i])){
                stk[++top]=i;
            }
            else{
                ans[v]=0;
                ans[i]=1;
                un(val[v],val[i]);
                top--;
            }
        }
    }
    ans[stk[top--]]=1;
    ans[stk[top--]]=0;
    for(int i=1;i<=2*n;i++){
        cout<<(ans[i]==0?'(':')');
    }
    cout<<endl;
}

int main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}