#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int MAXB = 1e3+5;

int n,m;
int val[MAXN];

int blen;
int bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int sorted[MAXN];
int lazy[MAXB];
int preeor[MAXN];

int tree[MAXN<<2];

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

void up(int i){
    tree[i]=gcd(tree[i<<1],tree[i<<1|1]);
}

void build(int l,int r,int i){
    if(l==r){
        tree[i]=val[l];
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return tree[i];
    }
    else{
        int mid=(l+r)>>1;
        if(jobl<=mid&&jobr>mid){
            return gcd(query(jobl,jobr,l,mid,i<<1),query(jobl,jobr,mid+1,r,i<<1|1));
        }
        else if(jobl<=mid){
            return query(jobl,jobr,l,mid,i<<1);
        }
        else{
            return query(jobl,jobr,mid+1,r,i<<1|1);
        }
    }
}

void update(int pos,int jobv,int l,int r,int i){
    if(l==r){
        tree[i]=jobv;
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

void update(int id,int x){
    int b=bi[id];
    for(int i=b+1;i<=bnum;i++){
        lazy[i]^=x;
    }
    int l=id,r=br[bi[id]];
    for(int i=l;i<=r;i++){
        preeor[i]^=x;
    }
    for(int i=bl[bi[id]];i<=br[bi[id]];i++){
        sorted[i]=preeor[i];
    }
    sort(sorted+bl[bi[id]],sorted+br[bi[id]]+1);
}

bool find(int l,int r,int val){
    int ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sorted[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    if(ans!=-1&&sorted[ans]==val){
        return true;
    }
    return false;
}

int query(int l,int r,int x){
    int lb=bi[l];
    int rb=bi[r];
    if(lb==rb){
        x^=lazy[lb];
        for(int i=l;i<=r;i++){
            if(x==preeor[i]){
                return i;
            }
        }
        return -1;
    }
    else{
        int val=x;
        val^=lazy[lb];
        for(int i=l;i<=br[lb];i++){
            if(val==preeor[i]){
                return i;
            }
        }
        for(int i=lb+1;i<rb;i++){
            if(find(bl[i],br[i],lazy[i]^x)){
                int val=x^lazy[i];
                int lt=bl[i],rt=br[i];
                for(int i=lt;i<=rt;i++){
                    if(preeor[i]==val){
                        return i;
                    }
                }
            }
        }
        val=x^lazy[rb];
        for(int i=bl[rb];i<=r;i++){
            if(val==preeor[i]){
                return i;
            }
        }
        return -1;
    }
}

int findr(int l,int r,int val){
    int ans=l;
    while(l<=r){
        int mid=(l+r)>>1;
        if(query(1,mid,1,n,1)==val){
            ans=mid;
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return ans;
}

void prepare(){
    for(int i=1;i<=n;i++){
        preeor[i]=preeor[i-1]^val[i];
        sorted[i]=preeor[i];
    }
    blen=sqrt(n);
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
        sort(sorted+bl[i],sorted+br[i]+1);
    }

    build(1,n,1);
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    prepare();
    cin>>m;
    for(int i=1;i<=m;i++){
        string s;
        int id,x;
        cin>>s;
        if(s[0]=='M'){
            cin>>id>>x;
            id++;
            update(id,x,1,n,1);
            update(id,x^val[id]);
            val[id]=x;
        }
        else{
            cin>>x;
            int l=1,r=0;
            bool flag=false;
            while(l<=n){
                int val=query(1,l,1,n,1);
                r=findr(l,n,val);
                if(x%val==0){
                    int ans=query(l,r,x/val);
                    if(ans!=-1){
                        ans--;
                        cout<<ans<<endl;
                        flag=true;
                        break;
                    }
                }
                l=r+1;
            }
            if(!flag){
                cout<<"no"<<endl;
            }
        }
    }
    return 0;
}