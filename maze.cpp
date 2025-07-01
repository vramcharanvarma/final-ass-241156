#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;
int n, m;
char maze[MAXN][MAXN];
bool visited[MAXN][MAXN];
pair<int, int> parent[MAXN][MAXN];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
pair<int, int> start, end_pos;

// 1. Check if (x, y) is a valid move
bool isValid(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m) && 
           (maze[x][y] != '0' && !visited[x][y]);
}

// 2. BFS Implementation
void bfs() {
    memset(visited, false, sizeof(visited));
    queue<pair<int, int>> q;
    visited[start.first][start.second] = true;
    q.push(start);

    while (!q.empty()) {
        pair<int, int> cur = q.front(); q.pop();
        if (cur == end_pos) {
            cout << "BFS Path found!" << endl;
            return;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];

            if (isValid(nx, ny)) {
                visited[nx][ny] = true;
                parent[nx][ny] = cur;
                q.push({nx, ny});
            }
        }
    }
    cout << "BFS: No path found." << endl;
}

// 3. DFS Implementation
bool dfs(int x, int y) {
    if (make_pair(x, y) == end_pos) {
        cout << "DFS Path found!" << endl;
        return true;
    }

    visited[x][y] = true;

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isValid(nx, ny)) {
            parent[nx][ny] = {x, y};
            if (dfs(nx, ny)) {
                return true;
            }
        }
    }
    return false;
}

// 4. Reconstruct and print the path
void reconstructPath(pair<int, int> end_point) {
    if (!visited[end_point.first][end_point.second]) {
        cout << "No path exists!" << endl;
        return;
    }

    vector<pair<int, int>> path;
    for (auto at = end_point; at != start; at = parent[at.first][at.second]) {
        path.push_back(at);
    }
    path.push_back(start);

    reverse(path.begin(), path.end());

    cout << "Path (row, col): ";
    for (auto p : path) {
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;

    // Optional: Mark path in maze with '*'
    for (auto p : path) {
        if (maze[p.first][p.second] != 'S' && maze[p.first][p.second] != 'E') {
            maze[p.first][p.second] = '*';
        }
    }
}

void printMaze() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << maze[i][j];
        }
        cout << '\n';
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> maze[i][j];
            if (maze[i][j] == 'S') start = {i, j};
            if (maze[i][j] == 'E') end_pos = {i, j};
        }
    }

    // Uncomment the one you want to test
    //bfs();
    // dfs(start.first, start.second);

     //reconstructPath(end_pos);
    // printMaze();

    return 0;
}
