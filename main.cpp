#include <iostream>
#include <fstream>

using namespace std;

struct call991{
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
	int tamanho = arquivoBin.tellg()/sizeof(call991);
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
	call991 aux1, aux2;
	arquivoBin.seekg(sizeof(call991)*pos_registroX, ios::beg);
	arquivoBin.read((char*) &aux1, sizeof(call991));
	arquivoBin.seekg(sizeof(call991)*pos_registroY, ios::beg);
	arquivoBin.read((char*) &aux2, sizeof(call991));

	arquivoBin.seekp(sizeof(call991)*pos_registroY, ios::beg); //escreve cada registro na posicao onde foi lido o outro registro, efetuando a troca
	arquivoBin.write((const char *) &aux1, sizeof(call991));
	arquivoBin.seekp(sizeof(call991)*pos_registroX, ios::beg);
	arquivoBin.write((const char*) &aux2, sizeof(call991));
	cout << "Dados trocados com sucesso!" << endl;	
	cout << "==================================================" << endl;
	cout << endl;
} 

void AlterarRegistro(fstream& arquivoBin){
	arquivoBin.seekg(0, ios::end);
	int tamanho = arquivoBin.tellg()/sizeof(call991);
	int pos_registro_desejado;
	cout << "==================================================" << endl;
	cout << "Digite a posicao do registro que deseja alterar" << endl;
	cout << "Posicoes disponiveis: de 0 a " << tamanho-1 << endl; 
	cin >> pos_registro_desejado;
	while(pos_registro_desejado < 0 or pos_registro_desejado >= tamanho){
		cout << "Posicao invalida. Digite uma posicao valida, por favor" << endl;
		cin >> pos_registro_desejado;
	}
	call991 registro_alterado;
	arquivoBin.seekg(sizeof(call991)*pos_registro_desejado, ios::beg);
	arquivoBin.read((char *) &registro_alterado, sizeof(call991)); //le o registro
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
	arquivoBin.seekg(sizeof(call991)*pos_registro_desejado, ios::beg);
	arquivoBin.write((const char *) &registro_alterado, sizeof(call991)); //escreve o registro no mesmo lugar q foi lido, porem com os dados alterados
	cout << "Registro alterado com sucesso!" << endl;
	cout << "==================================================" << endl;
	cout << endl;
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
