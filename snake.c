#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>

#define SIR 30
#define VIS 16
#define ZM (VIS-2)*(SIR-2)
#define MEM(x) if(x == NULL) { system("cls"); printf("Nedovoljno memorije!%c%c%c\nPritisnite bilo koje dugme da ugasite program.", 7, 7, 7); while(!kbhit()); exit(666); }

void pocetak(int tez, int zid);
void pomoc();
void podesavanja(int *tez, int *zid);
void meni(int x, int y, int *tez, int *zid);
void stampaj(int x);
void igra(int tez, int zid);
void jabuka(int **p);
int zmija(int **z, int **p, int *n, int key, int zid);
void cekaj(int sec);
void polje(int **p);
void izlaz();

void main() {
	srand((unsigned)time(NULL));
	printf("Dobrodosli u Zmijicu C. \n\nKoristite strelice da se krecete po meniju, \ni ENTER da potvrdite izabranu opciju. \n\nPomerajte zmijicu pomocu strelica ili dugmica W, A, S i D. \n\nPritisnite SPACE da pocnete.");
	while(getch() != 32);
	pocetak(2, 0);
}

void pocetak(int tez, int zid) {
	int menu = 0, key = 0;

	system("cls");
	printf("Dobrodosli u Zmijicu C. \n\n");
	switch(menu) {
		case 0: printf(" > Pocni\n   Podesavanja\n   Pomoc\n   Izadji\n   "); break;
		case 1: printf("   Pocni\n > Podesavanja\n   Pomoc\n   Izadji\n   "); break;
		case 2: printf("   Pocni\n   Podesavanja\n > Pomoc\n   Izadji\n   "); break;
		case 3: printf("   Pocni\n   Podesavanja\n   Pomoc\n > Izadji\n   "); break;
	}
	while(1) if(kbhit()) {
		key = getch();
		if(key == 80 || key == 115) { //dole
			menu++; if(menu > 3) menu = 0;
			system("cls");
			printf("Dobrodosli u Zmijicu C. \n\n");
			switch(menu) {
				case 0: printf(" > Pocni\n   Podesavanja\n   Pomoc\n   Izadji\n   "); break;
				case 1: printf("   Pocni\n > Podesavanja\n   Pomoc\n   Izadji\n   "); break;
				case 2: printf("   Pocni\n   Podesavanja\n > Pomoc\n   Izadji\n   "); break;
				case 3: printf("   Pocni\n   Podesavanja\n   Pomoc\n > Izadji\n   "); break;
			}
		}
		if(key == 72 || key == 119) { //gore
			menu--; if(menu < 0) menu = 3;
			system("cls");
			printf("Dobrodosli u Zmijicu C. \n\n");
			switch(menu) {
				case 0: printf(" > Pocni\n   Podesavanja\n   Pomoc\n   Izadji\n   "); break;
				case 1: printf("   Pocni\n > Podesavanja\n   Pomoc\n   Izadji\n   "); break;
				case 2: printf("   Pocni\n   Podesavanja\n > Pomoc\n   Izadji\n   "); break;
				case 3: printf("   Pocni\n   Podesavanja\n   Pomoc\n > Izadji\n   "); break;
			}
		}
		if(key == 13) {
			key = 0;
			switch(menu) {
				case 0: igra(tez, zid); break;
				case 1: podesavanja(&tez, &zid); break;
				case 2: pomoc(); break;
				case 3: izlaz(); break;
			}
		}
	}
}

void pomoc() {
	int key = 0;

	system("cls");
	printf("Koristite strelice ili W, A, S i D da se krecete po polju.\n\nCilj igre je da pojedete sto vise jabuka, i tako skupite poene.\nSvaka jabuka koju pojedete povecace vasu zmiju za jedno polje.\nIgra je gotova kada dotaknete zid ili ugrizete sami sebe.\n\nPritisnite SPACE da se vratite u glavni meni.");
	while(getch() != 32);
	system("cls");
	printf("Dobrodosli u Zmijicu C.\n\n   Pocni\n   Podesavanja\n > Pomoc\n   Izadji\n   ");
}

