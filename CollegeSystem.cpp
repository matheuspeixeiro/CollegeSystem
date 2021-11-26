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

int sequenceId(char* filename){
    char file[31];
    const char* ext = ".txt";
    strcat(strcpy(file, filename), ext);

	//variavel local
	int seq;

	//declaração do ponteiro para o arquivo
	FILE* pFile;

	// primeira vez - inicialização da sequência [verifica SE NÃO ja esta aberto]
	if ((pFile=fopen(file, "rb"))==NULL){
		// inicializa como 1
		seq = 1;

		//abrir o arquivo no modo escrita para armazenar o valor inicial
		pFile = fopen(file, "wb");

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
		pFile = fopen(file, "wb");

		// armazenar o valor inicial no arquivvo
		fprintf(pFile, "%d ", seq);

		// fechar o arquivo
		fclose(pFile);
	}
	return seq;
}

bool recordUser(int type){
	FILE* pFile;
	if ((pFile = fopen("users.txt", "ab")) == NULL)
        return false;
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

	char aux[31];
	strcpy(aux,"sequenceUser");

	// entrada do id
	user.id = sequenceId(aux);
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
	if ((pFile = fopen("students.txt", "ab")) == NULL)
        return false;
	STUDENT student;

    char aux[31];
	strcpy(aux,"sequenceStudent");
	student.id = sequenceId(aux);

	printf("Enter the name: ");
    fflush(stdin);
    gets(student.name);

    printf("\nEnter the birthdate: ");
    fflush(stdin);
    gets(student.birthDate);

    /*FAZER VALIDACAO DE SE O CURSO EXISTE NO FILE "courses" */
    FILE* pCoursesFile;
    bool courseExists=false;
    int  courseId, courseWorkTime;
    do{
        printf("\nEnter the course Id: ");
        scanf("%d", &student.courseId);
        pCoursesFile = fopen("courses.txt", "rb");
        char courseName[31];
        while (fscanf(pCoursesFile, "%i %*s %*i", &courseId) != -1){
            if (courseId == student.courseId){
                courseExists = true;
            }
        }
        system("cls");
    } while (courseExists == false);

    fclose(pCoursesFile);
	fprintf(pFile, "%i %s %s %i\n", student.id, student.name, student.birthDate, student.courseId);
	fclose(pFile);
    return true;
}

bool recordCourse(){
    // curso armazena-se o id, o nome e a carga horária e (discipinas listadas?).
    system("cls");

	FILE* pFile;
	if ((pFile = fopen("courses.txt", "ab")) == NULL)
        return false;
	COURSE course;

	char aux[31];
	strcpy(aux,"sequenceCourse");

	course.id = sequenceId(aux);
	printf("Course Id: %d\n\n", course.id);

	printf("Enter the course name: ");
    fflush(stdin);
    gets(course.name);

    printf("\nEnter the course worktime (hours): ");
    scanf("%d", &course.workTime);
    system("pause");

    // armazenar id, nome, timeWork
	fprintf(pFile, "%i %s %i\n", course.id, course.name, course.workTime);
	fclose(pFile);
	return true;
}

bool recordDiscipline(){
    system("cls");
	FILE* pDisciplineFile;
	if ((pDisciplineFile = fopen("disciplines.txt", "ab")) == NULL)
        return false;
	DISCIPLINE discipline;

    char aux[31];
    strcpy(aux,"sequenceDiscipline");

	discipline.id = sequenceId(aux);
	printf("Discipline ID: %i\n\n", discipline.id);

	printf("Enter the discipline name: ");
    fflush(stdin);
    gets(discipline.name);

    printf("\nEnter the worktime (hours): ");
    scanf("%i", &discipline.workTime);

    /*FAZER VALIDACAO DE SE O CURSO EXISTE NO FILE "courses" */
    FILE* pCoursesFile;
    bool courseExists=false;
    int  courseId, courseWorkTime;
    do{
        printf("\nEnter the course Id: ");
        //showCourses();
        scanf("%d", &discipline.courseId);
        pCoursesFile = fopen("courses.txt", "rb");
        char courseName[31];
        while (fscanf(pCoursesFile, "%i %s", &courseId, courseName) != -1){
            if (courseId == discipline.courseId){
                courseExists = true;
            }
        }
        system("cls");
    } while (courseExists == false);

    // armazena no arquivo disciplines.txt
    fprintf(pDisciplineFile, "%i %s %i %i\n", discipline.id, discipline.name, discipline.workTime, discipline.courseId);
    fclose(pDisciplineFile);
    fclose(pCoursesFile);
    return true;
}

