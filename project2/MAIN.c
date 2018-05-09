#include <stdio.h>
#define MAXN 10000
#include "QCOUNT.c"
#include "mysub.c"

main(){
	int N[] = {20,200,2000,17,18,19,0};
	int n,ct,loop,round,answer,total,biggest,smallest,errflag;
#define NLOOP 10000

	for (round = 0; N[round]>10; round++) {
		n = N[round];
		total = 0;
		smallest = 2000;
		biggest = -1;
		errflag = 0;
		for (loop=1; loop<=NLOOP; loop++) {
            if (n == 18 && loop == 18)
            {
                printf("Hello\n");
            }
			QCOUNT(0,n);
			answer = mysub( n );
			if (answer<0) {
				printf(" *** flagged error %d at n=%d, loop=%d\n",answer,n,loop);
				errflag = 1;
				break;
			}
			ct = QCOUNT(2,answer);
			if (ct<=0) {
                QCOUNT(-1);
				printf(" *** FAILED at n=%d, loop=%d\n",n,loop);
				errflag = 1;
				break;
			}
            if (ct<smallest) smallest=ct;
			if (ct>biggest) biggest=ct;
			total += ct;
		}
		if (errflag==0)
		printf("n=%5d,   min=%4d,   max=%5d,   avg=%7.2f\n",
			n,smallest,biggest,total/(1.*NLOOP));
		fflush(stdout);
	}

    return 0;
}
