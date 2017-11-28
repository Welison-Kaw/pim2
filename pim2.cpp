#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<iostream>
#include<fstream>
#include<regex>
#include<vector>
#include<time.h>
#include<iomanip>

using namespace std;

const string tituloTexto = "LEGAL RENT A CARS"; // TITULO USADO PARA TODAS AS TELAS
const int tituloLinha = 2; // POSICAO ONDE SERA MOSTRADO O TITULO

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

/*
	FUNCAO GENERICA USADA PARA REPETIR UM CARACTER 
	ESPECIFICO NUM ESPACO RETANGULAR DETERMINADO
*/
void repeteChar(int x1, int y1, int x2, int y2, char c) {
	for (int i=x1;i<x2+1;i++) {
		for (int j=y1;j<y2+1;j++) {
			gotoxy(i,j);
			cout << c;
		}
	}
}

/*
	FUNCAO USADA PARA RETONAR UMA POSICAO ESPECIFICA
	DA LINHA OBTIDA NOS ARQUIVOS DE TEXTO
*/
string retornaLinhaPos(string linha, int pos) {
	int cont = 0, npos=0, nposAnt=0;
	
	/* APOS PEGAR A PRIMEIRA POSICAO, O MESMO 
	PROCEDIMENTO O REPETIDO ATE ENCONTRAR A POSICAO DESEJADA */
	npos = linha.find(';',0);
	for (int i=0;i<pos;i++) {
		nposAnt = npos;
		npos = linha.find(';',npos+1);
	}
	
	/* RETORNA O TRECHO DA STRING QUE FOI REQUISITADA */
	return linha.substr(nposAnt+1, npos-nposAnt-1);
}

/*
	CENTRALIZA UMA STRING NUMA LINHA ESPECIFICA DA TELA
*/
void centraliza(int l, string s) {
	gotoxy((80-s.length())/2,l);
	cout << s;
}

/*
	CRIA BORDAS DE UM RETANGULO
*/
void borda (int xa, int ya, int xb, int yb, int tipo) {
	int bordaSimples[6] = {218,191,192,217,196,179}; // CODIGO ASCII DOS CARACTERES DE LINHA SIMPLES 
	int bordaDupla[6] = {201,187,200,188,205,186};   // CODIGO ASCII DOS CARACTERES DE LINHA DUPLA
	int bordaTipo[6];
	
	/* VERIFICA-SE QUAL O TIPO DE BORDA SERA UTILIZADA,
	ENTAO O ARRAY ESPECIFICO E COPIADO PARA O QUE SERA 
	UTILIZADO NO RESTANTE DA FUNCAO COMO PADRAO */
	if (tipo == 1) {
		memcpy(bordaTipo, bordaSimples, sizeof(bordaTipo));
	} else {
		memcpy(bordaTipo, bordaDupla, sizeof(bordaTipo));
	}
	
	/* CRIA OS CANTOS DO RETANGULO*/
	gotoxy(xa, ya);
	cout << char(bordaTipo[0]);
	gotoxy(xb, ya);
	cout << char(bordaTipo[1]);
	gotoxy(xa, yb);
	cout << char(bordaTipo[2]);
	gotoxy(xb, yb);
	cout << char(bordaTipo[3]);
	
	/* REPETE O CHAR DAS AREAS LATERAIS DO RETANGULO */
	repeteChar(xa,ya+1,xa,yb-1,char(bordaTipo[5]));
	repeteChar(xb,ya+1,xb,yb-1,char(bordaTipo[5]));
	repeteChar(xa+1,ya,xb-1,ya,char(bordaTipo[4]));
	repeteChar(xa+1,yb,xb-1,yb,char(bordaTipo[4]));
}

