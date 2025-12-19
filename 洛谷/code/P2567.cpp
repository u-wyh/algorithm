#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e4+5;

int l,r;
int nums[MAXN];
int tot;
int val[MAXN];
int cnt;
int ans;

void dfs(int val){
    if(val>r){
        return ;
    }
    if(val){
        nums[++tot]=val;
    }
    dfs(val*10+6);
    dfs(val*10+8);
}

void sieve(){
    sort(nums+1,nums+tot+1);
    for(int i=1;i<=tot;i++){
        bool flag=false;
        for(int j=1;j<=cnt;j++){
            if(nums[i]%val[j]==0){
                flag=true;
                break;
            }
        }
        if(!flag){
            val[++cnt]=nums[i];
        }
    }
}

bool cmp(int a,int b){
    return a>b;
}

int count(int l,int r,int val){
    return r/val-(l+val-1)/val+1;
}

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

void dfs(int dep,int t,int all){
    if(all>r){
        return ;
    }
    if(dep>cnt){
        if(t==0){
            return ;
        }
        ans+=count(l,r,all)*((t&1)?1:-1);
        return ;
    }
    dfs(dep+1,t,all);
    int lcm=all/gcd(all,val[dep]);
    if(1.0*lcm*val[dep]<=r){
        dfs(dep+1,t+1,lcm*val[dep]);
    }
}

signed main()
{
    cin>>l>>r;
    dfs(0);
    sieve();
    sort(val+1,val+cnt+1,cmp);
    dfs(1,0,1);
    cout<<ans<<endl;
    return 0;
}