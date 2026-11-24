//最最基本的模版题
// 高斯消元解决加法方程组模版(区分是否有唯一解)
// 一共有n个变量，给定n个加法方程，构成一个加法方程组
// 如果方程组存在矛盾或者无法确定唯一解，打印"No Solution"
// 如果方程组存在唯一解，打印每个变量的值，保留小数点后两位
// 1 <= n <= 100
// 测试链接 : https://www.luogu.com.cn/problem/P3389
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 101;
// 0.0000001 == 1e-7
// 因为double类型有精度问题，所以认为
// 如果一个数字绝对值  <  sml，则认为该数字是0
// 如果一个数字绝对值  >= sml，则认为该数字不是0
const double sml = 1e-7;

int n;
double mat[MAXN][MAXN + 1];

void swap(int a, int b) {
    //swap的作用是用于交换两个数组的某一行
    //使用系统的内置函数可以  但是时间稍微差一点
    //在程序中 建议全部手写
    //但是手写的时候一定要注意中间数组tmp的类型是int 还是 double
    //并且手写的时候一定要注意列的范围  不能缺少
    double tmp[MAXN + 1];
    for (int j = 0; j <= n+1; j++) {
        tmp[j] = mat[a][j];
        mat[a][j] = mat[b][j];
        mat[b][j] = tmp[j];
    }
}

//这个函数的作用是求出mat矩阵的解  n是x1 x2    xn
//如果无解返回0  有解返回1
int gauss(int n) {
    for (int i = 1; i <= n; i++) {
        //每次求解一个xi  也不是最终的值
        //只是将其他式子中的xi的系数消除为0
        //只保留自己的系数  最终将系数化为1
        int max = i;
        for (int j = 1; j <= n; j++) {
            if (j < i && abs(mat[j][j]) >= sml) {
                continue;
            }
            if (abs(mat[j][i]) > abs(mat[max][i])) {
                max = j;
            }
        }
        swap(i, max);//交换改行最大值
        if (abs(mat[i][i]) < sml) {
            //表示xi为0  那么不可能有解了
            return 0;
        }
        if (abs(mat[i][i]) >= sml) {
            //消去其他式子中的xi
            double tmp = mat[i][i];
            for (int j = i; j <= n + 1; j++) {
                mat[i][j] /= tmp;
            }
            for (int j = 1; j <= n; j++) {
                if (i != j) {
                    double rate = mat[j][i] / mat[i][i];
                    for (int k = i; k <= n + 1; k++) {
                        mat[j][k] -= mat[i][k] * rate;
                    }
                }
            }
        }
    }
    return 1;
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n+1;j++){
            cin>>mat[i][j];
        }
    }
    if(gauss(n)==1){
        for(int i=1;i<=n;i++){
            printf("%.2lf\n",mat[i][n+1]);
        }
    }
    else{
        cout<<"No Solution"<<endl;
    }
    return 0;
}