#include <random>              // Includes the C++ random library. Needed for mt19937 RNG and random_device for seeding.
#include <iostream>            // Includes input/output streams. Needed for cout, cin, endl.
#include <vector>              // Includes std::vector, used for the maze grid, visited grid, and parent grid.
#include <deque>               // Includes std::deque, used for BFS queue because it supports push/pop from both ends.
#include <algorithm>
#include <windows.h>            // Includes algorithms like shuffle() used to randomize directions in DFS.

using namespace std;           // Allows using cout, vector, shuffle, etc. without prefixing std::.

// Constants representing what each cell contains
const char WALL = '#';         // Character used to represent a wall in the maze.
const char EMPTY = ' ';        // Character used to represent an empty carved cell.

// Movement arrays for 4 directions.
// DX and DY define offsets for Left, Right, Down, Up (or whichever order you use).
const int DX[4] = {-1,1,0,0};  // X direction offsets for moving horizontally.
const int DY[4] = {0,0,1,-1};  // Y direction offsets for moving vertically.

// Starting coordinates for maze generation and BFS start.
int x = 1 , y = 1 ;            // Hardcoded start position inside the maze. (1,1) must be odd so DFS works.

// RNG initialization
// mt19937 is a Mersenne Twister random number generator—fast, high-quality random numbers.
// random_device{}() provides a non-deterministic seed.
// This line seeds the RNG at program start.
mt19937 rng(random_device{}());

// Depth-First Search function to carve the maze.
void dfs(vector<vector<char>> &maze,int height, int width, int x, int y){
    
    vector<int> dirs = {0,1,2,3};           // Creates a list of direction indices 0 3.
    shuffle(dirs.begin(), dirs.end(), rng); // Randomizes the direction order to make the maze unpredictable.

    for (int d: dirs){                      // Loops through randomized directions.
        
        int nx = x + DX[d] * 2;             // Calculates next cell two steps away horizontally.
        int ny = y + DY[d] * 2;             // Calculates next cell two steps away vertically.
        
        // Bounds check: ensures nx, ny are inside the maze grid.
        // If out of bounds, we skip this direction using continue.
        if (ny < 0 || ny >= height || nx < 0 || nx >= width  )continue;
        
        // If the target cell is not a wall, it means it's already carved or visited.
        // We only carve walls. If it's not a wall → skip.
        if (maze[ny][nx] != WALL)continue;
        
        // Carve the wall between current cell and target two cells away.
        maze[y + DY[d]][x + DX[d]] = EMPTY; // Carves the passage 1 step away.
        maze[ny][nx] = EMPTY;               // Carves the cell 2 steps away.

        // Recursively continue carving from the new cell.
        dfs(maze,height,width,nx,ny);
    }

}

void print(vector<vector<char>> &maze ,int height, int width,vector<pair<int,int>> &path){
        cout << endl;
        for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (maze[i][j] == WALL){
                cout << "██";                // Print wall.
            }
            else{
                bool is_path = false;
                
                // Check if the current cell is part of the BFS path.
                for (pair<int, int> &p : path){
                    if (p.first == j && p.second == i){
                        is_path = true;
                        break;
                    }
                }

                if (is_path){
                    cout << "\033[32m" << "██" << "\033[0m";  // Print path in green.
                }
                else{
                    cout << "  ";                              // Print normal empty space.
                }
            }
        }
        cout << endl;
    }
}

int main(){
    SetConsoleOutputCP(65001);
    int height, width;
    
    cout << "ingrese altura del laberinto" << endl;   // Request maze height from user.
    cin >> height;                                    // Read height.
    
    cout << "ingrese altura del laberinto" << endl;   // Request maze width from user.
    cin >> width;                                     // Read width.

    // Maze generation requires odd dimensions so walls are always between cells.
    if (height % 2 == 0)height++;                     // If even, make height odd.
    if (width % 2 == 0)width++;                       // If even, make width odd.

    // Build a 2D vector maze initialized with WALL everywhere.
    vector<vector<char>> maze(height, vector<char>(width,WALL));

    // A visited matrix for BFS pathfinding.
    vector<vector<bool>> visited(height, vector<bool>(width,false));
    
    // Parent matrix for BFS: stores previous coordinate for every visited cell.
    // Initialized to {1,-1}, but these values are placeholders that will be replaced.
    vector<vector<pair<int,int>>> parent(height, vector<pair<int,int>>(width,{-1,-1}));

    // Coordinates of exit (goal). height-2, width-2 are guaranteed inside the maze.
    int salida_X = height - 2;
    int salida_Y = width - 2;

    // Generate maze using DFS starting at (x,y).
    dfs(maze,height,width,x,y);

    // Print generated maze before solving (walls as "██", empty as space).
    vector<pair<int,int>> empty_path;
    print(maze,height,width,empty_path );
    
    // BFS maze solver begins here.

    deque<pair<int,int>> q;            // BFS queue storing coordinates.
    q.push_back({x,y});                // Start BFS at (x,y).
    visited[x][y] = true;              // Mark start as visited.

    // Standard BFS loop
    while (!q.empty()){
        
        pair<int,int> cur = q.front(); // Take first element in queue.
        q.pop_front();                 // Remove it.

        int current_X = cur.first;     // Extract x coordinate.
        int current_Y = cur.second;    // Extract y coordinate.

        for (int i = 0; i < 4; i++){   // Explore 4 movement directions.
            
            int nx = current_X + DX[i]; // New x coordinate.
            int ny = current_Y + DY[i]; // New y coordinate.

            // Boundary check + not a wall check
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && maze[ny][nx] != WALL){
                
                if (visited[ny][nx]) continue; // Skip already visited cells.

                visited[ny][nx] = true;        // Mark new cell as visited.

                // Store where we came from for path reconstruction.
                parent[ny][nx] = {current_X,current_Y};

                q.push_back({nx,ny});          // Add new cell to queue.
            }
        }
    }

    // BFS done. Now reconstruct the path by walking backwards using parent matrix.
    pair<int,int> end = {salida_X,salida_Y}; // End/goal coordinate.
    vector<pair<int,int>> path;              // Vector to store reconstructed path.
    pair<int,int> cur = end;                 // Start from the exit.

    // Go backwards until reaching parent = (-1,-1) (never happens because you use {1,-1})
    while (cur.first != -1 && cur.second != -1){
        path.push_back(cur);                 // Add current cell to path.
        cur = parent[cur.second][cur.first]; // Move to parent cell.
    }

    reverse(path.begin(),path.end());        // Reverse so path goes start → goal.

    // Print solved maze, coloring the BFS path in green.
    print(maze,height,width,path);

    cin.get();
    cin.get();

}
