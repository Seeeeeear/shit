//#include <bits/stdc++.h>
using namespace std;

#define MVNum 20   // ���赱ǰ���������Ϊ20��
int visited[MVNum]; // ������ŵ�ǰ�����Ƿ������

// *****�����ڽӾ���****
typedef char VerTexType;
typedef int ArcType;
typedef struct {
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum, arcnum;
} AMGraph;

// ���ͼ���ڽӾ���
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

// ��G�д���v,�򷵻ظö�����ͼ��λ��,�����-1
int LocateVex(AMGraph G, char v) {
    int i;
    for (i = 0; i < G.vexnum; i++) {
        if (G.vexs[i] == v)
            return i;
    }
    return -1;
}

// �ڽӾ���洢��ʽ��������ͼ
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
        G.arcs[posY][posX] = 1; // ����ͼ
    }
}

// �ӵ�i�����㿪ʼ��ȱ���
void DFSAMGraph(AMGraph G, int i) {
    visited[i] = 1;
    cout << G.vexs[i] << "";
    for (int j = 0; j < G.vexnum; j++) {
        if (G.arcs[i][j] == 1 && !visited[j]) {
            DFSAMGraph(G, j);
        }
    }
}

// �ӵ�i�����㿪ʼ��ȱ���
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
            // ���ͼ�еĶ�����Ϣ���ڽӾ���
            // �������G�Ѿ�����ʼ�����������
            PrintAMGraph(G);
        }
        else if (choice == 2) {
            // ��������ͼ
            memset(visited, 0, sizeof(visited)); // ��ʼ��visited����
            CreateAMGraph(G);
        }
        else if (choice == 3) {
            // ��ȱ���ͼ
            memset(visited, 0, sizeof(visited)); // ��ʼ��visited����

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
            // ��ȱ���ͼ
            memset(visited, 0, sizeof(visited)); // ��ʼ��visited����
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