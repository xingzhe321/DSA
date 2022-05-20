#include <iostream>
using namespace std;
//本文件全部使用c++写法 struct不需要类型别名（之前章节中主要是指针）的不再使用typedef


//图的存储结构
//1.邻接矩阵表示法
#define MAXINT 32767//极大值 也可以用定义好的宏INT32_MAX
#define MAXVERTEXNUM 100//最大顶点数
typedef char VertexType;//设定顶点为char型
typedef int ArcType;//设定边的权值为int型

struct AMGraph//adjacent matrix graph
{
    VertexType vexs[MAXVERTEXNUM];
    ArcType arcs[MAXVERTEXNUM][MAXVERTEXNUM];
    int vexnum, arcnum;//图的当前点数和边数
};

//2.邻接表表示法（链式）
//边结点
#define OtherInfo int
struct ArcNode{
    int adjvex;//该边所指向的顶点的位置
    struct ArcNode *nextarc;//指向下一条边的指针
    OtherInfo info;//和边相关的信息,可以是权值
};
//顶点
#define MVNum 100
typedef struct VNode{
    VertexType data;
    ArcNode *firstarc;
} AdjList[MVNum];
//邻接表
struct ALGraph{
    AdjList vertices;
    int vexnum, arcnum;//图的当前顶点数和弧数
};

//图的存储结构结束

//图相关算法
//算法1.采用邻接矩阵表示法创建无向网
/**
 * @brief 算法思想
 * 输入总顶点数和总边数
 * 依次输入点的信息存入顶点表
 * 初始化邻接矩阵，每个权值初始化为极大值//如果是构建无向图，则权值初始化为0
 * 构造邻接矩阵//如果是构建无向图，则权值赋1
 */
//查找顶点坐标函数
int LocateVex(const AMGraph &G, const VertexType &v);
//算法本体，创建无向网
bool CreateUDN(AMGraph &G){//undirected net
    //输入总顶点数和总边数
    cout << "please input the vexnum and arcnum in order" << endl;
    cin >> G.vexnum >> G.arcnum;
    //依次输入点的信息存入顶点表
    cout << "please input the information of vertices in order" << endl;
    for (int i = 0; i < G.vexnum; i++){
        cin >> G.vexs[i];
    }
    //初始化邻接矩阵，每个权值初始化为极大值
    for (int i = 0; i < G.vexnum; i++){
        for (int j = 0; j < G.vexnum; j++){
            G.arcs[i][j] = MAXINT;
        }   
    }
    //构造邻接矩阵
    cout << "input the related vertices and their weight in order" << endl;
    cout << "as this type: >> v1 >> v2 >> w" << endl;
    VertexType v1, v2;
    ArcType w;
    for (int k = 0; k < G.arcnum; k++){
        cin >> v1 >> v2 >> w;
        //v1和v2是两顶点的信息，查找v1和v2在G中位置
        int i = LocateVex(G, v1);
        int j = LocateVex(G, v2);
        G.arcs[j][i] = G.arcs[i][j] = w;
    }//for
    return true;
}
//LocateVex函数实现
int LocateVex(const AMGraph &G, const VertexType &v){
    int i = 0;
    while (i < G.vexnum && G.vexs[i] != v){
        i++;
    }
    if (G.vexs[i] == v) return i;
    else return -1;
}
//[结束]算法1.采用邻接矩阵表示法创建无向网

//算法2.采用邻接表表示法创建无向网
/**
 * @brief 算法思想 
 * 输入总顶点数和总边数
 * 建立顶点表：
 *      依次输入点的信息存入顶点表中
 *      使每个表头结点的指针域初始化为NULL
 * 创建邻接表
 *      依次输入每条边依附的两个顶点
 *      确定两个顶点的序号i和j，建立边结点
 *      将此边结点分别插入到vi和vj对应的两个边链表的头部
 */
//LocateVex函数，邻接矩阵的重载版本
int LocateVex(const ALGraph &G, const VertexType &v);
//算法本体，创建无向网
bool CreateUDG(ALGraph &G){//采用邻接表表示法，创建无向图G
    //输入总顶点数，总边数
    cout << "please input the number of the vextices and arcs of the graph in order" << endl;
    cin >> G.vexnum >> G.arcnum;
    //建立顶点表
    cout << "please input the information of the vertices in ordre" << endl;
    for (auto &i : G.vertices){//遍历图的邻接表
        cin >> i.data;//输入顶点信息
        i.firstarc = nullptr;//初始化表头结点的指针域
    }
    //创建邻接表
    cout << "please input the vertices linked by each arc in order" << endl;
    VertexType v1, v2;
    for (int k = 0; k < G.arcnum; k++){
        cin >> v1 >> v2;
        int i = LocateVex(G, v1); 
        int j = LocateVex(G, v2);
        ArcNode *p1 = new ArcNode;
        p1->adjvex = j;//p1是v1指向v2的边(这是是无向边，为了方便理解)
        p1->nextarc = G.vertices[i].firstarc;//将p1插入v1对应边链表头部
        G.vertices[i].firstarc = p1;
        //对v2对应边链表做同样操作
        ArcNode *p2 = new ArcNode;
        p2->adjvex = i;//p2是v2指向v1的边
        p2->nextarc = G.vertices[j].firstarc;
        G.vertices[j].firstarc = p2;
    }//for
    return true;
}

int LocateVex(const ALGraph &G, const VertexType &v){
    int i = 0;
    for (; i < G.vexnum; i++){
        if (G.vertices[i].data == v) return i;
    }
    return -1;
}