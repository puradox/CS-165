#define ARRAYLIMIT 10000
double dshrandom( long );

#include <stdarg.h>
int QCOUNT(int arg1, ...) {
/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
/*	Queries to determine a majority element			*/
/*	QCOUNT( 0,n ) initializes a random array of length n	*/
/*				 all Boolean values		*/
/*		returns  0 normally				*/
/*		returns -1 if n is out of range			*/
/*	QCOUNT( 1,Q[] ) views array[ Q[0] ] ... array[ Q[3] ]	*/
/*	         counts the number, num, of 1-values		*/
/*		returns -88 if any Q[i] is out of range		*/
/*		returns -99 if any duplicates among Q[]		*/
/*		returns  abs( 4-2*num ), otherwise		*/
/*		returns 0 if Boolean 1s/0s split 2,2		*/
/*		returns 2 if split 3,1 or 1,3			*/
/*		returns 4 if split 4,0 or 0,4			*/
/*	QCOUNT( 2, answer ) checks whether answer is correct	*/
/*		returns -99999 if any errors			*/
/*		returns number of queries performed, otherwise	*/
/*	QCOUNT( -1 ) turns on debugging 			*/
/*	QCOUNT( -2 ) turns off debugging 			*/
/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
	va_list ap;
	static int marble[ARRAYLIMIT+1];
	static int querycount, OneCount, AnswerValue, arraysize=0;
	static int debug=0;
	int i,j,t,num,*Q,answer;

	va_start(ap, arg1);

	if (arg1<-2 || arg1>2) {
		va_end(ap);
		printf("******* ERROR: QCOUNT(arg1, ...) -- 'arg1'=%d out of range **********\n",arg1);
		return(-1);
	}
	if (arg1== -1) {
		int lim, ct;
		ct = 0;
		debug = 1;
		lim = (arraysize<=100) ? arraysize : 100;
		for (i=1; i<=lim; i+=10) {
			printf("%4d:",i);
			for (j=0; j<=9; j++) {
				if (i+j<=lim) {
					printf(" %d",marble[i+j]);
					ct += marble[i+j];
				}
			}
			printf("    %3d\n",ct);
		}
		printf("OneCount = %d, AnswerValue = %d\n",OneCount,AnswerValue);
		return(0);
	}
	if (arg1== -2) { debug = 0; return(0); }
	if (arg1==0) {
		arraysize = va_arg(ap, int);
		debug = 0;
		va_end(ap);
		if (arraysize<4 || arraysize>ARRAYLIMIT) {
			printf("******* ERROR: QCOUNT(0,n) -- 'n'=%d out of range **********\n",arraysize);
			return(-1);
		}
		j = 0;
		for (i=1; i<=arraysize; i++) {
			marble[i] = dshrandom(0)<0.5 ? 0 : 1;
			j += marble[i];
		}
		OneCount = j;
		AnswerValue = (j < arraysize-j) ? 0 : (j > arraysize-j) ? 1 : -1;
		querycount = 0;
		return(0);
	}
	if (arg1==1) {
		Q = va_arg(ap, int *);
		va_end(ap);
		num = 0;
		for (i=0; i<4; i++) {
			t = Q[i];
			if (t<1 || t>arraysize) return(-88);
			if (i<3)
				for (j=i+1; j<4; j++)
					if (Q[j]==t) return(-99);
			num += marble[t];
		}
		querycount++;
		num = 4-2*num;
		return (num<0) ? -num : num;
	}
	if (arg1==2) {
		answer = va_arg(ap, int);
		va_end(ap);
		if (answer<0 || answer>arraysize) {
			printf("******* ERROR: QCOUNT(2,answer) -- 'answer'=%d out of range (arraysize=%d)**********\n",answer,arraysize);
			return(-99999);
		}
		if ( (answer==0 && AnswerValue<0) ||
                     (answer>0 && marble[answer]==AnswerValue) ) {
			if (debug==1)
				printf("returning querycount=%d\n",querycount);
			return(querycount);
		}
		printf("******* ERROR: QCOUNT(2,answer) -- 'answer'=%d incorrect **********\n",answer);
		if (debug==1)
			printf("******* marble[%d] = %d **********\n",answer,marble[answer]);
		return(-99999);
	}
}
double dshrandom( long input ) {
/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
/*	Random Number Generator					*/
/*		first called with seed				*/
/*		thereafter called with 0			*/
/*	Based on code appearing in				*/
/*	"Random number generators: good ones are hard to find"	*/
/*		by Stephen Park and Keith Miller		*/
/*		CACM 31 (Oct 1988) 1192-1201.			*/
/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
	static long seed = 3125;
	static long a = 16807;
	static long m = 2147483647;
	static long q = 127773;      /* m div a */
	static long r = 2836;        /* m mod a */
	long lo, hi, test;

	if (input>0) seed = input;
	hi = seed/q;
	lo = seed - (hi*q);
	test = a*lo - r*hi;
	if (test>0) seed = test;
	else        seed = test+m;
				/* seed equally in range 0...2^31 -1  */
	return( ((double)seed)/(double)m );
}
