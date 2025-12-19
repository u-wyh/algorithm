#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,q;
int nums[MAXN];
int pos[MAXN];
int val[MAXN];
int tmp[MAXN];

int arr[MAXN<<1];
int m;

int tree[MAXN<<1];

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

inline void add(int x,int v){
    while(x<=m){
        tree[x]+=v;
        x+=lowbit(x);
    }
}

inline int query(int x){
    int ans=0;
    while(x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}

int find(int val){
    int l=1,r=m,ans=1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

void prepare(){
    for(int i=1;i<=m;i++){
        tree[i]=0;
    }
}

signed main()
{
    int T;
    T=read();
    while(T--){
        n=read(),q=read();
        for(int i=1;i<=n;i++){
            nums[i]=read();
            tmp[i]=nums[i];
            arr[i]=nums[i];
        }
        for(int i=1;i<=q;i++){
            pos[i]=read(),val[i]=read();
            tmp[pos[i]]+=val[i];
            arr[n+i]=tmp[pos[i]];
        }
        // for(int i=1;i<=n+q;i++){
        //     cout<<arr[i]<<' ';
        // }
        // cout<<endl;
        sort(arr+1,arr+n+q+1);
        m=1;
        for(int i=2;i<=n+q;i++){
            if(arr[i]!=arr[i-1]){
                arr[++m]=arr[i];
            }
        }
        // cout<<m<<endl;
        prepare();
        for(int i=1;i<=n;i++){
            tmp[i]=nums[i];
            nums[i]=find(nums[i]);
            add(nums[i],1);
        }
        int limit=n/2;
        int l=1,r=m,ans=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if((n-query(mid))>=limit){
                ans=mid;
                l=mid+1;
            }
            else{
                r=mid-1;
            }
        }
        // cout<<limit<<' '<<ans<<":   "<<query(ans)<<endl;
        for(int i=1;i<=q;i++){
            add(nums[pos[i]],-1);
            nums[pos[i]]=tmp[pos[i]]+val[i];
            tmp[pos[i]]=nums[pos[i]];
            nums[pos[i]]=find(nums[pos[i]]);
            add(nums[pos[i]],1);
            l=ans,r=m;
            while(l<=r){
                int mid=(l+r)>>1;
                if((n-query(mid))>=limit){
                    ans=mid;
                    l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
            // cout<<ans<<":  ";
            cout<<query(ans)<<endl;
        }
    }
    return 0;
}