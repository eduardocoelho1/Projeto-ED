# Conversão de Arquivos CSV para Arquivos Binário

Este sistema é responsável pela conversão dos dados presentes no arquivo .csv em um arquivo binário. O usuário tem a capacidade de escolher qual arquivo será usado e o nome do arquivo binário gerado. Além disso, as informações deverão estar organizadas da seguinte forma: Id,lat,lng,desc,zip,title,timeStamp,twp,addr,e. E o uso das virgulas deve ser usado exclusivamente para dividir os campos.

Escrito em C++ e desenvolvido utilizando o software Geany.

# Operações no Arquivo Binário

  *Troca de registros de posição:*

Inicialmente, o usuário deve digitar dois numeros que serão os números de identificação dos registros que serão alterados, portanto, não é permitido digitar números de identificação que não estejam no arquivo — como números negativos ou maiores que a quantidade de registros no arquivo — e também não é possível que os dois números sejam iguais. Caso esses dois números digitados não satisfaçam as condições citadas, então será impressa uma mensagem no terminal dizendo que o número é inválido e solicitará que o usuário digite outro. Isso ocorrerá até que os dois números sejam válidos.

Após isso, o programa irá ler no arquivo binário os registros com os ids digitados, armazenando-os em duas variáveis e após isso ocorrerá a inversão dos ids dos registros armazenados, para que ao reescrever esses registros no código, os ids continuem ordenados.

Por fim, cada registro será reescrito no arquivo binário na posição do outro regstro, para que ocorra a troca dos registros.

![ed-projeto](https://github.com/eduardocoelho1/Projeto-ED/assets/138143297/97bf20e9-b5d2-4df9-a1fe-d9436b1f7247)
