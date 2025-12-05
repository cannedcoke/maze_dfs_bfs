#include <iostream>//this is for standard input and output
#include <vector>// this is for vectors
#include <algorithm>// this is for shuffle
#include <random>// for the random positions
#include <deque>//for the deque for the dfs
#include <unistd.h>// for the time
#include <thread>//time units

using namespace std; //to not have to always pot std::

//constatnts for walls,spaces, positions, these will be relaced by ascii at the end 
const char WALL = '#';
const char EMPTY = ' ';
const int DX[4] = {0, 0, 1, -1};
const int DY[4] = {-1, 1, 0, 0};
int x = 1, y = 1;

/* `mt19937 rng(random_device{}());` is creating a Mersenne Twister pseudo-random number generator object named `rng`. Here's a breakdown of what each part does:
- `random_device{}` creates a random number generator device that provides non-deterministic random numbers.
- `mt19937` is a pseudo-random number generation algorithm that produces 32-bit numbers.
- `rng(random_device{}())` initializes the Mersenne Twister generator `rng` with a random seed obtained from the `random_device`. */
mt19937 rng(random_device{}());

/**
 * The function `dfs` performs a depth-first search traversal on a maze represented by a 2D vector of characters, creating paths by removing walls in a randomized order.
 * 
 * @param maze The `maze` parameter is a 2D vector representing the maze where each cell can be either a wall or empty space. The function `dfs` performs a depth-first search traversal starting from the cell at coordinates `(x, y)` within the maze of size `height` by `width`.
 * @param height The `height` parameter in the `dfs` function represents the height of the maze, which is the number of rows in the maze grid. It is used to check boundaries and ensure that the algorithm stays within the maze while exploring paths.
 * @param width The `width` parameter in the `dfs` function represents the width of the maze grid. It indicates the number of columns in the maze grid where the cells are located.
 * @param x The parameter `x` in the `dfs` function represents the current x-coordinate (column) of the cell being visited in the maze. It is used to keep track of the current position within the maze while performing depth-first search traversal.
 * @param y The parameter `y` in the `dfs` function represents the current y-coordinate (vertical position) within the maze grid where the algorithm is currently exploring or backtracking. It is used to keep track of the current position in the maze during the depth-first search traversal.
 */
void dfs(vector<vector<char>> &maze, int height, int width, int x, int y)
{
    vector<int> dirs = {0, 1, 2, 3};
    shuffle(dirs.begin(), dirs.end(), rng);

    for (int d : dirs)
    {
        int nx = x + DX[d] * 2;
        int ny = y + DY[d] * 2;

        if (ny < 0 || ny >= height || nx < 0 || nx >= width)
            continue;
        if (maze[ny][nx] != WALL)
            continue;

        maze[y + DY[d]][x + DX[d]] = EMPTY;
        maze[ny][nx] = EMPTY;

        dfs(maze, height, width, nx, ny);
    }
}
int main()
{
    int height, width;
    cout << "ingrese numero de filas: ";
    cin >> height;
    cout << "ingrese numero de columnas: ";
    cin >> width;

    if (height % 2 == 0)
        height++;
    if (width % 2 == 0)
        width++;

    vector<vector<char>> maze(height, vector<char>(width, WALL));
    // aca genero un amatriz igual pero con booleanos
    vector<vector<bool>> visited(height, vector<bool>(width, false));
    // aca genero una matriz parent para el baktracking
    vector<vector<pair<int, int>>> parent(height, vector<pair<int, int>>(width, {-1, -1}));

    // aca es todo para generar el alaberinto
    int sx = 1;
    int sy = 1;

    int ex = height - 2;
    int ey = width - 2;

    // int escape1 = height - 3;
    // int escape2 = width - 2;

    // maze[sx][sy] = 'x';
    // maze[ex][ey] = 'y';
    // maze[escape1][escape2] = EMPTY;

    dfs(maze, height, width, sx, sy);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (maze[i][j] == WALL)
            {
                cout << "██";
            }
            else
            {
                cout << maze[i][j] << " ";
            }
        }
        cout << endl;
    }

    deque<pair<int, int>> q;
    q.push_back({sx, sy});
    visited[sy][sx] = true;

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
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && maze[ny][nx] != WALL)
            {
                if (visited[ny][nx])
                    continue;
                visited[ny][nx] = true;
                parent[ny][nx] = {cx, cy};
                q.push_back({nx, ny});
            }
        }
    }
    pair<int, int> target = {ey,ex};

    vector<pair<int, int>> path;

    pair<int, int> cur = target;

    while (cur.first != -1 && cur.second != -1)
    {
        path.push_back(cur);
        cur = parent[cur.second][cur.first];
    }
    reverse(path.begin(), path.end());

    for (pair<int, int> &p : path)
    {
        cout << "(" << p.first << "," << p.second << ")" << endl;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (maze[i][j] == WALL)
            {
                cout << "██";
            }
            else{
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
                    cout << "\033[32m" << "██" << "\033[0m";
                    // std::this_thread::sleep_for(std::chrono::seconds(1));
                }
                else
                {
                    cout << "  ";
                }
            }
        }
        cout << endl;
    }

    return 0;
}
