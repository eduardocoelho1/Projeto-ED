/* Equipe:
 * Estevão Augusto da Fonseca Santos
 * Felipe Geraldo de Oliveira
 * Eduardo Cesar Cauduro Coelho
 */


#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

struct call991{
	int e;
	int id;//atributo secundario
	float lat, lng, zip;
	char addr[150]; //atributo primario
	char desc[150], title[150];
	char timeStamp[20], twp[150];
	
};


void converter(){ //Convertera dados do arquivo .csv em arquivo binario
	string arquivo;
	cout << "Digite o nome do arquivo: ";
	cin >> arquivo;
	ifstream ler(arquivo);
	if(ler){ // a conversao só ocorrera se o arquivo .csv existir
		cout << "Arquivo encontrado" << endl;
		call991 c1;
		fstream escrever("binario.dat", ios::out|ios::binary); 
		string lixo;
		char auxiliar;
		ler >> lixo;
		while(ler >> c1.id){ //lera todos os dados do arquivo .csv. 
			//   A razão de ser ler >> c1.id se deve ao fato de que o id é o primeiro atributo que será lido, 
			//   isso significa que se ele estiver presente, então a linha toda possui os outros atributos.
			ler >> auxiliar;
			ler >> c1.lat;
			ler >> auxiliar;
			ler >> c1.lng;
			ler >> auxiliar;
			ler.getline(c1.desc, 150, ',');
			ler >> c1.zip;
			ler >> auxiliar;
			ler.getline(c1.title, 150, ','); 
			ler.getline(c1.timeStamp, 20, ',');
			ler.getline(c1.twp, 150, ',');
			ler.getline(c1.addr, 150, ',');
			ler >> c1.e;
			escrever.write((const char *) &c1, sizeof(call991)); //escreve os dados obtidos no arquivo binario. 
			//Funciona que nem o ofstream num arquivo de texto, com a exceção de estar usando um conjunto de bytes.
		}
		cout << "Conversao concluida!" << endl << endl;
		escrever.close();
	} else {
		cout << "Arquivo nao encontrado!" << endl << endl;
	}
	ler.close();
}

int main()
{
	char comando = '1';
	
	do{
		cout << "#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=" << endl;
		cout << "      Conversor de arquivo CSV para Binario" << endl;
		cout << "#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=" << endl << endl;
		
		cout << "1) Converter arquivo CSV" << endl;
		cout << "0) Sair" << endl << endl;
	
		cout << "#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=" << endl;
		cout << "Sua resposta: ";
		cin >> comando;
		cout << endl;
	
		switch(comando){
			case '1':
				converter();
				break;
			case '0':
				break;
			default:
				cout << "Opcao inexistente" << endl;
		}
	}while(comando != '0');
	
	return 0;
}
