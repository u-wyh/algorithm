//这里有一点需要特别注意  就是高度一样的要一起处理
//比如数据 1 4 3 3 2 1  答案应该是1
//排完序后 应该是1 2 3 3 如果第三个位置上的3是原来第一个位置上的3  那么它和1 2都不联通
//那么就会导致答案加一  从而出错
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n,m;
int arr[MAXN][MAXN];
bool ok[MAXN][MAXN];
int fa[MAXN*MAXN];
struct node{
    int x,y,val;
}nums[MAXN*MAXN];
int walk[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int ans=0;
int val[MAXN*MAXN];

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

bool cmp(node a,node b){
    return a.val<b.val;
}

int id(int x,int y){
    return (x-1)*m+y;
}

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
    val[fy]|=val[fx];
}

int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            arr[i][j]=read();
            if(arr[i][j]>0){
                ok[i][j]=true;
            }
            arr[i][j]=abs(arr[i][j]);
            int u=id(i,j);
            nums[u]={i,j,arr[i][j]};
            fa[u]=u;
        }
    }
    for(int i=0;i<=m;i++){
        arr[0][i]=arr[n+1][i]=INT_MAX;
    }
    for(int i=0;i<=n;i++){
        arr[i][0]=arr[i][m+1]=INT_MAX;
    }
    sort(nums+1,nums+id(n,m)+1,cmp);
    for(int i=1;i<=n*m;i++){
        for(int j=0;j<4;j++){
            int tx=nums[i].x+walk[j][0];
            int ty=nums[i].y+walk[j][1];
            if(arr[tx][ty]<=nums[i].val){
                un(id(tx,ty),id(nums[i].x,nums[i].y));
            }
        }
        if(nums[i].val!=nums[i+1].val){
            for(int j=i;j;j--){
                if(nums[j].val!=nums[i].val){
                    break;
                }
                if(ok[nums[j].x][nums[j].y]){
                    int f=find(id(nums[j].x,nums[j].y));
                    if(!val[f]){
                        val[f]=1;
                        ans++;
                    }
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}