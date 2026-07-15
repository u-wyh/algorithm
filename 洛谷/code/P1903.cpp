#include<bits/stdc++.h>
using namespace std;
const int MAXN = 150005;
const int MAXV = 1e6+5;

int n,m;
int val[MAXN];

struct Update{
    int pos,val;
};
Update update[MAXN];

struct Query{
    int l,r,t,id;
};
Query query[MAXN];

int cntq,cntu;
int ans[MAXN];

int bi[MAXN];

int kind;
int cnt[MAXV];

bool cmp(Query &a,Query &b){
    if(bi[a.l]!=bi[b.l]){
        return bi[a.l]<bi[b.l];
    }
    if(bi[a.r]!=bi[b.r]){
        return bi[a.r]<bi[b.r];
    }
    return a.t<b.t;
}

void prepare(){
    int blen=max(1.0,pow(n,2.0/3));
    for(int i=1;i<=n;i++){
        bi[i]=(i+blen-1)/blen;
    }

    sort(query+1,query+cntq+1,cmp);
}

void add(int val){
    cnt[val]++;
    if(cnt[val]==1){
        kind++;
    }
}

void del(int val){
    cnt[val]--;
    if(cnt[val]==0){
        kind--;
    }
}

void movetime(int jobl,int jobr,int t){
    int pos=update[t].pos;
    int v=update[t].val;
    if(jobl<=pos&&pos<=jobr){
        del(val[pos]);
        add(v);
    }
    swap(val[pos],update[t].val);
}

void compute(){
    int winl=1,winr=0,wint=0;
    for(int i=1;i<=cntq;i++){
        int l=query[i].l;
        int r=query[i].r;
        int t=query[i].t;
        int id=query[i].id;

        while(winl>l){
            add(val[--winl]);
        }
        while(winr<r){
            add(val[++winr]);
        }
        while(winl<l){
            del(val[winl++]);
        }
        while(winr>r){
            del(val[winr--]);
        }
        while(wint<t){
            movetime(l,r,++wint);
        }
        while(wint>t){
            movetime(l,r,wint--);
        }
        
        ans[id]=kind;
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
    for(int i=1;i<=m;i++){
        char op;
        cin>>op;
        if(op=='Q'){
            ++cntq;
            int l,r;
            cin>>l>>r;
            query[cntq]={l,r,cntu,cntq};
        }
        else{
            int pos,val;
            cin>>pos>>val;
            ++cntu;
            update[cntu]={pos,val};
        }
    }

    prepare();
    compute();

    for(int i=1;i<=cntq;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}