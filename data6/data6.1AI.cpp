#include <iostream>
using namespace std;

#define MaxInt 32767        //���������
#define MVNum 10            //���赱ǰ���������Ϊ10��
typedef char VerTexType;    //�����������
int visited[MVNum];            //������ŵ�ǰ�����Ƿ������

//******�����ڽӱ�******
typedef struct ArcNode {            //�߽��
    int adjvex;                    //�ڽӵ��������е�λ��
    struct ArcNode* nextarc;    //ָ����һ���߽���ָ��
    int weight;                    //�ߵ�Ȩ��(>0)    
}ArcNode;
typedef struct VNode {            //��ͷ���
    VerTexType data;
    ArcNode* firstarc;
}VNode, AdjList[MVNum];
typedef struct {                    //�ڽӱ�
    AdjList vexs;
    int vexnum, arcnum;
}ALGraph;

//��G�д���v,�򷵻ظö�����ͼ��λ��,���򷵻�-1
int LocateVex(ALGraph G, char v) {
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (G.vexs[i].data == v)
            return i;
    }
    return -1;
}

//�����ڽӱ�洢��ʽ������ͼ
void CreateALGraph(ALGraph& G)
{
    /*    1.����ͼ�ж���������ߵ�����
        2.����ͼ�ж�����Ϣ
        3.����ߵ���Ϣ�������߽�㣬���뵽���Ӧ����Ԫ�غ�ı߱��У�ע������ͼ��ÿ������Ҫ���������߽�㣩��*/
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
//--------�������--Start------


//--------�������--End------


//��ȱ����ڽӱ�
void DFSALGraph(ALGraph G, int i)
{
    //--------�������--Start------
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

    //--------�������--End------
}

//����ͼ�����бߵ�Ȩֵ֮��
int GetGraphWeight(ALGraph G)
{
    //--------�������--Start------
    int sum = 0;
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode* p = G.vexs[i].firstarc;
        while (p) {
            sum += p->weight;
            p = p->nextarc;
        }
    }
    return sum;

    //--------�������--End------
}

//����ͼ�г��ȴ�����ȵĽ�����
int GetNode(ALGraph G)
{
    //--------�������--Start------
    int outDegree[MVNum] = { 0 }, inDegree[MVNum] = { 0 };
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode* p = G.vexs[i].firstarc;
        while (p) {
            outDegree[i]++; // ͳ�Ƴ���
            int adjvex = p->adjvex;
            inDegree[adjvex]++; // ͳ�����
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
    //--------�������--End------
}

//������
int main()
{
    int i, select, vex;
    char start;
    ALGraph G;
    G.vexnum = G.arcnum = 0;

    while (cin >> select)
    {
        if (select == 1) {//����������
            CreateALGraph(G);
        }
        else if (select == 2) {//��ȱ���
            cin >> start;//��������ʼ����
            vex = LocateVex(G, start);
            for (i = 0; i < G.vexnum; i++)
                visited[i] = 0;
            DFSALGraph(G, vex);
            cout << endl;
        }
        else if (select == 3)//��Ȩ��
            cout << GetGraphWeight(G) << endl;
        else if (select == 4)//������
            cout << GetNode(G) << endl;
    }
    return 0;
}