void podesavanja(int *tez, int *zid) {
	int x = 0, y = 0, key = 0;

	system("cls");
	meni(x, y, tez, zid);
	while(1) if(kbhit()) {
		key = getch();
		if(key == 80 || key == 115) { //dole
			y++; if(y > 2) y = 0;
			x = 0;
			meni(x, y, tez, zid);
		}
		if(key == 72 || key == 119) { //gore
			y--; if(y < 0) y = 2;
			x = 0;
			meni(x, y, tez, zid);
		}
		if(key == 75 || key == 97) { //levo
			if(y == 0) {
				x--; if(x < 0) x = 4;
			}
			if(y == 1) {
				x--; if(x < 0) x = 1;
			}
			meni(x, y, tez, zid);
		}
		if(key == 77 || key == 100) { //desno
			if(y == 0) {
				x++; if(x > 4) x = 0;
			}
			if(y == 1) {
				x++; if(x > 1) x = 0;
			}
			meni(x, y, tez, zid);
		}
		if(key == 13) { //select
			if(y == 0) {
				*tez = x;
				meni(x, y, tez, zid);
			}
			if(y == 1) {
				*zid = x;
				meni(x, y, tez, zid);
			}
			if(y == 2) {
				system("cls");
				printf("Dobrodosli u Zmijicu C. \n\n   Pocni\n > Podesavanja\n   Pomoc\n   Izadji\n   ");
				break;
			}
		}
	}
}

void meni(int x, int y, int *tez, int *zid) {
	int i;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	WORD def;

	GetConsoleScreenBufferInfo(h, &csbi);
	def = csbi.wAttributes;
	system("cls");
	printf("  Tezina:\n\n");
	for(i = 0; i < 5; i++) {
		if(y == 0 && x == i) {
			SetConsoleTextAttribute (h, 7 | 8);
			printf("  > ");
			SetConsoleTextAttribute (h, def);
		}
		else printf("    ");
		if(*tez == i) {
			SetConsoleTextAttribute (h, 7 | 8);
			stampaj(i);
			SetConsoleTextAttribute (h, def);
		}
		else stampaj(i);
	}
	printf("\n\n\n  Zid:\n\n");
	for(i = 0; i < 2; i++) {
		if(y == 1 && x == i) {
			SetConsoleTextAttribute (h, 7 | 8);
			printf("  > ");
			SetConsoleTextAttribute (h, def);
		}
		else printf("    ");
		if(*zid == i) {
			SetConsoleTextAttribute (h, 7 | 8);
			stampaj(i+5);
			SetConsoleTextAttribute (h, def);
		}
		else stampaj(i+5);
	}
	if (y == 2) printf("\n\n\n> Nazad <\n");
	else printf("\n\n\n  Nazad  \n");
}

void stampaj(int x) {
	switch(x) {
		case 0: printf("jako lako"); break;
		case 1: printf("lako"); break;
		case 2: printf("srednje"); break;
		case 3: printf("tesko"); break;
		case 4: printf("najteze"); break;
		case 5: printf("ne"); break;
		case 6: printf("da"); break;
	}
}

void igra(int tez, int zid) {
	int i, **p, **z, t, n = 5, key = 2, s, m;
	time_t start;

	switch(tez) {
		case 0: t = 50; break;
		case 1: t = 20; break;
		case 2: t = 10; break;
		case 3: t = 3; break;
		case 4: t = 1; break;
	}
	p = malloc(VIS * sizeof(int*)); MEM(p);
	for(i = 0; i < VIS; i++) {
		p[i] = calloc(SIR, sizeof(int)); MEM(p[i]);
	}
	for(i = 0; i < SIR; i++) p[0][i] = p[VIS-1][i] = -2;
	for(i = 0; i < VIS; i++) p[i][0] = p[i][SIR-1] = -2;
	z = malloc(ZM * sizeof(int*)); MEM(z);
	for(i = 0; i < ZM; i++) {
		z[i] = malloc(2 * sizeof(int)); MEM(z[i]);
	}
	for(i = 0; i < n; i++) {
		z[i][0] = VIS/2-2;
		z[i][1] = SIR/2 - i;
	}
	zmija(z, p, &n, key, zid);
	jabuka(p);
	system("cls"); printf(" vreme: 00:00      bodovi:  0\n");
	polje(p);
	printf("\nPritisnite bilo koje dugme da pocnete.");
	while(!kbhit());
	start = clock();
	/* POCETAK */
	while(1) {
		if(kbhit()) {
			i = getch();
			if(i==224) i = getch();
			switch(i) {
			case 75:
			case 97:	if(key != 2) key = 1; break;
			case 77:
			case 100:	if(key != 1) key = 2; break;
			case 80:
			case 115:	if(key != 4) key = 3; break;
			case 72:
			case 119:	if(key != 3) key = 4; break;
			}
		}
		cekaj(t);
		for(s = difftime(clock(), start)/CLOCKS_PER_SEC, m = 0; s >= 60; s -= 60) m++;
		system("cls"); printf(" vreme: %.2d:%.2d      bodovi:%3d\n", m, s, n-5);
		if(zmija(z, p, &n, key, zid)) polje(p);
		/* KRAJ */
		else {
			polje(p);
			for(i = 0; i < VIS; i++) free(p[i]);
			free(p);
			for(i = 0; i < n; i++) free(z[i]);
			free(z);
			printf("%c%c%c\nIzgubili ste. Pritisnite SPACE da nastavite.", 7, 7, 7);
			while(getch() != 32);
			key = i = 1;
			system("cls");
			printf("Ugasiti igricu?\n\n  > Ne    Da\n");
			while(key != 13) if(kbhit()) {
				key = getch();
				if(key == 75 || key == 100) i++;
				if(key == 77 || key == 97) i--;
				if(i%2) {
					system("cls");
					printf("Ugasiti igricu?\n\n  > Ne    Da\n");
				}
				else {
					system("cls");
					printf("Ugasiti igricu?\n\n    Ne  > Da\n");
				}
			}
			if(i%2) pocetak(tez, zid);
			else izlaz();
		}
	}
}

