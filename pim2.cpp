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

void centraliza(int l, std::string s) {
	//gotoxy((120-s.length())/2,l);
	gotoxy((80-s.length())/2,l);
	std::cout << s;
}

void borda (int xa, int ya, int xb, int yb, int tipo) {
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

bool valida_entrada(std::string n) {
	/*if (n.length() > 0) {
		return true;
	} else {
		return false;
	}*/
	
	return true;
}

void titulo() {
	centraliza(tituloLinha, tituloTexto);
	//borda((120-tituloTexto.length())/2-2,tituloLinha-1,(120-tituloTexto.length())/2+tituloTexto.length()+1,tituloLinha+1,1);
	borda((80-tituloTexto.length())/2-2,tituloLinha-1,(80-tituloTexto.length())/2+tituloTexto.length()+1,tituloLinha+1,1);
}

/*void tela (int v) {
	system("cls");
	
	gotoxy (57,2);

	std::cout << "Tela " << v+1;
	getch();
}*/

void telaCadastroClientes() {
	system("cls");
	int l = 7;
	bool salvar;
	
	char nome[30];
	char rg[9];
	char cpf[14];
	char habilitacao[10];
	char nascimento[10];
	char ong[10];
	
	textcolor(WHITE);
	titulo();
	borda(0,0,79,24,2);
	
	centraliza(l-2, "Cadastro de Clientes");
	
	borda(2,l-1,77,23,1);

	std::string item_cad[6] = {"Nome/Razao Social:", "RG:", "CPF/CNPJ:", "Habilitacao:", "Nascimento:", "ONG:"};
	
	textcolor(LIGHT_RED);
	for (int i=0; i<6; i++) {
		gotoxy(5,++l);
		++l;
		cout << item_cad[i];
	}
	
	l = 7;

	textcolor(WHITE);
	gotoxy(item_cad[0].length()+6, ++l);

	/*   ~~~~~~~~~ TESTE OS DOIS ~~~~~~~~  */	
	/*nome = valida_entrada(nome);
	
	while (!valida_entrada(nome)) {
		scanf("%s", &nome);
	}*/
	
	++l;
	scanf("%s", &nome);
	gotoxy(item_cad[1].length()+6, ++l);
	++l;
	scanf("%s", &rg);
	gotoxy(item_cad[2].length()+6, ++l);
	++l;
	scanf("%s", &cpf);
	gotoxy(item_cad[3].length()+6, ++l);
	++l;
	scanf("%s", &habilitacao);
	gotoxy(item_cad[4].length()+6, ++l);
	++l;
	scanf("%s", &nascimento);
	gotoxy(item_cad[5].length()+6, ++l);
	++l;
	scanf("%s", &ong);
		
	l++;	
	//borda(20,l,60,l+4,1);
	
	centraliza(l++, "Deseja salvar o usuario?");
	//centraliza(++l, "Sim   Nao");

	gotoxy(35, l);
	cout << "Sim";
	gotoxy(41, l);
	textcolor(LIGHT_RED);
	cout << "Nao";
	salvar = false;

	unsigned char cIn;
	do {
		cIn = getch();
		switch ((int)cIn) {
			case 75:
				textcolor(LIGHT_RED);
				gotoxy(35,l);
				cout << "Sim";
				textcolor(WHITE);
				gotoxy(41,l);
				cout << "Nao";
				salvar = true;
				break;
			case 77:
				textcolor(WHITE);
				gotoxy(35,l);
				cout << "Sim";
				textcolor(LIGHT_RED);
				gotoxy(41,l);
				cout << "Nao";
				salvar = false;
				break;
		}
	} while ((int)cIn != 13);
	
	if (salvar) {
		/* SALVAR ARQUIVO */
	}
}

void telaListaClientes() {
	system("cls");
	
	string linha;
	ifstream arquivoCliente("clientes.dat");
	int posicao = 0;
	int tamanhoColuna = 12;
	int l;
	
	textcolor(WHITE);
	titulo();
	borda(0,0,79,24,2);
	l = 7;
	
	/*l=7;
	centraliza(l-2, "Cadastro de Clientes");*/
	
	if (arquivoCliente.is_open()) {
		l = 7;
		centraliza(l-2,"Lista de Clientes");
		borda(2,l-1,77,23,1);
		gotoxy(5,l);
		
		while (getline(arquivoCliente, linha)) {
			
			switch (linha[0]) {
				case '0':
					textcolor(WHITE);
					break;
				case '1':
					textcolor(LIGHT_RED);
					break;
				case 'F':
					textcolor(LIGHT_GREEN);
					break;
			}

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
			
			l++;
			gotoxy(5,l);
			
			posicao = 0;
		}
		arquivoCliente.close();
	} else {
		cout << "Não foi possível abrir o arquivo";
	}
	
	getch();
}

void telaCadastroVeiculos() {
	system("cls");
	int l = 7;

	textcolor(WHITE);
	titulo();
    borda(0,0,79,24,2);
    
    borda(2,l-1,77,23,1);
    
	centraliza(l-2,"Cadastro de Veiculos");

	getch();
}

void telaListaVeiculos() {
	system("cls");
	string linha;
	ifstream arquivoVeiculos("veiculos.dat");
	int posicao = 0;
	int tamanhoColuna = 15;
	int l;
	
	textcolor(WHITE);
	titulo();
    borda(0,0,79,24,2);
	
	if (arquivoVeiculos.is_open()) {
		l = 7;
		centraliza(l-2,"Listagem de Veiculos");
		borda(2,l-1,77,23,1);
		gotoxy(5,l);
		
		while (getline(arquivoVeiculos, linha)) {
			
			switch (linha[0]) {
				case '0':
					textcolor(WHITE);
					break;
				case '1':
					textcolor(LIGHT_RED);
					break;
				case 'F':
					textcolor(LIGHT_GREEN);
					break;
			}

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
			
			l++;
			gotoxy(5,l);
			
			//cout << '\n';
			posicao = 0;
		}
		arquivoVeiculos.close();
	} else {
		cout << "Não foi possível abrir o arquivo";
	}
	
	getch();
}

void tela_menu(int menu) {
	//clrscr();
	system("cls");
	int linha;
	string item_menu[6] = {"Cadastrar Novo Cliente", "Visualizar Lista de Clientes", "Cadastrar Novo Veiculo", "Verificar Lista de Veiculos", "Devolucao", "Sair"};
	
	// BRANCO
	textcolor(WHITE);
    borda(0,0,79,24,2);
	
	titulo();
	
	linha = 6;
	
	for (int i=0; i<6; i++) {
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
					menu = 5;
				} else {
					menu--;
				}
				textcolor(LIGHT_RED);
				centraliza(8+menu*2, item_menu[menu]);
				break;
			case 80:
				textcolor(WHITE);
				centraliza(8+menu*2, item_menu[menu]);
				if (menu == 5) {
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
		case 0:
			telaCadastroClientes();
			tela_menu(menu);
			break;
		case 1:
			telaListaClientes();
			tela_menu(menu);
			break;
		case 2:
			telaCadastroVeiculos();
			tela_menu(menu);
			break;
		case 3:
			telaListaVeiculos();
			tela_menu(menu);
			break;
		case 4:
			//
			tela_menu(menu);
			break;
		case 5:
			break;
	}
}

int main() {
	//int menu = 4;
	int menu = 0;
    tela_menu(menu);
    //getch();

	return 0;
}
