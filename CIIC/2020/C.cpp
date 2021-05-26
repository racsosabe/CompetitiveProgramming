#include<bits/std++.c>
using namespace::std;

const int MOD = 1000000000 + 7;
const int N = 1000000 + 5;

int n;
int q;
int a[N];
vector<int> st[4 * N];

vector<int> merge(vector<int> &a, vector<int> &b){
	
}



vector<int> query(int x, int y, int pos = 1, int l = 1, int r = n){
	
}

int main(){
	scanf("%d %d", &n, &q);
	build();
	while(q--){
		int t, i, j;
		scanf("%d %d %d", &t, &i, &j);
		if(t == 1){
			a[i] ^= 1 << j;
			update(i);
		}
		else{
			
		}
	}
	return 0;
}
