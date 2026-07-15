#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 4e5+5;

int n,q;
long long ans1;
long long ans2;
int val[MAXN];
int t[MAXN];
int tmp[MAXN];

int head;
int cnt;
int key[MAXN];
int ls[MAXN];
int rs[MAXN];
int sz[MAXN];
double priority[MAXN];
long long all[MAXN];

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

void up(int i){
    sz[i]=sz[ls[i]]+sz[rs[i]]+1;
    all[i]=all[ls[i]]+all[rs[i]]+key[i];
}

int getrank(int val){
    int u=head;
    int ans=0;
    while(u!=0){
        if(key[u]<val){
            ans+=sz[ls[u]]+1;
            u=rs[u];
        }
        else{
            u=ls[u];
        }
    }
    return ans+1;
}

void split(int l, int r, int i, int rank) {
    if (i == 0) {
        rs[l] = ls[r] = 0;
    } else {
        if (sz[ls[i]] + 1 <= rank) {
            rs[l] = i;
            split(i, r, rs[i], rank - sz[ls[i]] - 1);
        } else {
            ls[r] = i;
            split(l, i, ls[i], rank);
        }
        up(i);
    }
}

int merge(int l, int r) {
    if (l == 0 || r == 0) {
        return l + r;
    }
    if (priority[l] >= priority[r]) {
        rs[l] = merge(rs[l], r);
        up(l);
        return l;
    } else {
        ls[r] = merge(l, ls[r]);
        up(r);
        return r;
    }
}

signed main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        val[i]=read(),t[i]=read();
        tmp[i]=t[i];
        ans1+=val[i];
    }
    sort(tmp+1,tmp+n+1);
    for(int i=1;i<=n;i++){
        key[++cnt]=tmp[i];
        all[cnt]=tmp[i];
        sz[cnt]=1;
        priority[cnt]=(double)rand()/RAND_MAX;
        head=merge(head,cnt);
    }
    for(int i=1;i<=n;i++){
        ans2+=1ll*(n-i+1)*tmp[i];
    }
    cout<<(ans1-ans2)<<endl;
    while(q--){
        int r,l,tt;
        r=read(),l=read(),tt=read();

        ans1+=l-val[r];
        val[r]=l;

        int rk1=getrank(t[r]);
        split(0,0,head,rk1);
        int lm=rs[0];
        int rt=ls[0];
        ans2+=all[rt];
        // cout<<ans2<<' ';
        ans2-=1ll*(n-rk1+1)*t[r];
        // cout<<ans2<<' ';
        split(0,0,lm,rk1-1);
        head=merge(rs[0],rt);

        int rk2=getrank(tt);
        split(0,0,head,rk2-1);
        lm=rs[0];
        rt=ls[0];
        ans2-=all[rt];
        // cout<<ans2<<' ';
        ans2+=1ll*(n-rk2+1)*tt;
        // cout<<ans2<<' '<<endl;
        t[r]=tt;

        key[++cnt]=tt;
        all[cnt]=tt;
        sz[cnt]=1;
        priority[cnt]=(double)rand()/RAND_MAX;
        head=merge(merge(lm,cnt),rt);

        // cout<<q<<":  "<<ans1<<' '<<ans2<<' '<<rk1<<' '<<rk2<<endl;
        // for(int i=1;i<=n;i++){
        //     cout<<val[i]<<' ';
        // }
        // cout<<endl;
        // for(int i=1;i<=n;i++){
        //     cout<<t[i]<<' ';
        // }
        // cout<<endl;
        // cout<<endl;

        cout<<(ans1-ans2)<<endl;
    }
    return 0;
}