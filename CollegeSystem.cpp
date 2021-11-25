/* Desenvolver um programa para cadastrar alunos, cursos e disciplinas.
Para os alunos deve-se cadastrar o id, nome, data de nascimento e o curso (código).
De cada curso armazena-se o código, o nome e a carga horária.
Os dados das disciplinas são id, nome, carga horária e curso (código).
O sistema poderá ser acessado apenas por usuários cadastrados, o acesso se dá por login e senha, contudo haverá dois tipos de usuários (administrador e comum).
Os usuários administradores poderão cadastrar alunos, cursos e disciplinas, bem como consultá-los e criar  novos usuários.
Os usuários comuns não poderão cadastrar cursos, disciplinas e novos usuários.
Todos os cadastros deverão ser armazenados em arquivo em modo binário.
Os id e códigos deverão ser gerados sequencialmente.
Implementar integridade referencial entre aluno e curso e entre curso e disciplina.
As opções do menu são:
Cadastrar usuário (apenas adm)
Cadastrar aluno
Cadastrar curso (apenas adm)
Cadastrar disciplina (apenas adm)
Listar aluno
Listar disciplina
Listar curso
Consultar aluno por código
Sair			*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct tempUsers{
	int id;
	char name[31];
	//type 0 - adm | type 1 - comum
	int type;
	char password[31];
}USER;

typedef struct tempStudents{
	int id;
	char name[31];
	char birthDate[11]; //xx-xx-xxxx
	int courseId;
}STUDENT;

typedef struct tempCourse{
	int id;
	char name[31];
	int workTime;
}COURSE;

typedef struct tempDiscipline{
	int id;
	char name[31];
	int workTime;
	int courseId;
}DISCIPLINE;

// variaveis globais
int typeUser;

int sequenceId(){
	//variavel local
	int seq;

	//declaração do ponteiro para o arquivo
	FILE* pFile;

	// primeira vez - inicialização da sequência [verifica SE NÃO ja esta aberto]
	if ((pFile=fopen("sequenceUser.txt", "rb"))==NULL){
		// inicializa como 1
		seq = 1;

		//abrir o arquivo no modo escrita para armazenar o valor inicial
		pFile = fopen("sequenceUser.txt", "wb");

		// armazenar o valor inicial no arquivvo
		fprintf(pFile, "%d ", seq);

		// fechar o arquivo
		fclose(pFile);
	} else {	// se o arquivo ja está aberto (n vezes)
		// encontrar o valor corrente da sequência
		fscanf(pFile, "%d", &seq);

		//incrementa 1
		seq++;

		// fechar o arquivo
		fclose(pFile);

		//abrir o arquivo no modo escrita para armazenar o valor inicial
		pFile = fopen("sequenceUser.txt", "wb");

		// armazenar o valor inicial no arquivvo
		fprintf(pFile, "%d ", seq);

		// fechar o arquivo
		fclose(pFile);
	}
	return seq;
}

int sequenceIdStudent(){
	//variavel local
	int seq;

	//declaração do ponteiro para o arquivo
	FILE* pFile;

	// primeira vez - inicialização da sequência [verifica SE NÃO ja esta aberto]
	if ((pFile=fopen("sequenceStudent.txt", "rb"))==NULL){
		// inicializa como 1
		seq = 1;

		//abrir o arquivo no modo escrita para armazenar o valor inicial
		pFile = fopen("sequenceStudent.txt", "wb");

		// armazenar o valor inicial no arquivvo
		fprintf(pFile, "%d ", seq);

		// fechar o arquivo
		fclose(pFile);
	} else {	// se o arquivo ja está aberto (n vezes)
		// encontrar o valor corrente da sequência
		fscanf(pFile, "%d", &seq);

		//incrementa 1
		seq++;

		// fechar o arquivo
		fclose(pFile);

		//abrir o arquivo no modo escrita para armazenar o valor inicial
		pFile = fopen("sequenceStudent.txt", "wb");

		// armazenar o valor inicial no arquivvo
		fprintf(pFile, "%d ", seq);

		// fechar o arquivo
		fclose(pFile);
	}
	return seq;
}

bool recordUser(int type){
	system("cls");

	FILE* pFile;
	if ((pFile = fopen("users.txt", "ab")) == NULL);
	USER user;

 	// entrada do type
 	user.type = type;

	// entrada do nome - com tratamento de erro
	// -> se o usuario nao digitar nada, a string tem tamanho 0 (strlen=0)
	do {
		system("cls");
		printf("Enter username: ");
		fflush(stdin);
		gets(user.name);
	} while(strlen(user.name) == 0);

	// entrada do id
	user.id = sequenceId();
	printf("\nId = %d", user.id);
	sleep(1);

	// entrada da senha - com tratamento de erro
	// -> se o usuario nao digitar nada, a string tem tamanho 0 (strlen=0)
	do {
		system("cls");
		printf("\nEnter password: ");
		fflush(stdin);
		gets (user.password);
	} while(strlen(user.password) == 0);


	// armazenar type, nome, id, password
	fprintf(pFile, "%i %s %i %s\n", user.type, user.name, user.id, user.password);
	fclose(pFile);
	return true;
}

bool recordStudent(){
    system("cls");

	FILE* pFile;
	if ((pFile = fopen("students.txt", "ab")) == NULL);
	STUDENT student;

	student.id = sequenceIdStudent();

	printf("Enter the name: ");
    fflush(stdin);
    gets(student.name);

    printf("Enter the birthdate: ");
    fflush(stdin);
    gets(student.birthDate);


    /*FAZER VALIDACAO DE SE O CURSO EXISTE NO FILE "courses"*/
    FILE* pCoursesFile;
    bool courseExists=false;
    int  courseId;
    do{
        printf("Enter the course Id: ");
        pCoursesFile = fopen("courses.txt", "rb");
        scanf("%d", &student.courseId);
        while (fscanf(pCoursesFile, "%i", &courseId) != -1){
            if (courseId == student.courseId)
                courseExists = true;
        }
        fclose(pCoursesFile);
        system("cls");
    } while (courseExists == false);

	fprintf(pFile, "%i %s %s %i\n", student.id, student.name, student.birthDate, student.courseId);
	fclose(pFile);
    return true;
}

