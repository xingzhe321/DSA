#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
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
//邻接表表示有向图 缺点：求结点的度困难 改进：十字链表
//邻接表表示无向图 缺点：每条边都要存储两遍 改进：邻接多重表
//图的存储结构结束

//图相关算法
//算法1.采用邻接矩阵表示法创建无向网
/**
 * @brief 算法思想
 * 输入总顶点数和总边数
 * 依次输入点的信息存入顶点表
 * 初始化邻接矩阵，每个权值初始化为极大值//如果是构建无向图(这里是无向网，网是带权的图），则权值初始化为0
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
//LocateVex函数实现
int LocateVex(const ALGraph &G, const VertexType &v){
    int i = 0;
    for (; i < G.vexnum; i++){
        if (G.vertices[i].data == v) return i;
    }
    return -1;
}
//[结束]算法2.采用邻接表表示法创建无向图

//图的遍历 DFS深度优先搜索 BFS广度优先搜索
//算法3.采用邻接矩阵表示图的深度优先搜索遍历 递归
//访问标志数组，初值为false
bool visited[MAXVERTEXNUM] = {false};//c++11默认初始化值也为0（false）
void DFS(AMGraph G, int v){
    //遍历过程依次输出访问顶点顺序
    cout << v;
    visited[v] = true;//访问到顶点时，将访问标志置为true
    for (int i = 0; i < G.vexnum; i++){
        if (G.arcs[v][i] != 0 && !visited[i]){
            DFS(G, i);
        }
    }
}
//算法4.采用邻接表表示图的深度优先搜索遍历 递归
void DFS_AL(ALGraph G, int v){
    cout << v;
    visited[v] = true;
    ArcNode *p = G.vertices[v].firstarc;//p指向v的边链表的第一个边结点
    //当边结点非空时 访问边结点连接的顶点 递归调用遍历函数 退出递归后访问边结点的下一个边结点
    //如下
    while (p != nullptr){
        int w = p->adjvex;//p指向边结点存储的顶点位置
        if (!visited[w]) DFS_AL(G, w);//递归访问每个结点的firstarc存储的顶点
        p = p->nextarc;//退出递归后，p指向下一个边结点
    }    
}
//算法5.深度优先搜索遍历非连通图
//检查顶点访问状态，false的遍历调用算法3.或算法4.即可
void DFSTraverse(ALGraph G){
    for (int v = 0; v < G.vexnum; v++) visited[v] = false;//所有顶点访问标志置为false
    for (int v = 0; v < G.vexnum; v++){
        if (!visited[v]) DFS_AL(G, v);//对尚未访问的顶点调用DFS
    }
}

//算法6.广度优先搜索遍历非连通图
//算法6.1.广度优先搜索遍历连通图
void BFS(ALGraph G, int v){
    cout << v;
    visited[v] = true;
    queue<int> q;
    q.push(v);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int w = G.vertices[u].firstarc->adjvex; w >= 0; w = G.vertices[u].firstarc->nextarc->adjvex){//可以用算法4.的while(p)写法 简洁一点
            if (!visited[w]){
                cout << w;
                visited[w] = true;
                q.push(w);
            }//if
        }//for
    }//while
}//BFS
//广度优先搜索遍历非连通图
void BFSTraverse(ALGraph G){
    for (int v = 0; v < G.vexnum; v++) visited[v] = false;//所有顶点访问标志置为false
    for (int v = 0; v < G.vexnum; v++){
        if (!visited[v]) BFS(G, v);//对尚未访问的顶点调用DFS
    }
}
//[结束]图的遍历算法

//图的应用
//最小生成树
//算法7. Prim算法实现最小生成树
/**
 * @brief 算法思想
 * 将初始顶点u加入U中，对其余的每一个顶点vj，将closedge[j]（辅助数组，用来记录从顶点集U到V-U的权值最小的边）均初始化为到u的边信息
 * 循环n-1次：
 *      从各组边closedge中选出最小边closedge[k]，输出此边；
 *      将k加入U中；
 *      更新剩余的每组最小边信息closedge[j]，对于V-U中的点，新增加了一条从k到j的边
 *      如果新边的权值比closedge[j].lowcost（最小边上的权值）小，将closedge[j].lowcost更新为新边的权值
 */
