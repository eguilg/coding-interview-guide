# include <bits/stdc++.h>
using namespace std;

void rotate1(vector<vector<int>> & mat) {
    int n = mat.size()-1;
    int tR = 0, tC = 0, dR = n, dC = n;

    while (tR < dR) {
        int time = dR - tR;
        int tmp = 0;
        for (int i = 0; i < time; ++i) {
            // 顺时针
            tmp = mat[tR+i][dC];
            mat[tR+i][dC] = mat[tR][tC+i];
            mat[tR][tC+i] = mat[dR-i][tC];
            mat[dR-i][tC] = mat[dR][dC-i];
            mat[dR][dC-i] = tmp;
        }
        tR++;tC++;dR--;dR--;
    }
}

int main(){
    vector<vector<int>> mat={
        {1,2,3},{4,5,6},{7,8,9}
    };
    rotate1(mat);
    for (auto r : mat) {
        for (auto val : r){
            cout << val << " ";
        }
        cout << endl;
    }
}