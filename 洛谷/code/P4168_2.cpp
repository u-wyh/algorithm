#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e4+5;
const int MAXB = 205;

int n,m;
int val[MAXN];
int len;
int sortv[MAXN];

int blen,bnum;
int bi[MAXN];
int bl[MAXB];
int br[MAXB];

int freq[MAXB][MAXN];
int mode[MAXB][MAXB];
int numcnt[MAXN];

int find(int val){
    int l=1,r=len,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(sortv[mid]>=val){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    return ans;
}

int getcnt(int l,int r,int val){
    return freq[r][val]-freq[l-1][val];
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

    for(int i=1;i<=n;i++){
        sortv[i]=val[i];
    }
    sort(sortv+1,sortv+n+1);
    len=1;
    for(int i=2;i<=n;i++){
        if(sortv[i]!=sortv[i-1]){
            sortv[++len]=sortv[i];
        }
    }
    for(int i=1;i<=n;i++){
        val[i]=find(val[i]);
    }

    for(int i=1;i<=n;i++){
        freq[bi[i]][val[i]]++;
    }
    for(int i=1;i<=bnum;i++){
        for(int j=1;j<=len;j++){
            freq[i][j]+=freq[i-1][j];
        }
    }

    for(int i=1;i<=bnum;i++){
        for(int j=i;j<=bnum;j++){
            int most=mode[i][j-1];
            int mostcnt=getcnt(i,j,most);
            for(int k=bl[j];k<=br[j];k++){
                int cnt=getcnt(i,j,val[k]);
                if(cnt>mostcnt||mostcnt==cnt&&val[k]<most){
                    most=val[k];
                    mostcnt=cnt;
                }
            }
            mode[i][j]=most;
        }
    }
}

int compute(int l,int r){
    int lb=bi[l];
    int rb=bi[r];
    int most=len+1;
    int mostcnt=0;
    if(lb==rb){
        for(int i=l;i<=r;i++){
            numcnt[val[i]]++;
            if(numcnt[val[i]]>mostcnt){
                most=val[i];
                mostcnt=numcnt[val[i]];
            }
            else if(numcnt[val[i]]==mostcnt&&most>val[i]){
                most=val[i];
            }
        }
        for(int i=l;i<=r;i++){
            numcnt[val[i]]=0;
        }
    }
    else{
        for (int i = l; i <= br[bi[l]]; i++) {
            numcnt[val[i]]++;
        }
        for (int i = bl[bi[r]]; i <= r; i++) {
            numcnt[val[i]]++;
        }
        most=mode[lb+1][rb-1];
        mostcnt=getcnt(lb+1,rb-1,most)+numcnt[most];
        for (int i = l; i <= br[bi[l]]; i++) {
            int cur = val[i];
            int curCnt = getcnt(bi[l] + 1, bi[r] - 1, cur) + numcnt[cur];
            if (curCnt > mostcnt || (curCnt == mostcnt && cur < most)) {
                most = cur;
                mostcnt = curCnt;
            }
        }
        //枚举右散块
        for (int i = bl[bi[r]]; i <= r; i++) {
            int cur = val[i];
            int curCnt = getcnt(bi[l] + 1, bi[r] - 1, cur) + numcnt[cur];
            if (curCnt > mostcnt || (curCnt == mostcnt && cur < most)) {
                most = cur;
                mostcnt = curCnt;
            }
        }
        for (int i = l; i <= br[bi[l]]; i++) {
            numcnt[val[i]]=0;
        }
        for (int i = bl[bi[r]]; i <= r; i++) {
            numcnt[val[i]]=0;
        }
    }
    return most;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>val[i];
    }
    prepare();
    int ans=0;
    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        l=(l+ans-1)%n+1;
        r=(r+ans-1)%n+1;
        if(l>r){
            swap(l,r);
        }
        ans=sortv[compute(l,r)];
        cout<<ans<<endl;
    }
    return 0;
}