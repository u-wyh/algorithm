#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXM = 250005;

int n,m;
int nums[MAXM];
int val[MAXN];

int tmp[MAXN];
int len;

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

int find(int val){
    int l=1,r=len,ans=-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(tmp[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int compute(int l,int r){
    len=0;
    for(int i=l+1;i<r;i++){
        if(val[i]<=val[l]||val[i]>=val[r]){
            continue;
        }
        int pos=find(val[i]);
        if(pos==-1){
            tmp[++len]=val[i];
        }
        else{
            tmp[pos]=val[i];
        }
    }
    return len;
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=m;i++){
        nums[i]=read();
    }
    sort(nums+1,nums+m+1);
    nums[++m]=n+1;
    val[n+1]=INT_MAX;
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=2;i<=m;i++){
        if(val[nums[i]]<=val[nums[i-1]]){
            cout<<"impossible"<<endl;
            return 0;
        }
    }
    int ans=m-1;
    // ans+=compute(0,nums[1]);
    for(int i=0;i<m;i++){
        if(nums[i]==nums[i+1]-1){
            continue;
        }
        // cout<<nums[i]<<' '<<nums[i+1]<<' '<<compute(nums[i],nums[i+1])<<endl;
        ans+=compute(nums[i],nums[i+1]);
    }
    cout<<ans<<endl;
    return 0;
}