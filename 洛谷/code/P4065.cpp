#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 3e5+5;

int n;
int nums[MAXN];
int eorval[MAXN];
int lastpos[MAXN];
int val[MAXN];
int sum[MAXN];

int m;
int arr[MAXN];

mt19937_64 rng(time(0));

int cnt[MAXN];

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

signed main()
{
    int T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            eorval[i]=0;
        }
        for(int i=1;i<=n;i++){
            nums[i]=read();
            lastpos[nums[i]]=i;
        }
        for(int i=1;i<=n;i++){
            if(lastpos[nums[i]]==i){
                val[i]=eorval[nums[i]];
            }
            else{
                val[i]=rng();
                eorval[nums[i]]^=val[i];
            }
        }
        sum[0]=0;
        for(int i=1;i<=n;i++){
            sum[i]=sum[i-1]^val[i];
        }
        arr[n+1]=0;
        for(int i=1;i<=n;i++){
            arr[i]=sum[i];
        }
        sort(arr+1,arr+n+2);
        m=1;
        for(int i=2;i<=n+1;i++){
            if(arr[i]!=arr[i-1]){
                arr[++m]=arr[i];
            }
        }
        for(int i=0;i<=n;i++){
            sum[i]=find(sum[i]);
        }


        for(int i=1;i<=m;i++){
            cnt[i]=0;
        }
        int ans=0;
        for(int i=0;i<=n;i++){
            int w=sum[i];
            ans+=cnt[w];
            cnt[w]++;
        }
        cout<<ans<<endl;
    }
    return 0;
}