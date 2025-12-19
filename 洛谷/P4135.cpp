#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXB = 405;

int n,c,m;
int nums[MAXN];

int blen;
int bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int freq[MAXB][MAXN];
int even[MAXB][MAXB];
int cnt[MAXN];

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

int getcnt(int l,int r,int v){
    return freq[r][v]-freq[l-1][v];
}

int delta(int pre){
    if(pre==0){
        return 0;
    }
    if(pre&1){
        return 1;
    }
    return -1;
}

void prepare(){
    blen=sqrt(n);
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=n;i++){
        bi[i]=(i-1)/blen+1;
    }
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }
    for(int i=1;i<=bnum;i++){
        for(int j=bl[i];j<=br[i];j++){
            freq[i][nums[j]]++;
        }
        for(int j=1;j<=c;j++){
            freq[i][j]+=freq[i-1][j];
        }
    }
    for(int i=1;i<=bnum;i++){
        for(int j=i;j<=bnum;j++){
            even[i][j]=even[i][j-1];
            for(int k=bl[j];k<=br[j];k++){
                even[i][j]+=delta(cnt[nums[k]]++);
            }
        }
        for(int j=1;j<=c;j++){
            cnt[j]=0;
        }
    }
}

int query(int l,int r){
    int ans=0;
    if(bi[l]==bi[r]){
        for(int i=l;i<=r;i++){
            ans+=delta(cnt[nums[i]]++);
        }
        for(int i=l;i<=r;i++){
            cnt[nums[i]]=0;
        }
    }
    else{
        ans=even[bi[l]+1][bi[r]-1];
        for(int i=l;i<=br[bi[l]];i++){
            ans+=delta(getcnt(bi[l]+1,bi[r]-1,nums[i])+cnt[nums[i]]);
            cnt[nums[i]]++;
        }
        for(int i=bl[bi[r]];i<=r;i++){
            ans+=delta(getcnt(bi[l]+1,bi[r]-1,nums[i])+cnt[nums[i]]);
            cnt[nums[i]]++;
        }
        for(int i=l;i<=br[bi[l]];i++){
            cnt[nums[i]]=0;
        }
        for(int i=bl[bi[r]];i<=r;i++){
            cnt[nums[i]]=0;
        }
    }
    return ans;
}

int main()
{
    n=read(),c=read(),m=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    prepare();
    int ans=0;
    for(int i=1;i<=m;i++){
        int l,r;
        l=read(),r=read();
        l=(l+ans)%n+1;
        r=(r+ans)%n+1;
        if(l>r){
            swap(l,r);
        }
        ans=query(l,r);
        printf("%d\n",ans);
    }
    return 0;
}