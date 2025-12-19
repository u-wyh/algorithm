#include<iostream>
#include<map>
#include<string>
#include<cstring>
#include<cstdio>
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
