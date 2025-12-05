// i have to generate a maze randomly with an entrace and an exit
// uisng dfs for randomized paths
#include <vector>
#include <random>
#include <deque>
#include <algorithm>
#include <iostream>
#include <windows.h>

using namespace std;

const char WALL = '#';
const char EMPTY = ' ';
const int DX[4] = {-1, 1, 0, 0};
const int DY[4] = {0, 0, 1, -1};
int x = 1, y = 1;

mt19937 rng(random_device{}());

void dfs(vector<vector<char>> &maze, int height, int width, int x, int y)
{
    vector<int> dirs = {0, 1, 2, 3};
    shuffle(dirs.begin(), dirs.end(), rng);

    for (int d : dirs)
    {
        int nx = x + DX[d] * 2;
        int ny = y + DY[d] * 2;

        if (nx < 0 || nx >= width || ny < 0 || ny >= height)continue;
        if (maze[ny][nx] != WALL)continue;

        maze[y + DY[d]][x + DX[d]] = EMPTY;
        maze[ny][nx] = EMPTY;

        dfs(maze, height, width, nx, ny);
    }
}

void print(vector<vector<char>> &maze, int height, int width, vector<pair<int, int>> &path)
{
    maze[y][x] = '0';
    maze[height -2][width -2] = 'X';
    
    
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (maze[i][j] == WALL)
            {
                cout << "\033[97m" <<"██";

            }
            else
            {
                bool is_path = false;
                for (pair<int, int> &p : path)
                {
                    if (p.first == j && p.second == i)
                    {
                        is_path = true;
                        break;
                    }
                }
                if (is_path)
                {
                    cout << "\033[94m" << "██" << "\033[0m";
                }
                else
                {
                    cout << maze[i][j] << " ";
                }
            }
        }
        cout << endl;
    }
}

int main()
{
    SetConsoleOutputCP(65001);
    int height, width;
    cout << "ingrese la altura para el laberinto: ";
    cin >> height;
    cout << "ingrese anchura para el laberinto: ";
    cin >> width;

    if (height % 2 == 0)
        height++;
    if (width % 2 == 0)
        width++;

    vector<vector<char>> maze(height, vector<char>(width, WALL));

    vector<vector<bool>> visited(height, vector<bool>(width, false));

    vector<vector<pair<int, int>>> parent(height, vector<pair<int, int>>(width, {-1, -1}));

    dfs(maze, height, width, x, y);

    vector<pair<int, int>> empty_path;

    print(maze, height, width, empty_path);

    int salidaX = width - 2;
    int salidaY = height - 2;


    deque<pair<int, int>> q;
    q.push_back({x, y});
    visited[y][x] = true;

    while (!q.empty())
    {
        pair<int, int> cur = q.front();
        q.pop_front();

        int curx = cur.first;
        int cury = cur.second;
        for (int i = 0; i < 4; i++)
        {
            int nx = curx + DX[i];
            int ny = cury + DY[i];
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && maze[ny][nx] != WALL)
            {
                if (visited[ny][nx])continue;
                visited[ny][nx] = true;
                parent[ny][nx] = {curx, cury};
                q.push_back({nx, ny});
            }
        }
    }

    pair<int,int> goal = {salidaX,salidaY};
    /* The line `vector<pair<int,int>> path;` is declaring a vector named `path` that will store pairs of integers. Each pair represents a coordinate in the maze. This vector will be used to store the path from the entrance to the exit of the maze as the program navigates through it. */
    vector<pair<int,int>> path;
    /* The line `pair<int,int> cur = goal;` is initializing a pair of integers named `cur` with the values from the `goal` pair. In this context, `goal` represents the coordinates of the exit in the maze. By setting `cur` to `goal`, the program is starting from the exit point and then backtracking through the maze using the `parent` vector to find the path from the exit to the entrance. */
    pair<int,int> cur = goal;

    while (cur.first != -1 && cur.second != -1){
        path.push_back(cur);
        cur = parent[cur.second][cur.first];

    }
    reverse(path.begin(),path.end());

    print(maze,height,width,path);

    cin.ignore();
    cin.get();

    return 0;



}