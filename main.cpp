#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct call911{
	int e;
	int id;//atributo secundario
	float lat, lng, zip;
	char addr[66]; //atributo primario
	char desc[121], title[37];
	char timeStamp[20], twp[18];
};

void TrocarRegistro(fstream& arquivoBin){ 
	int pos_registroX, pos_registroY;
	arquivoBin.seekg(0, ios::end);
	int tamanho = arquivoBin.tellg()/sizeof(call911);
	cout << "==================================================" << endl;
	cout << "Digite a posicao de um dos registros que deseja trocar" << endl;
	cout << "Posicoes disponiveis: de 0 a " << tamanho-1 << endl; 
	cin >> pos_registroX;
	while(pos_registroX < 0 or pos_registroX >= tamanho){ //nao pode ser negativo nem maior que a quantidade total
		cout << "Posicao invalida. Digite uma posicao valida, por favor" << endl;
		cin >> pos_registroX;
	}
	cout << "Digite a posicao de outro registro para que seja efetuada a troca" << endl;
	cin >> pos_registroY;
	while(pos_registroY < 0 or pos_registroY >= tamanho or pos_registroY == pos_registroX){ //alem das restricoes ja citadas, nao pode ser igual ao outro registro
		cout << "Posicao invalida ou ja selecionada. Digite uma posicao valida que não tenha sido selecionada, por favor" << endl;
		cin >> pos_registroY;
	}
	call911 aux1, aux2;
	arquivoBin.seekg(sizeof(call911)*pos_registroX, ios::beg);
	arquivoBin.read((char*) &aux1, sizeof(call911));
	arquivoBin.seekg(sizeof(call911)*pos_registroY, ios::beg);
	arquivoBin.read((char*) &aux2, sizeof(call911));

	arquivoBin.seekp(sizeof(call911)*pos_registroY, ios::beg); //escreve cada registro na posicao onde foi lido o outro registro, efetuando a troca
	arquivoBin.write((const char *) &aux1, sizeof(call911));
	arquivoBin.seekp(sizeof(call911)*pos_registroX, ios::beg);
	arquivoBin.write((const char*) &aux2, sizeof(call911));
	cout << "Dados trocados com sucesso!" << endl;	
	cout << "==================================================" << endl;
	cout << endl;
} 

void AlterarRegistro(fstream& arquivoBin){
	arquivoBin.seekg(0, ios::end);
	int tamanho = arquivoBin.tellg()/sizeof(call911);
	int pos_registro_desejado;
	cout << "==================================================" << endl;
	cout << "Digite a posicao do registro que deseja alterar" << endl;
	cout << "Posicoes disponiveis: de 0 a " << tamanho-1 << endl; 
	cin >> pos_registro_desejado;
	while(pos_registro_desejado < 0 or pos_registro_desejado >= tamanho){
		cout << "Posicao invalida. Digite uma posicao valida, por favor" << endl;
		cin >> pos_registro_desejado;
	}
	call911 registro_alterado;
	arquivoBin.seekg(sizeof(call911)*pos_registro_desejado, ios::beg);
	arquivoBin.read((char *) &registro_alterado, sizeof(call911)); //le o registro
	cout << "Digite os novos campos do registro, na seguinte ordem:" << endl;
	cout << "lat, lng, desc, zip, title, timeStamp, twp, addr, e" << endl;
	cin >> registro_alterado.lat; //substitui os dados
	cin >> registro_alterado.lng;
	cin.ignore();
	cin.getline(registro_alterado.desc, 121);
	cin >> registro_alterado.zip;
	cin.ignore();
	cin.getline(registro_alterado.title, 37);
	cin.getline(registro_alterado.timeStamp, 20);
	cin.getline(registro_alterado.twp, 18);
	cin.getline(registro_alterado.addr, 66);
	cin >> registro_alterado.e;
	arquivoBin.seekg(sizeof(call911)*pos_registro_desejado, ios::beg);
	arquivoBin.write((const char *) &registro_alterado, sizeof(call911)); //escreve o registro no mesmo lugar q foi lido, porem com os dados alterados
	cout << "Registro alterado com sucesso!" << endl;
	cout << "==================================================" << endl;
	cout << endl;
}

