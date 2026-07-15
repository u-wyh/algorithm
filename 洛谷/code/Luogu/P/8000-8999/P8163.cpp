#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int MAXH = 17;

int n,k,m,q;
pair<int,int> up[MAXM];
pair<int,int> down[MAXM];
int cntup,cntdown;
int lt[MAXN][MAXH];
int rt[MAXN][MAXH];
int que[MAXM],head,tail;

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

bool cmp(pair<int,int>a,pair<int,int>b){
    return a.first>b.first;
}

struct segment{
    int tree1[MAXN<<2];
    int tree2[MAXN<<2];

    void up(int i){
        tree1[i]=min(tree1[i<<1],tree1[i<<1|1]);
        tree2[i]=max(tree2[i<<1],tree2[i<<1|1]);
    }

    void build(int l,int r,int i,int k){
        if(l==r){
            tree1[i]=lt[l][k];
            tree2[i]=rt[l][k];
        }
        else{
            int mid=(l+r)>>1;
            build(l,mid,i<<1,k);
            build(mid+1,r,i<<1|1,k);
            up(i);
        }
    }

    int queryleft(int jobl,int jobr,int l,int r,int i){
        if(jobl<=l&&r<=jobr){
            return tree1[i];
        }
        else{
            int mid=(l+r)>>1;
            int ans=n;
            if(jobl<=mid){
                ans=min(ans,queryleft(jobl,jobr,l,mid,i<<1));
            }
            if(jobr>mid){
                ans=min(ans,queryleft(jobl,jobr,mid+1,r,i<<1|1));
            }
            return ans;
        }
    }
    
    int queryright(int jobl,int jobr,int l,int r,int i){
        if(jobl<=l&&r<=jobr){
            return tree2[i];
        }
        else{
            int mid=(l+r)>>1;
            int ans=0;
            if(jobl<=mid){
                ans=max(ans,queryright(jobl,jobr,l,mid,i<<1));
            }
            if(jobr>mid){
                ans=max(ans,queryright(jobl,jobr,mid+1,r,i<<1|1));
            }
            return ans;
        }
    }

}root[MAXH];

void init(){
    sort(up+1,up+cntup+1);
    sort(down+1,down+cntdown+1,cmp);
    for(int i=1;i<=n;i++){
        lt[i][0]=rt[i][0]=i;
    }
    head=1,tail=0;
    for(int i=1,j=1;i<=n;i++){
        while(j<=cntup&&up[j].first<=i){
            int r=up[j].second;
            while(head<=tail&&up[que[tail]].second<=r){
                tail--;
            }
            que[++tail]=j;
            j++;
        }
        while(head<=tail&&up[que[head]].first<=i-k){
            head++;
        }
        if(head<=tail){
            rt[i][0]=max(rt[i][0],up[que[head]].second);
        }
    }

    head=1,tail=0;
    for(int i=n,j=1;i>=1;i--){
        while(j<=cntdown&&down[j].first>=i){
            int l=down[j].second;
            while(head<=tail&&down[que[tail]].second>=l){
                tail--;
            }
            que[++tail]=j;
            j++;
        }
        while(head<=tail&&down[que[head]].first>=i+k){
            head++;
        }
        if(head<=tail){
            lt[i][0]=min(lt[i][0],down[que[head]].second);
        }
    }
}

void prepare(){
    init();
    root[0].build(1,n,1,0);
    for(int k=1;k<MAXH;k++){
        for(int i=1;i<=n;i++){
            lt[i][k]=root[k-1].queryleft(lt[i][k-1],rt[i][k-1],1,n,1);
            rt[i][k]=root[k-1].queryright(lt[i][k-1],rt[i][k-1],1,n,1);
        }
        root[k].build(1,n,1,k);
    }
}

int query(int st,int en){
    int ans=0;
    int lt=st,rt=st;
    for(int k=MAXH-1;k>=0;k--){
        int l=root[k].queryleft(lt,rt,1,n,1);
        int r=root[k].queryright(lt,rt,1,n,1);
        if(l<=en&&en<=r){
            continue;
        }
        lt=l,rt=r;
        ans+=(1<<k);
    }
    int l=root[0].queryleft(lt,rt,1,n,1);
    int r=root[0].queryright(lt,rt,1,n,1);
    if(l<=en&&en<=r){
        return ans+1;
    }
    return -1;
}

int main()
{
    n=read(),k=read(),m=read();
    for(int i=1;i<=m;i++){
        int x,y;
        x=read(),y=read();
        if(x<y){
            up[++cntup]={x,y};
        }
        else{
            down[++cntdown]={x,y};
        }
    }
    prepare();
    q=read();
    while(q--){
        int st,en;
        st=read(),en=read();
        cout<<query(st,en)<<endl;
    }
    return 0;
}