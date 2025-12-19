#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXB = 505;

int n,m;
int op[MAXN];
int x[MAXN];
int y[MAXN];

int a[MAXN];
int b[MAXN];
int ans[MAXN];

int arr[MAXN];
set<int>s[MAXN];

unordered_map<long long,int>mp;

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int maxx[MAXN];
int maxblock[MAXN];

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
    int len=0;
    for(int i=1;i<=n;i++){
        if(op[i]==1){
            arr[++len]=y[i];
        }
    }
    sort(arr+1,arr+len+1);
    m=1;
    for(int i=2;i<=len;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(op[i]==1){
            ++cnt;
            y[i]=find(y[i]);
            a[cnt]=x[i],b[cnt]=y[i];
            mp[a[cnt]*(m+1)+b[cnt]]=cnt;
        }
    }

    blen=sqrt(m);
    bnum=(m+blen-1)/blen;
    for(int i=1;i<=m;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(m,i*blen);
    }
}

void add(int x,int y){
    s[x].insert(y);
    maxx[x]=max(maxx[x],y);
    maxblock[bi[x]]=max(maxblock[bi[x]],y);
}

int query(int x,int y){
    for(int i=y;i<=br[bi[y]];i++){
        if(i==y){
            if(maxx[i]>x){
                auto it=s[i].upper_bound(x);
                int val=*it;
                return mp[i+val*(m+1)];
            }
        }
        else{
            if(maxx[i]>=x){
                auto it=s[i].lower_bound(x);
                int val=*it;
                return mp[i+val*(m+1)];
            }
        }
    }
    for(int b=bi[y]+1;b<=bnum;b++){
        if(maxblock[b]>=x){
            for(int i=bl[b];i<=br[b];i++){
                if(maxx[i]>=x){
                    auto it=s[i].lower_bound(x);
                    int val=*it;
                    return mp[i+val*(m+1)];
                }
            }
        }
    }
    return 0;
}

void compute(){
    for(int i=1;i<=n;i++){
        if(op[i]==1){
            add(y[i],x[i]);
        }
        else{
            ans[i]=query(a[x[i]],b[x[i]]);
        }
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        char c;
        scanf(" %c",&c);
        if(c=='D'){
            op[i]=1;
            scanf("%d %d",&x[i],&y[i]);
        }
        else{
            op[i]=2;
            scanf("%d",&x[i]);
        }
    }
    prepare();
    compute();
    for(int i=1;i<=n;i++){
        if(op[i]==2){
            if(ans[i]){
                printf("%d\n",ans[i]);
            }
            else{
                printf("NE\n");
            }
        }
    }
    return 0;
}