#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 2e5+5;
const int MOD = 1e9+7;

int n,m;
int val[MAXN];

int one[MAXN<<2];
int two[MAXN<<2];
int len[MAXN<<2];
int addtag[MAXN<<2];
int multag[MAXN<<2];
int times[MAXN<<2];

vector<pair<int,int>>vec[MAXN];

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

void up(int i){
    if(times[i]==0){
        one[i]=(one[i<<1]+one[i<<1|1])%MOD;
        two[i]=(two[i<<1]+two[i<<1|1])%MOD;
        len[i]=len[i<<1]+len[i<<1|1];
    }
}

void build(int l,int r,int i){
    multag[i]=1;

    if(l==r){
        one[i]=val[l];
        len[i]=1;
    }
    else{
        int mid=(l+r)>>1;
        build(l,mid,i<<1);
        build(mid+1,r,i<<1|1);
        up(i);
    }
}

void addlazy(int i,int v){
    one[i]=(one[i]+v*len[i])%MOD;
    addtag[i]=(addtag[i]+v)%MOD;
}

void mullazy(int i,int v){
    one[i]=(one[i]*v)%MOD;
    addtag[i]=(addtag[i]*v)%MOD;
    multag[i]=(multag[i]*v)%MOD;
}

void down(int i){
    if(multag[i]!=1){
        if(times[i<<1]==0){
            mullazy(i<<1,multag[i]);
        }
        if(times[i<<1|1]==0){
            mullazy(i<<1|1,multag[i]);
        }
        multag[i]=1;
    }
    if(addtag[i]){
        if(times[i<<1]==0){
            addlazy(i<<1,addtag[i]);
        }
        if(times[i<<1|1]==0){
            addlazy(i<<1|1,addtag[i]);
        }
        addtag[i]=0;
    }
}

void add(int jobl,int jobr,int jobv,int l,int r,int i){
    if(times[i]){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        addlazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            add(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            add(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void mul(int jobl,int jobr,int jobv,int l,int r,int i){
    if(times[i]){
        return ;
    }
    if(jobl<=l&&r<=jobr){
        mullazy(i,jobv);
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            mul(jobl,jobr,jobv,l,mid,i<<1);
        }
        if(jobr>mid){
            mul(jobl,jobr,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void block(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        if(l!=r){
            down(i);//先将信息传递下去  暂时不用up
        }
        if(times[i]==0){
            two[i]=(one[i]+two[i])%MOD;
            one[i]=0;
            len[i]=0;
        }
        times[i]++;
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            block(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            block(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

void deblock(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        times[i]--;
        if(times[i]==0){
            if(l==r){
                one[i]=two[i];
                two[i]=0;
                len[i]=1;
            }
            else{
                // down(i);
                up(i);
            }
        }
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        if(jobl<=mid){
            deblock(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            deblock(jobl,jobr,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

int query(int jobl,int jobr,int l,int r,int i){
    if(jobl<=l&&r<=jobr){
        return (one[i]+two[i])%MOD;
    }
    else{
        int mid=(l+r)>>1;
        down(i);
        int ans=0;
        if(jobl<=mid){
            ans+=query(jobl,jobr,l,mid,i<<1);
        }
        if(jobr>mid){
            ans+=query(jobl,jobr,mid+1,r,i<<1|1);
        }
        ans%=MOD;
        return ans;
    }
}

signed main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    build(1,n,1);
    for(int i=1;i<=m;i++){
        int op,l,r,x;
        op=read(),l=read(),r=read();
        for(int j=0;j<(int)vec[i].size();j++){
            int lt=vec[i][j].first;
            int rt=vec[i][j].second;
            deblock(lt,rt,1,n,1);
        }
        if(op==1){
            x=read();
            add(l,r,x,1,n,1);
        }
        else if(op==2){
            x=read();
            mul(l,r,x,1,n,1);
        }
        else if(op==3){
            x=read();
            block(l,r,1,n,1);
            if(i+x+1<=m){
                vec[i+x+1].push_back({l,r});
            }
        }
        else{
            printf("%lld\n",query(l,r,1,n,1));
        }
    
    }
    return 0;
}