void cekaj(int sec) {
  clock_t end;

  end = clock() + sec*10;
  while (clock() < end);
}

int zmija(int **z, int **p, int *n, int key, int zid) {
	int i;

	for(i = *n-1; i > 0; i--) {
					z[i][0] = z[i-1][0];
					z[i][1] = z[i-1][1];
	}
	switch(key) {
	case 2:	z[0][1]++;
				if(z[0][1] > SIR - 2) {
					if(zid) {
						p[z[0][0]][z[0][1]] = 666;
						return 0;
					}
					else z[0][1] = 1;
				} break;
	case 1:	z[0][1]--;
				if(z[0][1] < 1) {
					if(zid) {
						p[z[0][0]][z[0][1]] = 666;
						return 0;
					}
					else z[0][1] = SIR-2;
				} break;
	case 3:	z[0][0]++;
				if(z[0][0] > VIS-2) {
					if(zid) {
						p[z[0][0]][z[0][1]] = 666;
						return 0;
					}
					else z[0][0] = 1;
				} break;
	case 4:	z[0][0]--;
				if(z[0][0] < 1) {
					if(zid) {
						p[z[0][0]][z[0][1]] = 666;
						return 0;
					}
					else z[0][0] = VIS-2;
				} break;
	}
	for(i = 1; i < *n-1; i++) p[z[i][0]][z[i][1]] = -1;
	p[z[*n-1][0]][z[*n-1][1]] = 0;
	if(p[z[0][0]][z[0][1]] < 0) {
		p[z[0][0]][z[0][1]] = 666;
		return 0;
	}
	for(i = 1; i < *n-1; i++) if((z[0][0] == z[i][0]) && (z[0][1] == z[i][1])) {
		p[z[0][0]][z[0][1]] = 666;
		return 0;
	}
	if(p[z[0][0]][z[0][1]] == 2) {
		(*n)++;
		p[z[0][0]][z[0][1]] = 1;
		jabuka(p);
	}
	else p[z[0][0]][z[0][1]] = 1;
	return 1;
}

void jabuka(int **p) {
	int a, b;
	a = rand() / ((double)RAND_MAX) * (VIS-1);
	b = rand() / ((double)RAND_MAX) * (SIR-1);
	while(p[a][b]) {
		a = rand() / ((double)RAND_MAX) * (VIS-1);
		b = rand() / ((double)RAND_MAX) * (SIR-1);
	}
	p[a][b] = 2;
}

void polje(int **p) {
	int i, j;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	WORD def;

	GetConsoleScreenBufferInfo(h, &csbi);
	def = csbi.wAttributes;
	for(i = 0; i < VIS; i++, printf("\n")) for(j = 0; j < SIR; j++) {
		if(p[i][j] == 0) printf(" "); //prazno
		if(p[i][j] == -1) { //telo
			SetConsoleTextAttribute (h, 2 | 8);
			printf("O");
		}
		if(p[i][j] == 1) { //glava
			SetConsoleTextAttribute (h, 6 | 8);
			printf("O");
		}
		if(p[i][j] == -2) { //zid
			SetConsoleTextAttribute (h, 8);
			printf("X");
		}
		if(p[i][j] == 2) { //jabuka
			SetConsoleTextAttribute (h, 4 | 8);
			printf("Q");
		}
		if(p[i][j] == 666) { //sudar
			SetConsoleTextAttribute (h, 4 | 8);
			printf("X");
		}
	}
	SetConsoleTextAttribute (h, def);
}

void izlaz() {
	int key = 0;

	system("cls");
	printf("Zmijica C\n        by Velibor Bacujkov 2012.\n\n\nPritisnite bilo koje dugme da izadjete.");
	while(!kbhit());
	exit(123);
}