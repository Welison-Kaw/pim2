#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<iostream>

using namespace std;

enum DOS_COLORS {
        BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
        LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
        LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE };

void gotoxy(int x, int y) { 
    COORD coord;
    coord.X = x; 
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textcolor (DOS_COLORS iColor) {
        HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
        bufferInfo.wAttributes &= 0x00F0;
        SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
}

void backcolor (DOS_COLORS iColor) {
        HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
        bufferInfo.wAttributes &= 0x000F;
        SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= (iColor << 4));
}

centraliza(int l, std::string s) {
	gotoxy((120-s.length())/2,l);
	std::cout << s;
}

tela (int v) {
	system("cls");
	
	gotoxy (57,2);
	//char numero = (char)v;

	std::cout << "Tela " << v+1;
	getch();
}

tela_menu(int menu) {
	//clrscr();
	system("cls");
	int linha;
	string item_menu[5] = {"Cadastrar Novo Cliente", "Visualizar Lista de Clientes", "Cadastrar Novo Veiculo", "Verificar Lista de Veiculos", "Sair"};
	
	// BRANCO
	textcolor(WHITE);
	
	centraliza(2, "ALUGUEL DE VEICULOS");
	
	linha = 6;
	
	for (int i=0; i<5; i++) {
		if (menu == i) {
			textcolor(LIGHT_RED);
		} else {
			textcolor(WHITE);
		}
		linha += 2;
		centraliza(linha, item_menu[i]);
	}
	
	unsigned char cIn;
	do {
		cIn = getch();
		switch ((int)cIn) {
			case 72:
				textcolor(WHITE);
				centraliza(8+menu*2, item_menu[menu]);
				if (menu == 0) {
					menu = 4;
				} else {
					menu--;
				}
				textcolor(LIGHT_RED);
				centraliza(8+menu*2, item_menu[menu]);
				break;
			case 80:
				textcolor(WHITE);
				centraliza(8+menu*2, item_menu[menu]);
				if (menu == 4) {
					menu = 0;
				} else {
					menu++;
				}
				textcolor(LIGHT_RED);
				centraliza(8+menu*2, item_menu[menu]);
				//std:cout << "DOWN";
				break;
		}
	} while ((int)cIn != 13);
	
	switch (menu) {
		case 4:
			break;
		default:
			tela(menu);
			tela_menu(menu);
	}
}

int main() {
	int menu = 4;
	printf("teste");
    tela_menu(menu);
    //getch();

	return 0;
}
