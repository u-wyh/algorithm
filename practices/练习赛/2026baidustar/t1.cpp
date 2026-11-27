#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef __int128_t i128;
const int MAXN = 105;

int n,k,s;
struct node{
    int a,b;
};
node nums[MAXN];

bool cmp(node &a,node &b){
    if(a.a!=b.a){
        return a.a<b.a;
    }
    return a.b>b.b;
}

int stk[200];
int top=0;

void print(i128 ans){
    top=0;
    while(ans){
        stk[++top]=ans%10;
        ans/=10;
    }
    if(top){
        while(top){
            cout<<stk[top--];
        }
        cout<<endl;
    }
    else{
        cout<<0<<endl;
    }
}

void solve(){
    cin>>n>>k>>s;
    for(int i=1;i<=n;i++){
        cin>>nums[i].a>>nums[i].b;
    }
    sort(nums+1,nums+n+1,cmp);
    i128 ans=s;
    int now=0;
    while(now+1<=n&&ans>=nums[now+1].a){
        ans+=nums[now+1].b;
        now++;
    }
    while(k){
        k--;
        ans*=2;
        while(now+1<=n&&ans>=nums[now+1].a){
            ans+=nums[now+1].b;
            now++;
        }
    }
    print(ans);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}