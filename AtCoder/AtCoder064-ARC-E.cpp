#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Basic geometry and SSSP problem.

	- Just notice that once we are inside a barrier, we can travel to any interior point with 0 cost.

	- Thus, we only care about arriving to a barrier with the minimum distance from

	  our current position.

	- If we consider the source and target points as circles with radii 0, the 

	  problem reduces to the sum of distances between the circles we will be traversing.

	- Observation: The minimal distance is max(0, d(c1, c2) - r1 - r2), where

	  c1 and c2 are the centers of the circles and r1 and r2 the radii, respectively.

	- We can use Dijkstra to solve the problem.

	- Complexity: O(n^2)
*/

const int N = 1000 + 5;
const long double inf = 1e18;

int n;
int x[N];
int y[N];
int r[N];
bool vis[N];
long double D[N];
long double d[N][N];

void init(){
	for(int i = 0; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			d[i][j] = d[j][i] = hypotl(x[i] - x[j], y[i] - y[j]);
		}
	}
}

long double Dijkstra(){
	for(int i = 0; i <= n; i++) D[i] = inf;
	D[0] = 0;
	for(int step = 0; step < n; step++){
		int best = -1;
		for(int i = 0; i <= n; i++){
			if(vis[i]) continue;
			if(best == -1 or D[best] > D[i]) best = i;
		}
		if(best == -1) break;
		vis[best] = true;
		for(int i = 0; i <= n; i++){
			long double w = max(d[best][i] - r[best] - r[i], 0.0L);
			D[i] = min(D[i], D[best] + w);
		}
	}
	return D[n];
}

int main(){
	int xs, ys, xt, yt;
	scanf("%d %d %d %d", &xs, &ys, &xt, &yt);
	scanf("%d", &n);
	x[0] = xs;
	y[0] = ys;
	for(int i = 1; i <= n; i++){
		scanf("%d %d %d", &x[i], &y[i], &r[i]);
	}
	n += 1;
	x[n] = xt;
	y[n] = yt;
	init();
	printf("%.10Lf\n", Dijkstra());
	return 0;
}
