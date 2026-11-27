// https://codeforces.com/problemset/problem/135/B
// 题意：给平面上 8 个互异整点，分成两组各 4 个。
// 第一组组成正方形，第二组组成矩形，面积都须大于 0。
// 输出：可行时输出 YES，再分别输出两组点的编号。
// 无法划分时输出 NO。
// 数据范围：共 8 个点，坐标在 [-10^4, 10^4] 内。
// 算法标签：枚举、计算几何
#include<bits/stdc++.h>
using namespace std;

struct Point{
    long long x,y;
};
Point nums[10];

Point operator-(Point a,Point b){
    return {a.x-b.x,a.y-b.y};
}

// 叉积
long long operator*(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

// 点积
long long dot(Point a,Point b){
    return a.x*b.x+a.y*b.y;
}

int cntone(int x){
    int ans=0;
    while(x){
        if(x&1){
            ans++;
        }
        x>>=1;
    }
    return ans;
}

int a[5];
int b[5];
int alen,blen;

// 判断四个点能否组成矩形或正方形
bool judge(int p[],bool square){
    // 枚举与 p[1] 构成对角线的顶点
    for(int i=2;i<=4;i++){
        int u=p[1],v=p[i];
        int x=0,y=0;

        // 剩余两个点构成另一条对角线
        for(int j=2;j<=4;j++){
            if(j==i){
                continue;
            }
            if(x==0){
                x=p[j];
            }
            else{
                y=p[j];
            }
        }

        Point d1=nums[u]-nums[v];
        Point d2=nums[x]-nums[y];

        // 两条对角线中点必须相同
        if(nums[u].x+nums[v].x!=nums[x].x+nums[y].x){
            continue;
        }
        if(nums[u].y+nums[v].y!=nums[x].y+nums[y].y){
            continue;
        }

        // 两条对角线长度必须相等
        if(dot(d1,d1)!=dot(d2,d2)){
            continue;
        }

        // 面积必须非零
        if(d1*d2==0){
            continue;
        }

        // 正方形还要求两条对角线垂直
        if(square && dot(d1,d2)!=0){
            continue;
        }

        return true;
    }
    return false;
}

bool check1(){
    return judge(a,true);
}

bool check2(){
    return judge(b,false);
}

bool check(){
    return check1()&&check2();
}

int main()
{
    for(int i=1;i<=8;i++){
        cin>>nums[i].x>>nums[i].y;
    }

    for(int i=0;i<(1<<8);i++){
        if(cntone(i)==4){
            alen=blen=0;

            for(int k=0;k<8;k++){
                if((i>>k)&1){
                    a[++alen]=k+1;
                }
                else{
                    b[++blen]=k+1;
                }
            }

            if(check()){
                cout<<"YES"<<endl;

                for(int j=1;j<=4;j++){
                    cout<<a[j]<<' ';
                }
                cout<<endl;

                for(int j=1;j<=4;j++){
                    cout<<b[j]<<' ';
                }
                cout<<endl;
                return 0;
            }
        }
    }

    cout<<"NO"<<endl;
    return 0;
}
