#include <bits/stdc++.h>
using namespace std;


struct State {
    vector<int> board;      
    int g;                  
    int h;                 
    string path;            

    int f() const { return g + h; }
};


struct Compare {
    bool operator()(const State& a, const State& b) const {
        return a.f() > b.f();
    }
};


int manhattan(const vector<int>& board) {
    int dist = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) continue;
        int val = board[i] - 1;
        dist += abs(i / 3 - val / 3) + abs(i % 3 - val % 3);
    }
    return dist;
}


bool isSolvable(const vector<int>& board) {
    int inv = 0;
    for (int i = 0; i < 9; i++)
        for (int j = i + 1; j < 9; j++)
            if (board[i] && board[j] && board[i] > board[j]) inv++;
    return inv % 2 == 0;
}

int main() {
    vector<int> start(9);
    cout << "Ingrese la configuracion inicial (use 0 para el espacio vacio):\n";
    for (int i = 0; i < 9; i++) cin >> start[i];

    vector<int> goal = {1,2,3,4,5,6,7,8,0};

    if (!isSolvable(start)) {
        cout << "Esta configuracion no tiene solucion.\n";
        return 0;
    }

    priority_queue<State, vector<State>, Compare> pq;
    unordered_set<string> visited;

    State init{start, 0, manhattan(start), ""};
    pq.push(init);

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    char moveChar[4] = {'W', 'S', 'A', 'D'};


    while (!pq.empty()) {
        State cur = pq.top(); pq.pop();

        string key;
        for (int x : cur.board) key += char(x + '0');
        if (visited.count(key)) continue;
        visited.insert(key);

        if (cur.board == goal) {
            cout << "Solucion encontrada en " << cur.g << " movimientos.\n";
            cout << "Secuencia: " << cur.path << endl;
            cout <<"W:Arriba, S:Abajo, A:Izquierda, D:Derecha";
            return 0;
        }

        int zero = find(cur.board.begin(), cur.board.end(), 0) - cur.board.begin();
        int x = zero / 3, y = zero % 3;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3) continue;
            int nz = nx * 3 + ny;

            State next = cur;
            swap(next.board[zero], next.board[nz]);
            next.g = cur.g + 1;
            next.h = manhattan(next.board);
            next.path = cur.path + moveChar[i];

            pq.push(next);
        }
    }

    cout << "No se encontro solucion.\n";
    return 0;
}
