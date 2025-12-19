//P9725
#include<bits/stdc++.h>
using namespace std;

int u[100005]={0},v[100005]={0},du[100005]={0};

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        memset(du,0,sizeof du);//所有入度清零
        for(int i=1;i<n;i++){
            cin>>u[i]>>v[i];
            du[u[i]]++;
            du[v[i]]++;//相应入度加一
        }
        if(n<=3){
            //如果三个点都没有 一定不行
            puts("-1");
            continue;
        }
        map<int,int> q;//表示以i为中心直接连接的点中  有多少是叶子结点
        int leaf=0;
        for(int i=1;i<n;i++){
            if(du[u[i]]==1)q[v[i]]++,leaf++;
            if(du[v[i]]==1)q[u[i]]++,leaf++;//如果一个节点是叶子结点  那么与他相连的点加一
        }
        if(q.size()==1){
            //说明是菊花图   一定不行 即只有一个节点有叶子结点
            puts("-1");
            continue;
        }
        //到了这一步还没有退出  说明一定有答案
        int ans=0;
        for(auto it=q.begin();it!=q.end();it++){
            ans=max(ans,it->second);//表示一个节点最多连接多少个叶子结点
        }
        cout<<((ans>leaf/2)?ans:(leaf+1)/2)<<endl;
        //如果说有一个节点的叶子结点个数超出叶子结点总数一半  那么没办法 只能是这个数了
        //否则就是叶子结点的总数除二  向上取整
    }
    return 0;
}

