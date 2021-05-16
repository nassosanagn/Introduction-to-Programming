/* calculate.c */

#include <stdio.h>
#include <stdbool.h>

int parenthesi();

int ERROR=0;

int main()
{

char x,praksi;
int result,symbols,num,product,kena,i=0;
bool poll;

while(x!=EOF){

symbols=1; 			/* � ������� ��� ������� ��� �������� ������ ������� � ���������� ��� ������� */
num=0;				/* � ������� ��� �������������� ���� ���� �����-����� */
product=1;  		/* �� �������� ��� ��������������� ���� ���� */
result=0;			/* �� ������ ���������� ��� ���� ����������,����� �� ������� �� ENTER */
praksi='+';			/* ������� ���� ����� ���� � ����������� ��� ���� ��� ���������� ����� ��� �� ���� ����� ������������� �� ������� */
kena=0;				/* � ������� ��� ����� ��� �������� ������ ������� */

while(((x=getchar())!='\n')&&(x!=EOF)){

if(ERROR==0){					/* �� ������ ����� ������ ����� ���� ���������� ����� �� ������� �� ENTER */

	if(((x>='0')&&(x<='9'))||(x=='+')||(x=='-')||(x=='*')||(x==' ')||(x=='	')||(x=='(')||(x==')')){		/* ���� �� ��������� ���������� */

		if((x>='0')&&(x<='9')) {							/* ��� �� x ����� ����� [0-9] */

			num = num * 10;
			num = (x-'0') + num;						/* ����������� ������� �����-����� */
			if((symbols==0)&&(kena>0)){				/* �� ��� �������� ������� ������ 2 ������� ���� �������� ����, �������� ERROR */
				ERROR =1;
				continue; }			/* �� �� continue ���� ������ ERROR �� ���������� ���� ������� ��������� ��� ���� �� ���� �������� ����� ����� �� ENTER */
			symbols=0;
			kena=0;

		}else if((x=='+')||(x=='-')||(x=='*')){					/* ��� �� x ������� ������ ����� [-,+,*] */

			if(x=='*'){							/*���� ��������� ��� ������� ��������������� */
				if (praksi=='-')
					product = product * -1; 		 /* ���� � ����� ���� �� �������� ����� '-' ���� ����/�� �� �������� �� �� -1 */
				product = product * num;
				poll =1;

			}else{						/* �� � ���������� ��� ���������� ����� ��� ����� '*' ������, x!='*' */

				if(poll==0){					/*	poll==0 �������� ��� ��� �������� �� ������� ����� ���  ��������������� */
					if(praksi=='+')
						result = result+num;
					else if(praksi=='-')
						result = result-num;

				}else{								/* poll==1 , ������ �� ������� ����� �� ��������������� ������ �� ����� ����� ���� ���� ��������� '*' */

					if(symbols!=1){
						if (praksi=='-')
							product = product * -1;
						product = num * product;
						result = result + product;
						poll = 0;
						product = 1; }
				 	}
				}

			symbols++;

			if((symbols>2)||((symbols==2)&&(praksi=='*')&&(x=='*'))){		/* �� ������� ��� ����� �� ������� ��� ��������������� �.�. 1**1, �������� ERROR */
				ERROR=1;													 /* � �� �������� ���� ��� 2 ������� ������ ������� �.�. 1---1, �������� ERROR */
				continue; }

			if((symbols==2)&&(praksi!='*')){
				if(praksi==x)							/* �� � ����� ��� ����� �������������� ��� �� ������� ����� ���� �� ��� ������� ���� ���� �������� �.�. 1--1 = 1+1 */
					praksi='+';
				else
					praksi='-';							/* �� � ����� ��� ����� �������������� ��� �� ������� ����� ����������� ��� ��� ������� ���� ���� �������� �.�. 1+-1 = 1-1 */
			}else				/* �� symbols==1 � ����� ����� �� x*/
				praksi=x;

			num=0;							/* ���� ��������� ��� ����� ���� ���������� ���� ���������� ������ �������, ���� �� ��������� � �������� ������� */

		}else if((x==' ')||(x=='	'))          /* �� � ���������� ��� ����� ���������� ����� space � tab, �������� +1 ��� ���� */
			kena++;

		else if(x=='('){

			if(symbols==0){					 /* ��� ����������� �� ��� ������� �������� ���� ��� ��������� �.�. 1(1+2) */
				ERROR=1;
				continue; }

				if(symbols>=2){				/* ��� ����������� 2 ������� ���� ��� �����������, ������ �������� ��� ������� */
					ERROR=2;
					continue; }

				symbols=0;
				num = parenthesi();

				if(ERROR!=0)
					if(ERROR==3) 			 /* �� ���� ��������� ������ � ��������� ����������,(����� �������� ��� �� ENTER ���� ���������) */
						break;
					else					/* �� ���������� ���� ����� ��� ������� ���� �� ��������� ������ ���� ���������� ���������� ����� �� ������� ENTER */
						continue;

		}else if(x==')')
			ERROR=5; 					/* �� ������� � ���������� ')' ��� main �������� ��� ��� ���� ��������� � ���������� '(' , ��� ������ � ���������*/


	}else{							/* �� � ���������� ����� ������������ ��� ���� ���������� ���������� */
		ERROR=1;
		symbols=0;
		continue;
		}

}
}

/* ����� ������� ENTER (���� ��� main ���� ��� ���������) ������� ��� �� while */

i++;

if((x=='\n')&&(symbols>0)&&(ERROR==0))		/* ���� ��������� ���� �������� ENTER ��� � ���������� ���������� ���� �������, */
	ERROR=4;								/* ������� 'Unexpected end of input' , ����� ��� ���� ��������� ���� ERROR */

if(ERROR==0){					/* ���� ��������� ���� ��� ������� ERROR ����������� �������� �� ���������� */
	if(poll==0){
		if(praksi=='+')
			result = result + num;
		else if(praksi=='-')
			result = result - num;

	}else{							/* ���� ��������� ���� poll==1 */

			if(praksi=='-')
				product = product * -1;
			product = num * product;
			result = result + product; }

	printf("Result %d: %d\n",i,result);

}else{							/* ���� ��������� ���� ������� ������ ���������� �����, ������ ERROR!=0 */

	if(ERROR==1)													/* ������� �� ��� ���� ��� ERROR ��������� �� ����� */
		printf("Result %d: Unexpected character\n",i);
	else if(ERROR==2)
		printf("Result %d: A sign before a parentheses\n",i);
	else if(ERROR==3)
		printf("Result %d: Missing closing parenthesis\n",i);
	else if(ERROR==4)
		printf("Result %d: Unexpected end of input\n",i);
	else if(ERROR==5)
		printf("Result %d: Missing opening parenthesis\n",i);

}

ERROR=0;		/* �� ���� ��������� �� ERROR ����������� ��� ���� 0 */

}
}
/* ���������� ��������� ����������� ��� ����������� */

