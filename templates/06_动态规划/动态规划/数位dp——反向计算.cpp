// https://www.luogu.com.cn/problem/P7415
// 这道题可以抽象化题意为  查询0~d范围内  给定数字xy  使得x+d和y+d的三进制位上的数字奇偶性相同
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 40;

// 表示目前来到了第i位  a的进位输入是j  b的进位输入是k  是否有限制
// 从高位到低位推  这里的进位输入指的是这一位要想上一位的进位输入  即对上一位的贡献
int f[MAXN][2][2][2];
int a[MAXN],b[MAXN],d[MAXN];

bool check(int x,int y){
    if(x<0||x>2||y<0||y>2){
        return false;
    }
    return (x&1)==(y&1);
}

int dfs(int x,int aa,int bb,int free){
    if(x<0){
        // 最低位一定是没有进制的
        return (aa==0)&&(bb==0);
    }
    if(f[x][aa][bb][free]!=-1){
        return f[x][aa][bb][free];
    }

    int ans=0;
    int up=free?2:d[x];
    for(int v=0;v<=up;v++){
        // 枚举下一位的进位输入  也就是下一位要向这一位的进位
        for(int aaa=0;aaa<=1;aaa++){
            for(int bbb=0;bbb<=1;bbb++){
                if(check(a[x]+v+aaa-3*aa,b[x]+v+bbb-3*bb)){
                    // 检查这一位是否可以符合条件  条件是在下一位的进位输入以及这一位上d的贡献加上本身的值  减去对上一位的贡献
                    // 最终的数字是否符合条件  处于0~2并且奇偶性相同
                    ans+=dfs(x-1,aaa,bbb,free||v<d[x]);
                }
            }
        }
    }

    f[x][aa][bb][free]=ans;
    return ans;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        int x,y,z;
        cin>>z>>x>>y;
        memset(f,-1,sizeof(f));
        for(int i=0;i<MAXN;i++){
            a[i]=x%3;
            b[i]=y%3;
            d[i]=z%3;
            x/=3,y/=3,z/=3;
        }
        // 这个位置上根本不会有数字 所以进位一定是0
        cout<<dfs(MAXN-1,0,0,0)<<endl;
    }
    return 0;
}