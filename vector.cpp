#include <vector>
#include <iostream>

using namespace std;

int main(){
    int height = 5;
    int width = 5;

    vector<vector<bool>> visited(height, vector<bool>(width, false));
    visited[2][3]= true;// the first value is y axis and the second on eis x

    for(int i = 0; i < height ;i++){
        for(int j = 0; j < width ;j++){
            if(visited[i][j]){
                cout << 1 << " ";
            }else{
                cout << 0 << " ";
            }
        }
        cout << endl;
    }

}