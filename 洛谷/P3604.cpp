#include<bits/stdc++.h>
using namespace std;
const int MAXN = 6e4+5;
const int MAXB = 305;

int n,q,m;
char s[MAXN];
int diff[26];

int pre[MAXN];
int arr[MAXN];

int cnt[MAXN];
int to[MAXN][26];

int blen;
int bi[MAXN];

struct node{
    int l,r,k,id;
};
node nums[MAXN];
long long ans[MAXN];

long long res=0;

bool cmp(node &a, node &b) {
    if (bi[a.l] != bi[b.l]) {
        return bi[a.l] < bi[b.l];
    }
    if ((bi[a.l] & 1) == 1) {
        return a.r < b.r;
    } else {
        return a.r > b.r;
    }
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
    blen=sqrt(n+1);
    for(int i=0;i<=n;i++){
        bi[i]=i/blen+1;
    }
    sort(nums+1,nums+q+1,cmp);

    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]^diff[s[i]-'a'];
    }

    for(int i=1;i<=n;i++){
        arr[i]=pre[i];
    }
    arr[n+1]=0;
    sort(arr,arr+n+2);
    m=1;
    for(int i=2;i<=n+1;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=0;i<=n;i++){
        pre[i]=find(pre[i]);
    }
    for(int i=1;i<=m;i++){
        for(int j=0;j<26;j++){
            int val=arr[i]^diff[j];
            int pos=find(val);
            if(arr[pos]==val){
                to[i][j]=pos;
            }
        }
    }
}

void add(int val){
    res+=cnt[val];
    for(int i=0;i<26;i++){
        res+=cnt[to[val][i]];
    }
    cnt[val]++;
}

void del(int val){
    cnt[val]--;
    res-=cnt[val];
    for(int i=0;i<26;i++){
        res-=cnt[to[val][i]];
    }
}

int main()
{
    scanf("%d %d %s",&n,&q,s+1);
    for(int i=0;i<26;i++){
        diff[i]=(1<<i);
    }
    for(int i=1;i<=q;i++){
        scanf("%d %d",&nums[i].l,&nums[i].r);
        nums[i].l--;
        nums[i].id=i;
    }
    prepare();
    cnt[1]=1;
    int winl=0,winr=0;
    for(int i=1;i<=q;i++){
        int jobl=nums[i].l;
        int jobr=nums[i].r;
        int jobi=nums[i].id;
        while(jobl<winl){
            add(pre[--winl]);
        }
        while(jobl>winl){
            del(pre[winl++]);
        }
        while(jobr>winr){
            add(pre[++winr]);
        }
        while(jobr<winr){
            del(pre[winr--]);
        }
        ans[jobi]=res;
    }
    for(int i=1;i<=q;i++){
        printf("%lld\n",ans[i]);
    }
    return 0;
}