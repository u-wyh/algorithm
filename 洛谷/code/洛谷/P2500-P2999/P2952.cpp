// https://www.luogu.com.cn/problem/P2952
// 题意：输入操作指令条数 S，初始队列为空，
// 奶牛将按 1, 2, ... 依次入队且出队后不再返回。
// 指令共四种：A L/R 表示下一头牛从队列左侧或右侧加入；
// D L/R K 表示从队列左侧
// 或右侧离开 K 头牛（保证操作合法且最终队列非空）。
// 按顺序模拟全部 S 条指令。
// 按从左到右的顺序输出最终队列中的所有奶牛编号，每行一个。
// 数据范围：对于 100% 的数据，1 <= S <= 100000。
// 算法标签：双端队列、模拟
#include<bits/stdc++.h>
using namespace std;

int n,d=1;
deque<int >Deque;

int main()
{
    cin>>n;
    char a,b;
    int c;
    while(n--){
        cin>>a;
        if(a=='A'){
            cin>>b;
            if(b=='L')
                Deque.push_front(d);
            else if(b=='R')
                Deque.push_back(d);
            d++;
        }else{
            cin>>b>>c;
            if(b=='L'){
                while(c--){
                    Deque.pop_front();
                }
            }else{
                while(c--){
                    Deque.pop_back();
                }
            }
        }
    }
    for(int a:Deque)
        cout<<a<<endl;
    return  0;
}
