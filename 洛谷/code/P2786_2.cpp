// https://www.luogu.com.cn/problem/P2786
// 题意：输入词汇数 N、模数 P，随后 N 个高级词汇 A_i（含数字、大小写字母）及其含金量 B_i
// 以及末尾含 M 个单词和分隔符（仅含 , . ! ?）的英文作文。
// 以完整单词为最小匹配单位且大小写敏感，高级词汇每在作文中出现一次，总含金量就增加 B_i。
// 计算整篇作文的总含金量。
// 输出一个整数，为总含金量对 P 取模的结果。
// 数据范围：对于 100% 的数据，1 <= N <= 10^5，1 <= M <= 3*10^4，1 <= P <= 10^9
// 0 < B_i <= 10^5（测试点 6~7 标明 Lmax <= 50）。
#include<iostream>
#include<map>
#include<string>
#include<cstring>
#include<cstdio>
// 算法标签：字符串、模拟、map
using namespace std;
typedef long long ll;
ll n,p;
map<string,ll>a;
ll ans;
int main()
{
    scanf("%lld%lld",&n,&p);
    for(int i=1;i<=n;i++)
    {
        string word;
        ll value;
        cin>>word>>value;
        a[word]=value;
        //word即高级词汇，value即其含金量
    }
    string t="";
    char c;
    //t存储词汇
    //c是用于输入的临时变量
    while(scanf("%c",&c)!=EOF)
    {
        if(!(isdigit(c)||isalpha(c)))
        {
            //不是数字，也不是字母，那就是分隔符或者空格回车之类的
            ans=((ans%p)+(a[t]%p))%p;
            //那么就更新答案，把上一个词的含金量加上
            //如果上一个词不是高级词汇，那么在map里对应的含金量就是0
            //相当于没有变化
            //为了答案不溢出，随时取模
            t="";
            //还原，以便记录下一个词
        }
        else t+=c;
    }
    printf("%lld\n",ans);
    return 0;
}
