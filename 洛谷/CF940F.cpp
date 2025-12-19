#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n,m;
int nums[MAXN];
int cnt;
int arr[MAXN<<1];

struct QUERY{
    int l,r,t,id;
};
struct UPDATE{
    int pos,val;
};

int bi[MAXN];
QUERY query[MAXN];
UPDATE update[MAXN];
int cntq,cntu;

int cnt1[MAXN<<1];
int cnt2[MAXN];

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

int find(int val){
    int l=1,r=cnt,ans=1;
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
    int len=0;
    for(int i=1;i<=n;i++){
        arr[++len]=nums[i];
    }
    for(int i=1;i<=cntu;i++){
        arr[++len]=update[i].val;
    }
    sort(arr+1,arr+len+1);
    cnt=1;
    for(int i=2;i<=len;i++){
        if(arr[i]!=arr[i-1]){
            arr[++cnt]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i]=find(nums[i]);
    }
    for(int i=1;i<=cntu;i++){
        update[i].val=find(update[i].val);
    }

    int blen=max(1,(int)pow(n,2.0/3));
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    sort(query+1,query+cntq+1,cmp);
}

void add(int val){
    cnt2[cnt1[val]]--;
    cnt1[val]++;
    cnt2[cnt1[val]]++;
}

void del(int val){
    cnt2[cnt1[val]]--;
    cnt1[val]--;
    cnt2[cnt1[val]]++;
}

void movetime(int jobl,int jobr,int jobt){
    int pos=update[jobt].pos;
    int val=update[jobt].val;
    if(jobl<=pos&&pos<=jobr){
        del(nums[pos]);
        add(val);
    }
    swap(update[jobt].val,nums[pos]);
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
        while(jobt<wint){
            movetime(jobl,jobr,wint--);
        }
        while(jobt>wint){
            movetime(jobl,jobr,++wint);
        }
        int res=1;
        while(res<=n&&cnt2[res]>0){
            res++;
        }
        ans[jobi]=res;
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
            int l,r;
            l=read(),r=read();
            query[++cntq]={l,r,cntu,cntq};
        }
        else{
            int pos,val;
            pos=read(),val=read();
            update[++cntu]={pos,val};
        }
    }
    prepare();
    compute();
    for(int i=1;i<=cntq;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}