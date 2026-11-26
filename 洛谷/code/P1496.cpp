// https://www.luogu.com.cn/problem/P1496
// 题意：给 n 段燃烧区间 [a,b)，重叠部分只算一次，输出所有被覆盖位置的总长度。
// 数据范围：1 ≤ n ≤ 20000，-2^31 ≤ a<b < 2^31，答案小于 2^31。

#include<bits/stdc++.h>
using namespace std;

int n;
int a[20005],b[20005],dtop,ctop,d[40005],f[40005];
long long ans,c[40005];

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
        d[++dtop]=a[i];
        d[++dtop]=b[i];
    }
    sort(d+1,d+dtop+1);
    for(int i=1;i<=dtop;i++){
        if(d[i]!=d[i-1]||i==1)
            c[++ctop]=d[i];
    }
    for(int i=1;i<=n;i++){
        int x=lower_bound(c+1,c+ctop+1,a[i])-c;
        int y=lower_bound(c+1,c+ctop+1,b[i])-c;
        for(int j=x;j<y;j++){
            f[j]=1;
        }
    }
    for(int i=1;i<ctop;i++){
        if(f[i])
            ans+=c[i+1]-c[i];
    }
    cout<<ans;
    return 0;
}
