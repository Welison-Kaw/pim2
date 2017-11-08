#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<iostream>
#include<fstream>
#include<regex>

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

std::string validaEntrada(int tipo, int x, int y) {
	/*	
		TIPO
		1 - APENAS NUMEROS
		2 - APENAS LETRAS, ESPACOS E APOSTROFE
		OUTROS - 1 e 2
	*/
	
	std::string n;
	n = "";
	
	unsigned char cIn;
	do {
		cIn = getch();
		
		std::regex match;
		switch (tipo) {
			case 1:
				match = ("[0-9]");
				break;
			case 2:
				match = ("[a-zA-Z' ]");
				break;
			default:
				match = ("[0-9a-zA-Z' ]");
				break;
		}

		if (std::regex_match(string(1,cIn), match) or (int)cIn == 8) {
			/*gotoxy(1,1);
			cout << (int)cIn;*/
			gotoxy(x,y);
	
			if ((int)cIn == 8) {
				if (n.length() > 0)
					n.pop_back();
				cout << n + ' ';
			} else {
				n += cIn;
				cout << n;
			}
		}
	} while ((n.length()) == 0 or ((int)cIn != 13));
	
	return n;
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
	
	struct cadastroCliente {
		std::string nome;
		std::string rg;
		std::string cpf;
		std::string habilitacao;
		std::string nascimento;
		std::string ong;
	};
	
	struct cadastroCliente cliente;
		
	textcolor(WHITE);
	titulo();
	borda(0,0,79,24,2);
	
	centraliza(l-2, "Cadastro de Clientes");
	
	borda(2,l-1,77,23,1);

	std::string item_cad[6] = {"Nome/Razao Social:", "RG:", "CPF/CNPJ:", "Habilitacao:", "Nascimento:", "ONG:"};
	
	textcolor(LIGHT_RED);
	/*for (int i=0; i<6; i++) {
		gotoxy(5,++l);
		++l;
		cout << item_cad[i];
	}*/
	
	gotoxy(5,++l);
	cout << item_cad[0];

	++l;
	gotoxy(5,++l);
	cout << item_cad[1];
	
	gotoxy(40,l);
	cout << item_cad[2];
	
	++l;
	gotoxy(5,++l);
	cout << item_cad[3];
	
	gotoxy(40,l);
	cout << item_cad[4];

	++l;
	gotoxy(5,++l);
	cout << item_cad[5];
	
	l = 7;

	textcolor(WHITE);
	
	char nn = '3';

	gotoxy(item_cad[0].length()+6, ++l);
	//nome = validaEntrada(2,item_cad[0].length()+6, l);
	cliente.nome = "NOME";

	l += 2;

	gotoxy(item_cad[1].length()+6, l);
	//rg = validaEntrada(1,item_cad[1].length()+6, l);
	cliente.rg = "RG";
	
	gotoxy(item_cad[2].length()+41, l);
	//cpf = validaEntrada(1,item_cad[2].length()+41, l);
	cliente.cpf = "CPF";
	
	l += 2;
	gotoxy(item_cad[3].length()+6, l);
	//habilitacao = validaEntrada(1,item_cad[3].length()+6, l);
	cliente.habilitacao = "HABILITACAO";

	gotoxy(item_cad[4].length()+41, l);
	//nascimento = validaEntrada(1,item_cad[4].length()+41, l);
	cliente.nascimento = "NASCIMENTO";
	
	l += 2;
	gotoxy(item_cad[5].length()+6, l);
	//ong = validaEntrada(3,item_cad[5].length()+6, l);
	cliente.ong = "ONG";
	
	l += 5;

	centraliza(l++, "Deseja salvar o usuario?");
	l++;

	gotoxy(34, l);
	cout << "Sim";
	gotoxy(42, l);
	textcolor(LIGHT_RED);
	cout << "Nao";
	textcolor(WHITE);
	borda(40,l-1,46,l+1,1);
	salvar = false;

	unsigned char cIn;
	do {
		cIn = getch();
		switch ((int)cIn) {
			case 75:
				textcolor(LIGHT_RED);
				gotoxy(34,l);
				cout << "Sim";
				textcolor(WHITE);
				gotoxy(42,l);
				cout << "Nao";
				
				textcolor(BLACK);
				borda(40,l-1,46,l+1,1);

				textcolor(WHITE);
				borda(32,l-1,38,l+1,1);
				
				salvar = true;
				break;
			case 77:
				textcolor(WHITE);
				gotoxy(34,l);
				cout << "Sim";
				textcolor(LIGHT_RED);
				gotoxy(42,l);
				cout << "Nao";

				textcolor(BLACK);
				borda(32,l-1,38,l+1,1);

				textcolor(WHITE);
				borda(40,l-1,46,l+1,1);

				salvar = false;
				break;
		}
	} while ((int)cIn != 13);
	
	if (salvar) {
		/* SALVAR ARQUIVO */
		ofstream arquivoCliente("clientes.dat",ios::app);
		if (arquivoCliente.is_open()) {
			arquivoCliente << "0;";
			arquivoCliente << cliente.nome << nn << ';';
			arquivoCliente << cliente.rg << nn << ';';
			arquivoCliente << cliente.cpf << nn << ';';
			arquivoCliente << cliente.habilitacao << nn << ';';
			arquivoCliente << cliente.nascimento << nn << ';';
			arquivoCliente << cliente.ong << nn << ';' << '\n';
			arquivoCliente.close();
		}
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
		cout << "Nao foi possivel abrir o arquivo";
	}
	
	getch();
}

