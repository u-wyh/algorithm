#include<bits/stdc++.h>
using namespace std;
const int MAXN = 4e5+5;
const int MAXM = 1e5+5;

int n,q,m;
int s[MAXN];
int id[MAXN];

//桶数组x[i] 辅助数组y[i] 计数数组c[i]
int x[MAXN];
int y[MAXN];
int c[MAXN];

// 后缀数组：排名第i的后缀的起始位置
int sa[MAXN];
// 排名数组：起始位置为i的后缀的排名
int rk[MAXN];

int blen;
int bi[MAXN];

struct QUERY{
    int l,r,id;
};
QUERY query[MAXM];
int cntq;

int ss[MAXM];

int ans;
int ans1[MAXM];
int ans2[MAXM];
int cnt[MAXM];

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

void getsa(int n){
    for(int i=1;i<=n;i++){
        x[i]=s[i],c[x[i]]++;
    }
    for(int i=1;i<=m;i++){
        c[i]+=c[i-1];
    }
    for(int i=n;i>=1;i--){
        sa[c[x[i]]--]=i;
    }
    for(int k=1;k<=n;k<<=1){
        // 按照第二个关键字排序
        for(int i=0;i<=m;i++){
            c[i]=0;
        }
        for(int i=1;i<=n;i++){
            y[i]=sa[i];
        }
        for(int i=1;i<=n;i++){
            c[x[y[i]+k]]++;
        }
        for(int i=1;i<=m;i++){
            c[i]+=c[i-1];
        }
        for(int i=n;i>=1;i--){
            sa[c[x[y[i]+k]]--]=y[i];
        }

        // 按照第一个关键字排序
        for(int i=0;i<=m;i++){
            c[i]=0;
        }
        for(int i=1;i<=n;i++){
            y[i]=sa[i];
        }
        for(int i=1;i<=n;i++){
            c[x[y[i]]]++;
        }
        for(int i=1;i<=m;i++){
            c[i]+=c[i-1];
        }
        for(int i=n;i>=1;i--){
            sa[c[x[y[i]]]--]=y[i];
        }

        // 保存上一轮的组号到y数组
        for(int i=1;i<=n;i++){
            y[i]=x[i];
        }
        m=0;
        for(int i=1;i<=n;i++){
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]){
                // 第一个关键字组号相同  第二个关键字组号相同  那么这一次也是一个组
                x[sa[i]]=m;
            }
            else{
                x[sa[i]]=++m;
            }
            if(m==n){
                break;
            }
        }
    }
}

bool cmp(QUERY &a,QUERY &b){
    if(bi[a.l]!=bi[b.l]){
        return a.l<b.l;
    }
    if(bi[a.l]&1){
        return a.r<b.r;
    }
    else{
        return a.r>b.r;
    }
}

void add(int x,int cur){
    if(++cnt[id[x]]==1){
        ans++;
        ans2[id[x]]+=cntq-cur+1;
    }
}

void del(int x,int cur){
    if(--cnt[id[x]]==0){
        ans--;
        ans2[id[x]]-=cntq-cur+1;
    }
}

int main()
{
    n=read(),q=read();
    int tot=0;
    m=10000;

    for(int i=1;i<=n;i++){
        for(int k=0;k<2;k++){
            int len=read();
            for(int j=1;j<=len;j++){
                s[++tot]=read();
                id[tot]=i;
            }
            s[++tot]=++m;
        }
    }
    getsa(tot);
    blen=sqrt(tot);
    for(int i=1;i<=tot;i++){
        bi[i]=(i-1)/blen+1;
    }

    cntq=0;
    for(int i=1;i<=q;i++){
        int len=read();
        for(int j=1;j<=len;j++){
            ss[j]=read();
        }
        int lt=1,rt=tot;
        for(int j=1;j<=len;j++){
            int l=lt,r=rt,tmp=rt+1;
            while(l<=r){
                int mid=(l+r)>>1;
                int pos=sa[mid]+j-1;
                if(pos>tot||s[pos]<ss[j]){
                    l=mid+1;
                }
                else{
                    tmp=mid;
                    r=mid-1;
                }
            }

            int l2=lt,r2=rt,tmp2=lt-1;
            while(l2<=r2){
                int mid=(l2+r2)>>1;
                int pos=sa[mid]+j-1;
                if(pos<=tot&&s[pos]<=ss[j]){
                    l2=mid+1;
                    tmp2=mid;
                }
                else{
                    r2=mid-1;
                }
            }

            lt=tmp,rt=tmp2;
            if(lt>rt){
                break;
            }
        }
        if(lt<=rt){
            query[++cntq]={lt,rt,i};
        }
    }

    sort(query+1,query+cntq+1,cmp);
    // cout<<' '<<cntq<<endl;
    int l=1,r=0;
    for(int i=1;i<=cntq;i++){
        while(l>query[i].l){
            add(sa[--l],i);
        }
        while(r<query[i].r){
            add(sa[++r],i);
        }
        while(l<query[i].l){
            del(sa[l++],i);
        }
        while(r>query[i].r){
            del(sa[r--],i);
        }
        ans1[query[i].id]=ans;
    }
    for(int i=1;i<=q;i++){
        cout<<ans1[i]<<endl;
    }
    for(int i=1;i<=n;i++){
        cout<<ans2[i]<<' ';
    }
    return 0;
}