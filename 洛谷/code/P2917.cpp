// https://www.luogu.com.cn/problem/P2917
// 题意：输入天数 D、两种消毒服务天数 N_1, N_2、单价 C_1, C_2、新玩具单价 Tc，以及每天所需玩具数量 T_i。
// 每天需备齐 T_i 个消毒玩具，可早上新购（花费 Tc），或在派对结束后将用过的玩具送往服务 1（N_1 晚后取回
// C_1/个）或服务 2（N_2 晚后取回，C_2/个）消毒后留待后用。
// 合理安排每天的购买与两种消毒方案，以最低总花费满足全部 D 天的需求。
// 输出一行一个整数，表示所需的最低总成本。
// 数据范围：对于 100% 的数据，1 <= D <= 10^5，1 <= T_i <= 50，1 <= Tc, C_1, C_2 <= 60
// 1 <= N_1, N_2 <= D。
#include<bits/stdc++.h>
// 算法标签：三分查找、贪心、双端队列
using namespace std;
const int MAXN = 1e5+5;
const int INF = 1e9;

int d,n1,n2,c1,c2,tc;
int need[MAXN];

struct node{
    int day;
    int cnt;
};
deque<node>dq1,dq2,dq3;

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

void add(int day,int cnt){
    dq1.push_back({day,cnt});
}

void update(int now){
    while(!dq1.empty()&&now-dq1.front().day>=n1){
        dq2.push_back(dq1.front());
        dq1.pop_front();
    }
    while(!dq2.empty()&&now-dq2.front().day>=n2){
        dq3.push_back(dq2.front());
        dq2.pop_front();
    }
}

int compute(int x){
    dq1.clear();
    dq2.clear();
    dq3.clear();

    int ans=(tc-c2)*x;
    add(-100005,x);
    for(int i=1;i<=d;i++){
        update(i);
        int now=need[i];
        while(now>0&&!dq3.empty()){
            node tmp=dq3.back();;
            dq3.pop_back();
            if(tmp.cnt>=now){
                tmp.cnt-=now;
                ans+=now*c2;
                now=0;
                dq3.push_back(tmp);
            }
            else{
                now-=tmp.cnt;
                ans+=c2*tmp.cnt;
            }
        }
        
        while(now>0&&!dq2.empty()){
            node tmp=dq2.back();;
            dq2.pop_back();
            if(tmp.cnt>=now){
                tmp.cnt-=now;
                ans+=now*c1;
                now=0;
                dq2.push_back(tmp);
            }
            else{
                now-=tmp.cnt;
                ans+=c1*tmp.cnt;
            }
        }
        if(now){
            return INF;
        }
        add(i,need[i]);
    }
    return ans;
}

int main()
{
    d=read(),n1=read(),n2=read(),c1=read(),c2=read(),tc=read();
    for(int i=1;i<=d;i++){
        need[i]=read();
    }
    if(n1>n2){
        swap(n1,n2);
        swap(c1,c2);
    }
    if(c1<c2){
        c2=c1;
    }

    int all=0;
    for(int i=1;i<=d;i++){
        all+=need[i];
    }
    int lt=0,rt=all;
    while(rt-lt>2){
        int mid1=lt+(rt-lt)/3;
        int mid2=rt-(rt-lt)/3;
        int cost1=compute(mid1);
        int cost2=compute(mid2);
        if(cost1<=cost2){
            rt=mid2;
        }
        else{
            lt=mid1;
        }
    }
    int ans=INF;
    for(int i=lt;i<=rt;i++){
        ans=min(ans,compute(i));
    }
    cout<<ans<<endl;
    return 0;
}