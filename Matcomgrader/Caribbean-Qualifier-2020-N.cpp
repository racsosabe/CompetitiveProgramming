#include<bits/stdc++.h>
using namespace::std;

int main(){
	vector<int> v(4);
	for(int i = 0; i < 4; i++) scanf("%d", &v[i]);
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(i == j) continue;
			for(int k = 0; k < 4; k++){
				if(i == k or j == k) continue;
				if(v[i] + v[j] == 2 * v[k]){
					puts("YES");
					return 0;
				}
			}
		}
	}
	puts("NO");
	return 0;
}
