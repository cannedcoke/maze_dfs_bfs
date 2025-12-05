#include <vector>
#include <iostream>
using namespace std;

int main() {
    int height = 5;
    int width = 5;

    vector<vector<bool>> visited(height, vector<bool>(width, false));

    int x = 2;
    int y = 2;

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    for (int i = 0; i < 4; i++) {

        int nx = x + dx[i];
        int ny = y + dy[i];

        if ( nx >= 0 && nx < width && ny >= 0 && ny < height ) {


            if (visited[ny][nx]) {
                cout << "(" << nx << "," << ny << ") skipped (visited)" << endl;
            } else {
                cout << "(" << nx << "," << ny << ") not visited yet" << endl;
                visited[ny][nx] = true;
            }

        } else {
            cout << "(" << nx << "," << ny << ") OUTSIDE" << endl;
        }
    }
}
