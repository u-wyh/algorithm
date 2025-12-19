#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e3+5;
const int MAXM = 1e4+5;

int n,m,k;
int d[MAXN];
struct node{
    int t,st,en;
}nums[MAXM];
struct COUNT{
    int cnt,sub;
}arr[MAXN];
int tim[MAXN];
int beg[MAXN];
int ove[MAXN];

bool cmp(COUNT a,COUNT b){
    return a.cnt>b.cnt;
}

int main()
{
    cin>>n>>m>>k;
    for(int i=2;i<=n;i++){
        cin>>d[i];
        arr[i].sub=i;
    }
    for(int i=1;i<=m;i++){
        cin>>nums[i].t>>nums[i].st>>nums[i].en;
        tim[nums[i].st]=max(tim[nums[i].st],nums[i].t);
        arr[nums[i].en].cnt++;
    }
    sort(arr+1,arr+n+1,cmp);
    for(int i=1;i<=n;i++){
        if(k<=0||arr[i].sub==1){
            break;
        }
        if(k>=d[arr[i].sub]){
            k-=d[arr[i].sub];
            d[arr[i].sub]=0;
        }
        else{
            d[arr[i].sub]-=k;
            k=0;
        }
    }
    beg[1]=ove[1]=tim[1];
    for(int i=2;i<=n;i++){
        ove[i]=beg[i-1]+d[i];
        beg[i]=max(tim[i],ove[i]);
    }
    long long ans=0;
    for(int i=1;i<=m;i++){
        ans+=ove[nums[i].en]-nums[i].t;
    }
    cout<<ans<<endl;
    return 0;
}