void adicionar(fstream& arquivoBin, int posicao) {
    int tamanho;
    call911 dado;

    arquivoBin.seekg(0, ios::end);
    tamanho = arquivoBin.tellg() / sizeof(call911);

    arquivoBin.seekg(-sizeof(call911), ios::end);
    arquivoBin.seekp(0, ios::end);

    for (int i = tamanho; i > posicao; i--) {
        arquivoBin.read((char *) &dado, sizeof(call911));
        arquivoBin.write((const char *) &dado, sizeof(call911));

        arquivoBin.seekg(-sizeof(call911), ios::cur);
        arquivoBin.seekp(-sizeof(call911), ios::cur);
    }

    cout << "===========================================================" << endl;
    cout << "Insira os dados:";
    cout << endl << "id: ";
    cin >> dado.id;
    cout << endl << "lat: ";
    cin >> dado.lat;
    cout << endl << "lng: ";
    cin >> dado.lng;
    cout << endl << "desc: ";
    cin >> dado.desc;
    cout << endl << "zip: ";
    cin >> dado.zip;
    cout << endl << "title: ";
    cin >> dado.title;
    cout << endl << "timeStamp: ";
    cin >> dado.timeStamp;
    cout << endl << "twp: ";
    cin >> dado.twp;
    cout << endl << "addr: ";
    cin >> dado.addr;
    cout << endl << "e: ";
    cin >> dado.e;
    cout << endl << "===========================================================" << endl;

    arquivoBin.write((const char *) &dado, sizeof(call911));
}

void imprimirDados(call911 dado) {
	string linha = "----------------------------------------------------------------------------------------------------------";
	cout << "==========================================================================================================" << endl;
	cout << left << setfill(' ') << setw(10) << dado.id << endl;
	cout << linha << endl;
	cout << dado.lat << endl;
	cout << linha << endl;
	cout << dado.lat << endl;
	cout << linha << endl;
	cout << dado.lat << endl;
	cout << linha << endl;
	cout << dado.lat << endl;
	cout << linha << endl;
	cout << dado.lat << endl;
	cout << linha << endl;
	cout << dado.lat << endl;
	cout << linha << endl;
	cout << dado.lat << endl;
	cout << linha << endl;
	cout << dado.lat << endl;
	cout << linha << endl;
	cout << dado.lat << endl;
	cout << linha << endl;
	cout << "==========================================================================================================" << endl << endl;	
}

void visualizar(fstream& arquivoBin, int inicio, int fim) { // não inclui a posição final
    call911 dado;
    arquivoBin.seekg(inicio * sizeof(call911), ios::beg);
    for (int i = inicio; i < fim; i++) {
        arquivoBin.read((char *) &dado, sizeof(call911));
        imprimirDados(dado);
        arquivoBin.seekg(sizeof(call911), ios::cur);
    }
}

void visualizar(fstream& arquivoBin) { // visualizar todos
    call911 dado;
    arquivoBin.seekg(0, ios::beg);
    while(not arquivoBin.eof()) {
        arquivoBin.read((char *) &dado, sizeof(call911));
        imprimirDados(dado);
        arquivoBin.seekg(sizeof(call911), ios::cur);
    }
}

int main() {
	fstream arquivoBin("binario.dat", ios::out|ios::in|ios::binary);
	bool executa_enquanto = true;
	int opcao;
	while(executa_enquanto){
		cout << "-----------------------------------------------" << endl;
		cout << "Menu principal" << endl;
		cout << "-----------------------------------------------" << endl;
		cout << "0) Sair" << endl;
		cout << "1) Trocar dois registros" << endl;
		cout << "2) Alterar um registro" << endl;
		cout << "Digite sua opcao: ";
		cin >> opcao;
		cout << endl;
		switch(opcao){
			case 0:
				executa_enquanto = false;
				break;
			case 1:
				TrocarRegistro(arquivoBin);
				break;
			case 2:
				AlterarRegistro(arquivoBin);
				break;
			default:
				cout << "Opcao invalida" << endl;
				break;		
		}
	}
	arquivoBin.close();
	return 0;
}