bool showStudent(){
    system("cls");
    int id, courseId;
    char name[31], birthDate[11];

    FILE* pFile;
	if ((pFile = fopen("students.txt", "rb"))==NULL)
		return false;

    printf("| Id | Name | Birth Date | Course Id |\n\n");

	while (fscanf(pFile, "%i %s %s %i\n", &id, name, birthDate, &courseId) != -1){
        printf("%i %s %s %i\n", id, name, birthDate, courseId);
	}
	system("pause");

	fclose(pFile);
    return true;
}

bool showCourses(){
    system("cls");
    int id, workTime;
    char name[31];
    FILE* pFile;
	if ((pFile = fopen("courses.txt", "rb"))==NULL)
		return false;

    printf("| Id | Name | Worktime |\n\n");
	while (fscanf(pFile, "%i %s %i\n", &id, name, &workTime) != -1){
        printf("%i %s %i\n", id, name, workTime);
	}
	system("pause");

	fclose(pFile);
    return true;
}

bool showDisciplines(){
    int id, workTime, courseId;
    char name[31];
    FILE* pFile;
	if ((pFile = fopen("disciplines.txt", "rb"))==NULL)
		return false;

    system("cls");
    printf("| Id | Name | Worktime | Course Id |\n\n");
	while (fscanf(pFile, "%i %s %i %i\n", &id, name, &workTime, &courseId) != -1){
        printf("%i %s %i %i\n", id, name, workTime, courseId);
	}

	fclose(pFile);
    return true;
}

