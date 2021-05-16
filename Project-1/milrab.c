/* File: milrab.c */

#include <stdio.h>
#include <time.h>

#define MINNUM 3990000000
#define MAXNUM 4010000000


int main()
{
unsigned int a,d,n,x,y;
int i,r,sum,flag,metritis_a;
float clock1,clock2;

/* Deterministic Algorithm */

sum = 0;
for(n=MINNUM|1;n<=MAXNUM;n+=2){
flag=1;
i=5;
if(n%3==0)
		flag=0;
else{
	while((i*i)<=n){
		if ((n%i==0)||(n%(i+2)==0)){
			flag = 0;
			break;}
		i=i+6; }
}								/* ��� �� n ��� ���������� �� ���� �������� 2,3 ����� �� ��������� ���� 2�������� ��� ����� ��� �� ������������� �� ����������� ���� */
if(flag==1)
	sum++;
}
clock1=clock() /(float) CLOCKS_PER_SEC;
printf("Checking range [%lld,%lld] for primes\n",MINNUM,MAXNUM);
printf("Deterministic algorithm: Found %6d primes in %.2f secs\n",sum,clock1);

/* Miller-Rabin Algorithm */

sum=0;
for(n=MINNUM|1;n<=MAXNUM;n+=2){

flag=1;
r=0;
d=n-1;
metritis_a=1;

while(flag==1)						/* ��������� �� 2^r * d */
	if(d%2==0){
		r++;
		d=d/2;}
	else
		flag=0;

while(metritis_a<=3){  						/* ��� ���� � (2,7,61) */

flag=1;
y=d;							/* �� y �� ����������� ��� �� ������� ��� ���� ��� �� d */
x=1;

if(metritis_a==1)
	a=2;
else if(metritis_a==2)
	a=3;
else
	a=61;

while (y>0){
	if(y%2==1)
		x=(a*(unsigned long long)x)%n;			/* ���� x <-- �^d mod n �� Right-to-left binary method*/
y=y>>1;
a=(a*(unsigned long long)a)%n;				/* type casting ���� �� ��� ������� ����������� */
}

if((x==1)||(x==n-1))
	flag=0;
else
	for(i=1;i<=(r-1);i++){
		x=(x*(unsigned long long)x)%n;
		if(x==n-1){
			flag=0;
			break;}
	}

if(flag==0)
	metritis_a++;
else
	break;
}

if(metritis_a==4)					  /* ��� ���� ������� ��� ��� �� a ���� �� � �� ���� ��� ���� 4 */
	sum++;
}

clock2=clock() / (float)CLOCKS_PER_SEC;
printf("Miller-Rabin algorithm: Found %d primes in %.2f secs\n",sum,clock2-clock1);
}
