// https://www.luogu.com.cn/problem/P2786
// 题意：输入词汇数 N、模数 P，随后 N 个高级词汇 A_i（含数字、大小写字母）及其含金量 B_i
// 以及末尾含 M 个单词和分隔符（仅含 , . ! ?）的英文作文。
// 以完整单词为最小匹配单位且大小写敏感，高级词汇每在作文中出现一次，总含金量就增加 B_i。
// 计算整篇作文的总含金量。
// 输出一个整数，为总含金量对 P 取模的结果。
// 数据范围：对于 100% 的数据，1 <= N <= 10^5，1 <= M <= 3*10^4，1 <= P <= 10^9
// 0 < B_i <= 10^5（测试点 6~7 标明 Lmax <= 50）。
#include<bits/stdc++.h>
using namespace std;

int n,mod;
map<string ,int>val;

int main()
{
    cin>>n>>mod;
    for(int i=1;i<=n;i++){
        string str;
        int v;
        cin>>str>>v;
        val[str]=v;
    }
    getchar();
    int ans=0;
    char c=getchar();
    string s="";
    while(c!=EOF){
        if(c!=' '&&c!=','&&c!='.'&&c!='!'&&c!='?'&&c!='\n'){
            s+=c;
        }
        else{
            ans+=val[s];
            ans%=mod;
            s="";
        }
        //ans%=mod;
        //cout<<ans<<endl;
        c=getchar();
    }
    ans%=mod;
    cout<<ans<<endl;
    return 0;
}
