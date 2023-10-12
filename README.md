# Conversão de Arquivos CSV para Arquivos Binário

Este sistema é responsável pela conversão dos dados presentes no arquivo .csv em um arquivo binário. O usuário tem a capacidade de escolher qual arquivo será usado e o nome do arquivo binário gerado. Além disso, as informações deverão estar organizadas da seguinte forma: Id,lat,lng,desc,zip,title,timeStamp,twp,addr,e. E o uso das virgulas deve ser usado exclusivamente para dividir os campos.

Escrito em C++ e desenvolvido utilizando o software Geany.

# Operações no Arquivo Binário

  **Troca de posição de registros:**

Inicialmente, o usuário deve digitar dois numeros que serão as posições dos registros trocados, portanto, não é permitido digitar posições não existentes no arquivo — como números negativos ou maiores que a quantidade de registros no arquivo — e também não é possível que as posições sejam iguais. Caso algum desses dois números digitados não satisfaçam as condições citadas, então será impressa uma mensagem no terminal dizendo que o número é inválido e solicitará que o usuário digite outro. Isso ocorrerá até que os dois números sejam válidos.

Após isso, dois registros serão lidos do arquivo binário, cujas posições foram escolhidas pelo usuário.

Por fim, cada registro será reescrito no arquivo binário na posição do outro regstro, para que ocorra a troca dos registros.

![ed-projeto (2)](https://github.com/eduardocoelho1/Projeto-ED/assets/138143297/92801aeb-bb43-478d-90a5-c066012446c1)


  **Alteração de um registro**:

Inicialmente, o usuário deve digitar um número que será a posição do registro que sofrerá a alteração, portanto, não é permitido digitar posições inválidas, como números negativos ou maiores que a quantidade de registros no arquivo. Caso o número digitado não satisfaça a condição citada, então será impressa uma mensagem no terminal dizendo que o número é invalido e solicitará que o usuário digite outro. Isso ocorrerá até que o número seja válido.

Após isso, o programa irá ler no arquivo binário o registro com a posição digitada, armazenando-o em uma variável e será solicitado que o usuário digite os novos campos do registro, alterando-o. O ID é fixo nesse caso, não sendo possível que o usário altere-o.

Por fim, o registro alterado será reescrito no arquivo binário na mesma posição em que foi lido.

![ed-projeto-alteracao (1)](https://github.com/eduardocoelho1/Projeto-ED/assets/138143297/5ef30385-73de-4f94-941b-6b1ec16e297e)




