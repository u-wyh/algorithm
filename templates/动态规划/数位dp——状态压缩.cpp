// https://www.luogu.com.cn/problem/P8766
// 这道题并不是严格意义上的状态压缩  但是很巧妙
// 我们可以枚举这个最大值 令这个最大值为a  那么有bc都要小于a
// 除此之外  a=b^c<b+c  b+c>=a^c
// 所以 b+c!=b^c  也就是说他们一定存在某一位上都是1
// 如果a这一位上是0  那么bc分别是 11 或者00
// 如果a的这一位上是1  那么bc只能是01 或者10
// 上面这两行时死规矩  任意一位都要满足
// 如果b<a  那么一定有一位  在这一位之前的全部一样  但是这一位ab分别是10
// ac同理  我们将这些要求状态压缩
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 32;

int f[MAXN][8][2];
int n;

// 我们实际上是枚举a的每一位来收集答案  从而保证答案的不重不漏
// bc的状态是寄托在a的状态的基础上的
int dfs(int x,int now,int free){
    if(x<0){
        return now==7;
    }
    if(f[x][now][free]!=-1){
        return f[x][now][free];
    }
    int v=(n>>x)&1;
    int ans=0;
    if(free){
        ans+=dfs(x-1,now,1);
        if((now&1)&&(now&2)){
            ans+=dfs(x-1,now|4,1);// 0 1 1  这样填的前提是已经满足了bc小于a  我们认为这是满足了第三个条件
        }

        ans+=dfs(x-1,now|1,1);//1 1 0满足b小于a的条件
        ans+=dfs(x-1,now|2,1);//1 0 1满足c小于a的条件
    }
    else{
        if(v==0){
            ans+=dfs(x-1,now,0);
            if((now&1)&&(now&2)){
                ans+=dfs(x-1,now|4,0);
            }
        }
        else{
            ans+=dfs(x-1,now,1);
            if((now&1)&&(now&2)){
                ans+=dfs(x-1,now|4,1);
            }
            ans+=dfs(x-1,now|1,0);
            ans+=dfs(x-1,now|2,0);
        }
    }
    f[x][now][free]=ans;
    return ans;
}

signed main()
{
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=0;i<=31;i++){
            for(int j=0;j<8;j++){
                f[i][j][0]=-1;
                f[i][j][1]=-1;
            }
        }
        cout<<dfs(31,0,0)*3<<endl;
    }
    return 0;
}