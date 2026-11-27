// https://www.luogu.com.cn/problem/P7597
// 题意：交互题。
// 以 1 为根的 n 个节点有根树，可询问两点距离（? 1 u v）或某点子树大小及无序点集（? 2 u），要求交互库输出总整数个数不超过 40000
// 还原所有点父节点。
// 数据范围：2 <= n <= 5000，1 <= u, v <= n。
// 算法标签：随机化、分治、位运算
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e3+5;

int n;
int dep[MAXN];
int fa[MAXN];
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int ask1(int u,int v){
    cout<<"? 1 "<<u<<' '<<v<<endl;
    int res;
    cin>>res;
    return res;
}

bitset<MAXN> ask2(int u){
    cout<<"? 2 "<<u<<endl;

    int sz;
    cin>>sz;

    bitset<MAXN>s;
    for(int i=1;i<=sz;i++){
        int x;
        cin>>x;
        s[x]=1;
    }
    return s;
}

void solve(int u,bitset<MAXN> s){
    while(true){
        int cnt=0,lst=0;

        for(int v=1;v<=n;v++){
            if(s[v] && dep[v]==dep[u]+1){
                fa[v]=u;
                cnt++;
                lst=v;
            }
        }

        if(cnt==0){
            return ;
        }

        if(cnt==1){
            s[u]=0;
            u=lst;
            continue;
        }

        int k=rnd()%((int)s.count()-1);
        int x=0;
        for(int v=1;v<=n;v++){
            if(s[v]&&v!=u){
                if(k==0){
                    x=v;
                    break;
                }
                k--;
            }
        }

        int heavy=lst;
        for(int v=1;v<=n;v++){
            if(v==lst){
                break;
            }
            if(s[v]&&dep[v]==dep[u]+1){
                if(ask1(v,x)==dep[x]-dep[v]){
                    heavy=v;
                    break;
                }
            }
        }

        for(int v=1;v<=n;v++){
            if(v==heavy){
                continue;
            }
            if(s[v]&&dep[v]==dep[u]+1){
                bitset<MAXN>s2=ask2(v);
                s&=~s2;
                solve(v,s2);
            }
        }

        s[u]=0;
        u=heavy;
    }
}

int main()
{
    cin>>n;
    for(int i=2;i<=n;i++){
        dep[i]=ask1(1,i);
    }

    bitset<MAXN>s;
    for(int i=1;i<=n;i++){
        s[i]=1;
    }

    solve(1,s);

    cout<<"!";
    for(int i=2;i<=n;i++){
        cout<<' '<<fa[i];
    }
    return 0;
}