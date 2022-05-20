#include <iostream>
#include <queue>
#include <stack>
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

//哈夫曼树测试函数 案例：n = 8, w = {5, 29, 7, 8, 14, 23, 3, 11}
void test() {
	HTNode* HT;
	int n = 8;
	CreatHuffmanTree(HT, n);
	ReadHuffman (HT, 2 * n - 1);
	delete []HT;//手动释放空间
}

//哈夫曼编码
//哈夫曼编码定义
typedef char **HuffmanCode;

//哈夫曼编码算法实现
void CreatHuffmanCode(const HuffmanTree &HT, HuffmanCode &HC, const int &n){//从叶子到跟逆求每个字符的哈夫曼编码，存储在编码表HC中
	HC = new char *[n + 1];//0位不用，从1号位开始
	char *cd = new char[n];//使用0位（但不一定用到，从后往前存放），临时存放每个字符编码的动态数组空间
	cd[n - 1] = '\0';//最后一位放置编码结束符
	for (int i = 1; i <= n; i++) {
		int start = n - 1;//start开始指向最后
		int c = i, f = HT[i].parent;//f指向结点c的双亲结点
		while (f != 0) {
			start--;//每次回溯start向前移动一位
			if (HT[f].lch == c) cd[start] = '0';
			else cd[start] = '1';
			c = f;
			f = HT[f].parent;//继续向上回溯			
		}//while结束，求出第i个字符的编码
		HC[i] = new char[n - start];//为第i个字符编码分配空间
		//strcpy函数把含有'\0'结束符的字符串复制到另一个地址空间
		strcpy(HC[i], &cd[start]);//形参都是字符串的开始地址
	}//for
	delete []cd;//释放临时空间
}
//用栈实现 后进先出
void StackHuffmanCode(const HuffmanTree &HT, HuffmanCode &HC, const int &n){
	HC = new char *[n + 1];
	//用栈保存临时数组
	stack<char> cd;
	cd.push('\0');
	for (int i = 1; i <= n; i++) {
		int c = i, f = HT[i].parent;
		while (f != 0)
		{
			if (HT[f].lch == c) cd.push('0');
			else cd.push('1');
			c = f;
			f = HT[f].parent;
		}
		HC[i] = new char[cd.size()];
		char ch;
		int ind = 0;
		while (ch = cd.top())
		{
			HC[i][ind++] = ch;
		}
	}
}

int main() {
	test();
	cin.get();
	return 0;
}