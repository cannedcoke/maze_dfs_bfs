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

const string WALL = "#";
const string EMPTY = " ";
const string START = "X";
const string END = "0";
const string DX = {0,0,1,-1};
const string DY = {1,-1,0,0};

class mazeGenerator{
private:
    int n,m;
    vector<vector<int>> maze;
    mt19937 random;

public:
    mazeGenerator(int n, int m, vector<int> & start, vector<int> & end){
        this -> n = n;
        this -> m = m;

        /* The line `maze = vector<vector<int>>(n,vector<int>(m,WALL));` is initializing a 2D vector called `maze` with dimensions `n` rows and `m` columns, where each cell is initially set to the value `WALL`. */
        maze = vector<vector<int>>(n,vector<int>(m,WALL));
        /* The line `random = mt19937(random_device()());` is initializing the `random` member variable of the `mazeGenerator` class with a Mersenne Twister pseudo-random number generator engine (`mt19937`) seeded with a random value obtained from the `random_device` class. */
        random = mt19937(random_device()());
        

    }

}


// estas variables deben poder cambiarse por el usuario




// generacion de laberinto











// visualizacion