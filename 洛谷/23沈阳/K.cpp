#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;

int n,q,all,m;
int val[MAXN];
int pos[MAXN];
int to[MAXN];
int arr[MAXN<<1];

int cnt[MAXN<<3];
int sum[MAXN<<3];

void up(int i){
    cnt[i]=cnt[i<<1]+cnt[i<<1|1];
    sum[i]=sum[i<<1]+sum[i<<1|1];
}

void add(int pos,int jobv,int l,int r,int i){
    if(l==r){
        cnt[i]+=jobv;
        sum[i]+=arr[l]*jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            add(pos,jobv,l,mid,i<<1);
        }
        else{
            add(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int find(int val){
    int l=1,r=m,ans=0;
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

int query(int jobk,int l,int r,int i){
    if(l==r){
        return arr[l]*jobk;
    }
    else{
        int mid=(l+r)>>1;
        if(cnt[i<<1]>=jobk){
            return query(jobk,l,mid,i<<1);
        }
        else{
            return sum[i<<1]+query(jobk-cnt[i<<1],mid+1,r,i<<1|1);
        }
    }
}

bool check(int mid){
    return query(mid,1,m,1)<=all;
}

signed main()
{
    cin>>n>>q;
    int numcnt=0;
    int now=0;
    for(int i=1;i<=n;i++){
        cin>>val[i];
        if(val[i]>0){
            arr[++numcnt]=val[i];
            now++;
        }
        else{
            all-=val[i];
        }
    }

    for(int i=1;i<=q;i++){
        cin>>pos[i]>>to[i];
        if(to[i]>0){
            arr[++numcnt]=to[i];
        }
    }

    sort(arr+1,arr+numcnt+1);
    // for(int i=1;i<=numcnt;i++){
    //     cout<<arr[i]<<' ';
    // }
    // cout<<endl<<endl;
    m=1;
    for(int i=2;i<=numcnt;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
            // cout<<' '<<arr[m]<<' '<<m<<endl;
        }
    }
    // cout<<endl;

    for(int i=1;i<=n;i++){
        if(val[i]>0){
            val[i]=find(val[i]);
            add(val[i],1,1,m,1);
        }
    }
    for(int i=1;i<=q;i++){
        if(val[pos[i]]>0){
            now--;
            add(val[pos[i]],-1,1,m,1);
        }
        else{
            all+=val[pos[i]];
        }

        if(to[i]>0){
            now++;
            to[i]=find(to[i]);
            add(to[i],1,1,m,1);
        }
        else{
            all-=to[i];
        }
        val[pos[i]]=to[i];

        // cout<<' '<<now<<' '<<all<<endl;
        if(now==0||now==n){
            cout<<1<<endl;
            continue;
        }
        else{
            int l=0,r=now,ans=0;
            while(l<=r){
                int mid=(l+r)>>1;
                if(check(mid)){
                    ans=mid;
                    l=mid+1;
                }
                else{
                    r=mid-1;
                }
            }
            cout<<(ans+1)<<endl;
        }
    }
    return 0;
}