#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e3+5;
const long long INF = 1e15;

int n;
int val[MAXN];

struct node{
    int pos;
    double p;
};
node nums[MAXN];

bool cmp(node &a,node &b){
    return a.p>b.p;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    sort(val+1,val+n+1);

    double ans=INF;
    for(int p=0;p<=n;p++){
        double tmp=0;
        for(int i=1;i<=p;i++){
            nums[i]={i,p-i+1+(n-p)/2.0};
        }
        for(int i=p+1;i<=n;i++){
            nums[i]={i,n-i+1.0};
        }
        sort(nums+1,nums+n+1,cmp);
        for(int i=1;i<=n;i++){
            tmp+=val[nums[i].pos]*nums[i].p;
        }
        ans=min(ans,tmp);
    }
    printf("%.1lf",ans);
    return 0;
}