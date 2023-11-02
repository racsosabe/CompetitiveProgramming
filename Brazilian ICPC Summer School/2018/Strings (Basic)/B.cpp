#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int z[N];
int a[N];
int pi[N];
int c = 1;

void build(){
	a[0] = 0;
	for(int i = 1; i < n; i++){
		if(pi[i] == 0){
			a[i] = c++;
			continue;
		}
		int k = pi[i - 1];
		while(k + 1 != pi[i]){
			k = pi[k - 1];
		}
		a[i] = a[k];
	}
}

void get_z(){
	int l = 0, r = 0;
	for(int i = 1; i < n; i++){
		z[i] = min(r - i + 1, z[i - l]);
		if(z[i] < 0) z[i] = 0;
		while(i + z[i] < n and a[i + z[i]] == a[z[i]]) z[i]++;
		if(r < i + z[i] - 1){
			l = i;
			r = i + z[i] - 1;
		}
	}

}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &pi[i]);
	}
	build();
	get_z();
	for(int i = 0; i < n; i++){
		printf("%d%c", z[i], " \n"[i + 1 == n]);
	}
	return 0;
}

