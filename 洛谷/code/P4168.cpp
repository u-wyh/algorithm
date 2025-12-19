#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e4+5;
const int MAXB = 205;

int n,q;
int nums[MAXN];

int m=1;
int arr[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int freq[MAXB][MAXN];
int mode[MAXB][MAXB];
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

int find(int val){
    int l=1,r=m,ans;
    while(l<=r){
        int mid=(l+r)/2;
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

int getcnt(int l,int r,int v){
    return freq[r][v]-freq[l-1][v];
}

void prepare(){
    for(int i=1;i<=n;i++){
        arr[i]=nums[i];
    }
    sort(arr+1,arr+n+1);
    for(int i=2;i<=n;i++){
        if(arr[i]!=arr[i-1]){
            arr[++m]=arr[i];
        }
    }
    for(int i=1;i<=n;i++){
        nums[i]=find(nums[i]);
    }

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
        for(int j=1;j<=m;j++){
            freq[i][j]+=freq[i-1][j];
        }
    }
    for(int i=1;i<=bnum;i++){
        for(int j=i;j<=bnum;j++){
            int most=mode[i][j-1];
            int mostcnt=getcnt(i,j,most);
            for(int k=bl[j];k<=br[j];k++){
                int cur=nums[k];
                int curcnt=getcnt(i,j,cur);
                if(curcnt>mostcnt||(curcnt==mostcnt&&cur<most)){
                    most=cur;
                    mostcnt=curcnt;
                }
            }
            mode[i][j]=most;
        }
    }
}

int query(int l,int r){
    int most=0;
    if(bi[l]==bi[r]){
        for(int i=l;i<=r;i++){
            cnt[nums[i]]++;
        }
        for(int i=l;i<=r;i++){
            if(cnt[nums[i]]>cnt[most]||(cnt[nums[i]]==cnt[most]&&nums[i]<most)){
                most=nums[i];
            }
        }
        for(int i=l;i<=r;i++){
            cnt[nums[i]]=0;
        }
    }
    else{
        most=mode[bi[l]+1][bi[r]-1];
        for(int i=l;i<=br[bi[l]];i++){
            cnt[nums[i]]++;
        }
        for(int i=bl[bi[r]];i<=r;i++){
            cnt[nums[i]]++;
        }

        int mostcnt=getcnt(bi[l]+1,bi[r]-1,most)+cnt[most];
        for(int i=l;i<=br[bi[l]];i++){
            int cur=nums[i];
            int curcnt=getcnt(bi[l]+1,bi[r]-1,cur)+cnt[cur];
            if(curcnt>mostcnt||(curcnt==mostcnt&&cur<most)){
                most=cur;
                mostcnt=curcnt;
            }
        }
        for(int i=bl[bi[r]];i<=r;i++){
            int cur=nums[i];
            int curcnt=getcnt(bi[l]+1,bi[r]-1,cur)+cnt[cur];
            if(curcnt>mostcnt||(curcnt==mostcnt&&cur<most)){
                most=cur;
                mostcnt=curcnt;
            }
        }

        for(int i=l;i<=br[bi[l]];i++){
            cnt[nums[i]]=0;
        }
        for(int i=bl[bi[r]];i<=r;i++){
            cnt[nums[i]]=0;
        }
    }
    return arr[most];
}

int main()
{
    n=read(),q=read();
    for(int i=1;i<=n;i++){
        nums[i]=read();
    }
    prepare();
    int ans=0;
    for(int i=1;i<=q;i++){
        int l=read(),r=read();
        l=(l+ans-1)%n+1;
        r=(r+ans-1)%n+1;
        if(l>r){
            swap(l,r);
        }
        ans=query(l,r);
        printf("%d\n",ans);
    }
    return 0;
}