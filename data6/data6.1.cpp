//#include <bits/stdc++.h>
using namespace std;

#define MVNum 20   // 假设当前顶点数最多为20个
int visited[MVNum]; // 用来存放当前顶点是否遍历过

// *****定义邻接矩阵****
typedef char VerTexType;
typedef int ArcType;
typedef struct {
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum, arcnum;
} AMGraph;

// 输出图的邻接矩阵
void PrintAMGraph(AMGraph MG) {
    int i, j;
    if (MG.vexnum <= 0)
        return;
    for (i = 0; i < MG.vexnum; i++)
        cout << MG.vexs[i] << "";
    cout << endl;

    for (i = 0; i < MG.vexnum; i++) {
        for (j = 0; j < MG.vexnum; j++)
            cout << MG.arcs[i][j] << "";
        cout << endl;
    }
}

// 若G中存在v,则返回该顶点在图中位置,否则回-1
int LocateVex(AMGraph G, char v) {
    int i;
    for (i = 0; i < G.vexnum; i++) {
        if (G.vexs[i] == v)
            return i;
    }
    return -1;
}

// 邻接矩阵存储方式建立无向图
void CreateAMGraph(AMGraph& G) {
    int n, m;
    cin >> n >> m;
    G.vexnum = n;
    G.arcnum = m;
    for (int i = 0; i < n; i++) {
        cin >> G.vexs[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            G.arcs[i][j] = 0;
        }
    }
    for (int i = 0; i < m; i++) {
        char x, y;
        cin >> x >> y;
        int posX = LocateVex(G, x);
        int posY = LocateVex(G, y);
        G.arcs[posX][posY] = 1;
        G.arcs[posY][posX] = 1; // 无向图
    }
}

// 从第i个顶点开始深度遍历
void DFSAMGraph(AMGraph G, int i) {
    visited[i] = 1;
    cout << G.vexs[i] << "";
    for (int j = 0; j < G.vexnum; j++) {
        if (G.arcs[i][j] == 1 && !visited[j]) {
            DFSAMGraph(G, j);
        }
    }
}

// 从第i个顶点开始广度遍历
void BFSAMGraph(AMGraph G, int i) {
    vector<int> queue;
    visited[i] = 1;
    queue.push_back(i);

    while (!queue.empty()) {
        int v = queue.front();
        cout << G.vexs[v] << "";
        queue.erase(queue.begin());

        for (int j = 0; j < G.vexnum; j++) {
            if (G.arcs[v][j] == 1 && !visited[j]) {
                visited[j] = 1;
                queue.push_back(j);
            }
        }
    }
}

int main() {
    int choice;
    AMGraph G;
    char startVertex;

    while (cin >> choice) {


        if (choice == 1) {
            // 输出图中的顶点信息和邻接矩阵
            // 这里假设G已经被初始化并填充数据
            PrintAMGraph(G);
        }
        else if (choice == 2) {
            // 创建无向图
            memset(visited, 0, sizeof(visited)); // 初始化visited数组
            CreateAMGraph(G);
        }
        else if (choice == 3) {
            // 深度遍历图
            memset(visited, 0, sizeof(visited)); // 初始化visited数组

            cin >> startVertex;
            int startVex = LocateVex(G, startVertex);
            if (startVex != -1) {
                DFSAMGraph(G, startVex);
                cout << endl;
            }
            else {
                cout << endl;
            }
        }
        else if (choice == 4) {
            // 广度遍历图
            memset(visited, 0, sizeof(visited)); // 初始化visited数组
            cin >> startVertex;
            int startVex = LocateVex(G, startVertex);
            if (startVex != -1) {
                BFSAMGraph(G, startVex);
                cout << endl;
            }
            else {
                cout << endl;
            }
        }
        else {
            cout << endl;
        }
    }

    return 0;
}