//generatea 5 5 maze
#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int height = 5;// now this are 
    int width = 5;
    int x =0, y = 0;
    int DX[4] = {-1,1,0,0};
    int DY[4] = {0,0,1,-1};

    vector<vector<char>> maze(height, vector<char>(width,'#'));

    vector<vector<bool>> visited(height, vector<bool>(width,false));
    
    vector<vector<pair<int,int>>> parent(height, vector<pair<int,int>>(width,{-1,-1}));
    

    maze[0][0] = '.';// this will be my maze generator
    maze[0][1] = '.';
    maze[0][2] = '.';
    maze[0][3] = '.';
    maze[0][4] = '.';
    // maze[4][0] = '.';
    maze[1][4] = '.';
    maze[2][4] = '.';
    maze[3][4] = '.';
    maze[4][4] = '.';

    deque<pair<int,int>> q;
    q.push_back({x,y});
    visited[y][x] = true;


    while (!q.empty()){
        pair<int,int> cur = q.front();
        q.pop_front();
        int cx = cur.first;
        int cy = cur.second;
        cout << "visiting " << cx << " " << cy << endl;
        for (int i = 0; i < 4; i++){
            int nx = cx + DX[i];
            int ny = cy + DY[i];
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && maze[ny][nx] != '#')
            {
                if (visited[ny][nx]){
                    continue;
                }
                visited[ny][nx] = true;
                cout << "push " << nx << " " << ny << endl;
                parent[ny][nx] = {cx,cy};
                q.push_back({nx,ny});
                
            }
            
        }
        

    }
    pair<int,int> target = {4,4};
    vector<pair<int,int>> path;

    pair<int,int> cur = target;

    while (cur.first != -1 && cur.second != -1){
        path.push_back(cur);
        cur = parent[cur.second][cur.first];

    }

    reverse(path.begin(), path.end());

    for (pair<int,int> &p:path)
    {
        cout << "(" << p.first << "," << p.second << ")" << endl;
    }
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++)
        {
            cout << maze[j][i] << " ";
        }
        cout << endl;
        
    }
    
    

    
    


    
}