#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;

int n;
int m;
int a[N][N];

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d", &a[0][i]);
	for(int j = 1; j <= m; j++){
		for(int i = 1; i <= n; i++){
			if(a[j - 1][i - 1] == a[j - 1][i + 1]) a[j][i] = 0;
			else a[j][i] = 1;
		}
	}
	for(int i = 1; i <= n; i++) printf("%d%c", a[m][i], " \n"[i == n]);
	return 0;
}