bool showStudent(){
    int id, courseId;
    char name[31], birthDate[11];

    FILE* pFile;
	if ((pFile = fopen("students.txt", "rb"))==NULL)
		return false;

	while (fscanf(pFile, "%i %s %s %i\n", &id, name, birthDate, &courseId) != -1){
        printf("%i %s %s %i\n", id, name, birthDate, courseId);
	}
	system("pause");

	fclose(pFile);
    return true;
}

/*int id;
	char name[31];
	char birthDate;
	int courseId;*/

bool login(){
	// variaveis locais
	int sourceId=NULL, targetId=NULL;
	char sourcePassword[31], targetPassword[31];

	/* entrada de username e senha */
	do {
		system("cls");
		printf("Enter the id: ");
		scanf("%d", &sourceId);
	} while(sourceId == NULL);

	do {
		system("cls");
		printf("Enter the password: ");
		fflush(stdin);
		gets(sourcePassword);
	} while(strlen(sourcePassword) == 0);

	// Abrindo o arquivo de usuarios em modo leitura
	FILE* pFile;
	if ((pFile = fopen("users.txt", "rb"))==NULL)
		return false;

	// fseek - se o Id for 10. pular (9?) structs de sizeof(USER) --------------------------------------
	// obs.: %*i ou %*s , faz o programa ignorar a captura do dado
	//bool loginFlag = false;

	while (fscanf(pFile, "%i %*s %i %s\n", &typeUser, &targetId, targetPassword) != -1){
		if (sourceId == targetId){
			// achou o Id
			printf("\nID encontrado!\n");

			// se a senha for correta
			if(strcmp(sourcePassword, targetPassword)==0){
				printf("Senha encontrada!\n\n");
				//loginFlag = true;
				system("pause");
				fclose(pFile);
				return true;
			}
		}
	}
	return false;
}

void commonMenu(){
    /*
    int option;
    printf("\nMenu - Common:\n\n");
    printf("Choose one option\n\t1-Record student\n\t2-Show students\n\t3-Find student by ID");
    printf("\n\t4-Show disciplines\n\t5-Show courses\n\t9-Exit\n: ");
    scanf("%i", &option);

    switch (option){
        case 1:


    }


    Cadastrar aluno

    Listar aluno
    Consultar aluno por código

    Listar disciplina
    Listar curso

    Sair
    */

}

void adminMenu(){
    printf("\n\nADM MENU\n\n");
    system("pause");
}

int main(){
	// garantindo que haverá arquivo criado:
	// criando um arquivo txt com o nome de "users"
	FILE* pFile = fopen("users.txt", "ab");
	fclose(pFile);

	/* VER SE O ARQUIVO DE USUÁRIOS POSSUI CADASTROS */
	// abre o arquivo que armazena os usuarios em modo leitura binaria
	pFile = fopen("users.txt", "rb");

	// por padrão, considera-se que nao ha administrador
	bool hasAdm = false;
	char type;
	// se o primeiro caracter do arquivo users.txt for 0, entao há adm e deve mandar para menu de escolha
	while ((char(type = getc(pFile)))!=EOF){
		if (type == '0'){
			hasAdm = true;
		}
		// break para pegar apenas o primeiro caracter
		break;
	}
	fclose(pFile);

	// Caso tenha adm cadastrado, deve-se fazer login (ou sair),
	// caso não, deve mandar para a fauncao recordUser passando o type
	// do usuario como '0' = adm
	bool loginSuccess=false;
	do {
        if (hasAdm){
		int option;
		// se tem pelo menos 1 administrador cadastrado e nenhum outro comum, menu de escolha
		do {
			system("cls");
			printf("\nWhat do you choose? <1 - Login | 9 - Sair>: ");
			scanf("%d", &option);

			switch (option){
				case 1:
					// chama login dentro de um if (bool -> portanto)
					// se login é false (!), avise que deu erro de login
					if(login()){
						loginSuccess = true;
						system("cls");
					} else {
                        printf("A login error occurred, try again.. :(\n\n");
						system("pause");
					}
					break;
				case 9:
					exit(0);
				default:
					printf("\nInvalid option! Try again..\n");
                }
            } while (option != 1 && option != 9);
        } else {
            // type 0 - adm
            printf("\nYou are the first here!\n");
            system("pause");
            recordUser(0);
            hasAdm = true;
        }
	} while (!loginSuccess);

    recordStudent();
    showStudent();
    exit(0);

    /* Menu de acordo com o tipo de usuario */
    if (typeUser == 0)
        adminMenu();
    else
        commonMenu();


    system("pause");

	return 0;
}


