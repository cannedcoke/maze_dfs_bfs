// nescesito crear un laberinto 
// tiene que ser geenrado de forma aleatoria
// debe tener una entrada en la esquina superior derecha
// debe tener una salida en la esquina inferior derecha
// debe hacer un camino que las conecte
// usar backtracking para raecorrer el laberinto
// el tamaño dede poder cambiarse por teclado

/* The line `using namespace std;` is a directive that tells the compiler to use the `std` namespace for the standard C++ library. This allows you to use standard C++ library functions and objects without having to prefix them with `std::`. It makes your code cleaner and easier to read. */
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>


using namespace std;

const char WALL = '#';
const char EMPTY = ' ';
const char START = 'x';
const char END = 'x';
const int DX[] = {0,0,1,-1};
const int DY[] = {1,-1,0,0};

class mazeGenerator{
private:
    int n,m;
    vector<vector<char>> maze;
    mt19937 random;

public:
    mazeGenerator(int n, int m, vector<int> & start, vector<int> & end){
        this -> n = n;
        this -> m = m;
        /* The line `maze = vector<vector<int>>(n,vector<int>(m,WALL));` is initializing a 2D vector called `maze` with dimensions `n` rows and `m` columns, where each cell is initially set to the value `WALL`. */
        this -> maze = vector<vector<char>>(n,vector<char>(m,WALL));
        /* The line `random = mt19937(random_device()());` is initializing the `random` member variable of the `mazeGenerator` class with a Mersenne Twister pseudo-random number generator engine (`mt19937`) seeded with a random value obtained from the `random_device` class. */
        this -> random = mt19937(random_device()());
        
        for(int i =0; i < n ; i++){
            /* The line `fill(maze[i].begin(), maze[i].end(), WALL);` is a standard C++ algorithm that fills a range of elements in a vector with a specified value. In this case, it is filling the entire row `i` of the `maze` vector with the value `WALL`. */
            fill(maze[i].begin(), maze[i].end(), WALL);
        }

        maze[start[0]][start[1]] = START;
        maze[end[0]][end[1]] = END;


        /* The line `dfs(start[0]start[1]);` appears to be a function call to a Depth First Search (DFS) algorithm with the starting position specified as `start[0]start[1]`. However, there seems to be a syntax error in the function call. It should likely be `dfs(start[0], start[1]);` with a comma separating the two arguments. */
        dfs(start[0],start[1]);

        for (int i = 0; i < n ; i++){
            for (int j = 0; j < m; j++){
                        if (maze[i][j] == WALL) {
                            cout << "██";      // print a wall
                      } else {
                            cout << maze[i][j] << " ";   // print the value
                        }
            }
            cout << endl;
        }


    }


private:
    void dfs (int x , int y){
        // maze[x][y] = EMPTY;
        vector<int> directions = {0,1,2,3};
        shuffle(directions.begin(), directions.end(), random);

        for(int d : directions){
            int nx = x + DX[d]*2;
            int ny = y + DY[d]*2;

            if(nx < 0 || nx >= n || ny < 0 || ny >= m  ){
                continue;
            }
            if ( maze[nx][ny] != WALL){
                continue;
            }
            maze[x + DX[d]][y + DY[d]] = EMPTY;
            maze[nx][ny] = EMPTY;
            // maze[n-3][n-3] = EMPTY;
            // maze[n-3][n-2] = EMPTY;
            maze[n-2][m-3] = EMPTY;

            dfs(nx,ny);
        }

    }
};

int main(){
    int n,m;
    cout << "ingrese numero de filas: ";
    cin >> n;
    cout << "ingrese numero de columnas: ";
    cin >> m;

    if(n % 2 == 0) n++;
    if(m % 2 == 0) m++;

    vector<int> start = {1,1}, end = {n-2,m-2};
    mazeGenerator maze(n,m,start,end);
    return 0;
}




// estas variables deben poder cambiarse por el usuario


// generacion de laberinto






// visualizacion