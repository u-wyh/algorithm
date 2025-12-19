#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXB = 1e3+5;

int n,m;
int nums[MAXN];
int arr[MAXN];

int blen;
int bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];
int tag[MAXB];

void prepare(){
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
    for(int i=1;i<=n;i++){
        arr[i]=nums[i];
    }
    for(int i=1;i<=bnum;i++){
        sort(arr+bl[i],arr+br[i]+1);
    }
}

int getcnt(int i,int v){
    v-=tag[i];
    int l=bl[i],r=br[i],ans=br[i]+1;
    while(l<=r){
        int mid=(l+r)/2;
        if(arr[mid]>=v){
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
        v-=tag[bi[l]];
        for(int  i=l;i<=r;i++){
            if(nums[i]>=v){
                ans++;
            }
        }
    }
    else{
        for(int i=l;i<=br[bi[l]];i++){
            if(nums[i]+tag[bi[l]]>=v){
                ans++;
            }
        }
        for(int i=bl[bi[r]];i<=r;i++){
            if(nums[i]+tag[bi[r]]>=v){
                ans++;
            }
        }
        for(int i=bi[l]+1;i<bi[r];i++){
            ans+=getcnt(i,v);
        }
    }
    return ans;
}

void update(int l,int r,int v){
    if(bi[l]==bi[r]){
        for(int i=l;i<=r;i++){
            nums[i]+=v;
        }
        for(int i=bl[bi[l]];i<=br[bi[l]];i++){
            arr[i]=nums[i];
        }
        sort(arr+bl[bi[l]],arr+br[bi[l]]+1);
    }
    else{
        for(int i=l;i<=br[bi[l]];i++){
            nums[i]+=v;
        }
        for(int i=bl[bi[l]];i<=br[bi[l]];i++){
            arr[i]=nums[i];
        }
        sort(arr+bl[bi[l]],arr+br[bi[l]]+1);

        for(int i=bl[bi[r]];i<=r;i++){
            nums[i]+=v;
        }
        for(int i=bl[bi[r]];i<=br[bi[r]];i++){
            arr[i]=nums[i];
        }
        sort(arr+bl[bi[r]],arr+br[bi[r]]+1);

        for(int i=bi[l]+1;i<bi[r];i++){
            tag[i]+=v;
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    prepare();
    for(int i=1;i<=m;i++){
        int l,r,v;
        char op;
        cin>>op>>l>>r>>v;
        if(op=='A'){
            printf("%d\n",query(l,r,v));
        }
        else{
            update(l,r,v);
        }
    }
    return 0;
}