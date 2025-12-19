#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;

struct Juice{
    int d,p,l;
}juice[MAXN];

int ans[MAXN];

int qid[MAXN];
long long money[MAXN];
long long least[MAXN];

int lset[MAXN];
int rset[MAXN];
int used=0;

int maxp;
long long all[MAXN<<2];
long long cost[MAXN<<2];

bool cmp(Juice a,Juice b){
    return a.d>b.d;
}

void up(int i){
    all[i]=all[i<<1]+all[i<<1|1];
    cost[i]=cost[i<<1]+cost[i<<1|1];
}

void add(int jobi,int jobv,int l,int r,int i){
    if(l==r){
        all[i]+=jobv;
        cost[i]+=1ll*jobv*jobi;
    }
    else{
        int mid=(l+r)>>1;
        if(jobi<=mid){
            add(jobi,jobv,l,mid,i<<1);
        }
        else{
            add(jobi,jobv,mid+1,r,i<<1|1);
        }
        up(i);
    }
}

long long query(long long volumne,int l,int r,int i){
    if(l==r){
        return volumne*l;
    }
    else{
        int mid=(l+r)>>1;
        if(all[i<<1]>=volumne){
            return query(volumne,l,mid,i<<1);
        }
        else{
            return cost[i<<1]+query(volumne-all[i<<1],mid+1,r,i<<1|1);
        }
    }
}

void compute(int ql,int qr,int vl,int vr){
    if(ql>qr){
        return ;
    }
    if(vl==vr){
        for(int i=ql;i<=qr;i++){
            ans[qid[i]]=vl;
        }
    }
    else{
        int mid=(vl+vr)>>1;
        while(used<mid){
            used++;
            add(juice[used].p,juice[used].l,1,maxp,1);
        }
        while(used>mid){
            add(juice[used].p,-juice[used].l,1,maxp,1);
            used--;
        }
        int lsz=0,rsz=0;
        for(int i=ql;i<=qr;i++){
            int id=qid[i];
            if(all[1]>=least[id]&&query(least[id],1,maxp,1)<=money[id]){
                lset[++lsz]=id;
            }
            else{
                rset[++rsz]=id;
            }
        }
        for(int i=ql;i<=ql+lsz-1;i++){
            qid[i]=lset[i-ql+1];
        }
        for(int i=ql+lsz;i<=qr;i++){
            qid[i]=rset[i-ql-lsz+1];
        }
        compute(ql,ql+lsz-1,vl,mid);
        compute(ql+lsz,qr,mid+1,vr);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>juice[i].d>>juice[i].p>>juice[i].l;
        maxp=max(maxp,juice[i].p);
    }
    sort(juice+1,juice+n+1,cmp);
    for(int i=1;i<=m;i++){
        qid[i]=i;
        cin>>money[i]>>least[i];
    }
    compute(1,m,1,n+1);
    for(int i=1;i<=m;i++){
        if(ans[i]==n+1){
            printf("-1\n");
        }
        else{
            printf("%d\n",juice[ans[i]].d);
        }
    }
    return 0;
}