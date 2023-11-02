#include<cstdio>
#include<algorithm>
using namespace::std;

const int N = 100000 + 5;

int tot;
const int BUF=25000000;
char Buf[BUF],*buf=Buf;
void read(int &a) {
    for(a = 0; *buf < 48; buf++);
    while(*buf > 47) a = a * 10 + *buf++ - 48;
}

int n;
int k;
int prefix[N];
int Q[N];

bool up(int i, int pos){
	return 1ll * (prefix[Q[i + 1]] - prefix[Q[i]]) * (pos - Q[i]) <= 1ll * (Q[i + 1] - Q[i]) * (prefix[pos] - prefix[Q[i]]);
}

bool down(int i, int pos){
	return 1ll * (prefix[Q[i]] - prefix[Q[i - 1]]) * (pos - Q[i]) >= 1ll * (Q[i] - Q[i - 1]) * (prefix[pos] - prefix[Q[i]]);
}

double f(int at, int pos){
	return 1.0 * (prefix[pos] - prefix[Q[at]]) / (pos - Q[at]);
}

double solve(){
	int at = 0, sz = 0;
	Q[sz++] = 0;
	double ans = 0;
	for(int i = k; i <= n; i++){
		while(at + 1 < sz and up(at, i)) at++;
		ans = max(ans, f(at, i));
		int j = i - k + 1;
		while(at < sz - 1 and down(sz - 1, j)) sz--;
		Q[sz++] = j;
	}
	return ans;
}

int main(){
	tot = fread(Buf, 1, BUF, stdin);
	while(true){
		if(buf - Buf + 1 >= tot) break;
		read(n);
		read(k);
		for(int i = 1; i <= n; i++){
			int x;
			read(x);
			prefix[i] = prefix[i - 1] + x;
		}
		printf("%.2f\n", solve());
	}
	return 0;
}
