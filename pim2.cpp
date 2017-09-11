#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<iostream>
#include<fstream>

using namespace std;

const string tituloTexto = "LEGAL RENT A CARS";
const int tituloLinha = 2;

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

borda (int xa, int ya, int xb, int yb, int tipo) {
	int bordaSimples[6] = {218,191,192,217,196,179};
	int bordaDupla[6] = {201,187,200,188,205,186};
	int bordaTipo[6];
	
	if (tipo == 1) {
		memcpy(bordaTipo, bordaSimples, sizeof(bordaTipo));
	} else {
		memcpy(bordaTipo, bordaDupla, sizeof(bordaTipo));
	}
	
	gotoxy(xa, ya);
	cout << char(bordaTipo[0]);
	gotoxy(xb, ya);
	cout << char(bordaTipo[1]);
	gotoxy(xa, yb);
	cout << char(bordaTipo[2]);
	gotoxy(xb, yb);
	cout << char(bordaTipo[3]);
	
	int i;
	for(i=xa+1;i<xb;i++){
		gotoxy(i,ya);
		cout << char(bordaTipo[4]);
		gotoxy(i,yb);
		cout << char(bordaTipo[4]);
	}
	for(i=ya+1;i<yb;i++){
		gotoxy(xa,i);
		cout << char(bordaTipo[5]);
		gotoxy(xb,i);
		cout << char(bordaTipo[5]);
	}
}

titulo() {
	centraliza(tituloLinha, tituloTexto);
	borda((120-tituloTexto.length())/2-2,tituloLinha-1,(120-tituloTexto.length())/2+tituloTexto.length()+1,tituloLinha+1,1);
}

tela (int v) {
	system("cls");
	
	gotoxy (57,2);

	std::cout << "Tela " << v+1;
	getch();
}

telaListaVeiculos() {
	system("cls");
	string linha;
	ifstream arquivoVeiculos("veiculos.dat");
	int posicao = 0;
	int tamanhoColuna = 15;
	
	textcolor(WHITE);
	titulo();
	
	if (arquivoVeiculos.is_open()) {
		gotoxy(1,5);
		
		while (getline(arquivoVeiculos, linha)) {
			for(std::string::size_type i = 0; i < linha.size(); ++i) {
				if (posicao > 0 && linha[i] != ';') {
					cout << linha[i];
				}
				if (posicao > 1 && linha[i] == ';') {
					for (int i=posicao;i<=tamanhoColuna;i++) {
						cout << ' ';
					}
					posicao = 1;
				}
				posicao++;
			}
			cout << '\n';
			posicao = 0;
		}
		arquivoVeiculos.close();
	} else {
		cout << "Não foi possível abrir o arquivo";
	}
	getch();
}

tela_menu(int menu) {
	//clrscr();
	system("cls");
	int linha;
	string item_menu[5] = {"Cadastrar Novo Cliente", "Visualizar Lista de Clientes", "Cadastrar Novo Veiculo", "Verificar Lista de Veiculos", "Sair"};
	
	// BRANCO
	textcolor(WHITE);
	
	titulo();
	
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
				break;
		}
	} while ((int)cIn != 13);
	
	switch (menu) {
		case 3:
			telaListaVeiculos();
			tela_menu(menu);
			break;
		case 4:
			break;
		default:
			tela(menu);
			tela_menu(menu);
	}
}

int main() {
	int menu = 4;
    tela_menu(menu);
    //getch();

	return 0;
}