int parenthesi(){

	char x,praksi;
	int product,num,kena,symbols,result_2;
	bool poll;

symbols=1;
result_2=0;
product=1;
poll=0;
num=0;
praksi='+';
kena=0;

while((x=getchar())!='\n'){


if(((x>='0')&&(x<='9'))||(x=='+')||(x=='-')||(x=='*')||(x==' ')||(x=='	')||(x=='(')||(x==')')){				/* ���� �� ��������� ���������� */


	if((x>='0')&&(x<='9')) {

			num = num * 10;
			num = (x-'0') + num;
			if((symbols==0)&&(kena>0)){
				ERROR = 1;
				return 0; }				/* �� ���� ��������� ������ � ��������� ����� retutn �� 0 ���� �� ���������� */
			symbols=0;
			kena=0;

	}else if((x=='+')||(x=='-')||(x=='*')){


		if(x=='*'){
			if (praksi=='-')
				product = product * -1; 	 /* ���� � ����� ���� �� �������� ����� '-' ���� ����/�� �� �������� �� �� -1 */
			product = product * num;
			poll=1;

		}else{						/* �� x!= '*' */
			if(poll==0)
				if(praksi=='+')
					result_2 = result_2 + num;
				else
					result_2 = result_2 - num;

			else{

				if(symbols!=1){
					if (praksi=='-')
						product = product * -1;
					product = num * product;
					result_2 = result_2 + product;
					poll = 0;
					product = 1; }

				}
			}

		symbols++;

		if((symbols>2)||((symbols==2)&&(praksi=='*')&&(x=='*'))){		/* �������� ��� ����������� ����� ���� ��� ��� main */
			ERROR=1;
			return 0; }

		if((symbols==2)&&(praksi!='*')){
			if(praksi==x)
				praksi ='+';
			else
				praksi ='-';
		}else
			praksi = x;

		num=0;

	}else if((x==' ')||(x=='	')){
		kena++;

	}else if(x=='('){

		if(symbols==0){
			ERROR=1;
			continue; }

		if(symbols>=2){
			ERROR=2;
			continue; }

		symbols=0;
		num = parenthesi();			/* �� ������ '(' �������� ���� � ��������� ��� � ������� ������� �� ���������� ��� ���������� */

		if(ERROR!=0)
			return 0;

	}else if(x==')'){

		if(symbols>0){		/* ���� ��������� ���� ��� ������� ������� ���� �� �������� ��� ����������, ���� ������� �.�. (1+) */
			ERROR =1;
			return 0;
		}

		if(poll==1){
			if (praksi=='-')
				product = product * -1;
			product = num * product;
			result_2 = result_2 + product;
			poll = 0;

		}else
			if(praksi=='+')
				result_2 = result_2 + num;
			else if(praksi=='-')
				result_2 = result_2 - num;

		return result_2;
	}

}else{
	ERROR =1;
	return 0; }
}
ERROR=3;	/* ���� ��������� ���� ��� ��������� �������� ENTER ��� ��������� ��� ��� ��������� �� ')' ���� �� ��������� �� result_2 ,���� ������ � ��������� ��� ����� */
}
