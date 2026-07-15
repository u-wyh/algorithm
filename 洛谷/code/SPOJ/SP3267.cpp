#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+5;
const int MAXM = 1e6+5;
const int MAXQ = 2e5+5;

int n,q;
int val[MAXN];

struct node{
    int l,r,id;
};
node nums[MAXQ];
int ans[MAXQ];

int blen;
int bi[MAXN];

int cnt[MAXM];
int kind;

bool cmp(node a,node b){
    if(bi[a.l]!=bi[b.l]){
        return bi[a.l]<bi[b.l];
    }

    if(bi[a.l]&1){
        return a.r>b.r;
    }
    else{
        return a.r<b.r;
    }
}

void prepare(){
    blen=sqrt(n);
    for(int i=1;i<=n;i++){
        bi[i]=(i+blen-1)/blen;
    }

    sort(nums+1,nums+q+1,cmp);
}

void add(int pos){
    cnt[val[pos]]++;
    if(cnt[val[pos]]==1){
        kind++;
    }
}

void del(int pos){
    cnt[val[pos]]--;
    if(cnt[val[pos]]==0){
        kind--;
    }
}

void compute(){
    int winl=1,winr=0;
    for(int i=1;i<=q;i++){
        int l=nums[i].l;
        int r=nums[i].r;
        int id=nums[i].id;
        while(winl>l){
            add(--winl);
        }
        while(winr<r){
            add(++winr);
        }
        while(winl<l){
            del(winl++);
        }
        while(winr>r){
            del(winr--);
        }
        ans[id]=kind;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    cin>>q;
    for(int i=1;i<=q;i++){
        cin>>nums[i].l>>nums[i].r;
        nums[i].id=i;
    }

    prepare();
    compute();

    for(int i=1;i<=q;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}