#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;

int n,m;
int nums[MAXN];
int bi[MAXN];

struct QUERY{
    int l,r,t,id;
};
struct UPDATE{
    int pos,val;
};

int cntq,cntu;
QUERY query[MAXN];
UPDATE update[MAXN];

int cnt[MAXN];
int curans;

int ans[MAXN];

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

bool cmp(QUERY a,QUERY b){
    if(bi[a.l]!=bi[b.l]){
        return bi[a.l]<bi[b.l];
    }
    if(bi[a.r]!=bi[b.r]){
        return bi[a.r]<bi[b.r];
    }
    return a.t<b.t;
}

void prepare(){
    int blen=max(1,(int)pow(n,2.0/3));
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    sort(query+1,query+cntq+1,cmp);
}

void add(int num){
    if(cnt[num]==0){
        curans++;
    }
    if(cnt[num]==1){
        curans--;
    }
    cnt[num]++;
}

void del(int num){
    if(cnt[num]==1){
        curans--;
    }
    if(cnt[num]==2){
        curans++;
    }
    cnt[num]--;
}

void movetime(int jobl,int jobr,int jobt){
    int pos=update[jobt].pos;
    int val=update[jobt].val;
    if(jobl<=pos&&pos<=jobr){
        del(nums[pos]);
        add(val);
    }
    swap(nums[pos],update[jobt].val);
}

void compute(){
    int winl=1,winr=0,wint=0;
    for(int i=1;i<=cntq;i++){
        int jobl=query[i].l;
        int jobr=query[i].r;
        int jobt=query[i].t;
        int jobi=query[i].id;
        while(jobl<winl){
            add(nums[--winl]);
        }
        while(jobr>winr){
            add(nums[++winr]);
        }
        while(jobl>winl){
            del(nums[winl++]);
        }
        while(jobr<winr){
            del(nums[winr--]);
        }
        while(wint<jobt){
            movetime(jobl,jobr,++wint);
        }
        while(wint>jobt){
            movetime(jobl,jobr,wint--);
        }
        ans[jobi]=curans;
    }
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }

    for(int i=1;i<=m;i++){
        int op=read();
        if(op==1){
            int pos,val;
            pos=read(),val=read();
            update[++cntu]={pos+1,val};
        }
        else{
            int l,r;
            l=read(),r=read();
            query[++cntq]={l+1,r+1,cntu,cntq};
        }
    }

    prepare();
    compute();

    for(int i=1;i<=cntq;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}