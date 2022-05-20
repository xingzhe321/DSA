#include <iostream>
#include <queue>
using namespace std;
//采用顺序存储结构————一维数组结构
//结点类型定义
typedef struct {
	int weight;//权重
	int parent, lch, rch;//双亲、左右孩子
} HTNode, *HuffmanTree;

//哈夫曼树中共有2n-1个结点，不使用0下标，数组大小2n
// Select函数声明
void Select(const HuffmanTree &HT, const int &bound, int &s1, int &s2);
//哈夫曼树构造算法的实现
void CreatHuffmanTree(HuffmanTree &HT, const int &n) {
	//step1.初始化数组，将所有node中双亲、左右孩子置为0，输入前n个结点权重
	if (n <= 1) return;
	int m = 2 * n - 1;//数组中元素个数
	HT = new HTNode[m + 1];//0号位不用，HT[m]表示根结点
	for (int i = 1; i <= m; i++) {
		HT[i].parent = HT[i].lch = HT[i].rch = 0;
	}
	int w = 0;
	cout << "请输入叶子结点权重" << endl;
	for (int i = 1; i <= n; i++) {
		cin >> w;
		HT[i].weight = w;
	}
	//step2.建立哈夫曼树
	for (int i = n + 1; i <= m; i++) {
		int s1 = 0, s2 = 0;
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lch = s1;
		HT[i].rch = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	cout << "哈夫曼树创建完成" << endl;
}
//Select函数定义
void Select(const HuffmanTree &HT, const int &bound, int &s1, int &s2) {
	int min1 = INT_MAX, min2 = INT_MAX;
	for (int i = 1; i <= bound; i++) {
		if (HT[i].parent == 0 && min1 > HT[i].weight) {
			min1 = HT[i].weight;
			s1 = i;
		}
	}
	for (int i = 1; i <= bound; i++) {
		if (i != s1 && HT[i].parent == 0 && min2 > HT[i].weight) {
			min2 = HT[i].weight;
			s2 = i;
		}
	}
}
//遍历哈夫曼树 注意：哈夫曼树是数组结构 不能用链表遍历
void ReadHuffman(const HuffmanTree &HT, const int &n) {
	if (n <= 0) return;
	for (int i = 1; i <= n; i++)
	{
		cout << HT[i].weight << " ";
	}
	cout << endl;
}

// n = 8, w = {5, 29, 7, 8, 14, 23, 3, 11}
void test() {
	HTNode* HT;
	int n = 8;
	CreatHuffmanTree(HT, n);
	ReadHuffman (HT, 2 * n - 1);
	delete []HT;//手动释放空间
}

int main() {
	test();
	cin.get();
	return 0;
}