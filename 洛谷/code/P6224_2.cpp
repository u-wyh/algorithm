// https://www.luogu.com.cn/problem/P6224
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+5;
const int MAXP = 19;
const int INF = 2e9;

int n,m;

// 点的信息
int x[MAXN];
int y[MAXN];
int arr[MAXN];

int cntkdt;
// 每个组的根节点
int root[MAXP];
int ls[MAXN];
int rs[MAXN];
int xmin[MAXN];
int xmax[MAXN];
int ymin[MAXN];
int ymax[MAXN];

int ans;

int compare(int i,int j,int dimension){
    int v1=dimension==0?x[i]:y[i];
    int v2=dimension==0?x[j]:y[j];
    return v1==v2?0:v1<v2?-1:1;
}

struct cmp{
    int dimension;
    bool operator()(int a,int b)const{
        return compare(a,b,dimension)<0;
    }
};

void maintain(int i){
    xmin[i]=min(x[i],min(xmin[ls[i]],xmin[rs[i]]));
    xmax[i]=max(x[i],max(xmax[ls[i]],xmax[rs[i]]));
    ymin[i]=min(y[i],min(ymin[ls[i]],ymin[rs[i]]));
    ymax[i]=max(y[i],max(ymax[ls[i]],ymax[rs[i]]));
}

// 将编号范围为l到r的点按照dimension维度排序
int build(int l,int r,int dimension){
    if(l>r){
        return 0;
    }
    int mid=(l+r)>>1;
    // 在区间arr[l ... r]中，参数分别是l mid  r+1
    // 按照 Cmp{dimension} 这个比较规则，把第 mid-l+1 小的元素放到 arr[mid]
    // mid前面的小于它  mid后面的大于它
    nth_element(arr+l,arr+mid,arr+r+1,cmp{dimension});
    int rt=arr[mid];
    ls[rt]=build(l,mid-1,dimension^1);
    rs[rt]=build(mid+1,r,dimension^1);
    maintain(rt);
    return rt;
}

void add(int qx,int qy){
    cntkdt++;
    x[cntkdt]=qx;
    y[cntkdt]=qy;
    arr[cntkdt]=cntkdt;
    // 找到第一个根节点为空的组
    // 因为非空的组都是满的
    int p=0;
    while(root[p]!=0){
        root[p++]=0;
    }
    // 第一个非空的组，将会把前面所有组的值全部收集上来
    // 实际上，他们的编号都是固定的  一定都是最后的几个
    root[p]=build(cntkdt-(1<<p)+1,cntkdt,0);
}

int guess(int qx,int qy,int op,int i){
    if(i==0){
        if(op==1) return INF;
        else return -INF;
    }

    if(op==1){
        int dx=0,dy=0;

        if(qx<xmin[i]) dx=xmin[i]-qx;
        else if(qx>xmax[i]) dx=qx-xmax[i];

        if(qy<ymin[i]) dy=ymin[i]-qy;
        else if(qy>ymax[i]) dy=qy-ymax[i];

        return dx+dy;
    }
    else{
        return max(abs(qx-xmin[i]),abs(qx-xmax[i]))
             + max(abs(qy-ymin[i]),abs(qy-ymax[i]));
    }
}

void query(int qx,int qy,int op,int i){
    if(i==0){
        return ;
    }
    int d=abs(qx-x[i])+abs(qy-y[i]);
    if(op==1){
        ans=min(ans,d);
    }
    else{
        ans=max(ans,d);
    }
    int gl=guess(qx,qy,op,ls[i]);
    int gr=guess(qx,qy,op,rs[i]);
    if(op==1){
        if(gl<gr){
            if(gl<ans){
                query(qx,qy,op,ls[i]);
            }
            if(gr<ans){
                query(qx,qy,op,rs[i]);
            }
        }
        else{
            if(gr<ans){
                query(qx,qy,op,rs[i]);
            }
            if(gl<ans){
                query(qx,qy,op,ls[i]);
            }
        }
    }
    else{
        if(gl>gr){
            if(gl>ans){
                query(qx,qy,op,ls[i]);
            }
            if(gr>ans){
                query(qx,qy,op,rs[i]);
            }
        }
        else{
            if(gr>ans){
                query(qx,qy,op,rs[i]);
            }
            if(gl>ans){
                query(qx,qy,op,ls[i]);
            }
        }
    }
}

int main()
{
    cin>>n;
    // 0号节点作为空儿子使用
    xmin[0]=ymin[0]=INF;
    xmax[0]=ymax[0]=-INF;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        add(x,y);
    }

    cin>>m;
    for(int i=1;i<=m;i++){
        int op,x,y;
        cin>>op>>x>>y;
        if(op==0){
            add(x,y);
        }
        else if(op==1){
            ans=INF;
            for(int i=0;i<MAXP;i++)
                query(x,y,1,root[i]);
            cout<<ans<<endl;
        }
        else{
            ans=-INF;
            for(int i=0;i<MAXP;i++)
                query(x,y,-1,root[i]);
            cout<<ans<<endl;
        }
    }
    return 0;
}