# Conversão de Arquivos CSV para Arquivos Binário

Este sistema é responsável pela conversão dos dados presentes no arquivo .csv em um arquivo binário. O usuário tem a capacidade de escolher qual arquivo será usado e o nome do arquivo binário gerado. Além disso, as informações deverão estar organizadas da seguinte forma: Id,lat,lng,desc,zip,title,timeStamp,twp,addr,e. E o uso das virgulas deve ser usado exclusivamente para dividir os campos.

Escrito em C++ e desenvolvido utilizando o software Geany.

# Operações no Arquivo Binário

  **Troca de posição de registros:**

Inicialmente, o usuário deve digitar dois numeros que serão os números de identificação dos registros que terão posição trocada, portanto, não é permitido digitar números de identificação que não estejam no arquivo — como números negativos ou maiores que a quantidade de registros no arquivo — e também não é possível que os dois números sejam iguais. Caso esses dois números digitados não satisfaçam as condições citadas, então será impressa uma mensagem no terminal dizendo que o número é inválido e solicitará que o usuário digite outro. Isso ocorrerá até que os dois números sejam válidos.

Após isso, o programa irá ler no arquivo binário os registros com os IDs digitados, armazenando-os em duas variáveis e após isso ocorrerá a inversão dos IDs dos registros armazenados, para que ao reescrever esses registros no código, os IDs continuem ordenados.

Por fim, cada registro será reescrito no arquivo binário na posição do outro regstro, para que ocorra a troca dos registros.

![ed-projeto (1)](https://github.com/eduardocoelho1/Projeto-ED/assets/138143297/c0139497-dddc-42d3-88bc-722d0a894714)

  **Alteração de um registro**:

Inicialmente, o usuário deve digitar um número que será o número de identificação do registro que sofrerá a alteração, portanto, não é permitido digitar números de identificação que não estejam no arquivo, como números negativos ou maiores que a quantidade de registros no arquivo. Caso o número digitado não satisfaça a condição citada, então será impressa uma mensagem no terminal dizendo que o número é invalido e solicitará que o usuário digite outro. Isso ocorrerá até que o número seja válido.

Após isso, o programa irá ler no arquivo binário o registro com o ID digitado, armazenando-o em uma variável e será solicitado que o usuário digite os novos campos do registro, alterando-o. O ID é fixo nesse caso, não sendo possível que o usário altere-o.

Por fim, o registro alterado será reescrito no arquivo binário na mesma posição em que foi lido.

![ed-projeto-alteracao](https://github.com/eduardocoelho1/Projeto-ED/assets/138143297/0c887119-4b13-462a-b1fd-819345527271)



