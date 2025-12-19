#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int MAXN = 5e4+5;

int n,k,m;
int p[MAXN],c[MAXN];
bool bought[MAXN];
int ans=0;

priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>price,coupon;
priority_queue<int,vector<int>,greater<>>delta;

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

signed main()
{
    n=read(),k=read(),m=read();
    for(int i=1;i<=n;i++){
        p[i]=read(),c[i]=read();
        price.push({p[i],i});
        coupon.push({c[i],i});
    }
    for(int i=1;i<=k;i++){
        delta.push(0);
    }
    while(!price.empty()){
        pair<int,int>tmp1=price.top();
        pair<int,int>tmp2=coupon.top();

        if(bought[tmp1.second]){
            price.pop();
            continue;
        }
        if(bought[tmp2.second]){
            coupon.pop();
            continue;
        }

        int d=delta.top();
        if(d+tmp2.first<=tmp1.first){
            m-=d+tmp2.first;
            delta.pop();
            coupon.pop();
            bought[tmp2.second]=true;
            delta.push(p[tmp2.second]-c[tmp2.second]);
        }
        else{
            m-=tmp1.first;
            price.pop();
            bought[tmp1.second]=true;
        }

        if(m>=0){
            ans++;
        }
        else{
            break;
        }
    }
    cout<<ans<<endl;
    return 0;
}