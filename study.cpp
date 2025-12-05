#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <deque>
#include <unistd.h>
#include <thread>

using namespace std;

const char WALL = '#';
const char EMPTY = ' ';
const int DX[4] = {0, 0, 1, -1};
const int DY[4] = {-1, 1, 0, 0};

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

        if (nx <0 || nx >= width ||ny < 0 || ny >= height || maze[ny][nx] != WALL)continue;
        maze[y + DY[d]][x + DX[d]] = EMPTY;
        maze[ny][nx] = EMPTY;
        

        // TODO: boundary check

        // TODO: wall check

        // TODO: remove wall between current and next

        // TODO: carve the next cell

        // TODO: recursive DFS call
    }
}

int main()
{
    int height, width;
    cout << "ingrese numero de filas: ";
    cin >> height;
    cout << "ingrese numero de columnas: ";
    cin >> width;

    if(height % 2 == 0 )height++;
    if(width % 2 == 0 )width++;
    // TODO: adjust for odd dimensions

    vector<vector<char>> maze(height, vector<char>(width, WALL));
    vector<vector<bool>> visited(height, vector<bool>(width, false));
    vector<vector<pair<int, int>>> parent(height, vector<pair<int, int>>(width, {-1, -1}));

    int sx = 1;
    int sy = 1;

    // TODO: calculate exit positions
    int ex = height - 2;
    int ey = width - 2;

    int escape1 = height - 2 ;
    int escape2 = width - 2 ;

    // TODO: place start and exit symbols

    dfs(maze, height, width, sx, sy);

    // TODO: print maze (first print)
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++)
        {
            if (maze[j][i] == WALL)
            {
                cout << "██" ;
            }else{
                cout << " ";
            }
            
        }
    cout << endl;
    }
    

    deque<pair<int, int>> q;
    q.push_back({x, y});
    visited[y][x] = true;

    while (!q.empty())
    {
        pair<int, int> cur = q.front();
        q.pop_front();

        int cx = cur.first;
        int cy = cur.second;

        for (int i = 0; i < 4; i++)
        {
            int nx = cx + DX[i];
            int ny = cy + DY[i];

            

            // TODO: boundary & wall check for BFS

            // TODO: skip if visited

            // TODO: mark visited + set parent

            // TODO: push to queue
        }
    }

    pair<int, int> target = {ex, ey};
    vector<pair<int, int>> path;

    pair<int, int> cur = target;

    // TODO: parent backtracking loop

    // TODO: reverse path

    // TODO: print path coordinates

    // TODO: print maze with green path

    return 0;
}