bool login(){
	// variaveis locais
	char sourcePassword[31], targetPassword[31], sourceId[2], targetId[2];

	/* entrada de username e senha */
	do {
		system("cls");
		printf("Enter the id: ");
		fflush(stdin);
		gets(sourceId);
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

	// obs.: %*i ou %*s , faz o programa ignorar a captura do dado

	while (fscanf(pFile, "%i %*s %s %s\n", &typeUser, targetId, targetPassword) != -1){
		if (strcmp(sourceId,targetId)== 0){
			// achou o Id
			printf("\nID encontrado!\n");

			// se a senha for correta
			if(strcmp(sourcePassword, targetPassword)==0){
				printf("Senha encontrada!\n\n");
                system("pause");
				fclose(pFile);
				return true;
			}
		}
	}
	return false;
}

bool hasCourse(){
	FILE* pFile = fopen("courses.txt", "rb");
	// por padrão, considera-se que nao ha administrador
	char type;
	// se o primeiro caracter do arquivo users.txt for 0, entao há adm e deve mandar para menu de escolha
	while ((char(type = getc(pFile)))!=EOF){
		if (type != NULL){
			return true;
		}
		// break para pegar apenas o primeiro caracter
		break;
	}
	fclose(pFile);
    return false;
}

bool findStudentByKey(){
    system("cls");
    printf("Enter de search key (student id): ");
    int searchId, id, courseId;
    char birthDate[10];
    scanf("%d", &searchId);

    FILE* pFile = fopen("students.txt", "rb");

    bool flag;
    char name[31];
    while (fscanf(pFile, "%i %s %s %i\n", &id, name, birthDate, &courseId) != -1){
        if (id == searchId){
            printf("\nStudent finded!\n\t%i %s %s %i\n\n", id, name, birthDate, courseId);
            system("pause");
            flag = true;
        }
	}
	fclose(pFile);
	if (flag)
        return true;
	return false;
}

void commonMenu(){
    int option;
    do{
        system("cls");
        printf("\nMenu - Common:\n\n");
        printf("Choose one option\n\t1-Record student\n\t2-Show students\n\t3-Find student by ID");
        printf("\n\t4-Show disciplines\n\t5-Show courses\n\t9-Exit\n-> ");
        scanf("%i", &option);

        switch (option){
            case 1:
                // se nao tiver curso cadastrado, nao permite cadastrar estudante
                if (hasCourse()){
                    if(!recordStudent())
                        printf("Couldn't record a new student, try again..\n\n");
                } else {
                    printf("Couldn't record a new student, because there's no courses..\n\n");
                    system("pause");
                }
                break;
            case 2:
                if(!showStudent()){
                    printf("Couldn't show the students, try again..\n\n");
                    system("pause");
                }
                break;
            case 3:
                if(!findStudentByKey()){
                    printf("Couldn't find the student, try again..\n\n");
                    system("pause");
                }
                break;
            case 4:
                // se nao tiver curso cadastrado, nao permite cadastrar disciplina
                if (hasCourse()){
                    if(!showDisciplines())
                        printf("Couldn't show the disciplines, because there's no courses..\n\n");
                } else {
                    printf("Couldn't show the disciplines, becas..\n\n");
                }
                system("pause");
                break;
            case 5:
                if(!showCourses()){
                    printf("Couldn't show the courses, try again..\n\n");
                    system("pause");
                }
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid option, try again..\n\n");
        }
    } while (option != 9);
}

void adminMenu(){
    int option;
    do {
        system("cls");
        printf("\nMenu - Admin:\n\n");
        printf("Choose one option:\n\n\t1-Record user\n\t2-Record student\n\t3-Record course");
        printf("\n\t4-Record discipline\n\t5-Show disciplines\n\t6-Show courses\n\t7-Show students");
        printf("\n\t8-Find student by ID\n\t9-Exit\n-> ");
        scanf("%i", &option);

        switch (option) {
            case 1:
                system("cls");
                int type;
                printf("Enter the user type <0 - admin | 1 - common>: ");
                scanf("%d", &type);

                if(!recordUser(type))
                    printf("Couldn't record a new user, try again..\n\n");
                break;
            case 2:
                // se nao tiver curso cadastrado, nao permite cadastrar estudante
                if (hasCourse()){
                    if(!recordStudent())
                        printf("Couldn't record a new student, try again..\n\n");
                } else {
                    printf("Couldn't record a new student, because there's no courses..\n\n");
                    system("pause");
                }
                system("pause");
                break;
            case 3:
                if(!recordCourse())
                    printf("Couldn't record a new course, try again..\n\n");
                break;
            case 4:
                if (hasCourse()){
                    if(!recordDiscipline())
                        printf("Couldn't record a new discipline, try again..\n\n");
                } else {
                    printf("Couldn't record a new discipline, because there's no courses..\n\n");
                }
                system("pause");
                break;
            case 5:
                // se nao tiver curso cadastrado, nao permite cadastrar disciplina
                if (hasCourse()){
                    if(!showDisciplines())
                        printf("Couldn't show the disciplines, try again..\n\n");
                } else {
                    printf("Couldn't show the disciplines, because there's no courses..\n\n");
                }
                system("pause");
                break;
            case 6:
                if(!showCourses())
                    printf("Couldn't show the courses, try again..\n\n");
                system("pause");
                break;
            case 7:
                if(!showStudent())
                    printf("Couldn't show the students, try again..\n\n");
                system("pause");
                break;
            case 8:
                if(!findStudentByKey())
                    printf("Couldn't find the student, try again..\n\n");
                system("pause");
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid option, try again..\n\n");
        }
    } while (option != 9);

    system("pause");
}

void createFile(char* filename){
    char file[31];
    const char* ext = ".txt";
    strcat(strcpy(file, filename), ext);
    // garantindo que haverá arquivo criado:
	// criando um arquivo txt com o nome de "users"
	FILE* pFile = fopen(file, "ab");
	fclose(pFile);
}

int main(){
    char aux1[31], aux2[31], aux3[31], aux4[31];
	strcpy(aux1,"users");
	strcpy(aux2,"students");
	strcpy(aux3,"courses");
	strcpy(aux4,"disciplines");

    /*Criando arquivos*/
    createFile(aux1);
    createFile(aux2);
    createFile(aux3);
    createFile(aux4);


	/* VER SE O ARQUIVO DE USUÁRIOS POSSUI CADASTROS */
	// abre o arquivo que armazena os usuarios em modo leitura binaria
	FILE* pFile = fopen("users.txt", "rb");
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

    /* Menu de acordo com o tipo de usuario */
    if (typeUser == 0)
        adminMenu();
    else
        commonMenu();

    system("pause");

	return 0;
}


