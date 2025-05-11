#include <iostream>
using namespace std;

#define MaxInt 32767        //代表无穷大
#define MVNum 10            //假设当前顶点数最多为10个
typedef char VerTexType;    //结点数据类型
int visited[MVNum];            //用来存放当前顶点是否遍历过

//******定义邻接表******
typedef struct ArcNode {            //边结点
    int adjvex;                    //邻接点在数组中的位置
    struct ArcNode* nextarc;    //指向下一个边结点的指针
    int weight;                    //边的权重(>0)    
}ArcNode;
typedef struct VNode {            //表头结点
    VerTexType data;
    ArcNode* firstarc;
}VNode, AdjList[MVNum];
typedef struct {                    //邻接表
    AdjList vexs;
    int vexnum, arcnum;
}ALGraph;

//若G中存在v,则返回该顶点在图中位置,否则返回-1
int LocateVex(ALGraph G, char v) {
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vexs[i].data == v)
            return i;
    }
    return -1;
}

//建立邻接表存储方式的无向图
void CreateALGraph(ALGraph& G)
{
    /*    1.输入图中顶点总数与边的总数
        2.输入图中顶点信息
        3.输入边的信息，建立边结点，插入到相对应数组元素后的边表中（注：无向图中每条边需要插入两个边结点）。*/
    int i, j, k;
    char v1, v2;
    ArcNode* p;
    int w;

    cin >> G.vexnum >> G.arcnum;
    for (i = 0; i < G.vexnum; i++) {
        cin >> G.vexs[i].data;
        G.vexs[i].firstarc = NULL;
    }
    for (k = 0; k < G.arcnum; k++) {
        cin >> v1 >> v2 >> w;
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        p = new ArcNode;
        p->adjvex = j;
        p->weight = w;
        p->nextarc = G.vexs[i].firstarc;
        G.vexs[i].firstarc = p;
    }
}
//--------补充代码--Start------


//--------补充代码--End------


//深度遍历邻接表
void DFSALGraph(ALGraph G, int i)
{
    //--------补充代码--Start------
    ArcNode* p;
    visited[i] = 1;
    cout << G.vexs[i].data << "";
    p = G.vexs[i].firstarc;
    while (p) {
        int j = p->adjvex;
        if (!visited[j]) {
            DFSALGraph(G, j);
        }
        p = p->nextarc;
    }

    //--------补充代码--End------
}

//计算图中所有边的权值之和
int GetGraphWeight(ALGraph G)
{
    //--------补充代码--Start------
    int sum = 0;
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode* p = G.vexs[i].firstarc;
        while (p) {
            sum += p->weight;
            p = p->nextarc;
        }
    }
    return sum;

    //--------补充代码--End------
}

//计算图中出度大于入度的结点个数
int GetNode(ALGraph G)
{
    //--------补充代码--Start------
    int outDegree[MVNum] = { 0 }, inDegree[MVNum] = { 0 };
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode* p = G.vexs[i].firstarc;
        while (p) {
            outDegree[i]++; // 统计出度
            int adjvex = p->adjvex;
            inDegree[adjvex]++; // 统计入度
            p = p->nextarc;
        }
    }
    int count = 0;
    for (int i = 0; i < G.vexnum; i++) {
        if (outDegree[i] > inDegree[i]) {
            count++;
        }
    }
    return count;
    //--------补充代码--End------
}

//主函数
int main()
{
    int i, select, vex;
    char start;
    ALGraph G;
    G.vexnum = G.arcnum = 0;

    while (cin >> select)
    {
        if (select == 1) {//建立有向网
            CreateALGraph(G);
        }
        else if (select == 2) {//深度遍历
            cin >> start;//遍历的起始顶点
            vex = LocateVex(G, start);
            for (i = 0; i < G.vexnum; i++)
                visited[i] = 0;
            DFSALGraph(G, vex);
            cout << endl;
        }
        else if (select == 3)//求权和
            cout << GetGraphWeight(G) << endl;
        else if (select == 4)//求结点数
            cout << GetNode(G) << endl;
    }
    return 0;
}