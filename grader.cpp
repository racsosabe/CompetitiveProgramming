#include <cstdio>
#include <utility>
#include <algorithm>
#include "device.h"
using namespace std;
static const int MAXN = 1500;
static const int MAXQ = 7777;
static int N, q, str[MAXN], ans;

void bad(int a, int b, int c) {
    printf("Presentation Error\n");
    printf("%d %d %d is not a valid query\n",a,b,c);
    exit(0);
}

int Med3(int a, int b, int c){
    if (a == b || b == c || a == c) bad(a,b,c);
    if (a < 1 || a > N) bad(a,b,c);
    if (b < 1 || b > N) bad(a,b,c);
    if (c < 1 || c > N) bad(a,b,c);
    if(q == MAXQ){
	    printf("Query Limit Exceeded\n");
	    exit(0);
    }
    q++;
    pair<int,int> x(make_pair(str[a-1],a)), y(make_pair(str[b-1],b)), z(make_pair(str[c-1],c));
    return (max(min(x,y),min(max(x,y),z))).second;
}

int main(){
    scanf("%d%d",&ans,&N);
    for (int i=0; i<N; i++) scanf("%d",&str[i]);
    int ret = Median(N);
    if (ans==ret) printf("Accepted\n");
    else printf("Wrong Answer. Expected %d, found %d\n",ans,ret);
    if (q>MAXQ) printf("Queries Limit Exceeded\n");
}
