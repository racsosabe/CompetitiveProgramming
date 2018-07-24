#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
	Author: Racso Galvan

	Idea:
		- Greedy Variation of Flip Game (original is Brute Force)

		- Let's say that we will brute force the flips for the first row.

		  Let's denote ti as the flip value of the i-th column in the i-th row.
		
		  If ti == 1 then we flip it, else not.

		  Then, we would end up with this dependencies for the i-th and (i-1)-th rows:

		  a[i-1][1] = (t1 + t2) % 2
		  a[i-1][2] = (t1 + t2 + t3) % 2
		
		  There are always 2 options for (t1,t2), according to a[i-1][1], so if we fix those
		
		  for each row, then we can get all the other flip values easily.

		  We can brute force all the flip values for the first row and the 2 first columns from rows 2 -> n

		  Each flip value can be gotten in O(m) per row, flipping can be done in O(1) and checking the whole table
		
		  can be done in O(n) if handling them with bitmask.

		  Complexity: O(nm2^{m+2n-2})

*/

class LightedPanels {
public:
	void change(int x, int y, vector<int> &table, int n, int m){
		int dx[] = {1,1,1,0,0,-1,-1,-1,0};
		int dy[] = {1,0,-1,1,-1,1,0,-1,0};
		for(int k=0; k<9; k++){
			int vx = x + dx[k];
			int vy = y + dy[k];
			if(vx >= 0 and vx < n and vy >=0 and vy < m){
				table[vx] ^= 1<<vy;
			}
		}
	}
	
	void Print(vector<int> &v, int n, int m){
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				putchar('0'+((v[i]>>j)&1));
			}
			puts("");
		}
		puts("");
	}
	
	int minTouch(vector <string> board) {
		vector<int> G;
		int n = board.size();
		int m = board[0].size();
		for(int i=0; i<n; i++){
			int bitmask = 0;
			for(int j=0; j<m; j++){
				if(board[i][j] == '*') bitmask |= 1<<j;
			}
			G.push_back(bitmask);
		}
		if(m == 1){ // Per row
			int ans = -1;
			for(int mask=0; mask<(1<<n); mask++){
				vector<int> table;
				for(int i=0; i<n; i++) table.push_back(G[i]);
				int act = __builtin_popcount(mask);
				for(int j=0; j<n; j++){
					if((mask>>j)&1){
						change(j,0,table,n,m);
					}
				}
				bool can = true;
				for(int i=0; i<n; i++){
					can = can && (table[i] == 1);
				}
				if(can){
					if(ans < 0 or ans > act) ans = act;
				}
			}
			return ans;
		}
		else{ // General case
			int ans = -1;
			for(int mask=0; mask<(1<<(m+2*n-2)); mask++){
				vector<int> table;
				for(int i=0; i<n; i++) table.push_back(G[i]);
				for(int j=0; j<m; j++){
					if((mask>>j)&1) change(0,j,table,n,m);
				}
				bool can = true;
				int act = __builtin_popcount(mask);
				for(int i=1; i<n and can; i++){
					int needed = ~table[i-1];
					int t1 = (mask>>(m+2*(i-1)))&1;
					int t2 = (mask>>(m+2*(i-1)+1))&1;
					if((t1^t2) == (needed&1)){
						if(t1) change(i,0,table,n,m);
						if(t2) change(i,1,table,n,m);
						for(int j=1; j<m-1; j++){
							int t3 = ((needed>>j)&1)^t1^t2;
							if(t3){
								change(i,j+1,table,n,m);
								act++;
							}
							t1 = t2;
							t2 = t3;
						}
						if(table[i-1] != (1<<m)-1) can = false;
					}
					else can = false;
				}
				if(!can) continue;
				for(int i=0; i<n and can; i++){
					can = can && (table[i] == (1<<m)-1);
				}
				if(can){
					if(ans < 0 or ans > act) ans = act;
				}
			}
			return ans;
		}
	}
};
