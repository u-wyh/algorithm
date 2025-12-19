// 根据匹配定义求匹配子串的数量
// 给定长为n的字符串s，以及长度为m的字符串p，还有一个正数k
// s'与s匹配的定义为，s'与s长度相同，且最多有k个位置字符不同
// 要求查找字符串s中有多少子串与字符串p匹配
// 测试链接 : https://www.luogu.com.cn/problem/P3763
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
//这道题是通过二分来检测是否有不超过k个的不同
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e5+5;
const int BASE = 499;

int n,m,k;
int p[MAXN];
int hs[MAXN];
int ht[MAXN];
char s[MAXN];
char t[MAXN];

void prepare(){
    for(int i=1;i<=n;i++){
        hs[i]=hs[i-1]*BASE+s[i]-'A'+1;
    }
    for(int i=1;i<=n;i++){
        ht[i]=ht[i-1]*BASE+t[i]-'A'+1;
    }
}

int gethash(int l,int r,int op){
    if(op==1){
        return hs[r]-hs[l-1]*p[r-l+1];
    }
    else{
        return ht[r]-ht[l-1]*p[r-l+1];
    }
}

// s[l...r] 和 t[1...m] 取等长的两段
// 返回这两段上字符不一样的位置是不是<=k个
bool check(int l,int r,int k){
    int le=1;//t数组的目前匹配位置
    int diff=0;
    while(l<=r&&diff<=k){
        int lt=1,rt=r-l+1,len=0;
        while(lt<=rt){
            //二分找到第一个不一样的位置
            int mid=(lt+rt)>>1;
            if(gethash(l,l+mid-1,1)==gethash(le,le+mid-1,2)){
                len=mid;
                lt=mid+1;
            }
            else{
                rt=mid-1;
            }
        }
        if(l+len<=r){
            diff++;
        }
        l+=len+1;
        le+=len+1;
    }
    return diff<=k;
}

// s中有多少子串修改最多k个位置的字符就可以变成t
// s长度为n，t长度为m，时间复杂度O(n * k * logm)
int compute(int k){
    n=strlen(s+1);
    m=strlen(t+1);
    if(n<m){
        return 0;
    }
    prepare();
    int ans=0;
    for(int i=1;i<=n-m+1;i++){
        if(check(i,i+m-1,k)){
            ans++;
        }
    }
    return ans;
}

signed main()
{
    p[0]=1;
    for(int i=1;i<MAXN;i++){
        p[i]=(p[i-1]*BASE);
    }
    int T;
    scanf("%lld",&T);
    k=3;//最多可以不同的位置个数   这道题明确设置为3
    while(T--){
        scanf("%s %s",s+1,t+1);
        cout<<compute(k)<<endl;
    }
    return 0;
}