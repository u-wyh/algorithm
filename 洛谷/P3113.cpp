#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,q;
int x[MAXN],y[MAXN];
int sum[MAXN<<2];
int maxx[MAXN<<2];

inline int dist(int u,int v){
    return abs(x[u]-x[v])+abs(y[u]-y[v]);
}

void upmax(int i){
    maxx[i]=max(maxx[i<<1],maxx[i<<1|1]);
}

int querymax(int jobl,int jobr,int l,int r,int i){
    if(jobl>jobr){
        return 0;
    }
    if(jobl<=l&&r<=jobr){
        return maxx[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans=max(ans,querymax(jobl,jobr,l,mid,i<<1));
        }
        if(jobr>mid){
            ans=max(ans,querymax(jobl,jobr,mid+1,r,i<<1|1));
        }
        return ans;
    }
}

void updatemax(int pos,int jobv,int l,int r,int i){
    if(l==r){
        maxx[i]=jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            updatemax(pos,jobv,l,mid,i<<1);
        }
        else{
            updatemax(pos,jobv,mid+1,r,i<<1|1);
        }
        upmax(i);
    }
}

void up(int i){
    sum[i]=sum[i<<1]+sum[i<<1|1];
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        sum[i]=jobv;
    }
    else{
        int mid=(l+r)>>1;
        if(pos<=mid){
            update(pos,jobv,l,mid,i<<1);
        }
        else{
            update(pos,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return sum[i];
    }
    else{
        int mid=(l+r)>>1;
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        return ans;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    for(int i=1;i<n;i++){
        update(i,dist(i,i+1),1,n,1);
    }
    for(int i=2;i<n;i++){
        int val=dist(i,i+1)+dist(i,i-1)-dist(i-1,i+1);
        updatemax(i,val,1,n,1);
    }
    while(q--){
        char op;
        int u,v,xx,yy;
        cin>>op>>u;
        if(op=='Q'){
            cin>>v;
            int ans=query(u,v-1,1,n,1);
            ans-=querymax(u+1,v-1,1,n,1);
            cout<<ans<<endl;
        }
        else{
            cin>>xx>>yy;
            x[u]=xx,y[u]=yy;
            if(u>1){
                update(u-1,dist(u,u-1),1,n,1);
            }
            if(u<n){
                update(u,dist(u+1,u),1,n,1);
            }

            if(u>1&&u<n){
                int val=dist(u,u+1)+dist(u,u-1)-dist(u-1,u+1);
                updatemax(u,val,1,n,1);
            }
            if(u>2){
                int val=dist(u-1,u-2)+dist(u-1,u)-dist(u-2,u);
                updatemax(u-1,val,1,n,1);
            }
            if(u<n-1){
                int val=dist(u+1,u)+dist(u+1,u+2)-dist(u,u+2);
                updatemax(u+1,val,1,n,1);
            }
        }
    }
    return 0;
}