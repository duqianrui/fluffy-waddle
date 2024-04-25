#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <fstream>
int N, M;

using namespace std;

const int DEFAULT_N = 50;
const int DEFAULT_M = 50;

class Maze {
private:
    int N;  // 行数
    int M;  // 列数
    vector<vector<int>> maze;  // 迷宫矩阵
    pair<int, int> start;  // 入口坐标
    pair<int, int> end;  // 出口坐标

public:
    Maze(int n = DEFAULT_N, int m = DEFAULT_M) {
        N = n;
        M = m;
        maze.resize(N, vector<int>(M, 1));  // 初始化迷宫矩阵为全1
        srand(time(NULL));
        start = make_pair(0, rand() % M);  // 随机选择入口坐标
        end = make_pair(N - 1, rand() % M);  // 随机选择出口坐标
        maze[start.first][start.second] = 0;  // 入口设置为0
        maze[end.first][end.second] = 0;  // 出口设置为0
    }

    void generateMaze() {
        generateMazeDFS(start.first, start.second);  // 使用深度优先算法生成迷宫
    }

    void generateMazeDFS(int x, int y) {
        vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };  // 上下左右四个方向
        std::random_shuffle(directions.begin(), directions.end());  // 随机打乱方向
        for (const auto& dir : directions) {
            int nx = x + dir.first * 2;
            int ny = y + dir.second * 2;
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && maze[nx][ny] == 1) {
                maze[nx][ny] = 0;  // 打通墙壁
                maze[x + dir.first][y + dir.second] = 0;  // 打通路径
                generateMazeDFS(nx, ny);  // 递归生成迷宫
            }
        }
    }

    void generateMazeBFS() {
        queue<pair<int, int>> q;
        vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };  // 上下左右四个方向
        q.push(start);
        while (!q.empty()) {
            pair<int, int> cur = q.front();
            q.pop();
        std:random_shuffle(directions.begin(), directions.end());  // 随机打乱方向
            for (const auto& dir : directions) {
                int nx = cur.first + dir.first * 2;
                int ny = cur.second + dir.second * 2;
                if (nx >= 0 && nx < N && ny >= 0 && ny < M && maze[nx][ny] == 1) {
                    maze[nx][ny] = 0;  // 打通墙壁
                    maze[cur.first + dir.first][cur.second + dir.second] = 0;  // 打通路径
                    q.push(make_pair(nx, ny));  // 将新的坐标加入队列
                }
            }
        }
    }

    void printMaze() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (maze[i][j] == 0) {
                    cout << "  ";  // 路径用两个空格表示
                }
                else {
                    cout << "##";  // 墙壁用两个#表示
                }
            }
            cout << endl;
        }
    }
    void saveToFile()
    {
        ofstream file("maze.txt");
        if (file.is_open())
        {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (maze[i][j] == 0) {
                        file << "  ";
                    }
                    else {
                        file << "##";
                    }
                }
                file << "\n";
            }
            file.close();
            cout << "保存成功！" << endl;
        }
        else
        {
            cout << "无法打开文件！" << endl;
        }
    }

};

int main() {

    cout << "请输入迷宫的行数N（默认为50）：";
    cin >> N;
    cout << "请输入迷宫的列数M（默认为50）：";
    cin >> M;

    Maze maze(N, M);
    cout << "生成的迷宫：" << endl;
    maze.generateMaze();
    maze.printMaze();
    maze.saveToFile();
    cout << "生成的迷宫（广度优先算法）：" << endl;
    maze.generateMazeBFS();
    maze.printMaze();

    return 0;
}