void telaCadastroVeiculos() {
	system("cls");
	int l = 7;
	bool salvar;

	textcolor(WHITE);
	titulo();
    borda(0,0,79,24,2);
    
    borda(2,l-1,77,23,1);
    
	centraliza(l-2,"Cadastro de Veiculos");
	
	//F;Placa;Modelo;Marca;
	std::string item_cad[3] = {"Placa:", "Modelo:", "Marca:"};
	
	struct clienteVeiculo {
		std::string placa;
		std::string modelo;
		std::string marca;
	};
	
	struct clienteVeiculo veiculo;
	
	textcolor(LIGHT_RED);
	gotoxy(5,++l);
	cout << item_cad[0];
	++l;
	gotoxy(5,++l);
	cout << item_cad[1];
	++l;
	gotoxy(5,++l);
	cout << item_cad[2];
	
	textcolor(WHITE);
	
	l = 7;
	gotoxy(item_cad[0].length()+6, ++l);
	veiculo.placa = "";
	getch();
	++l;

	gotoxy(item_cad[1].length()+6, ++l);
	veiculo.modelo = "";
	getch();
	++l;
	
	gotoxy(item_cad[2].length()+6, ++l);
	veiculo.marca = "";
	getch();
	
	l += 2;
	
	centraliza(l++, "Deseja salvar o usuario?");
	l++;
	
	gotoxy(34, l);
	cout << "Sim";
	gotoxy(42, l);
	textcolor(LIGHT_RED);
	cout << "Nao";
	textcolor(WHITE);
	borda(40,l-1,46,l+1,1);
	salvar = false;
	
	unsigned char cIn;
	do {
		cIn = getch();
		switch ((int)cIn) {
			case 75:
				textcolor(LIGHT_RED);
				gotoxy(34,l);
				cout << "Sim";
				textcolor(WHITE);
				gotoxy(42,l);
				cout << "Nao";
				
				textcolor(BLACK);
				borda(40,l-1,46,l+1,1);

				textcolor(WHITE);
				borda(32,l-1,38,l+1,1);
				
				salvar = true;
				break;
			case 77:
				textcolor(WHITE);
				gotoxy(34,l);
				cout << "Sim";
				textcolor(LIGHT_RED);
				gotoxy(42,l);
				cout << "Nao";

				textcolor(BLACK);
				borda(32,l-1,38,l+1,1);

				textcolor(WHITE);
				borda(40,l-1,46,l+1,1);

				salvar = false;
				break;
		}
	} while ((int)cIn != 13);
	
	veiculo.placa = 'A';
	veiculo.modelo = 'B';
	veiculo.marca = 'C';
	
	if (salvar) {
		// SALVAR ARQUIVO DO VEÃƒÂCULO
		ofstream arquivoVeiculo("veiculos.dat",ios::app);
		if (arquivoVeiculo.is_open()) {
			arquivoVeiculo << "0;";
			arquivoVeiculo << veiculo.placa << ';';
			arquivoVeiculo << veiculo.modelo << ';';
			arquivoVeiculo << veiculo.marca << ';' << '\n';
			arquivoVeiculo.close();
		}
	}
	
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
			
			posicao = 0;
		}
		arquivoVeiculos.close();
	} else {
		cout << "Nao foi possivel abrir o arquivo";
	}
	
	getch();
}

