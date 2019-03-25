/*pipebid.c*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXBUFF 1024  

// rm exec && gcc control_tower.c -o exec && ./exec

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


pilot (readfd, writefd)

int readfd, // leitura do pipe2[0]
    writefd; // escrita no pipe1[1]

{
	int id_question;
	
	char* buff_escrita;
	char buff_leitura[MAXBUFF];

      while(1)	
       {
	
	id_question = generate_question();

	if(id_question == 1)
	{
		buff_escrita = "d";
	}else if(id_question == 2)
	{
		buff_escrita = "e";
	}else
	{
		buff_escrita = "f";
	}

	write(writefd, buff_escrita, 10);
	 
	read(readfd,buff_leitura,10);
	//printf(" \n Recebi leitura: %s",buff_leitura);

	if(strcmp(buff_leitura, "t") == 0)
	{
		printf("\nParabéns, você salvou o dia!\n");
	}else
	{
		printf("\nSua resposta causaria uma explosao :(\n");
	}
	exit(0);
       }


	  }

tower(readfd, writefd)
int readfd, // leitura do pipe1[0]
    writefd; // escrita no pipe2[1]

{	
	
	char teclado[MAXBUFF];
	char buff_leitura[MAXBUFF];
	char* buff_escrita;

	int n, fd;
	
	while(1)	
          {
	        read(readfd,buff_leitura,10);
		//printf(" \n Pergunta eh: %s",buff_leitura);	
		
		generate_statement(buff_leitura);
		generate_options(buff_leitura);	
                
                printf(" \nQual o seu comando? ");

		gets(teclado);

		if(strcmp(buff_leitura, "d") == 0)
		{
			if(strcmp(teclado, "a") == 0)
			{
				buff_escrita = "t";
			}else
			{
				buff_escrita = "f";
			}
		}else if(strcmp(buff_leitura, "e") == 0)
		{
			if(strcmp(teclado, "c") == 0)
			{
				buff_escrita = "t";
			}else
			{
				buff_escrita = "f";
			}
		}else if(strcmp(buff_leitura, "f") == 0)
		{
			if(strcmp(teclado, "b") == 0)
			{
				buff_escrita = "t";
			}else
			{
				buff_escrita = "f";
			}
		}
		
		write(writefd, buff_escrita, 10);
		//printf("Enviei Leitura: %s", buff_escrita);	
		exit(0);
            }


    }

generate_question()
{
	srand(time (NULL));

	int id_question;
	id_question = rand() % 4;

	return id_question;
	
}

generate_statement(buff_leitura)
char buff_leitura[MAXBUFF];
{
	if(strcmp(buff_leitura, "d") == 0)
	{
		printf("\nTorre de controle, a asa traseira esta danificada!");
	}else if(strcmp(buff_leitura, "e") == 0)
	{
		printf("\nTorre de controle, estamos sem radares");
	}else if(strcmp(buff_leitura, "f") == 0)
	{
		printf("\nTorre de controle, a turbina 3 esta em chamas!!!");
	}
}

generate_options(buff_leitura)
char buff_leitura[MAXBUFF];
{
	if(strcmp(buff_leitura, "d") == 0)
	{
		printf("\nA) Aumentar potencia na turbina principal.\nB) Esvaziar combustível e preparar para pouso.\nC) Desativar piloto automatico.");
	}else if(strcmp(buff_leitura, "e") == 0)
	{
		printf("\nA) Aumentar potencia na turbina principal.\nB) Esvaziar combustível e preparar para pouso.\nC) Desativar piloto automatico.");
	}else if(strcmp(buff_leitura, "f") == 0)
	{
		printf("\nA) Aumentar potencia na turbina principal.\nB) Esvaziar combustível e preparar para pouso.\nC) Desativar piloto automatico.");
	}
}
