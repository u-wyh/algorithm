// https://www.luogu.com.cn/problem/P4465
// 题意：维护一个初始为空的数字串，支持 T 次操作：在指定位置插入字符串、删除左闭右开区间、查询左闭右开区间内给定子串 z_i 的出现次数。
// 数据范围：插入总长度 <= 2*10^6，任意时刻串长 <= 10^6，插入次数 <= 1001，删除次数 <= 1000
// 询问子串 z_i 总长度 <= 10^4。
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+5;

bitset<MAXN>bs[10];

int main()
{
    int T;
    cin>>T;

    int n=0;
    while(T--){
        int op,x;
        cin>>op>>x;
        if(op==0){
            string s;
            cin>>s;
            int len=s.size();
            for(int i=0;i<10;i++){
                bitset<MAXN>suf=(bs[i]>>x)<<x;
                bs[i]^=suf;
                bs[i]^=(suf<<len);
            }
            for(int i=0;i<len;i++){
                bs[s[i]-'0'][x+i]=1;
            }
            n+=len;
        }
        else if(op==1){
            int y;
            cin>>y;
            int len=y-x;
            for(int i=0;i<10;i++){
                bitset<MAXN>bsx=(bs[i]>>x)<<x;
                bitset<MAXN>bsy=(bs[i]>>y)<<y;
                bs[i]^=bsx;
                bs[i]^=(bsy>>len);
            }
            n-=len;
        }
        else{
            int y;
            string s;
            cin>>y>>s;

            int len=s.size();
            if(y-x<len){
                cout<<0<<endl;
                continue;
            }
            bitset<MAXN>cur;
            cur.set();
            bitset<MAXN>now;
            now.set();

            cur<<=x;
            now<<=(y-len+1);
            cur^=now;

            for(int i=0;i<len;i++){
                if(i){
                    cur<<=1;
                }
                cur&=bs[s[i]-'0'];
            }
            cout<<cur.count()<<endl;
        }
    }
    return 0;
}