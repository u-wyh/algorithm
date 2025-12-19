#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 30*MAXN;
const int BIT = 28;

int n;
int nums[MAXN];
int tree[MAXM][2];
int p[MAXM];
int cnt;

stack<int>st1[2];
stack<int>st2[2];

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

void insert(int num){
    int cur=0;
    for(int b=0;b<=BIT;b++){
        int path=(num>>b)&1;
        if(tree[cur][path]==0){
            tree[cur][path]=++cnt;
        }
        cur=tree[cur][path];
        p[cur]++;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
        insert(nums[i]);
    }
    // for(int i=1;i<=cnt;i++){
    //     cout<<i<<": "<<p[i]<<endl;
    // }
    long long ans=0;
    long long power=1;
    ans+=1ll*p[tree[0][0]]*p[tree[0][1]];
    // cout<<ans<<endl;
    if(tree[0][0])
        st1[1].push(tree[0][0]);//0
    if(tree[0][1])
        st2[1].push(tree[0][1]);//1
    for(int i=0;i<=BIT;i++){
        int now=i&1;
        int pass=1-now;
        int u0=0,v0=0,u1=0,v1=0;
        while(!st1[pass].empty()){
            int u=st1[pass].top();
            st1[pass].pop();
            int node=tree[u][0];
            if(node!=0){
                st1[now].push(node);
                u0+=p[node];
            }
            node=tree[u][1];
            if(node!=0){
                st2[now].push(node);
                u1+=p[node];
            }
        }
        while(!st2[pass].empty()){
            int u=st2[pass].top();
            st2[pass].pop();
            int node=tree[u][0];
            if(node!=0){
                st2[now].push(node);
                v0+=p[node];
            }
            node=tree[u][1];
            if(node!=0){
                st1[now].push(node);
                v1+=p[node];
            }
        }
        power*=2;
        ans+=1ll*(1ll*u0*u1+1ll*v1*v0)*power;
        // cout<<u0<<' '<<v0<<' '<<u1<<' '<<v1<<"   ";
        // cout<<ans<<endl;
    }
    cout<<ans<<endl;
    return 0;
}
/*
3
5 3 9
*/