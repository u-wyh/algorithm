#include<bits/stdc++.h>
using namespace std;

namespace GenHelper {
    unsigned z1, z2, z3, z4, b;

    inline unsigned rand_() {
        b = ((z1 << 6) ^ z1) >> 13;
        z1 = ((z1 & 4294967294U) << 18) ^ b;
        b = ((z2 << 2) ^ z2) >> 27;
        z2 = ((z2 & 4294967288U) << 2) ^ b;
        b = ((z3 << 13) ^ z3) >> 21;
        z3 = ((z3 & 4294967280U) << 7) ^ b;
        b = ((z4 << 3) ^ z4) >> 12;
        z4 = ((z4 & 4294967168U) << 13) ^ b;
        return z1 ^ z2 ^ z3 ^ z4;
    }

    inline void seed(unsigned x) {
        z1 = x;
        z2 = (~x) ^ 0x233333333U;
        z3 = x ^ 0x1234598766U;
        z4 = (~x) + 51;
    }
}

inline int readRand() {
    using namespace GenHelper;
    int a = rand_() & 32767;
    int b = rand_() & 32767;
    return a * 32768 + b;
}

const int MAXN = 2e7+5;
const int MAXB = 1e6+5;
const int MAXH = 22;
int n,m,s;
int blen;
int bnum;

int val[MAXN];
int pre[MAXN];
int suf[MAXN];

int maxx[MAXB];
int bl[MAXB];
int br[MAXB];

int lg2[MAXB];

int st[MAXH][MAXB];

void prepare(){
    blen=32;
    bnum=(n+blen-1)/blen;
    for(int i=1;i<=bnum;i++){
        bl[i]=(i-1)*blen+1;
        br[i]=min(n,i*blen);
    }

    for(int i=1;i<=bnum;i++){
        int maxval=0;
        int l=bl[i];
        int r=br[i];
        for(int i=l;i<=r;i++){
            pre[i]=max(maxval,val[i]);
            maxval=pre[i];
        }
        maxval=0;
        for(int i=r;i>=l;i--){
            suf[i]=max(maxval,val[i]);
            maxval=suf[i];
        }

        maxx[i]=pre[r];
    }

    lg2[0]=-1;
    for(int i=1;i<=bnum;i++){
        lg2[i]=lg2[i>>1]+1;
    }

    for(int i=1;i<=bnum;i++){
        st[0][i]=maxx[i];
    }
    for(int i=1;i<=lg2[bnum];i++){
        for(int j=1;j+(1<<i)-1<=bnum;j++){
            st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
        }
    }
}

int query(int l,int r){
    int len=r-l+1;
    int i=lg2[len];
    return max(st[i][l],st[i][r-(1<<i)+1]);
}

int main()
{
    ios::sync_with_stdio(false); // 修改：关闭同步
    cin.tie(nullptr);       
    cin>>n>>m>>s;
    GenHelper::seed(s);

    for(int i=1;i<=n;i++){
        val[i]=readRand();
    }
    prepare();

    unsigned long long ans = 0;
    for(int i=1;i<=m;i++){
        int l=readRand()%n+1;
        int r=readRand()%n+1;
        if(l>r){
            swap(l,r);
        }
        int lb = (l - 1) / blen + 1;
        int rb = (r - 1) / blen + 1;
        int tmp=0;
        if(lb==rb){
            for(int i=l;i<=r;i++){
                tmp=max(tmp,val[i]);
            }
        }
        else{
            tmp=max(pre[r],suf[l]);
            if(lb<rb-1){
                tmp=max(tmp,query(lb+1,rb-1));
            }
        }
        ans+=tmp;
    }
    cout<<ans<<endl;
    return 0;
}