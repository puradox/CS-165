#include <stdio.h>
#define MAXN 10000
#include "QCOUNT.c"
#include "mysub.c"

main(){
	int N[] = {20,200,2000,17,18,19,0};
	int n,ct,loop,round,answer,total,biggest,errflag;
#define NLOOP 10000

	for (round = 0; N[round]>10; round++) {
		n = N[round];
		total = 0;
		biggest = -1;
		errflag = 0;
		for (loop=1; loop<=NLOOP; loop++) {
			QCOUNT(0,n);
			answer = mysub( n );
			if (answer<0) {
				printf(" *** flagged error %d at n=%d, loop=%d\n",answer,n,loop);
				errflag = 1;
				break;
			}
			ct = QCOUNT(2,answer);
			if (ct<=0) {
				printf(" *** FAILED at n=%d, loop=%d\n",n,loop);
				errflag = 1;
				break;
			}
			if (ct>biggest) biggest=ct;
			total += ct;
		}
		if (errflag==0)
		printf("n=%5d,   max=%6d,   avg=%8.2f\n",
			n,biggest,total/(1.*NLOOP));
		fflush(stdout);
	}
}
