// 反尼姆博弈(反常游戏)
// 一共有n堆石头，两人轮流进行游戏
// 在每个玩家的回合中，玩家需要选择任何一个非空的石头堆，并从这堆石头中移除任意正数的石头数量
// 谁先拿走最后的石头就失败，返回最终谁会获胜
// 先手获胜，打印John
// 后手获胜，打印Brother
// 测试链接 : https://www.luogu.com.cn/problem/P4279
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过
//这道题主要是推理  如果所有堆都是1  那么根据奇偶性进行特判
//如果只有一堆多于1  其余都是1  那么此时的先手一定赢  因为他一定可以使局面变成全是1  并且控制1的奇偶性
//那么只要一开始不全是1  一定会撞上只有一堆多于1  其余都是1的状态
//那么也就是说  只有一堆多于1  其余都是1 这种情况是必胜态
//必胜态的异或结果一定不是0  因为大于1的数字的二进制除了最低位之外一定会有一个1  这个1无法被消除
//并且我们知道一定可以将局面从 异或值=0 <--> 异或值!=0
//那么最开始异或不为0一定可以比后手先到达必胜态  （因为后手永远只能面临必败态）
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 51;

vector<int> stones(MAXN);

int t, n;

string compute() {
    int eor = 0, sum = 0;
    for (int i = 0; i < n; i++) {
        eor ^= stones[i];
        sum += stones[i] == 1 ? 1 : 0;
    }
    if (sum == n) {
        //特判：所有堆都是1个
        return (n & 1) == 1 ? "Brother" : "John";
    } else {
        return eor != 0 ? "John" : "Brother";
    }
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        for (int j = 0; j < n; j++) {
            cin >> stones[j];
        }
        cout << compute() << endl;
    }
    return 0;
}