/*
	MOSTRA A DIFERENCA EM HORAS ENTRE DUAS DATAS
*/
int diferencaHoras (string d1, string d2) {
	time_t t1, t2, rawtime;
	/* CRIA AS ESTRUTURAS COM DAS DATAS (HORA, DIA, MES E ANO) */
	struct tm timeD1 = {0, 0, stoi(d1.substr(8,2)), stoi(d1.substr(6,2)), stoi(d1.substr(4,2))-1, stoi(d1.substr(0,4))-1900};
	struct tm timeD2 = {0, 0, stoi(d2.substr(8,2)), stoi(d2.substr(6,2)), stoi(d2.substr(4,2))-1, stoi(d2.substr(0,4))-1900};
	
	/* CRIA AS DUAS VARIAVEIS DE TEMPO QUE SERAO COMPARADAS */
	t1 = mktime(&timeD1);
	t2 = mktime(&timeD2);

	/* O RETORNO DA FUNCAO SE DA EM SEGUNDOS,
	ENTAO DIVIDE-SE POR SEGUNDOS E MINUTOS (60 * 60) */
	return difftime(t2, t1) / (60*60);
}

/*
	FORMATA A DATA DE MODO QUE SEJA MOSTRADA PARA O USUARIO
	OU PARA ESCREVER EM ARQUIVO
*/
string formataData(string d, int tipo = 0, int hora = 0) {
	string aux;
	/* TIPO = 0 - A DATA ESTA NO FORMATO YYYYMMDDHH E SERA FORMATADA PARA O FORMATO DD/MM/YYYY */
	if (tipo == 0){
		aux = d.substr(6,2) + '/' + d.substr(4,2) + '/' + d.substr(0,4);
		/* CASO SEJA ESPECIFICADO, ADICIONA-SE A HORA */
		if (hora == 1)
			aux += ' ' + d.substr(8,2) + ":00";
	} else {
		/* TIPO <> 0 - A DATA ESTA NO FORMATO DD/MM/YYYY E SERA FORMATADA PARA O FORMATO YYYYMMDD */
		aux = d.substr(6,4) + d.substr(3,2) + d.substr(0,2);
	}
	
	return aux;
}