void telaLocacao() {
	system("cls");
	int l = 7;
	int v1, v2, v3;
	int aux = 0, qtde = 0;
	int i;
	string linha;
	//bool salvar;

	textcolor(WHITE);
	titulo();
    borda(0,0,79,24,2);
    
    borda(2,l-1,77,23,1);
    
	centraliza(l-2,"Locacao de Veiculos");
	
	/* ESCOLHE VEICULO */
	/* SELECIONA DATA DE ENTREGA */
	
	ifstream arquivoVeiculos("veiculos.dat");

	gotoxy(0,l);
	if (arquivoVeiculos.is_open()) {
		while (getline(arquivoVeiculos, linha)) {
			if (linha[0] == '0')
				qtde++;
		}
		arquivoVeiculos.close();
	}

	string placa[qtde][3];

	arquivoVeiculos.clear();
	arquivoVeiculos.open("veiculos.dat");
	if (arquivoVeiculos.is_open()) {
		while (getline(arquivoVeiculos, linha)) {
			if (linha[0] == '0') {
				v1 = linha.find(';',2);
				v2 = linha.find(';',v1+1);
				v3 = linha.find(';',v2+1);
				//cout << linha.substr(2,linha.find(';',2)-2) << '\n';
				//cout << "1 - " << linha.substr(2, v1-2) << '\n';
				//cout << "2 - " << linha.substr(v1+1, v2-v1-1) << '\n';
				//cout << "3 - " << linha.substr(v2+1, v3-v2-1) << '\n';
				//cout << aux << linha[0] << '\n';
				placa[aux][0] = linha.substr(2, v1-2);
				placa[aux][1] = linha.substr(v1+1, v2-v1-1);
				placa[aux][2] = linha.substr(v2+1, v3-v2-1);
				aux++;
			}
		}
		arquivoVeiculos.close();
	}

	//cout << 'Carro:';
	
	//gotoxy(5, l+1);
	//cout << placa[1][0];
	
	cout << qtde;
	
	aux = 0;
		gotoxy(5, l+1);
		cout << placa[aux][0] << '\n';
		gotoxy(5, l+2);
		cout << placa[aux][1] << '\n';
		gotoxy(5, l+3);
		cout << placa[aux][2] << '\n';

		gotoxy(75,l);
		cout << '-';

		for(i=l+1;i<22;i++){
			gotoxy(75,i);
			cout << char(179);
		}
	
		gotoxy(75,22);
		cout << '-';
			
		gotoxy(75,((13*(aux*100)/(qtde-1))/100)+8);
		cout << char(219);

	unsigned char cIn;
	do {
		cIn = getch();
		switch ((int)cIn) {
			case 72:
				if (aux > 0)
					aux--;
				break;
			case 80:
				if (aux < qtde-1)
					aux++;
				break;
		}
		gotoxy(5, l+1);
		cout << placa[aux][0] << '\n';
		gotoxy(5, l+2);
		cout << placa[aux][1] << '\n';
		gotoxy(5, l+3);
		cout << placa[aux][2] << '\n';
		
		gotoxy(75,l);
		cout << '-';

		for(i=l+1;i<22;i++){
			gotoxy(75,i);
			cout << char(179);
		}
	
		gotoxy(75,22);
		cout << '-';
			
		gotoxy(75,((13*(aux*100)/(qtde-1))/100)+8);
		cout << char(219);

		gotoxy(5,l-1);
		cout << (aux*100)/(qtde-1) << ' ' << aux << ' ' << qtde-1;

	} while ((int)cIn != 13);
	
	getch();
}

void telaDevolucao() {
	system("cls");
	int l = 7;
	//bool salvar;

	textcolor(WHITE);
	titulo();
    borda(0,0,79,24,2);
    
    borda(2,l-1,77,23,1);
    
	centraliza(l-2,"Devolucao de Veiculos");
	
	getch();
}

void telaMenu(int menu) {
	system("cls");
	int linha;
	string itemMenu[7] = {"Cadastrar Novo Cliente", "Visualizar Lista de Clientes", "Cadastrar Novo Veiculo", "Verificar Lista de Veiculos", "Locacao", "Devolucao", "Sair"};
	
	// BRANCO
	textcolor(WHITE);
    borda(0,0,79,24,2);
	
	titulo();
	
	linha = 6;
	
	for (int i=0; i<7; i++) {
		if (menu == i) {
			textcolor(LIGHT_RED);
		} else {
			textcolor(WHITE);
		}
		linha += 2;
		centraliza(linha, itemMenu[i]);
	}
	
	unsigned char cIn;
	do {
		cIn = getch();
		switch ((int)cIn) {
			case 72:
				textcolor(WHITE);
				centraliza(8+menu*2, itemMenu[menu]);
				if (menu == 0) {
					menu = 6;
				} else {
					menu--;
				}
				textcolor(LIGHT_RED);
				centraliza(8+menu*2, itemMenu[menu]);
				break;
			case 80:
				textcolor(WHITE);
				centraliza(8+menu*2, itemMenu[menu]);
				if (menu == 6) {
					menu = 0;
				} else {
					menu++;
				}
				textcolor(LIGHT_RED);
				centraliza(8+menu*2, itemMenu[menu]);
				break;
		}
	} while ((int)cIn != 13);
	
	switch (menu) {
		case 0:
			telaCadastroClientes();
			telaMenu(menu);
			break;
		case 1:
			telaListaClientes();
			telaMenu(menu);
			break;
		case 2:
			telaCadastroVeiculos();
			telaMenu(menu);
			break;
		case 3:
			telaListaVeiculos();
			telaMenu(menu);
			break;
		case 4:
			telaLocacao();
			telaMenu(menu);
			break;
		case 5:
			telaDevolucao();
			telaMenu(menu);
			break;
		case 6:
			break;
	}
}

int main() {
	int menu = 6;
    telaMenu(menu);
    
	/*std::string nome;
    
    nome = validaEntrada(2,0,10);
    
    gotoxy(1,1);
    cout << nome;*/

	return 0;
}
