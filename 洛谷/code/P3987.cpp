#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 5e5+5;

int n,m;
int val[MAXN];
long long tree[MAXN];
vector<int>fac[MAXM];

vector<vector<int>::iterator> need;

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

inline int lowbit(int x){
    return x&-x;
}

void add(int x,int v){
    while(x<=n){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

long long query(int x){
    long long ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

void prepare(){
    for(int i=1;i<=n;i++){
        add(i,val[i]);
        if(val[i]==0){
            continue;
        }
        for(int j=1;j*j<=val[i];j++){
            if(val[i]%j==0){
                fac[j].push_back(i);
                if(j*j!=val[i]){
                    fac[val[i]/j].push_back(i);
                }
            }
        }
    }
    for(int i=1;i<MAXM;i++){
        if(!fac[i].empty()){
            sort(fac[i].begin(),fac[i].end());
        }
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    prepare();
    while(m--){
        int op,l,r,x;
        op=read(),l=read(),r=read();
        if(op==1){
            x=read();
            if(x==1||fac[x].empty()){
                continue;
            }
            auto lt=lower_bound(fac[x].begin(),fac[x].end(),l);
            auto rt=upper_bound(fac[x].begin(),fac[x].end(),r);
            if(lt==fac[x].end()){
                continue;
            }
            need.clear();
            for(auto it=lt;it!=rt;it++){
                int pos=*it;
                if(val[pos]%x){
                    continue;
                }
                int old=val[pos];
                int now=old/x;
                val[pos]=now;
                add(pos,now-old);
                if(val[pos]%x!=0){
                    need.push_back(it);
                }
            }
            if(!need.empty()){
                for(int i=need.size()-1;i>=0;i--){
                    fac[x].erase(need[i]);
                }
            }
        }
        else{
            printf("%lld\n",query(r)-query(l-1));
        }
    }
    return 0;
}