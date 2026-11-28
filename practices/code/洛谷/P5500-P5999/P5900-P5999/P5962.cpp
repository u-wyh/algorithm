// https://www.luogu.com.cn/problem/P5962
// 题意：给定 n*n 黑白棋盘每行黑格（船）的列区间描述，
// 四连通的黑格块算作一艘船、格数为吨位，统计每种吨位各有多少艘船。
// 输入 n 及每行的列区间（逗号分隔、分号结尾）；按吨位降序输出（吨位 数量）。
// 数据范围：1 <= n < 3*10^4，
// 船舶总数和每艘船的吨位均不超过 10^3。
// 难度评分：1500（洛谷分级换算）
// 算法标签：并查集、双指针、模拟
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3e4+5;
const int MAXM = 1e6+5;

int n;
int now,last;//表示这一行和上一行分别有多少个联通块
struct node{
    int u,v,id;//表示起点 终点 编号
}nums[MAXN],arr[MAXN];//分别表示这一行和上一行的联通块信息
int cnt;//联通块编号
int fa[MAXM];
int sz[MAXM];
string str;
int ans[1005];//ans[i]表示大小为i的联通块的个数

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx==fy){
        return ;
    }
    fa[fx]=fy;
    sz[fy]+=sz[fx];
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>str;
        if(str==";"){
            now=0;
            continue;
        }

        //复制上一层的信息
        for(int j=1;j<=now;j++){
            arr[j]=nums[j];
        }
        last=now;
        now=0;

        bool flag=false;//用于判断是  点  还是  段
        int a,b,num=0;//如果是段  那么a是左边界 b是右边界  num是用于辅助计算多位数
        for(int j=0;j<(int)str.size();j++){
            if(str[j]>='0'&&str[j]<='9'){
                num=num*10+(str[j]-'0');
            }
            else if(str[j]=='-'){
                a=num,flag=true,num=0;
            }
            else if(str[j]==','||str[j]==';'){
                if(flag){
                    //表示这是一段
                    b=num;//右边界
                }
                else{
                    a=b=num;//左右边界都是一个点
                }
                //新建联通块
                fa[++cnt]=cnt;
                sz[cnt]=b-a+1;

                nums[++now]={a,b,cnt};
                //判断与上一层是否相交
                int u=1;
                while(u<=last&&arr[u].v<a){
                    u++;
                }
                while(u<=last&&arr[u].u<=b){
                    un(arr[u].id,cnt);
                    u++;
                }

                a=0,b=0,num=0,flag=false;
            }
        }
    }
    for(int i=1;i<=cnt;i++){
        if(i==find(i)){
            ++ans[sz[i]];
        }
    }
    for(int i=1000;i>=1;i--){
        if(ans[i]){
            cout<<i<<' '<<ans[i]<<endl;
        }
    }
    return 0;
}