//辅助数组，用来记录从顶点集U到V-U的权值最小的边
struct edge{
    VertexType adjvex;//最小边在U中的顶点
    ArcType lowcost;//最小边上的权值
} closedge[MVNum];
//选择最小边函数Min()
int Min(edge *e);
//Prim算法
void MiniSpanTree_Prim(AMGraph G, VertexType u){//无向网以邻接矩阵形式存储，从顶点u出发构造G的最小生成树T，输出T的各条边
    int k = LocateVex(G, u);//k为顶点u下标
    for (int j = 0; j < G.vexnum; j++){
        if (j != k) closedge[j] = {u, G.arcs[k][j]};//给其余每个点初始化
    }
    closedge[k].lowcost = 0;
    for (int i = 1; i < G.vexnum; i++){
        k = Min(closedge);//最小生成树的下一个结点位置k，closedge[k]中存有当前最小边
        VertexType u0 = closedge[k].adjvex;//最小边的一个顶点，u0∈U
        VertexType v0 = G.vexs[k]; //最小边的另一个顶点，v0∈V-U
        cout << u0 << v0;//输出当前的最小边(u0, v0)，第一次u0应该就是u
        closedge[k].lowcost = 0;//第k个顶点并入U集
        for (int j = 0; j < G.vexnum; j++){
            if (G.arcs[k][j] < closedge[j].lowcost){
                closedge[j] = {G.vexs[k], G.arcs[k][j]};//更新最小边
            }
        }
    }//for
}//Prim算法
//Min()函数实现
int Min(edge *e){
    int len = sizeof(e) / sizeof(edge);
    int min = INT32_MAX;
    int ind = -1;
    for (int i = 0; i < len; i++){
        if (min > e[i].lowcost && e[i].lowcost != 0){//从权值非0的closedge中找
            min = e[i].lowcost;
            ind = i;
        }
    }
    return ind;
}//没测试，不确定有没有问题
//算法8.Kruskal算法实现最小生成树
/**
 * @brief 算法思想
 * 将辅助数组AEdge（存放如下Edge类）中的元素按权值从小到大排序
 * 依次查看数组AEdge中的边，循环执行以下操作
 *      依次从排好序的数组Edge中选出一条边(U1, U2)
 *      在辅助数组Vexset中分别查找v1和v2所在的连通分量vs1和vs2，进行判断
 *          如果vs1和vs2不等，表明所选的两个顶点分属不同的连通分量，输出此边，并合并vs1和vs2两个连通分量
 *          如果vs1和vs2相等，舍去此边，选择下一条权值最小的边
 */
struct Edge{
    VertexType Head, Tail;
    ArcType lowcost;
    bool operator()(Edge e1, Edge e2){
        return e1.lowcost < e2.lowcost;
    }
};
int Vexset[MVNum];//标志各顶点的连通分量 比如v1连接v2 则Vexset[1] = 2
void MiniSpanTree_Kruskal(AMGraph G){//无向网G以邻接矩阵形式存储，构造G的最小生成树T，输出T的各条边
    //辅助数组AEdge,生成并按权值从小到大排序
    //AEdge大小应为G.arcnum
    vector<Edge> AEdge; 
    for (int i = 0; i < G.vexnum - 1; i++){
        for (int j = i + 1; j < G.vexnum; j++){//因为无向网是对称矩阵，对角线遍历即可
            if (G.arcs[i][j] != MAXINT){
                Edge e;
                e.Head = G.vexs[i];
                e.Tail = G.vexs[j];
                e.lowcost = G.arcs[i][j];
                AEdge.push_back(e);
            }//if
        }//for
    }//for
    sort(AEdge.begin(), AEdge.end(), Edge());
    //初始化Vexset
    for (int i = 0; i < G.vexnum; i++){
        Vexset[i] = i;
    }
    //依次查看数组AEdge中的边
    for (int i = 0; i < G.arcnum; i++){
        int v1 = LocateVex(G, AEdge[i].Head);
        int v2 = LocateVex(G, AEdge[i].Tail);
        //获取v1和v2的连通分量vs1和vs2
        int vs1 = Vexset[v1];
        int vs2 = Vexset[v2];
        if (vs1 != vs2){
            cout << AEdge[i].Head << AEdge[i].Tail;//输出这条边
            for (int j = 0; j < G.vexnum; j++){
                if (Vexset[j] == vs2) Vexset[j] = vs1;//合并连通分量！！重点
            }
        }//if
    }//for
}
//[结束]最小生成树算法