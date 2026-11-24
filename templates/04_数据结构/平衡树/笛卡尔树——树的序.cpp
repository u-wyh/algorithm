// 树的序
// 给定一个长度为n的数组arr，表示依次插入数字，会形成一棵搜索二叉树
// 也许同样的一个序列，依次插入数字后，也能形成同样形态的搜索二叉树
// 请返回字典序尽量小的结果
// 1 <= n <= 10^5
// 测试链接 : https://www.luogu.com.cn/problem/P1377
// 提交以下的code，提交时请把类名改成"Main"，可以通过所有测试用例
// 答案一定是建立成树之后  前序遍历得到的结果
// 但问题是怎么建树  如果直接暴力建树的话 遇到非常不平衡的树会退化为O(n^2)
// 所以我们使用笛卡尔树
// 这道题给出的数据相当于按照值进行二叉树排序  他们的下标（也就是时间戳）按照小根堆排序（这个是总结出来的）
// 这种排序方式在极端情况下可能会导致时间复杂度超时
// 那么我们将数据建立成反向索引  那么此时值应该对应的是原来的下标   现在的下标对应原来的值
// 值按照堆排序  下标按照二叉树排序  很好的实现了建树
// 通过保证插入时的中序有序  以及   时间戳的相对关系   这样才能保证是唯一的
// 因为在中序有序的情况下 如果和原来的结构不一样 那么就意味着时间戳关系不一样 
// 这个转化很巧妙
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;

int n;
int arr[MAXN];
int ls[MAXN];
int rs[MAXN];
int sta[MAXN];

void build() {
    for (int i = 1, top = 0, pos = 0; i <= n; i++) {
        pos = top;
        while (pos > 0 && arr[sta[pos]] > arr[i]) {
            pos--;
        }
        if (pos > 0) {
            rs[sta[pos]] = i;
        }
        if (pos < top) {
            ls[i] = sta[pos + 1];
        }
        sta[++pos] = i;
        top = pos;
    }
}

void pre() {
    int size = 1, i = 0, cur;
    while (size > 0) {
        cur = sta[size--];
        arr[++i] = cur;
        if (rs[cur] != 0) {
            sta[++size] = rs[cur];
        }
        if (ls[cur] != 0) {
            sta[++size] = ls[cur];
        }
    }
}

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        arr[k]=i;
    }
    build();
    pre();
    for(int i=1;i<=n;i++){
        cout<<arr[i]<<' ';
    }
    return 0;
}