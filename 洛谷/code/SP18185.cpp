#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e5+5;
const int MAXB = 1005;

int n,m;

int nums[MAXN];
int arr[MAXN];

int blen;
int bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

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

void prepare(){
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=blen*(i-1)+1;
        br[i]=min(n,blen*i);
    }
    for(int i=1;i<=n;i++){
        arr[i]=nums[i];
    }
    for(int i=1;i<=bnum;i++){
        sort(arr+bl[i],arr+br[i]+1);
    }
}

void update(int pos,int val){
    int l=bl[bi[pos]];
    int r=br[bi[pos]];
    nums[pos]=val;
    for(int i=l;i<=r;i++){
        arr[i]=nums[i];
    }
    sort(arr+l,arr+r+1);
}

int getcnt(int i,int val){
    int l=bl[i],r=br[i],ans=br[i]+1;
    while(l<=r){
        int mid=(l+r)/2;
        if(arr[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return br[i]-ans+1;
}

int query(int l,int r,int v){
    int ans=0;
    if(bi[l]==bi[r]){
        for(int i=l;i<=r;i++){
            if(nums[i]>=v){
                ans++;
            }
        }
    }
    else{
        for(int i=l;i<=br[bi[l]];i++){
            if(nums[i]>=v){
                ans++;
            }
        }
        for(int i=bl[bi[r]];i<=r;i++){
            if(nums[i]>=v){
                ans++;
            }
        }
        for(int i=bi[l]+1;i<bi[r];i++){
            ans+=getcnt(i,v);
        }
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    prepare();
    m=read();
    for(int i=1;i<=m;i++){
        int op,a,b,c;
        op=read(),a=read(),b=read();
        if(op==0){
            c=read();
            printf("%d\n",query(a,b,c));
        }
        else{
            update(a,b);
        }
    }
    return 0;
}