#include<bits/stdc++.h>
using namespace std;
const int MAXN = 6e4+5;
const int MAXH = 16;

int n,m;
char str[MAXN];
int s[MAXN];
int lg2[MAXN];
int f[MAXN];
int g[MAXN];

struct SA{
    //桶数组x[i] 辅助数组y[i] 计数数组c[i]
    int x[MAXN];
    int y[MAXN];
    int c[MAXN];

    // 后缀数组：排名第i的后缀的起始位置
    int sa[MAXN];
    // 排名数组：起始位置为i的后缀的排名
    int rk[MAXN];
    // height[i]表示的是排名为i和排名为i-1的最长公共前缀的长度
    int height[MAXN]; 

    int st[MAXN][MAXH];

    void getsa(){
        for(int i=0;i<MAXN;i++){
            x[i]=y[i]=c[i]=sa[i]=rk[i]=height[i]=0;
        }
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

    void getheight(){
        for(int i=1;i<=n;i++){
            rk[sa[i]]=i;
        }
        for(int i=1,k=0;i<=n;i++){
            if(rk[i]==1){
                continue;
            }
            // 利用height性质：height[rk[i]] >= height[rk[i-1]] - 1
            if(k){
                k--;
            }
            int j=sa[rk[i]-1];
            while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k]){
                k++;
            }
            height[rk[i]]=k;
        }
    }

    void buildst(){
        for(int i=1;i<=n;i++){
            st[i][0]=height[i];
        }
        for(int i=1;i<=lg2[n];i++){
            for(int j=1;j+(1<<(i-1))-1<=n;j++){
                st[j][i]=min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
            }
        }
    }

    int query(int l,int r){
        // cout<<l<<' '<<r<<' ';
        int lt=rk[l],rt=rk[r];
        l=min(lt,rt)+1;
        r=max(lt,rt);
        int p=lg2[r-l+1];
        // cout<<l<<' '<<r<<' '<<p<<endl;
        return min(st[l][p],st[r-(1<<p)+1][p]);
    }
};
SA A,B;

void compute(){
    for(int i=1;i<=n+1;i++){
        f[i]=0,g[i]=0;
    }
    m=27;
    for(int i=1;i<=n;i++){
        s[i]=str[i]-'a'+1;
    }
    A.getsa();
    A.getheight();
    A.buildst();
    
    for(int l=1,r=n;l<r;l++,r--){
        swap(s[l],s[r]);
    }
    m=27;
    B.getsa();
    B.getheight();
    B.buildst();

    // for(int i=1;i<=n;i++){
    //     cout<<B.height[i]<<' ';
    // }
    // cout<<endl;

    for(int len=1;len<=n/2;len++){
        for(int i=len,j=i+len;j<=n;i+=len,j+=len){
            int lcp=min(len,A.query(i,j));
            int lcs=min(len-1,B.query(n-j+2,n-i+2));

            if(lcp+lcs>=len){
                int t=lcp+lcs-len+1;
                g[i-lcs]++;
                g[i-lcs+t]--;
                f[j+lcp-t]++;
                f[j+lcp]--;
            }
        }
    }

    for(int i=1;i<=n;i++){
        f[i]+=f[i-1];
        g[i]+=g[i-1];
    }

    long long ans=0;
    for(int i=1;i<n;i++){
        ans+=1ll*f[i]*g[i+1];
    }
    cout<<ans<<endl;

    
    // for(int i=1;i<=n;i++){
    //     cout<<A.sa[i]<<' ';
    // }
    // cout<<endl;
    // for(int i=1;i<=n;i++){
    //     cout<<B.sa[i]<<' ';
    // }
    // cout<<endl;
}

int main()
{
    lg2[0]=-1;
    for(int i=1;i<=30005;i++){
        lg2[i]=lg2[i>>1]+1;
    }
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",str+1);
        n=strlen(str+1);
        compute();
    }
    return 0;
}