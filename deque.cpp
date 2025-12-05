// i ahve to generate a mze that 5 * 5
// i have to check if it indiseede,
//chech if it was visiste

#include <iostream>
#include <deque>
#include <vector>
#include <utility>

using namespace std;

int main(){
    int height = 5;
    int width = 5;
    int x= 2, y = 2;
    int dx[4] = {-1,1,0,0};
    int dy [4] = {0,0,1,-1};

    vector<vector<bool>> visited(height, vector<bool>(width, false));

    deque<pair<int,int>> q;

    q.push_back({x,y});
    visited[y][x] = true;

    while (!q.empty()){
        
        pair<int,int> cur = q.front();
        q.pop_front();

        int cx= cur.first;
        int cy= cur.second;
        cout << "visiting" << cx << ", "<< cy << endl;
        for (int i = 0; i < 4; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if(nx >= 0 && nx < width && ny >= 0 && ny < height){
                cout << "inside" << nx << ", "<< ny << endl;
                if (visited[ny][nx])
                {
                    continue;
                }
                visited[ny][nx]= true;

                q.push_back({nx,ny});
                
            }else
            {
                cout << "not inside" << nx << ", "<< ny << endl;
            }
            
        }
        





    }
    

    return 0;


}