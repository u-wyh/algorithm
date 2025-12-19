#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9+7;
const int MAXN = 1e5+5;

int n,m,k;
struct node{
    int x,y,op;
}nums[MAXN];

int power(int a,int b){
    int ans=1;
    while(b){
        if(b&1){
            ans=(ans*a)%MOD;
        }
        b>>=1;
        a=(a*a)%MOD;
    }
    return ans;
}

bool cmpx(node a,node b){
    return a.x<b.x;
}

bool cmpy(node a,node b){
    return a.y<b.y;
}

int compute1(){
    // cout<<111<<endl;
    sort(nums+1,nums+k+1,cmpx);
    int res=n;
    int l=1,r=0;
    while(r<k){
        res--;
        l=r+1;
        r++;
        while(nums[r+1].x==nums[l].x&&r<k){
            r++;
        }
        int base=nums[l].op^(nums[l].y&1);
        for(int i=l+1;i<=r;i++){
            if((nums[i].op^(nums[i].y&1))!=base){
                return 0;
            }
        }
    }
    return power(2,res);
}

int compute2(){
    // cout<<222<<endl;
    sort(nums+1,nums+k+1,cmpy);
    int res=m;
    int l=1,r=0;
    while(r<k){
        res--;
        l=r+1;
        r++;
        while(nums[r+1].y==nums[l].y&&r<k){
            r++;
        }
        int base=nums[l].op^(nums[l].x&1);
        for(int i=l+1;i<=r;i++){
            if((nums[i].op^(nums[i].x&1))!=base){
                return 0;
            }
        }
    }
    return power(2,res);
}

int compute3(){
    // cout<<333<<endl;
    if(k==0){
        return 2;
    }
    int base=((nums[1].x+nums[1].y)&1)^nums[1].op;
    for(int i=2;i<=k;i++){
        if((((nums[i].x+nums[i].y)&1)^nums[i].op)!=base){
            return 0;
        }
    }
    return 1;
}

signed main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=k;i++){
        char op;
        cin>>op>>nums[i].x>>nums[i].y;
        nums[i].op=(op=='+')?1:0;
    }
    int ans=0;
    ans=compute1()+compute2()-compute3();
    ans%=MOD;
    ans=(ans+MOD)%MOD;
    cout<<ans<<endl;
    return 0;
}