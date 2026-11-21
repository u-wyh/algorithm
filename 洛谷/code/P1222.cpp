// https://www.luogu.com.cn/problem/P1222
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+5;

int n;
struct node{
    int y,l,r;
};
int cnt;
node nums[MAXN];
int ans;

bool cmp(node &a,node &b){
    if(a.y!=b.y){
        return a.y<b.y;
    }
    return a.l<b.l;
}

int calc(int l,int r,int t){
    int len=0;
    int lt=nums[l].l;
    int rt=nums[l].r-t;
    for(int i=l+1;i<=r;i++){
        if(nums[i].l>rt){
            len+=rt-lt;
            lt=nums[i].l;
            rt=nums[i].r-t;
        }
        else{
            rt=max(rt,nums[i].r-t);
        }
    }
    len+=rt-lt;
    // cout<<"   "<<l<<' '<<r<<' '<<len<<endl;
    return len;
}

void compute(int l,int r){
    int a=calc(l,r,0);
    int b=calc(l,r,1);
    ans+=a+b;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,y,m;
        cin>>x>>y>>m;
        for(int j=0;j<m;j++){
            nums[++cnt]={y+j,x,x+m-j};
        }
    }
    sort(nums+1,nums+cnt+1,cmp);

    int l=1,r=1;
    while(l<=cnt){
        while(r+1<=cnt && nums[r+1].y==nums[l].y){
            r++;
        }
        compute(l,r);
        r++;
        l=r;
    }
    // cout<<ans<<endl;
    double res=ans/2.0;
    printf("%.1f",res);
    return 0;
}