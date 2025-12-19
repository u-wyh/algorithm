#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 405;

int n,m;
int val[MAXN];

struct Query {
    int l, r, t, a,b,id;
};
Query query[MAXN];

struct Update {
    int pos, val;
};
Update update[MAXN];

int cntu,cntq;
int ans[MAXN];

int kind[MAXB];
int evenkind[MAXB];
int cnt[MAXN];

int blen,bnum;
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

bool cmp(Query &a, Query &b) {
    if (bi[a.l] != bi[b.l]) {
        return bi[a.l] < bi[b.l];
    }
    if (bi[a.r] != bi[b.r]) {
        return bi[a.r] < bi[b.r];
    }
    return a.t < b.t;
}

void prepare(){
    blen=max((int)pow(n,2.0/3),1);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
    sort(query+1,query+cntq+1,cmp);
}

void del(int val) {
    cnt[val]--;
    if(cnt[val]%2==1){
        evenkind[bi[val]]--;
    }
    else if(cnt[val]!=0){
        evenkind[bi[val]]++;
    }
    if(cnt[val]==0){
        kind[bi[val]]--;
    }
}

void add(int val) {
    cnt[val]++;
    if(cnt[val]==1){
        kind[bi[val]]++;
    }
    if(cnt[val]%2==0){
        evenkind[bi[val]]++;
    }
    else if(cnt[val]!=1){
        evenkind[bi[val]]--;
    }
}

void moveTime(int jobl, int jobr, int tim) {
    int pos = update[tim].pos;
    int num = update[tim].val;
    if (jobl <= pos && pos <= jobr) {
        del(val[pos]);
        add(val[pos]+num);
    }
    val[pos]+=num;
    update[tim].val*=-1;
}

int fun(int l,int r){
    int u=-1;
    int lb=bi[l],rb=bi[r];
    if(lb==rb){
        for(int i=l;i<=r;i++){
            if(cnt[i]&&(cnt[i]%2==0)){
                u=i;
                break;
            }
        }
    }
    else{
        for(int i=l;i<=br[lb];i++){
            if(cnt[i]&&(cnt[i]%2==0)){
                u=i;
                break;
            }
        }
        for(int b=lb+1;b<rb;b++){
            if(u!=-1){
                break;
            }
            if(evenkind[b]){
                for(int i=bl[b];i<=br[b];i++){
                    if(cnt[i]&&(cnt[i]%2==0)){
                        u=i;
                        break;
                    }
                }
            }
        }
        for(int i=bl[rb];i<=r;i++){
            if(u!=-1){
                break;
            }
            if(cnt[i]&&(cnt[i]%2==0)){
                u=i;
                break;
            }
        }
    }

    if(u==-1||u==r){
        return -1;
    }
    l=u+1;
    lb=bi[l],rb=bi[r];
    if(lb==rb){
        for(int i=l;i<=r;i++){
            if(cnt[i]){
                return i;
            }
        }
    }
    else{
        for(int i=l;i<=br[lb];i++){
            if(cnt[i]){
                return i;
            }
        }
        for(int b=lb+1;b<rb;b++){
            if(kind[b]){
                for(int i=bl[b];i<=br[b];i++){
                    if(cnt[i]){
                        return i;
                    }
                }
            }
        }
        for(int i=bl[rb];i<=r;i++){
            if(cnt[i]){
                return i;
            }
        }
    }
    return -1;
}

void compute(){
    int winl = 1, winr = 0, wint = 0;
    for (int i = 1; i <= cntq; i++) {
        int jobl = query[i].l;
        int jobr = query[i].r;
        int jobt = query[i].t;
        int joba = query[i].a;
        int jobb = query[i].b;
        int id = query[i].id;
        while (winl > jobl) {
            add(val[--winl]);
        }
        while (winr < jobr) {
            add(val[++winr]);
        }
        while (winl < jobl) {
            del(val[winl++]);
        }
        while (winr > jobr) {
            del(val[winr--]);
        }
        while (wint < jobt) {
            moveTime(jobl, jobr, ++wint);
        }
        while (wint > jobt) {
            moveTime(jobl, jobr, wint--);
        }
        ans[id] = fun(joba,jobb);
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=m;i++){
        int op=read();
        if(op==1){
            cntu++;
            update[cntu].pos=read();
            update[cntu].val=read();
        }
        else{
            cntq++;
            query[cntq].l=read();
            query[cntq].r=read();
            query[cntq].a=read();
            query[cntq].b=read();
            query[cntq].t=cntu;
            query[cntq].id=cntq;
        }
    }
    prepare();
    compute();
    for(int i=1;i<=cntq;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}