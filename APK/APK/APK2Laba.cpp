#include"stdio.h"
#include"math.h"
#include<stdlib.h>
#include"time.h"

#define k 1000000
int mass[k][16];
void CCode();
void Assem();
void MMX();

int main() {
	unsigned int init = 0;
	printf("Enter random number for initialisation <<Random>> n = ");
	scanf_s("%d", &init);
	for (long long int i = 0; i < k; i++) {
		for (int j = 0; j < 16; j++) {
			srand(init);
			mass[i][j] = rand() % 100;
		}
	}

	int n = 0, SolvingWay = 0;
	do {
		printf("Which method you prefer to calculate that task? (2/MMX Instructions)(1/C Code)(0/ Assembler Code): ");
		while (!scanf_s("%d", &SolvingWay) || abs(SolvingWay) > 2) {
			rewind(stdin);
			printf("You wrote incorrect value or unsupported symbols! Try again (2/MMX Instructions)(1/C code)(0/ Assembler code): ");
		}
		rewind(stdin);
		switch (SolvingWay) {
		case 0: Assem(); break;
		case 1: CCode(); break;
		case 2: MMX(); break;
		}
		rewind(stdin);
		printf("Do you want to calculate some more? (1/yes)(0/no): ");
		while (!scanf_s("%d", &n) || abs(n) > 1) {
			rewind(stdin);
			printf("You wrote incorrect value or unsupported symbols! Try again (1/yes)(0/no): ");
		}
	} while (n);

	return 0;
}


void CCode() {
	clock_t start, end;
	long long int sum = 0;
	start = clock();
	for (long long int i = 0; i < k; i++) {
		for (int j = 0; j < 16; j++) {
			sum += mass[i][j];
		}
	}
	printf("result is %lld\n", sum);
	end = clock();
	double seconds = (end - start)*1000/CLOCKS_PER_SEC;
	printf("time %0.2lf milisec", seconds);
	rewind(stdin);
	getchar();
}

void Assem() {
	clock_t start, end;
	long sum = 0;
	double seconds;
	start = clock();

	_asm {
		pusha
		xor esi, esi
		loop2 :
		mov edx, sum
			mov ax, mass[esi]
			add edx, eax
			add esi, 4
			mov sum, edx
			cmp esi, 64000000
			jne loop2
			popa
	}
	printf("result is %d\n", sum);
	end = clock();
	seconds = (end - start) * 1000 / CLOCKS_PER_SEC;
	printf("time %0.2lf milisec", seconds);
	rewind(stdin);
	getchar();
}

void MMX() {
	clock_t start, end;
	long sum = 0;
	double seconds;
	int test = 0;
	start = clock();
	_asm {
		pusha
		xor esi, esi
		pxor MM7, MM7
		loop2 :
		movq MM0, mass[esi]
		paddd MM7, MM0
		add esi, 8
		cmp esi, 64000000
		jl loop2
		movq MM0, MM7
			movd test, MM7
		psrlq MM7, 32
			movd test, MM7
		paddd MM7, MM0
		movd sum, MM7
		emms
		popa
	}
	printf("result is %d\n", sum);
	end = clock();
	seconds = (end - start) * 1000 / CLOCKS_PER_SEC;
	printf("time %0.2lf milisec", seconds);
	rewind(stdin);
	getchar();
}