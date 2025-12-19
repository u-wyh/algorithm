#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int mat[105][105];
int st[105],en[105];

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

inline int inv(int x) {//保证m为素数，求费马小定理逆元
	int res(1), q(m - 2);
	while (q) {
		if (q & 1) res = res * x % m;
		x = x * x % m;
		q >>= 1;
	}
	return res;
}

void swap(int a, int b) {
    int tmp[105];
    //cout<<"swap"<<endl;
    for (int j = 0; j <= n+1; j++) {
        tmp[j] = mat[a][j];
        mat[a][j] = mat[b][j];
        mat[b][j] = tmp[j];
    }
}

// 高斯消元解决同余方程组模版，保证初始系数没有负数
int gauss(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            // 已经成为主元的行不参与
            if (j < i && mat[j][j] != 0) {
                continue;
            }
            // 找到系数不等于0的行做主元即可
            if (mat[j][i] != 0) {
                swap(i,j);
                break;
            }
        }
        if (mat[i][i] != 0) {
            for (int j = 1; j <= n; j++) {
                if (i != j && mat[j][i] != 0) {
                    int gcd_val = gcd(mat[j][i], mat[i][i]);
                    int a = mat[i][i] / gcd_val;
                    int b = mat[j][i] / gcd_val;
                    if (j < i && mat[j][j] != 0) {
                        // 如果j行有主元，那么从j列到i-1列的所有系数 * a
                        // 正确更新主元和自由元之间的关系
                        for (int k = j; k < i; k++) {
                            mat[j][k] = (mat[j][k] * a) % m;
                        }
                    }
                    // 正常消元
                    for (int k = i; k <= n + 1; k++) {
                        mat[j][k] = ((mat[j][k] * a - mat[i][k] * b) % m + m) % m;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if(mat[i][i]==0&&mat[i][n+1]!=0)
            return 2;
        // 在模意义下应该求逆元，(a / b) % MOD = (a * b的逆元) % MOD
        mat[i][n + 1] = (mat[i][n + 1] * inv(mat[i][i])) % m;
        mat[i][i] = 1;
    }
    return 1;
}

signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int u;
            cin>>u;
            mat[u][i]=1;
        }
        mat[i][i]=1;
    }
    for(int i=1;i<=n;i++){
        cin>>st[i];
    }
    for(int i=1;i<=n;i++){
        cin>>en[i];
        mat[i][n+1]=((en[i]-st[i])%m+m)%m;
    }
//    for(int i=1;i<=n;i++){
//        cout<<i<<"  ";
//        for(int j=1;j<=n+1;j++){
//            cout<<mat[i][j]<<' ';
//        }
//        cout<<endl;
//    }
//    cout<<endl;
    int k=gauss(n);
    if(k==2){
        cout<<"niuza"<<endl;
    }else{
        for(int i=1;i<=n;i++){
            mat[i][n+1]=((mat[i][n+1]%m)+m)%m;
            cout<<mat[i][n+1]<<' ';
        }
    }
    return 0;
}
