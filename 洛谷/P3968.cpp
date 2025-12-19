#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = MAXN * 50;

int n,q;
int cnt=1;
int ls[MAXM];
int rs[MAXM];
int sum[MAXM];
map<int,int>pos;

struct node{
    int l,r;
};

struct cmpl{
    bool operator()(const node&a,const node&b){
        return a.l<b.l;
    }
};

struct cmpr{
    bool operator()(const node&a,const node&b){
        return a.r<b.r;
    }
};

struct cmplen{
    bool operator()(const node&a,const node&b){
        if(a.r-a.l!=b.r-b.l){
            return (a.r-a.l)>(b.r-b.l);
        }
        return a.l>b.l;
    }
};

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

set<node,cmpl>setl;
set<node,cmpr>setr;
set<node,cmplen>setlen;

void update(int pos,int val,int l,int r,int i){
    if(l==r){
        sum[i]=val;
    }
    else{
        int mid=(0ll+l+r)/2;
        if(pos<=mid){
            if(ls[i]==0){
                ls[i]=++cnt;
            }
            update(pos,val,l,mid,ls[i]);
        }
        else{
            if(rs[i]==0){
                rs[i]=++cnt;
            }
            update(pos,val,mid+1,r,rs[i]);
        }
        sum[i]=(sum[ls[i]]+sum[rs[i]]);
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
            if(ls[i]){
                ans+=query(jobl,jobr,l,mid,ls[i]);
            }
        }
        if(jobr>mid){
            if(rs[i]){
                ans+=query(jobl,jobr,mid+1,r,rs[i]);
            }
        }
        return ans;
    }
}

int main()
{
    n=read(),q=read();
    setl.insert({1,n});
    setr.insert({1,n});
    setlen.insert({1,n});
    while(q--){
        int k=read();
        if(k==0){
            int l,r;
            l=read(),r=read();
            printf("%d\n",query(l,r,1,n,1));
        }
        else{
            if(pos.find(k)!=pos.end()){
                int p=pos[k];
                pos.erase(k);
                update(p,0,1,n,1);

                bool left=false,right=false;
                node lt,rt;

                auto itr=setr.find({0,p-1});
                if(itr!=setr.end()){
                    lt=*itr;
                    left=true;
                }

                auto itl=setl.find({p+1,0});
                if(itl!=setl.end()){
                    rt=*itl;
                    right=true;
                }

                if(left){
                    setl.erase(lt);
                    setr.erase(lt);
                    setlen.erase(lt);
                }
                if(right){
                    setl.erase(rt);
                    setr.erase(rt);
                    setlen.erase(rt);
                }
                int l=p,r=p;
                if(left){
                    l=lt.l;
                }
                if(right){
                    r=rt.r;
                }
                setl.insert({l,r});
                setr.insert({l,r});
                setlen.insert({l,r});
            }
            else{
                node s=*setlen.begin();
                int lt=s.l,rt=s.r;
                int p=(lt+rt+1)/2;
                update(p,1,1,n,1);
                pos[k]=p;
                setl.erase(s);
                setr.erase(s);
                setlen.erase(s);

                if(lt<=p-1){
                    setl.insert({lt,p-1});
                    setr.insert({lt,p-1});
                    setlen.insert({lt,p-1});
                }
                if(p+1<=rt){
                    setl.insert({p+1,rt});
                    setr.insert({p+1,rt});
                    setlen.insert({p+1,rt});
                }
            }
        }
    }
    return 0;
}