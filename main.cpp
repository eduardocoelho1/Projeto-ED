#include <iostream>
#include <fstream>

using namespace std;

struct call991{
	int e = -1;
	int id = -1;//atributo secundario
	float lat = -1, lng = -1, zip = -1;
	char addr[60] = "-1"; //atributo primario
	char desc[30] = "-1", title[20] = "-1";
	char timeStamp[40] = "-1", twp[50] = "-1";
};

void TrocarRegistro(){
	cout << "Digite o id dos registros que quer trocar: " << endl;
	int id_registroX, id_registroY;
	cin >> id_registroX;
	cin >> id_registroY;
	arquivoBin.seekg(sizeof(call991)*id_registroX, ios::beg);
	call991 aux1, aux2;
	int id_aux;
	arquivoBin.read((char*) &aux1, sizeof(call991));
	arquivoBin.seekg(sizeof(call991)*id_registroY, ios::beg);
	arquivoBin.read((char*) &aux2, sizeof(call991));
	id_aux = aux1.id;
	aux1.id = aux2.id;
	aux2.id = id_aux;
	arquivoBin.write((const char *) &aux1, sizeof(call991));
	arquivoBin.seekp(sizeof(call991)*id_registroX, ios::beg);
	arquivoBin.write((const char*) &aux2, sizeof(call991));
	arquivoBin.clear();
	cout << "Dados trocados com sucesso!" << endl;	
}

void AlterarRegistro(){
	cout << "Digite o ID do registro que deseja alterar: " << endl;
	int id_registro_desejado;
	cin >> id_registro_desejado;
	call991 registro_alterado;
	arquivoBin.seekg(sizeof(call991)*id_registro_desejado, ios::beg);
	arquivoBin.read((char *) &registro_alterado, sizeof(call991));
	cin >> registro_alterado.lat;
	cin >> registro_alterado.lng;
	cin.ignore();
	cin.getline(registro_alterado.desc, 30);
	cin >> registro_alterado.zip;
	cin.ignore();
	cin.getline(registro_alterado.title, 20);
	cin.getline(registro_alterado.timeStamp, 40);
	cin.getline(registro_alterado.twp, 50);
	cin.getline(registro_alterado.addr, 20);
	cin >> registro_alterado.e;
	arquivoBin.write((const char *) &registro_alterado, sizeof(call991));
	cout << "Registro alterado com sucesso!" << endl;
	arquivoBin.clear();
}

int main() {
    return 0;
}
