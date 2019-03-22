/*pipebid.c*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXBUFF 1024  // numero de caract. do buffer

// Como executar
// gcc control_tower.c -o exec
// ./exec

main()
{
   int	descritor,  // usado para criar o processo filho pelo fork
	pipe1[2],  // comunicacao pai -> filho
	pipe2[2];  // comunicacao filho -> pai

   if (pipe(pipe1)<0 || pipe(pipe2) <0)
	{ printf("Erro na chamada PIPE");
	   exit(0);
	}

   //   Fork para criar o processo filho

    if ( (descritor = fork()) <0)
	{ printf("Erro na chamada FORK");
	   exit(0);
	}

	else if (descritor >0)  // PROCESSO PAI
	   {	close(pipe1[0]); // fecha leitura no pipe1
		close(pipe2[1]);  // fecha escrita no pipe2

		pilot(pipe2[0], pipe1[1]);  // Chama CLIENTE no PAI

		close(pipe1[1]); // fecha pipe1
		close(pipe2[0]);  // fecha pipe2
		exit(0);

	    } // FIM DO PROCESSO PAI

	else // PROCESSO FILHO

	   {	close(pipe1[1]); // fecha escrita no pipe1
		close(pipe2[0]);  // fecha leitura no pipe2

		tower(pipe1[0], pipe2[1]);  // Chama SERVIDOR no FILHO

		close(pipe1[0]); // fecha leitura no pipe1
		close(pipe2[1]);  // fecha escrita no pipe2
		exit(0);

	} // FIM DO PROCESSO FILHO
} // FIM DO MAIN

/* -----------------------------------------------------------------------------------------------------------
Funcao Client:	Executa no processo PAI
			Envia o nome do arquivo para o FILHO
			Recebe os dados do FILHO e imprime na tela
----------------------------------------------------------------------------------------------------------- */

pilot (readfd, writefd)

int readfd, // leitura do pipe2[0]
    writefd; // escrita no pipe1[1]

{
	srand(time (NULL));
	int valor;
	valor = rand() % 11;
	printf("Oi %d", valor);
	char buff[MAXBUFF];
      while(1)	
       {
	printf(" \n Piloto -> ");
	gets(buff);
	write(writefd, buff, 10);
	 
	read(readfd,buff,10);
	printf(" \n Piloto <- %s",buff);

       }


	  } // Fim da Funcao CLIENT

/* -----------------------------------------------------------------------------------------------------------
Funcao Server:	Executa no processo FILHO
			Abre o arquivo solicitado e envia seu conteudo
			para o PAI
----------------------------------------------------------------------------------------------------------- */
tower(readfd, writefd)
int readfd, // leitura do pipe1[0]
    writefd; // escrita no pipe2[1]

{
	char buff[MAXBUFF];
	int n, fd;

	
	while(1)	
          {
	        read(readfd,buff,10);
		printf(" \n Torre <- %s",buff);		
                
                printf(" \n Torre-> ");
		gets(buff);
		write(writefd, buff, 10);
	 
		

            }


    } // Fim da Funcao Server
