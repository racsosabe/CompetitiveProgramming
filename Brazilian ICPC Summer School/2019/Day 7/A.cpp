#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;

int n;
char s[N];

int main(){
	scanf("%s", s);
	n = strlen(s);
	printf("1 %d 2 %d\n", n - 1, n);
	return 0;
}
