#include<bits/stdc++.h>
using namespace std;

const int MAXN=1005;
const int MAXK=15;

int n,k;
int dif[MAXN][MAXK];
bool endpoint[MAXN];

int p1[MAXN],p2[MAXN],ans[MAXN];

int ask(int m,int v){
    cout<<"? "<<m<<" "<<v<<endl;

    int x;
    cin>>x;

    if(x==-1){
        exit(0);
    }

    return x;
}

// 已知当前点 cur 和上一个点 pre，求下一个点
int getnext(int cur,int pre){
    int nxt=0;

    for(int j=0;j<k;j++){
        int d=dif[cur][j];
        int b=(cur>>j)&1;
        int nb=0;

        if(endpoint[cur]){
            // 端点只有一个邻居
            if(d==1){
                nb=b;
            }
            else{
                nb=b^1;
            }
        }
        else{
            // 中间点有两个邻居
            // t = 两个邻居中第 j 位为 1 的个数
            int t;

            if(d==0){
                t=1;
            }
            else if(d==1){
                if(b==0){
                    t=2;
                }
                else{
                    t=0;
                }
            }
            else{
                if(b==0){
                    t=0;
                }
                else{
                    t=2;
                }
            }

            nb=t-((pre>>j)&1);
        }

        if(nb){
            nxt|=(1<<j);
        }
    }

    return nxt;
}

// 从一个非 0 端点开始，一直走到 0
int walk(int st,int *p){
    int len=0;

    int pre=-1;
    int cur=st;

    while(1){
        p[++len]=cur;

        if(cur==0){
            break;
        }

        int nxt=getnext(cur,pre);

        pre=cur;
        cur=nxt;
    }

    return len;
}

void solve(){
    cin>>n;

    if(n==1){
        cout<<"! 0"<<endl;
        return;
    }

    k=0;
    while((1<<k)<n){
        k++;
    }

    /*
        每一位：

        1 次 ? m -1
        n-1 次 ? m v, v=1...n-1

        总共正好 n 次。
    */

    for(int j=0;j<k;j++){
        int m=1<<j;

        int base=ask(m,-1);

        for(int v=1;v<n;v++){
            int x=ask(m,v);

            dif[v][j]=(x-base+3)%3;
        }
    }

    /*
        对非 0 点判断是不是端点。

        端点每一位 dif 都不可能为 0。
        中间点一定存在一位 dif=0。
    */

    int e1=-1,e2=-1;

    for(int v=1;v<n;v++){
        endpoint[v]=true;

        for(int j=0;j<k;j++){
            if(dif[v][j]==0){
                endpoint[v]=false;
                break;
            }
        }

        if(endpoint[v]){
            if(e1==-1){
                e1=v;
            }
            else{
                e2=v;
            }
        }
    }

    int len=0;

    if(e2==-1){
        /*
            只有一个非 0 端点。

            说明另一个端点就是 0。
        */

        len=walk(e1,ans);
    }
    else{
        /*
            两个端点都非 0。

            说明 0 是中间点。

            e1 -> ... -> 0
            e2 -> ... -> 0
        */

        int len1=walk(e1,p1);
        int len2=walk(e2,p2);

        for(int i=1;i<=len1;i++){
            ans[++len]=p1[i];
        }

        // p2[len2] 是 0，已经出现过了
        for(int i=len2-1;i>=1;i--){
            ans[++len]=p2[i];
        }
    }

    /*
        题目保证 p1 < pn
    */

    if(ans[1]>ans[len]){
        reverse(ans+1,ans+len+1);
    }

    cout<<"!";
    for(int i=1;i<=len;i++){
        cout<<" "<<ans[i];
    }
    cout<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin>>T;

    while(T--){
        solve();
    }

    return 0;
}