#include <stdio.h>
#include <string.h>

#define X_RES	100
#define Y_RES	40
#define PIXELS	(X_RES * Y_RES)
#define CENTER_X	(X_RES/2)
#define CENTER_Y	(Y_RES/2 + 1)
//R1=1 R2=2
#define distance 8

char brightness[] = ".,-~:;=!*#$@";

int k;
double sin() ,cos();
main(){
	float A=0, B=0, i, j, z[PIXELS];
	char b[PIXELS];
	printf("\x1b[2J");
	for(; ; ) {
		memset(b,32,sizeof(b));
		memset(z,0, sizeof(z));
		for(j=0; 6.28>j; j+=0.03) {
			for(i=0; 6.28 >i; i+=0.02) {
				float sini=sin(i),
				      cosj=cos(j),
				      sinA=sin(A),
				      sinj=sin(j),
				      cosA=cos(A),
				      cosj2=cosj+2,
				      mess=1/(sini*cosj2*cosA+sinj*sinA+ distance),
				      cosi=cos(i),
				      cosB=cos(B),
				      sinB=sin(B),
				      t=sini*cosj2*sinA-sinj* cosA;
				int x= CENTER_X + 40 * mess *(cosi * cosj2 * cosB - t * sinB),
				    y= CENTER_Y + 25 *mess * (cosi * cosj2 * sinB + t * cosB),
				    o= x + X_RES*y,
				    N=8*((sinj*cosA-sini*cosj*sinA)*cosB-sini*cosj*cosA-sinj*sinA-cosi *cosj*sinB);
				if(Y_RES>y && y>0 && x>0 && X_RES>x && mess>z[o]){
					z[o]=mess;
					b[o]=brightness[N>0?N:0];
				}
			}
		}
		printf("\x1b[d");
		for(k=0; (PIXELS+1) > k; k++)
			putchar(k%X_RES?b[k]:10);
		//printf("center (%d,%d) res(%d,%d)\n", CENTER_X, CENTER_Y, X_RES, Y_RES);
		A+=0.04;
		B+= 0.02;
	}
}
