#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e5+5;
const int MAXB = 605;

int n,m;
int val[MAXN];
int arr[MAXN];

struct node{
    int l,r,id;
};
node nums[MAXN];
int ans[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int cnt[MAXN];
int minmode;
int maxcnt;

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

bool cmp(node &a,node &b){
    if(bi[a.l]!=bi[b.l]){
        return a.l<b.l;
    }
    return a.r<b.r;
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

void prepare(){
    for(int i=1;i<=n;i++){
        arr[i]=val[i];
    }
    sort(arr+1,arr+n+1);
    m=1;
    for(int i=2;i<=n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
    }

    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,blen*i);
    }
    sort(nums+1,nums+n+1,cmp);
}

int force(int l,int r){
    int maxcnt=0,minmode=0;
    for(int i=l;i<=r;i++){
        cnt[val[i]]++;
    }
    for(int i=l;i<=r;i++){
        int num=val[i];
        if(cnt[num]>maxcnt||(cnt[num]==maxcnt&&num<minmode)){
            minmode=num;
            maxcnt=cnt[num];
        }
    }
    for(int i=l;i<=r;i++){
        cnt[val[i]]--;
    }
    return minmode;
}

void add(int val){
    cnt[val]++;
    if(cnt[val]>maxcnt||(cnt[val]==maxcnt&&val<minmode)){
        maxcnt=cnt[val];
        minmode=val;
    }
}

void del(int val){
    cnt[val]--;
}

void compute(){
    for(int b=1,q=1;b<=bnum&&q<=n;b++){
        minmode=0;
        maxcnt=0;
        for(int i=1;i<=m;i++){
            cnt[i]=0;
        }
        int winl=br[b]+1,winr=br[b];
        for(;q<=n&&bi[nums[q].l]==b;q++){
            int jobl=nums[q].l;
            int jobr=nums[q].r;
            int jobi=nums[q].id;
            if(jobr<=br[b]){
                ans[jobi]=force(jobl,jobr);
            }
            else{
                while(winr<jobr){
                    add(val[++winr]);
                }
                int backupmode=minmode;
                int backupcnt=maxcnt;
                while(winl>jobl){
                    add(val[--winl]);
                }
                ans[jobi]=minmode;
                minmode=backupmode;
                maxcnt=backupcnt;
                while(winl<=br[b]){
                    del(val[winl++]);
                }
            }
        }
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++){
        val[i]=read();
    }
    for(int i=1;i<=n;i++){
        nums[i].l=read(),nums[i].r=read();
        nums[i].id=i;
    }
    prepare();
    compute();
    for(int i=1;i<=n;i++){
        printf("%d\n",arr[ans[i]]);
    }
    return 0;
}