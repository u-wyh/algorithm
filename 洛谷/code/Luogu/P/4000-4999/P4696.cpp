#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

int n,m;

int p[MAXN];
int rk[MAXN];

int low[MAXN];
int high[MAXN];
int pre[MAXN];
int suf[MAXN];

int fail[MAXN];

int h[MAXN];

int ans[MAXN];
int anscnt;

bool check(int i,int q,int *p){
    int nxt=q+1;
    int st=i-q;

    int lt=low[nxt];
    if(lt!=0&&p[st+lt-1]>=p[i]){
        return false;
    }
    int rt=high[nxt];
    if(rt!=0&&p[st+rt-1]<=p[i]){
        return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;

    for(int i=1;i<=n;i++){
        cin>>p[i];
        rk[p[i]]=i;
    }
    for(int i=1;i<=m;i++){
        cin>>h[i];
    }

    for(int i=0;i<=n+1;i++){
        pre[i]=i-1;
        suf[i]=i+1;
    }

    for(int pos=n;pos>=1;pos--){
        int now=rk[pos];

        int lt=pre[now];
        int rt=suf[now];

        suf[lt]=rt;
        pre[rt]=lt;

        if(lt>=1){
            low[pos]=p[lt];
        }
        if(rt<=n){
            high[pos]=p[rt];
        }
    }

    int q=0;
    for(int i=2;i<=n;i++){
        while(q>0&&!check(i,q,rk)){
            q=fail[q];
        }
        if(check(i,q,rk)){
            q++;
        }

        fail[i]=q;
    }

    q=0;

    for(int i=1;i<=m;i++){
        while(q>0&&!check(i,q,h)){
            q=fail[q];
        }
        if(check(i,q,h)){
            q++;
        }
        if(q==n){
            q=fail[q];
            ans[++anscnt]=i-n+1;
        }
    }

    cout<<anscnt<<endl;
    for(int i=1;i<=anscnt;i++){
        cout<<ans[i]<<' ';
    }
    return 0;
}