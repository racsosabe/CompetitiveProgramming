#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
char s[N];

int main(){
	scanf("%d", &n);
	scanf("%s", s);
	int L = 0, R = 0, D = 0, U = 0;
	for(int i = 0; i < n; i++){
		if(s[i] == 'L') L += 1;
		else if(s[i] == 'R') R += 1;
		else if(s[i] == 'U') U += 1;
		else D += 1;
	}
	printf("%d\n", 2 * min(L, R) + 2 * min(D, U));
	return 0;
}
