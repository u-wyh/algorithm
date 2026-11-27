#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 5e5+5;

int n;
int nums[MAXN];
int sum[MAXN][61];

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

int find(int r,int val){
    int l=1,ans=r+1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(nums[mid]>=val){
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
    // cout<<(1ll<<61)<<endl;
    int T;
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++){
            nums[i]=read();
        }
        sort(nums+1,nums+n+1);
        int high=0;
        while((1ll<<high)<nums[n]){
            high++;
        }
        if((1ll<<high)>nums[n]){
            high--;
        }
        for(int i=1;i<=n;i++){
            for(int j=0;j<=high;j++){
                sum[i][j]=0;
                if(nums[i]&(1ll<<j)){
                    sum[i][j]++;
                }
                sum[i][j]+=sum[i-1][j];
            }
        }
        bool flag=false;
        for(int i=n;i>=2;i--){
            int r=i-1;
            for(int j=high;j>=0;j--){
                if(nums[i]&(1ll<<j)){
                    if(sum[r][j]>0){
                        flag=true;
                        break;
                    }
                }
                else{
                    if(nums[i]<(1ll<<j)){
                        continue;
                    }
                    int pos=find(r+1,1ll<<j)-1;
                    if(pos==0){
                        break;
                    }
                    r=pos;
                }
            }
            if(flag){
                break;
            }
        }
        if(flag){
            cout<<"NO"<<endl;
        }
        else{
            cout<<"YES"<<endl;
        }
    }
    return 0;
}