std::string validaEntrada(int tipo, int x, int y) {
	/*	
		TIPO
		1 - APENAS NUMEROS
		2 - APENAS LETRAS, ESPACOS E APOSTROFE
		3 - NUMEROS E BARRAS (DATA)
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
			case 3:
				match = ("[0-9/]");
				break;
			default:
				match = ("[0-9a-zA-Z' ]");
				break;
		}

		if (std::regex_match(string(1,cIn), match) or (int)cIn == 8) {
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

/* ESCREVE O TITULO NA LINHA ESPECIFICADA NAS CONTANTES*/
void titulo() {
	centraliza(tituloLinha, tituloTexto);
	borda((80-tituloTexto.length())/2-2,tituloLinha-1,(80-tituloTexto.length())/2+tituloTexto.length()+1,tituloLinha+1,1);
}

/*	
	FUNCAO QUE CRIA A TELA DE CADASTRO DE CLIENTES
*/

void telaCadastroClientes() {
	system("cls"); // LIMPA A TELA
	int l = 7;
	bool salvar;
	
	/*STRUCT COM OS DADOS DO CLIENTE */
	struct cadastroCliente {
		std::string nome;
		std::string rg;
		std::string cpf;
		std::string habilitacao;
		std::string nascimento;
		std::string ong;
	};
	struct cadastroCliente cliente;
	
	/* 	MUDA A COR DAS LETRAS PARA BRANCO
		POSICIONA O TITULO
		CRIA BORDA DUPLA EM TODA A TELA */	
	textcolor(WHITE);
	titulo();
	borda(0,0,79,24,2);
	
	/*	POSICIONA SUBTITULO
		CRIA BORDA SIMPLES NA AREA DA TELA DESTINADA AO CONTEUDO */
	centraliza(l-2, "Cadastro de Clientes");
	borda(2,l-1,77,23,1);

	/*	CRIA ARRAY COM OS NOMES DOS CAMPOS
		MUDA A COR DAS LETRAS PARA VERMELHO
		POSICIONA OS CAMPOS NA TELA */
	std::string item_cad[6] = {"Nome/Razao Social:", "RG:", "CPF/CNPJ:", "Habilitacao:", "Nascimento:", "ONG:"};
	
	textcolor(LIGHT_RED);
	
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

	/*	PERGUNTA SE DESEJA SALVAR E MOSTRA OPCAO DE SIM/NAO */
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

	/*	CAPTURA TECLA DO USUARIO
		ESQUERDA - SELECIONA "SIM"
		DIREITA - SELECIONA "NAO" */
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
	
	/* CASO O USUARIO ESCOLHA SALVAR */
	if (salvar) {
		/* SALVAR ARQUIVO  */
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

/*	FUNCAO QUE CRIA A TELA QUE LISTA OS CLIENTES CADASTRADOS */
void telaListaClientes() {
	system("cls"); // LIMPA A TELA
	
	string linha;
	ifstream arquivoCliente("clientes.dat"); // ARQUIVO QUE SERA LIDO
	int posicao = 0;
	int tamanhoColuna[] = {25,12,14,8,7};
	int l, campo;
	
	/* 	MUDA A COR DAS LETRAS PARA BRANCO
		POSICIONA O TITULO
		CRIA BORDA DUPLA EM TODA A TELA */	
	textcolor(WHITE);
	titulo();
	borda(0,0,79,24,2);
	
	if (arquivoCliente.is_open()) { // ABRE ARQUIVO PARA INICIAR A LEITURA
		l = 7; // LINHA INICIAL QUE COMECARA A SER ESCRITO
		/*	ESCREVE O SUBTITULO CENTRALIZADO
			CRIA UMA BORDA SIMPLES NA AREA A SER ESCRITA
			POSICIONA PARA O INICIO DA ESCRITA */
		centraliza(l-2,"Lista de Clientes"); 
		borda(2,l-1,77,23,1);
		gotoxy(5,l);
		
		while (getline(arquivoCliente, linha)) {
			/*	VERIFICA O PRIMEIRO CARACTER DA LINHA A COLORE A COR DE MODO ESPECIFICO
				F - TITULO
				0 - CLIENTE ATIVO 
				1 - CLIENTE INATIVO */
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
			
			campo = 0;
			for(std::string::size_type i = 0; i < linha.size(); ++i) {
				if (posicao > 0 && linha[i] != ';') {
					cout << linha[i];
				} else {
					if (linha[i] == ';')
						campo++;
				}
				if (posicao > 1 && linha[i] == ';') {
					for (int j=posicao;j<=tamanhoColuna[campo-2];j++) {
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
		arquivoCliente.close(); // FECHA O ARQUIVO
	} else {
		cout << "Nao foi possivel abrir o arquivo";
	}
	
	getch(); // ESPERA O USUARIO APERTAR QUALQUER TECLA
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
	
	std::string item_cad[4] = {"Placa:", "Modelo:", "Marca:", "Diaria:"};
	
	struct clienteVeiculo {
		string placa;
		string modelo;
		string marca;
		int diaria;
		//int km;
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
	++l;
	gotoxy(5,++l);
	cout << item_cad[3];
	
	/*++l;
	gotoxy(5,++l);
	cout << item_cad[4];*/
	
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
	++l;

	gotoxy(item_cad[3].length()+6, ++l);
	veiculo.diaria = 0;
	getch();
	++l;

	/*gotoxy(item_cad[4].length()+6, ++l);
	veiculo.km = 0;
	getch();*/
	
	l += 2;
	
	centraliza(l++, "Deseja salvar o veiculo?");
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
		// SALVAR ARQUIVO DO VEICULO
		ofstream arquivoVeiculo("veiculos.dat",ios::app);
		if (arquivoVeiculo.is_open()) {
			arquivoVeiculo << "0;";
			arquivoVeiculo << veiculo.placa << ';';
			arquivoVeiculo << veiculo.modelo << ';';
			arquivoVeiculo << veiculo.marca << ';';
			arquivoVeiculo << veiculo.diaria << ';';
			//arquivoVeiculo << veiculo.km << ';' << '\n';
			arquivoVeiculo.close();
		}
	}
	
	//getch();
}

void telaListaVeiculos() {
	system("cls");
	string linha;
	ifstream arquivoVeiculos("veiculos.dat");
	int tamanhoColuna[] = {9,10,14,10};
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

			cout << setw(tamanhoColuna[0]) << retornaLinhaPos(linha, 1); // PLACA
			cout << setw(tamanhoColuna[1]) << retornaLinhaPos(linha, 2); // MODELO
			cout << setw(tamanhoColuna[2]) << retornaLinhaPos(linha, 3); // MARCA
			if (linha[0] == 'F') {
				cout << setw(tamanhoColuna[3]) << retornaLinhaPos(linha, 4); // DIARIA
			} else {
				cout << setw(tamanhoColuna[3]) << stod(retornaLinhaPos(linha, 4)); // DIARIA
			}
		
			/*for(std::string::size_type i = 0; i < linha.size(); ++i) {
				if (campo <= 4) {
					if (posicao > 0 && linha[i] != ';') {
						cout << linha[i];
					} else {
						if (linha[i] == ';')
							campo++;
					}
					if (posicao > 1 && linha[i] == ';') {
						for (int j=posicao;j<=tamanhoColuna[campo-2];j++) {
							cout << ' ';
						}
						posicao = 1;
					}
					posicao++;
				}
			}*/
			
			if (linha[0] == 'F') {
				//cout << "  Cliente (CPF)";
				cout << "  Dt Devolucao";
			} else {
				if (linha[0] == '1') {
					//cout << retornaLinhaPos(linha, 5);
					cout << "  " << formataData(retornaLinhaPos(linha, 6), 0, 1);
				}
			}
			
			l++;
			gotoxy(5,l);
		}
		arquivoVeiculos.close();
	} else {
		cout << "Nao foi possivel abrir o arquivo";
	}
	
	getch();
}

void barraRolagem(int posicao) {
	int linha = 7;
	gotoxy(75,linha);
	cout << '-';

	for(int i=linha+1;i<22;i++){
		gotoxy(75,i);
		cout << char(179);
	}

	gotoxy(75,22);
	cout << '-';
	
	gotoxy(75,posicao);
	cout << char(219);
}

void alteraArquivoVeiculo(string placa, string cliente = "", string retorno = "", string dtLocacao = "") {
	ifstream filein("veiculos.dat");
	ofstream fileout("temp.dat");
	string linha;
	
	while (filein >> linha) {
		if (linha.substr(2,linha.find(';',2)-2) == placa) {
			if (cliente == "") {
				linha[0] = '0';
				linha = linha.substr(0,linha.rfind(';',linha.rfind(';',linha.rfind(';')-1)-1)+1);
			} else {
				linha[0] = '1';
				linha = linha + cliente + ';' + retorno + ';' + dtLocacao;
			}
			fileout << linha << '\n';
		} else {
			fileout << linha << '\n';
		}
	}
	
	filein.close();
	fileout.close();
	
	remove("veiculos.dat");
	rename("temp.dat", "veiculos.dat");
}

void telaLocacao() {
	system("cls");
	int l = 7, i, aux, qtde;
	string linha, dtLocacao, hrLocacao, dthrSistema;
	bool salvar;
	int veiculoEscolhido, clienteEscolhido;
	unsigned char cIn;
	
	struct sCliente {
		string nome;
		string cpf;
	};
	
	struct sVeiculo {
		string placa;
		string modelo;
		string marca;
	};
	
	vector<sCliente> cliente;
	vector<sVeiculo> veiculo;

	textcolor(WHITE);
	titulo();
    borda(0,0,79,24,2);
    
    borda(2,l-1,77,23,1);
    
	centraliza(l-2,"Locacao de Veiculos");
	
	/* ESCOLHA CLIENTE */
	
	ifstream arquivoClientes("clientes.dat");
	
	qtde = 0;
	gotoxy(0,1);
	if (arquivoClientes.is_open()) {
		while (getline(arquivoClientes, linha)) {
			if (linha[0] == '0') {
				cliente.push_back(sCliente());
				cliente[cliente.size()-1].nome = retornaLinhaPos(linha, 1);
				cliente[cliente.size()-1].cpf = retornaLinhaPos(linha, 3);
				qtde++;
			}
		}
		arquivoClientes.close();
	}
	
	aux = 0;
	
	if (qtde != 1)
		barraRolagem(((13*(aux*100)/(qtde-1))/100)+8);

	gotoxy(5, l+1);
	textcolor(LIGHT_RED);
	cout << "Nome: ";
	textcolor(WHITE);	
	cout << cliente[aux].nome << '\n';
	gotoxy(5, l+2);
	textcolor(LIGHT_RED);
	cout << "CPF/CNPJ: ";
	textcolor(WHITE);	
	cout << cliente[aux].cpf << '\n';
	
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
		
		repeteChar(5,l+1,74,l+2,' ');
		
		gotoxy(5, l+1);
		textcolor(LIGHT_RED);
		cout << "Nome: ";
		textcolor(WHITE);	
		cout << cliente[aux].nome << '\n';
		gotoxy(5, l+2);
		textcolor(LIGHT_RED);
		cout << "CPF/CNPJ: ";
		textcolor(WHITE);	
		cout << cliente[aux].cpf << '\n';
		
		if (qtde != 1)
			barraRolagem(((13*(aux*100)/(qtde-1))/100)+8);

	} while ((int)cIn != 13);
	
	clienteEscolhido = aux;
	
	/* ESCOLHE VEICULO */
	/* SELECIONA DATA DE ENTREGA */
	
	ifstream arquivoVeiculos("veiculos.dat");

	qtde = 0;
	gotoxy(0,l);
	if (arquivoVeiculos.is_open()) {
		while (getline(arquivoVeiculos, linha)) {
			if (linha[0] == '0'){
				veiculo.push_back(sVeiculo());
				
				veiculo[veiculo.size()-1].placa = retornaLinhaPos(linha, 1);
				veiculo[veiculo.size()-1].marca = retornaLinhaPos(linha, 2);
				veiculo[veiculo.size()-1].modelo = retornaLinhaPos(linha, 3);
				
				qtde++;
			}
		}
		arquivoVeiculos.close();
	}

	l+=3;
	
	aux = 0;

	if (qtde != 1)
		barraRolagem(((13*(aux*100)/(qtde-1))/100)+8);

	gotoxy(5, l+1);
	textcolor(LIGHT_RED);
	cout << "Placa: ";
	textcolor(WHITE);
	cout << veiculo[aux].placa << '\n';
	gotoxy(5, l+2);
	textcolor(LIGHT_RED);
	cout << "Modelo: ";
	textcolor(WHITE);
	cout << veiculo[aux].modelo << '\n';
	gotoxy(5, l+3);
	textcolor(LIGHT_RED);
	cout << "Marca: ";
	textcolor(WHITE);
	cout << veiculo[aux].marca << '\n';

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
		
		repeteChar(5,l+1,74,l+3,' ');
		
		gotoxy(5, l+1);
		textcolor(LIGHT_RED);
		cout << "Placa: ";
		textcolor(WHITE);
		cout << veiculo[aux].placa << '\n';
		gotoxy(5, l+2);
		textcolor(LIGHT_RED);
		cout << "Modelo: ";
		textcolor(WHITE);
		cout << veiculo[aux].modelo << '\n';
		gotoxy(5, l+3);
		textcolor(LIGHT_RED);
		cout << "Marca: ";
		textcolor(WHITE);
		cout << veiculo[aux].marca << '\n';
		
		if (qtde != 1)
			barraRolagem(((13*(aux*100)/(qtde-1))/100)+8);
		
	} while ((int)cIn != 13);
	
	veiculoEscolhido = aux;
	
	l+=3;
	gotoxy(5,l+2);
	textcolor(LIGHT_RED);
	cout << "Data de Devolucao (DD/MM/YYYY): ";
	textcolor(WHITE);
	cin >> dtLocacao;
	
	gotoxy(5,l+3);
	textcolor(LIGHT_RED);
	cout << "Hora de Devolucao (HH): ";
	textcolor(WHITE);
	cin >> hrLocacao;

	dtLocacao = formataData(dtLocacao,1) + hrLocacao;

	l += 5;
	
	centraliza(l++, "Deseja alugar o veiculo?");
	l++;
	
	gotoxy(34, l);
	cout << "Sim";
	gotoxy(42, l);
	textcolor(LIGHT_RED);
	cout << "Nao";
	textcolor(WHITE);
	borda(40,l-1,46,l+1,1);
	salvar = false;
	
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
		repeteChar(4,7,75,22,' ');
		
		centraliza(8, "RECIBO");
		borda((80-6)/2-2,7,(80-6)/2+6+1,9,1);
		
		l=11;
		gotoxy(5,l++);
		textcolor(LIGHT_RED);
		cout << "Hora da Locacao: ";
		textcolor(WHITE);

    	time_t t = time(0);
    	struct tm * now = localtime( & t );
    	cout	<< (now->tm_mday) << '/'
				<< (now->tm_mon + 1) << '/'
				<< (now->tm_year + 1900) << ' '
				<< (now->tm_hour) << ':'
				<< (now->tm_min) << ':'
				<< (now->tm_sec)
				<< endl;
				
		dthrSistema = to_string(now->tm_year + 1900) + to_string(now->tm_mon + 1) + to_string(now->tm_mday) + to_string(now->tm_hour);

		textcolor(LIGHT_RED);
		gotoxy(5,l++);
		cout << "Placa: ";
		textcolor(WHITE);
		cout << veiculo[veiculoEscolhido].placa;
		l++;
		
		textcolor(LIGHT_RED);
		gotoxy(5,l++);
		cout << "Cliente: ";
		textcolor(WHITE);
		cout << cliente[clienteEscolhido].nome;

		textcolor(LIGHT_RED);
		gotoxy(5,l++);
		cout << "CPF: ";
		textcolor(WHITE);
		cout << cliente[clienteEscolhido].cpf;
		l++;

		textcolor(LIGHT_RED);
		gotoxy(5,l++);
		cout << "Data de Devolucao: ";
		textcolor(WHITE);
		cout << formataData(dtLocacao, 0, 1);
		l++;
		
		alteraArquivoVeiculo(veiculo[veiculoEscolhido].placa, cliente[clienteEscolhido].cpf, dtLocacao, dthrSistema);

		getch();
	}
}

void telaDevolucao() {
	system("cls");
	int l = 7;
	int aux, qtde;
	string linha, dtDevolucao, dtAux;
	unsigned char cIn;	
	int veiculoEscolhido, periodo, atraso;
	int horaDevolucao;
	double totalFinal = 0;
	
	bool idoso, ong;
	
	struct sVeiculo {
		string placa;
		string modelo;
		string marca;
		string diaria;
		
		string cliente;
		string devolucao;
		string dtLocacao;
	};
	
	vector<sVeiculo> veiculo;
	
	textcolor(WHITE);
	titulo();
    borda(0,0,79,24,2);
    
    borda(2,l-1,77,23,1);
    
	centraliza(l-2,"Devolucao de Veiculos");
	
	ifstream arquivoVeiculos("veiculos.dat");
	ifstream arquivoClientes("clientes.dat");

	qtde = 0;
	if (arquivoVeiculos.is_open()) {
		while (getline(arquivoVeiculos, linha)) {
			if (linha[0] == '1'){
				veiculo.push_back(sVeiculo());

				veiculo[veiculo.size()-1].placa = retornaLinhaPos(linha, 1);
				veiculo[veiculo.size()-1].marca = retornaLinhaPos(linha, 2);
				veiculo[veiculo.size()-1].modelo = retornaLinhaPos(linha, 3);
				veiculo[veiculo.size()-1].diaria = retornaLinhaPos(linha, 4);
				veiculo[veiculo.size()-1].cliente = retornaLinhaPos(linha, 5);
				veiculo[veiculo.size()-1].devolucao = retornaLinhaPos(linha, 6);
				veiculo[veiculo.size()-1].dtLocacao = retornaLinhaPos(linha, 7);
				
				qtde++;
			}
		}
		arquivoVeiculos.close();
	}
	
	if (qtde == 0) {
		centraliza(14, "Sem veiculos para devolucao!");
		getch();
		return;
	}

	aux = 0;

	if (qtde != 1)
		barraRolagem(((13*(aux*100)/(qtde-1))/100)+8);

	gotoxy(5, l+1);
	textcolor(LIGHT_RED);
	cout << "Placa: ";
	textcolor(WHITE);
	cout << veiculo[aux].placa << '\n';
	
	gotoxy(5, l+2);
	textcolor(LIGHT_RED);
	cout << "Modelo: ";
	textcolor(WHITE);
	cout << veiculo[aux].modelo << '\n';
	
	gotoxy(5, l+3);
	textcolor(LIGHT_RED);
	cout << "Marca: ";
	textcolor(WHITE);
	cout << veiculo[aux].marca << '\n';

	gotoxy(5, l+4);
	textcolor(LIGHT_RED);
	cout << "Diaria: ";
	textcolor(WHITE);
	cout << veiculo[aux].diaria << '\n';
	
	gotoxy(5, l+5);
	textcolor(LIGHT_RED);
	cout << "CPF do Cliente: ";
	textcolor(WHITE);
	cout << veiculo[aux].cliente << '\n';

	gotoxy(5, l+6);
	textcolor(LIGHT_RED);
	cout << "Data de Locacao: ";
	textcolor(WHITE);
	cout << formataData(veiculo[aux].dtLocacao, 0, 1) << '\n';

	gotoxy(5, l+7);
	textcolor(LIGHT_RED);
	cout << "Devolucao: ";
	textcolor(WHITE);
	cout << formataData(veiculo[aux].devolucao, 0, 1) << '\n';
	
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
		
		repeteChar(5,l+1,74,l+3,' ');
		
		gotoxy(5, l+1);
		textcolor(LIGHT_RED);
		cout << "Placa: ";
		textcolor(WHITE);
		cout << veiculo[aux].placa << '\n';
		
		gotoxy(5, l+2);
		textcolor(LIGHT_RED);
		cout << "Modelo: ";
		textcolor(WHITE);
		cout << veiculo[aux].modelo << '\n';
		
		gotoxy(5, l+3);
		textcolor(LIGHT_RED);
		cout << "Marca: ";
		textcolor(WHITE);
		cout << veiculo[aux].marca << '\n';

		gotoxy(5, l+4);
		textcolor(LIGHT_RED);
		cout << "Diaria: ";
		textcolor(WHITE);
		cout << veiculo[aux].diaria << '\n';

		gotoxy(5, l+5);
		textcolor(LIGHT_RED);
		cout << "CPF do Cliente: ";
		textcolor(WHITE);
		cout << veiculo[aux].cliente << '\n';
	
		gotoxy(5, l+6);
		textcolor(LIGHT_RED);
		cout << "Data de Locacao: ";
		textcolor(WHITE);
		cout << formataData(veiculo[aux].dtLocacao, 0, 1) << '\n';

		gotoxy(5, l+7);
		textcolor(LIGHT_RED);
		cout << "Devolucao: ";
		textcolor(WHITE);
		cout << formataData(veiculo[aux].devolucao, 0, 1) << '\n';
		
		if (qtde != 1)
			barraRolagem(((13*(aux*100)/(qtde-1))/100)+8);
		
	} while ((int)cIn != 13);
	
	veiculoEscolhido = aux;
	
	l+=8;
	gotoxy(5,l++);
	textcolor(LIGHT_RED);
	cout << "Devolvido em (DD/MM/YYYY): ";
	textcolor(WHITE);
	cin >> dtDevolucao;

	gotoxy(5,l++);
	textcolor(LIGHT_RED);
	cout << "Hora da Devolucacao(HH): ";
	textcolor(WHITE);
	cin >> horaDevolucao;
	
	dtDevolucao = formataData(dtDevolucao,1) + to_string(horaDevolucao);
	
	atraso = diferencaHoras(veiculo[veiculoEscolhido].devolucao,dtDevolucao);
	
	if (arquivoClientes.is_open()) {
		while (getline(arquivoClientes, linha)) {
			if (retornaLinhaPos(linha, 3) == veiculo[veiculoEscolhido].cliente) {
				idoso = (retornaLinhaPos(linha, 4) == "Sim") ? true : false;
				ong = (retornaLinhaPos(linha, 5) == "Sim") ? true : false;
			}
		}
		arquivoClientes.close();
	}
	
	repeteChar(4,7,75,22,' ');
	
	l=7;
	
	textcolor(LIGHT_GREEN);
	centraliza(l, "Total a Pagar");
	//borda(31,l-1,47,l+1,1);
	
	l+=2;
	
	dtAux = veiculo[veiculoEscolhido].devolucao;
	periodo = diferencaHoras(veiculo[veiculoEscolhido].dtLocacao, dtAux);
	
	gotoxy(5,l++);
	textcolor(LIGHT_RED);
	cout << "Periodo de Locacao: ";
	textcolor(WHITE);

	cout << formataData(veiculo[veiculoEscolhido].dtLocacao, 0, 1) << " - " << formataData(veiculo[veiculoEscolhido].devolucao, 0, 1) ;
	
	gotoxy(5,l++);
	textcolor(LIGHT_RED);
	cout << "Diaria: ";
	textcolor(WHITE);
	cout << stod(veiculo[veiculoEscolhido].diaria);
	
	gotoxy(5,l++);
	textcolor(LIGHT_RED);
	cout << "Total Parcial: ";
	textcolor(WHITE);
	totalFinal = (stod(veiculo[veiculoEscolhido].diaria) / 24) * periodo;
	cout << totalFinal;
	
	atraso = diferencaHoras(veiculo[veiculoEscolhido].devolucao, dtDevolucao);
	
	gotoxy(0,0);
	cout << veiculo[veiculoEscolhido].dtLocacao << endl << dtDevolucao << endl;
	
	if (atraso > 0) {
		l++;
		gotoxy(5,l++);
		textcolor(LIGHT_RED);
		cout << "Multas";
		gotoxy(5,l++);
		textcolor(WHITE);
		totalFinal += (stoi(veiculo[veiculoEscolhido].diaria)/24*atraso);
		cout << (stod(veiculo[veiculoEscolhido].diaria)/24*atraso) << " (" << atraso << " horas de traso na devolucao)";
	}
	
	l++;
	
	if (idoso or ong) {
		gotoxy(5,l++);
		textcolor(LIGHT_RED);
		cout << "Descontos";
		
		textcolor(WHITE);
		if (idoso) {
			gotoxy(5,l++);
			cout << "Idoso: 10%";
			totalFinal *= 0.9;
		}
		if (ong) {
			gotoxy(5,l++);
			cout << "Pareceiro da ONG: 5%";
			totalFinal *= 0.95;
		}
	}

	l++;
	gotoxy(5,l++);
	textcolor(LIGHT_RED);
	cout << "Total Final: ";
	textcolor(LIGHT_GREEN);
	cout << totalFinal;
	
	alteraArquivoVeiculo(veiculo[veiculoEscolhido].placa);
	
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
	
	/* DEFINE A PRECISAO FIXA DE 2 CASAS DECIMAIS PARA VARIAVEIS DO TIPO */
	cout << fixed << setprecision(2);

	telaMenu(menu);
    
	/*std::string nome;
    
    nome = validaEntrada(3,0,10);
    
    gotoxy(1,1);
    cout << nome;*/

	return 0;
}
