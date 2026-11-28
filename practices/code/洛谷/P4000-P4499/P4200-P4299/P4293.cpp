// https://www.luogu.com.cn/problem/P4293
// 题意：有 n 个粒子各有质量 m_i 和结合系数 c_i，
// 粒子 a 的 N 极连粒子 b 的 S 极产生能量
// m_a*m_b*(c_a - c_b)；
// 第一问求选哪两个粒子直接相连能量最大；
// 第二问求选 k（2 <= k <= n）个不同粒子连成一圈
// （p_i 的 N 极连 p_{i+1} 的 S 极
// p_k 连 p_1）能得到的最大总能量及方案（误差 <= 1e-5）。
// 数据范围：n <= 50000，0 < m_i, c_i < 1e5。
// 难度评分：2400（洛谷分级换算）
// 算法标签：凸包、旋转卡壳
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5e4+5;

int n;
struct Point{
    double x,y;
    int id;
};
Point p[MAXN];

int top;
Point nums[MAXN];
Point sta[MAXN<<1];
Point q[MAXN];
double c[MAXN];
int ansa,ansb;

bool cmp(Point a,Point b){
    if(a.x!=b.x){
        return a.x<b.x;
    }
    return a.y<b.y;
}


// 使用基础函数中的三点叉积，正值表示从 AB 到 AC 逆时针转向。
double cross(Point a, Point b, Point c){
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

void Andrew(){
    top=0;
    sort(nums+1,nums+n+1,cmp);
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(cnt==0 || nums[i].x!=nums[cnt].x || nums[i].y!=nums[cnt].y){
            nums[++cnt]=nums[i];
        }
    }
    n=cnt;
    n = cnt;
    if (n <= 2){
        for (int i = 1; i <= n; i++){
            sta[++top] = nums[i];
        }
        if (top > 0){
            sta[top + 1] = sta[1];
        }
        return;
    }

    // 下凸链：只保留左转，删除凹点和共线中间点。
    for (int i = 1; i <= n; i++){
        while (top > 1 && cross(sta[top - 1], sta[top], nums[i]) <= 0){
            top--;
        }
        sta[++top] = nums[i];
    }
    int t = top;

    // 上凸链：从右向左扫描，t 之前的下凸链保持不动。
    for (int i = n - 1; i >= 1; i--){
        while (top > t && cross(sta[top - 1], sta[top], nums[i]) <= 0){
            top--;
        }
        sta[++top] = nums[i];
    }
    top--;
    sta[top + 1] = sta[1];
}

bool cmpang(Point a,Point b){
    if(c[a.id]!=c[b.id]){
        return c[a.id]>c[b.id];
    }
    return a.id<b.id;
}

double cross(Point a,Point b){
    return a.x*b.y-a.y*b.x;
}

void rotating_calipers(){
    if(top<=1){
        return;
    }

    for(int i=1;i<=top;i++){
        q[i]=sta[i];
    }
    sort(q+1,q+top+1,cmpang);

    // 找到第一个方向对应的最优支撑点
    int j=1;
    for(int i=2;i<=top;i++){
        if(cross(q[1],sta[i])>cross(q[1],sta[j])){
            j=i;
        }
    }

    double best=0;

    for(int i=1;i<=top;i++){
        while(cross(q[i],sta[j%top+1])>cross(q[i],sta[j])){
            j=j%top+1;
        }

        double now=cross(q[i],sta[j]);
        if(now>best){
            best=now;
            ansa=q[i].id;
            ansb=sta[j].id;
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        double m;
        cin>>m>>c[i];
        nums[i]={m*c[i],m,i};
    }
    ansa=1,ansb=n;

    Andrew();
    rotating_calipers();

    cout<<ansa<<' '<<ansb<<endl;
    cout<<top<<endl;
    for(int i=1;i<=top;i++){
        cout<<sta[i].id<<' ';
    }
    return 0;
}