#include <stdio.h>
#include <string.h>

#define X_RES	40
#define Y_RES	22
#define PIXELS	(X_RES * Y_RES)
#define CENTER_X	(X_RES/2)
#define CENTER_Y	(Y_RES/2)
#define R1 1 
#define R2 3
#define NEAR	4
#define FAR	12
#define TOP	(Y_RES/2)
#define RIGHT	(X_RES/2)
#define distance 10

char brightness[] = ".,-~:;=!*#$@";
const float K1 = CENTER_X *distance*6/(8*(R1+R2));
const float K2 = CENTER_Y *distance*6/(8*(R1+R2));

int k;
double sin() ,cos();
int main(void){
	float A=0, B=0, i, j, z_buff[PIXELS];
	char b[PIXELS];
	printf("\x1b[2J");
	for(; ; ) {
		memset(b,32,sizeof(b));
		memset(z_buff,0, sizeof(z_buff));
		for(j=0; 6.28>j; j+=0.03) {
			for(i=0; 6.28 >i; i+=0.02) {
				float sini=sin(i),
				      cosj=cos(j),
				      sinA=sin(A),
				      sinj=sin(j),
				      cosA=cos(A),
				      cosj2=R1 * cosj+ R2,
				      cosi=cos(i),
				      cosB=cos(B),
				      sinB=sin(B),
				      //z = (sini*cosj2*cosA+sinj*sinA+ distance),
				      mess=1/(sini*cosj2*cosA+sinj*sinA+ distance),// 1/z
				      t=sini*cosj2*sinA-sinj* cosA;
				int x= CENTER_X + K1 * mess *(cosi * cosj2 * cosB - t * sinB),
				    y= CENTER_Y + K2 *mess * (cosi * cosj2 * sinB + t * cosB),
				    o= x + X_RES*y,
				    N=8*((sinj*cosA-sini*cosj*sinA)*cosB-sini*cosj*cosA-sinj*sinA-cosi *cosj*sinB);
				if(Y_RES>y && y>0 && x>0 && X_RES>x && mess>z_buff[o]){
					z_buff[o]=mess;
					b[o]=brightness[N>0?N:0];
				}
			}
		}
		printf("\x1b[d");
		for(k=0; (PIXELS+1) > k; k++)
			putchar(k%X_RES?b[k]:10);
		A+=0.04;
		B+= 0.02;
	}
}
