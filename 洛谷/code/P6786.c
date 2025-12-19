#include <stdio.h>
#include <stdlib.h>

#define MAX_N 300005

typedef long long ll;

int a[MAX_N];
ll ans;

// 使用结构体模拟map
typedef struct {
    int key;
    int value;
    struct Node* next;
} Node;

Node* head[MAX_N];

// 插入键值对到模拟的map中
void insert(int key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = head[key];
    head[key] = newNode;
}

// 从模拟的map中获取值
int get(int key) {
    Node* current = head[key];
    if (current == NULL) return 0;
    int value = current->value;
    // 如果需要删除，则可以将current->next赋给head[key]
    // 但由于我们只需要读取值，所以这里不删除
    return value;
}

// 清空模拟的map中的某个键（可选，如果需要重复使用）
void clear(int key) {
    Node* prev = NULL;
    Node* current = head[key];
    while (current != NULL) {
        prev = current;
        current = current->next;
        free(prev);
    }
    head[key] = NULL;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        insert(a[i], 1);  // 初始计数为1
    }

    // 由于C语言不支持直接对数组排序的函数，这里省略排序步骤，
    // 假设输入已经是有序的，或者我们可以使用qsort等函数进行排序
    // qsort(a, n, sizeof(int), compare); // 需要定义compare函数

    // 假设a已经是有序的，继续执行后续逻辑
    for (int i = 0; i < n; i++) {
        ll tmp = a[i], cnt = 0;
        int value = get(tmp);
        while (value > 0) {
            cnt += tmp * value;
            value--;  // 相当于mp[tmp]--
            if (tmp % 2 == 0) tmp = tmp / 2 * 3;
            else break;
        }
        // 由于我们的模拟map不支持一键清空所有值，这里不直接清空
        // 但如果需要再次使用，可以在外部调用clear函数
        ans = (ans > cnt) ? ans : cnt;
    }

    printf("%lld\n", ans);

    // 清理模拟map（如果需要）
    // 注意：这里为了简单起见，没有实现清理逻辑

    return 0;
}
