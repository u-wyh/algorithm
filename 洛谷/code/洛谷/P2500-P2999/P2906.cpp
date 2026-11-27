// https://www.luogu.com.cn/problem/P2906
// 题意：输入奶牛数量 N、距离上限 C，
// 以及每头牛在牧场上的唯一整数坐标 (X_i, Y_i)。
// 若两头牛曼哈顿距离 |X_i - X_j| + |Y_i - Y_j| <= C
// 则互为邻居，有共同邻居的牛也同属一个「奶牛社区」（即传递连通块）。
// 统计所有「奶牛社区」的个数，以及最大社区包含的奶牛数量。
// 输出一行两个空格分隔的整数，依次为「奶牛社区」数量和最大社区内的牛数。
// 数据范围：对于 100% 的数据，1 <= N <= 10^5，
// 1 <= C <= 10^9，
// 1 <= X_i, Y_i <= 10^9（坐标均为整数）。
// 算法标签：并查集、扫描线、双指针
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int INF = 1e10;

int n,c;
int fa[MAXN];
int sz[MAXN];

struct node{
    int x,y,id;
    bool operator<(const node&other)const{
        return y<other.y;
    }
};
node nums[MAXN];
multiset<node>s;

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

int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

void un(int x,int y){
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy){
        sz[fx]+=sz[fy];
        fa[fy]=fx;
    }
}

bool cmp(node a,node b){
    return a.x<b.x;
}

void compute(){
    sort(nums+1,nums+n+1,cmp);

    s.insert(nums[1]);

    node tmp={0,INF,0};
    s.insert(tmp);
    tmp.y=-INF;
    s.insert(tmp);

    int head=1;
    for(int i=2;i<=n;i++){
        while(nums[i].x-nums[head].x>c){
            s.erase(s.find(nums[head]));
            head++;
        }
        auto it=s.lower_bound(nums[i]);
        tmp=*it;
        if(tmp.y-nums[i].y<=c){
            un(tmp.id,nums[i].id);
        }
        tmp=*(--it);
        if(nums[i].y-tmp.y<=c){
            un(tmp.id,nums[i].id);
        }
        s.insert(nums[i]);
    }
}

signed main()
{
    n=read(),c=read();
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
    for(int i=1;i<=n;i++){
        int x,y;
        x=read(),y=read();
        nums[i]={x+y,x-y,i};
    }
    compute();
    int ans=0,maxx=0;
    for(int i=1;i<=n;i++){
        if(i==find(i)){
            ans++;
            maxx=max(maxx,sz[i]);
        }
    }
    cout<<ans<<' '<<maxx<<endl;
    return 0;
}