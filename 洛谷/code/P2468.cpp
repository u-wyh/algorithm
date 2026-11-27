// https://www.luogu.com.cn/problem/P2468
// 题意：R*C 矩阵每格有书页数 P_{i,j}，共 M 次询问。
// 每次询问在子矩形 (x1,y1)-(x2,y2) 中至少选多少本书，使总页数 >= H_i。
// 输出最少本数，无法达到输出 Poor QLW。
// 数据范围：50% R, C <= 200, M <= 2*10^5；
// 另 50% R = 1, C <= 5*10^5, M <= 2*10^4；
// 1 <= P_{i,j} <= 1000，H_i <= 2*10^9。
#include<bits/stdc++.h>
// 算法标签：二维前缀和、贪心、二分查找
using namespace std;
const int MAXN = 205;
const int MAXH = 1005;
const int MAXM = 5e5+5;

int n,m,q;
int val[MAXN][MAXN];
int all[MAXN][MAXN];
int pre[MAXH][MAXN][MAXN];

int a[MAXM];
vector<int>pos[MAXH];

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

int main()
{
    n=read(),m=read(),q=read();
    if(n>1){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                val[i][j]=read();
                pre[val[i][j]][i][j]=1;
            }
        }
        for(int v=1;v<=1000;v++){
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    pre[v][i][j]+=pre[v][i-1][j]+pre[v][i][j-1]-pre[v][i-1][j-1];
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                all[i][j]=all[i-1][j]+all[i][j-1]+val[i][j]-all[i-1][j-1];
            }
        }

        while(q--){
            int x1,y1,x2,y2,need;
            x1=read(),y1=read(),x2=read(),y2=read(),need=read();
            int now=all[x2][y2]-all[x1-1][y2]-all[x2][y1-1]+all[x1-1][y1-1];
            if(now<need){
                printf("Poor QLW\n");
            }
            else{
                int sum=0,ans=0;
                for(int v=1000;v>=1;v--){
                    int c=pre[v][x2][y2]-pre[v][x1-1][y2]-pre[v][x2][y1-1]+pre[v][x1-1][y1-1];
                    if(c==0){
                        continue;
                    }
                    if(sum+v*c<need){
                        sum+=v*c;
                        ans+=c;
                    }
                    else{
                        ans+=(need-sum+v-1)/v;
                        break;
                    }
                }
                printf("%d\n",ans);
            }
        }
    }
    else{
        for(int i=1;i<=m;i++){
            a[i]=read();
            pos[a[i]].push_back(i);
            a[i]+=a[i-1];
        }
        while(q--){
            int x1,y1,x2,y2,need;
            x1=read(),y1=read(),x2=read(),y2=read(),need=read();
            int now=a[y2]-a[y1-1];
            if(now<need){
                printf("Poor QLW\n");
            }
            else{
                int sum=0,ans=0;
                for(int v=1000;v>=1;v--){
                    if(pos[v].empty()){
                        continue;
                    }
                    auto it1=lower_bound(pos[v].begin(),pos[v].end(),y1);
                    auto it2=upper_bound(pos[v].begin(),pos[v].end(),y2);
                    int c=it2-it1;
                    if(c==0){
                        continue;
                    }
                    if(sum+v*c<need){
                        sum+=v*c;
                        ans+=c;
                    }
                    else{
                        ans+=(need-sum+v-1)/v;
                        break;
                    }
                }
                printf("%d\n",ans);
            }
        }
    }
    return 0;
}