// 用途：单调栈求每个元素两侧第一个严格更小的位置。
// 时间：O(n)。
// 空间：O(n)。
// 注意：0 下标输入，输出 -1 表示不存在；n≤10000，相等元素要跳过。
#include<bits/stdc++.h>
using namespace std;

int st[10000];
int n,r=0;
int nums[10000],L[10000],R[10000];

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>nums[i];
    int cur;
    for(int i=0;i<n;i++){
        while(r>0&&nums[st[r-1]]>=nums[i]){
            //栈里面的元素严格大压小
            cur=st[--r];
            L[cur]=r>0?st[r-1]:-1;//如果左边没有元素 那么就是-1
            R[cur]=i;//右边的自然就是这个让他出栈的位置了
        }
        st[r++]=i;
    }

    while (r > 0) {
        //将栈中剩余的元素弹出
        cur = st[--r];
        L[cur] = r > 0 ? st[r - 1] : -1;//左边是栈中自己前面的一个元素
        R[cur] = -1;//右边一定是没有比自己小的了
    }

    //此时R数组需要修正  从后往前遍历  因为修正的是R  即右边的小于自己的
    //因为遍历到i的时候  那么i之后的所有的都是正确的
    for(int i=n-2;i>=0;i--){
        if(R[i]!=-1&&nums[i]==nums[R[i]]){
            //继续处理相等的情况
            //那么他的r数组就是他的r的r
            R[i]=R[R[i]];
        }
    }

    for(int i=0;i<n;i++)
        cout<<L[i]<<' '<<R[i]<<endl;
    return 0;
}
