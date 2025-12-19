#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 4e5+5;
const int MAXM = 2e5+5;
const int BASE = 499;

int n,m;
char s[MAXN];
char t[MAXM];
int p[MAXN];
int hs[MAXN];
int ht[MAXN];
int ans;
struct node{
    int len,sub;
};
node lt[MAXN];
node rt[MAXN];

int tree[2][MAXN];

int gethashs(int l,int r){
    return hs[r]-hs[l-1]*p[r-l+1];
}

int gethasht(int l,int r){
    return ht[r]-ht[l-1]*p[r-l+1];
}

void prepare(){
    p[0]=1;
    for(int i=1;i<=n;i++){
        p[i]=p[i-1]*BASE;
    }
    for(int i=1;i<=n;i++){
        hs[i]=hs[i-1]*BASE+s[i]-'a';
    }
    for(int i=1;i<=m;i++){
        ht[i]=ht[i-1]*BASE+t[i]-'a';
    }
}

void compute(int pos){
    int l=0,r=min(m,n-pos+1),ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(gethashs(pos,pos+mid-1)==gethasht(1,mid)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    lt[pos]={ans,pos};
    // cout<<pos<<" : "<<ans<<' ';
    l=0,r=min(m,pos),ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(gethashs(pos-mid+1,pos)==gethasht(m-mid+1,m)){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    // cout<<ans<<endl;
    rt[pos]={ans,pos};
}

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v,int op){
    while(x<=n){
        tree[op][x]+=v;
        x+=lowbit(x);
    }
}

int query(int x,int op){
    int ans=0;
    while(x){
        ans+=tree[op][x];
        x-=lowbit(x);
    }
    return ans;
}

bool cmp1(node a,node b){
    return a.len>b.len;
}

bool cmp2(node a,node b){
    return a.len<b.len;
}

signed main()
{
    scanf("%s %s",s+1,t+1);
    n=strlen(s+1);
    m=strlen(t+1);
    if(n<m){
        cout<<0<<endl;
        return 0;
    }
    prepare();
    int hasht=ht[m];
    for(int i=m;i<n;i++){
        if(gethashs(i-m+1,i)==hasht){
            ans+=1ll*(n-i+1)*(n-i)/2;
        }
    }
    cout<<' '<<ans<<endl;
    for(int i=2;i<n-m+2;i++){
        if(gethashs(i,i+m-1)==hasht){
            ans+=1ll*i*(i-1)/2;
        }
    }
    cout<<' '<<ans<<endl;
    for(int i=1;i<=n;i++){
        compute(i);
    }
    sort(lt+1,lt+n+1,cmp2);
    sort(rt+1,rt+n+1,cmp2);

    for(int i=1;i<=n;i++){
        cout<<i<<' ';
    }
    cout<<endl;
    for(int i=1;i<=n;i++){
        cout<<lt[i].len<<' ';
    }
    cout<<endl;
    for(int i=1;i<=n;i++){
        cout<<rt[i].len<<' ';
    }
    cout<<endl;

    int l0=1,r0=0,l1=0,r1=n;
    while(l0+1<=n&&lt[l0+1].len==0){
        l0++;
    }
    l0++;
    for(int i=l0;i<=n&&lt[i].len!=m;i++){
        add(lt[i].sub,1,0);
    }
    while(r1>0&&rt[r1].len==m){
        r1--;
    }
    int val=0;
    int B=0;
    for(int i=1;i<m;i++){
        r0=l0;
        while(r0<=n&&lt[r0].len==i){
            r0++;
        }
        r0--;
        l1=r1;
        while(l1>0&&rt[l1].len==m-i){
            l1--;
        }
        l1++;
        for(int j=l0;j<=r0;j++){
            val+=query(max(0ll,rt[j].sub-m),0);
        }
        for(int j=l1;j<=r1;j++){
            val-=B-query(min(n,lt[j].sub+m-1),1);
        }
        for(int j=l0;j<=r0;j++){
            add(lt[j].sub,-1,0);
        }
        for(int j=l1;j<=r1;j++){
            add(rt[j].sub,1,1);
            B++;
        }
        cout<<l0<<' '<<r0<<' '<<l1<<' '<<r1<<' '<<val<<endl;
        l0=r0+1,r1=l1-1;
        ans+=val;
    }
    cout<<ans<<endl;
    return 0;
}