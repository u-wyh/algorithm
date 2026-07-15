#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;
const int MAXB = 1e3+5;

int n,m;
int val[MAXN];
int arr[MAXN];

int blen,bnum;
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
        arr[i]=val[i];
    }
    for(int i=1;i<=bnum;i++){
        sort(arr+bl[i],arr+br[i]+1);
    }
}

int calc(int i,int val){
    val-=tag[i];
    int l=bl[i],r=br[i],ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(arr[mid]>=val){
            ans=br[i]-mid+1;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int query(int l,int r,int v){
    int lb=bi[l];
    int rb=bi[r];
    int ans=0;
    if(lb==rb){
        v-=tag[lb];
        for(int i=l;i<=r;i++){
            if(val[i]>=v){
                ans++;
            }
        }
    }
    else{
        for(int i=lb+1;i<rb;i++){
            ans+=calc(i,v);
        }
        for(int i=l;i<=br[lb];i++){
            if(val[i]+tag[lb]>=v){
                ans++;
            }
        }
        for(int i=bl[rb];i<=r;i++){
            if(val[i]+tag[rb]>=v){
                ans++;
            }
        }
    }
    return ans;
}

void add(int l,int r,int v){
    int lb=bi[l];
    int rb=bi[r];
    if(lb==rb){
        for(int i=l;i<=r;i++){
            val[i]+=v;
        }
        for(int i=bl[lb];i<=br[lb];i++){
            arr[i]=val[i];
        }
        sort(arr+bl[lb],arr+br[lb]+1);
    }
    else{
        for(int i=lb+1;i<rb;i++){
            tag[i]+=v;
        }
        add(l,br[lb],v);
        add(bl[rb],r,v);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    prepare();
    for(int i=1;i<=m;i++){
        char op;
        int l,r,c;
        cin>>op>>l>>r>>c;
        if(op=='M'){
            add(l,r,c);
        }
        else{
            cout<<query(l,r,c)<<endl;
        }
    }
    return 0;
}