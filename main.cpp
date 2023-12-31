/* Equipe:
 * Estevão Augusto da Fonseca Santos
 * Felipe Geraldo de Oliveira
 * Eduardo Cesar Cauduro Coelho
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include "ordenador.h"
#include "call911.h"

using namespace std;

void limpaCin() {
    // descarta o input do usuario que ultrassa o limite do vetor de char
    cin.clear();
    string lixo;
    getline(cin, lixo);
}

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
    call911 dado;
    arquivoBin.seekg(sizeof(call911)*pos_registro_desejado, ios::beg);
    arquivoBin.read((char *) &dado, sizeof(call911)); //le o registro
    cout << "===========================================================" << endl;
    cout << "Insira os dados:" << endl;
    cout << "lat: ";
    cin >> dado.lat;
    cout << "lng: ";
    cin >> dado.lng;
    cin.ignore();
    cout << "desc: ";
    cin.getline(dado.desc, 121);
    if (cin.fail()) {
        limpaCin();
    }
    cout << "zip: ";
    cin >> dado.zip;
    cin.ignore();
    cout << "title: ";
    cin.getline(dado.title, 37);
    if (cin.fail()) {
        limpaCin();
    }
    cout << "timeStamp: ";
    cin.getline(dado.timeStamp, 20);
    if (cin.fail()) {
        limpaCin();
    }
    cout << "twp: ";
    cin.getline(dado.twp, 18);
    if (cin.fail()) {
        limpaCin();
    }
    cout << "addr: ";
    cin.getline(dado.addr, 66);
    if (cin.fail()) {
        limpaCin();
    }
    cout << "e: ";
    cin >> dado.e;
    cout << "===========================================================" << endl << endl;
    arquivoBin.seekg(sizeof(call911)*pos_registro_desejado, ios::beg);
    arquivoBin.write((const char *) &dado, sizeof(call911)); //escreve o registro no mesmo lugar q foi lido, porem com os dados alterados
    cout << "Registro alterado com sucesso!" << endl;
    cout << "==================================================" << endl;
    cout << endl;
}

void AdicionarRegistro(fstream& arquivoBin) {
    int tamanho;
    call911 dado;

    arquivoBin.seekg(0, ios::end);
    tamanho = arquivoBin.tellg() / sizeof(call911);
    int posicao;
    cout << "==================================================" << endl;
    cout << "Digite a posicao em que deseja inserir" << endl;
    cout << "Posicoes disponiveis: de 0 a " << tamanho << endl; 
    cin >> posicao;
    while(posicao < 0 or posicao > tamanho){
        cout << "Posicao invalida. Digite uma posicao valida, por favor" << endl;
        cin >> posicao;
    }

    for (int i = tamanho-1; i >= posicao; i--) {
        // move todos os registros da posicao desejada ate o final uma posicao a frente
        arquivoBin.seekg(i*sizeof(call911));
        arquivoBin.read((char *) &dado, sizeof(call911));

        arquivoBin.seekp((i+1)*sizeof(call911));
        arquivoBin.write((const char *) &dado, sizeof(call911));
    }

    dado.id = tamanho;
    cout << "===========================================================" << endl;
    cout << "Insira os dados:" << endl;
    cout << "lat: ";
    cin >> dado.lat;
    cout << "lng: ";
    cin >> dado.lng;
    cin.ignore();
    cout << "desc: ";
    cin.getline(dado.desc, 121);
    if (cin.fail()) {
        limpaCin();
    }
    cout << "zip: ";
    cin >> dado.zip;
    cin.ignore();
    cout << "title: ";
    cin.getline(dado.title, 37);
    if (cin.fail()) {
        limpaCin();
    }
    cout << "timeStamp: ";
    cin.getline(dado.timeStamp, 20);
    if (cin.fail()) {
        limpaCin();
    }
    cout << "twp: ";
    cin.getline(dado.twp, 18);
    if (cin.fail()) {
        limpaCin();
    }
    cout << "addr: ";
    cin.getline(dado.addr, 66);
    if (cin.fail()) {
        limpaCin();
    }
    cout << "e: ";
    cin >> dado.e;
    cout << "===========================================================" << endl << endl;

    arquivoBin.seekp(posicao*sizeof(call911)); 
    arquivoBin.write((const char *) &dado, sizeof(call911)); // insere na posicao desejada que ficou vazia
    cout << "Registro inserido com sucesso!" << endl;
    cout << "==================================================" << endl;
}

void VisualizarIntervalo(fstream& arquivoBin) {
    int tamanho, inicio, fim;
    arquivoBin.seekg(0, ios::end);
    tamanho = arquivoBin.tellg() / sizeof(call911);
    cout << "==================================================" << endl;
    cout << "Posicoes disponiveis: de 0 a " << tamanho-1 << endl;
    cout << "Digite a posicao inicial" << endl; 
    cin >> inicio;
    while(inicio < 0 or inicio >= tamanho){
        cout << "Posicao invalida. Digite uma posicao valida, por favor" << endl;
        cin >> inicio;
    }
    cout << endl << "Digite a posicao final" << endl;
    cin >> fim;
    while(fim >= tamanho or fim < inicio){
        cout << "Posicao invalida. Digite uma posicao valida, por favor" << endl;
        cin >> fim;
    }
    call911 dado;
    arquivoBin.seekg(inicio * sizeof(call911), ios::beg);
    for (int i = inicio; i <= fim; i++) {
        arquivoBin.read((char *) &dado, sizeof(call911));
        dado.ImprimirDados();
    }
}

void VisualizarTodos(fstream& arquivoBin) {
    call911 dado;
    int tamanho;
    arquivoBin.seekg(0, ios::end);
    tamanho = arquivoBin.tellg() / sizeof(call911);
    arquivoBin.seekg(0, ios::beg);
    for(int i = 0; i < tamanho; i++) {
        arquivoBin.read((char *) &dado, sizeof(call911));
        dado.ImprimirDados();
    }
}

int main() {
    fstream arquivoBin("binario.dat", ios::out|ios::in|ios::binary);
    int opcao;
    do{
        cout << "=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" << endl;
        cout << "       Operacoes no Arquivo Binario" << endl;
        cout << "=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" << endl << endl;
        cout << "0) Sair" << endl;
        cout << "1) Trocar dois registros" << endl;
        cout << "2) Alterar um registro" << endl;
        cout << "3) Adicionar um registro" << endl;
        cout << "4) Visualizar todos os registros" << endl;
        cout << "5) Visualizar um intervalo de registros" << endl;
		cout << "6) Ordenar arquivo" << endl << endl;
        cout << "===============================================" << endl;
        cout << "Digite sua opcao: ";
        cin >> opcao;
        cout << endl;
        switch(opcao){
            case 0:
                arquivoBin.close();
                break;
            case 1:
                TrocarRegistro(arquivoBin);
                break;
            case 2:
                AlterarRegistro(arquivoBin);
                break;
            case 3:
                AdicionarRegistro(arquivoBin);
                break;
            case 4:
                VisualizarTodos(arquivoBin);
                break;
            case 5:
                VisualizarIntervalo(arquivoBin);
                break;
			case 6:
				ordenacao_externa();
                break;
            default:
                cout << "Opcao invalida" << endl;
                break;		
        }
    } while(opcao != 0);
    return 0;
}
