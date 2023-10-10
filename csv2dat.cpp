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
	int e = -1;
	int id = -1;//atributo secundario
	float lat = -1, lng = -1, zip = -1;
	char addr[65] = "-1"; //atributo primario
	char desc[115] = "-1", title[45] = "-1";
	char timeStamp[40] = "-1", twp[60] = "-1";
	
	
	void imprimir();//imprimira todos os dados na ordem que foram lidos, isto eh como esta no arquivo.
};




//Id,lat,lng,desc,zip,title,timeStamp,twp,addr,e
void call991::imprimir(){
	cout << id << "  " << lat << "   " << lng << "   " << desc << "   " << 
	zip << "   " << title << "   " << timeStamp << "   " << twp << "   " << addr << "   " << e << endl;
}

void processamento(ifstream& ler, string arquivo){ 
	//aqui os dados serao lidos do arquivo CSV, e serão escritos no arquivo binario.
	
	call991 *c1 = new call991;
	unsigned int tam = 0;
	
	ofstream escrever("binario.dat", ios::binary);
	
	escrever.seekp(0, ios::end); //colocar a posicao de escrita
	tam = escrever.tellp()/sizeof(call991);
	escrever.seekp(0, ios::beg);
	
	string lixo;
	
	char auxiliar;
	unsigned int aux = 0;
	int cont = 0;
	ler >> lixo;
	
	//cout << "---------------------------------------------------------------------------------------------------------" << endl;
	//cout << "| Id    | Lat    |  Lng   | desc    |   zip    |    title | timeStamp   |   twp    |   addr |   e    " << endl;
	//cout << "----------------------------------------------------------------------------------------------------------" << endl << endl;
	while(ler >> c1->id and cont <= 1000){
		//cout << "tam:" << tam << endl;
		ler >> auxiliar;
		ler >> c1->lat;
		ler >> auxiliar;
		ler >> c1->lng;
		ler >> auxiliar;
		
		ler.getline(c1->desc, 115, ',');
		ler >> c1->zip;
		ler >> auxiliar;
		ler.getline(c1->title, 45, ','); 
		ler.getline(c1->timeStamp, 40, ',');
		ler.getline(c1->twp, 60, ',');
		ler.getline(c1->addr, 65, ',');
		ler >> c1->e;
		
		
		escrever.seekp(sizeof(call991)*aux);
		escrever.write((const char *) &c1, sizeof(call991));
		cont++;
		aux = cont*tam;
		escrever.seekp(sizeof(call991)*aux);
		
		c1->imprimir();
		
	}
	
	delete c1;
	escrever.close();
}


void converter(){
	//decide se o arquivo existe ou nao,
	//se o arquivo existir, a conversao começa. Senao o usuario volta a tela inicial
	
	string arquivo;
	cout << "Digite o nome do arquivo: ";
	//cin >> arquivo;
	// nome do arquivo é call911_2.csv
	arquivo = "call911_2.csv";
	
	ifstream ler(arquivo);
	
	if(ler){
		cout << "Arquivo encontrado" << endl;
		processamento(ler, arquivo);
	} else {
		cout << "Arquivo nao encontrado!" << endl;
	}
	ler.close();
}

int main()//Menu prinicipal, bem auto explicatorio
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
