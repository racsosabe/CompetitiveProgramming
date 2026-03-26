/**
 * File: CF105394-GYM-G.cpp
 * Author: racsosabe
 * Date: 20/03/2026
 */

#include <bits/stdc++.h>
using namespace std;

vector<string> setting1 = {""};

vector<string> generate(int h, int w) {
    vector<string> res;

}

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int h, w;
    cin >> h >> w;
    if(h % 5 and w % 5) {
        cout << "no" << endl;
        return 0;
    }
    if(min(h, w) == 1) {
        if (max(h, w) == 5) {
            cout << "yes" << endl;
            if (h == 1) {
                cout << "IIIII" << endl;
            }
            else {
                cout << "I\nI\nI\nI\nI" << endl;
            }
        }
        else {
            cout << "no" << endl;
        }
        return 0;
    }
    bool rotated = false;
    if (w % 5) {
        rotated = true;
        swap(h, w);
    }
    vector<string> board = generate(h, w);
    if (rotated) {
        for (int j = 0; j < w; ++j) {
            for (int i = 0; i < h; ++i) {
                cout << board[i][j];
            }
            cout << endl;
        }
    }
    else {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                cout << board[i][j];
            }
            cout << endl;
        }
    }

    return 0;
}