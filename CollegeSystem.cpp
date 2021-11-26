/* Desenvolver um programa para cadastrar alunos, cursos e disciplinas.
Para os alunos deve-se cadastrar o id, nome, data de nascimento e o curso (c�digo).
De cada curso armazena-se o c�digo, o nome e a carga hor�ria.
Os dados das disciplinas s�o id, nome, carga hor�ria e curso (c�digo).
O sistema poder� ser acessado apenas por usu�rios cadastrados, o acesso se d� por login e senha, contudo haver� dois tipos de usu�rios (administrador e comum).
Os usu�rios administradores poder�o cadastrar alunos, cursos e disciplinas, bem como consult�-los e criar  novos usu�rios.
Os usu�rios comuns n�o poder�o cadastrar cursos, disciplinas e novos usu�rios.
Todos os cadastros dever�o ser armazenados em arquivo em modo bin�rio.
Os id e c�digos dever�o ser gerados sequencialmente.
Implementar integridade referencial entre aluno e curso e entre curso e disciplina.
As op��es do menu s�o:
Cadastrar usu�rio (apenas adm)
Cadastrar aluno
Cadastrar curso (apenas adm)
Cadastrar disciplina (apenas adm)
Listar aluno
Listar disciplina
Listar curso
Consultar aluno por c�digo
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

	//declara��o do ponteiro para o arquivo
	FILE* pFile;

	// primeira vez - inicializa��o da sequ�ncia [verifica SE N�O ja esta aberto]
	if ((pFile=fopen(file, "rb"))==NULL){
		// inicializa como 1
		seq = 1;

		//abrir o arquivo no modo escrita para armazenar o valor inicial
		pFile = fopen(file, "wb");

		// armazenar o valor inicial no arquivvo
		fprintf(pFile, "%d ", seq);

		// fechar o arquivo
		fclose(pFile);
	} else {	// se o arquivo ja est� aberto (n vezes)
		// encontrar o valor corrente da sequ�ncia
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
	system("cls");

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

	// entrada do id
	user.id = sequenceId("sequenceUser");
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

	student.id = sequenceId("sequenceStudent");

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
/*
int getWorkTime(FILE* pCourseFile, FILE* pDiscipineFile){
    int WorkTime;
    // pegar as strings de nomes, buscar no arquivo de disciplinas e somar WorkTime
    while (fscanf(pCourseFile, "%i %*s %i %s\n", &typeUser, &targetId, targetPassword) != -1){
		if (sourceId == targetId){

    return WorkTime;
    */

bool recordCourse(){
    // curso armazena-se o id, o nome e a carga hor�ria e (discipinas listadas?).
    system("cls");

	FILE* pFile;
	if ((pFile = fopen("courses.txt", "ab")) == NULL)
        return false;
	COURSE course;

	course.id = sequenceId("sequenceCourse");
	printf("Course Id: %d\n\n", course.id);

	printf("Enter the course name: ");
    fflush(stdin);
    gets(course.name);

    course.workTime = 0;
    printf("Course worktime defined: 0\t(There's no disciplines still, it will be added after)\n\n");
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

	discipline.id = sequenceId("sequenceDiscipline");
	printf("Discipline ID: %i\n\n", discipline.id);

	printf("Enter the discipline name: ");
    fflush(stdin);
    gets(discipline.name);

    printf("\nEnter the worktime (hours): ");
    scanf("%i", &discipline.workTime);

    // entrada de dados - course_id
    /*FAZER VALIDACAO DE SE O CURSO EXISTE NO FILE "courses"*/
    FILE* pCoursesFile;
    bool courseExists=false;
    int  courseId, courseWorkTime;
    do{
        printf("\nEnter the course Id: ");
        //showCourses();
        scanf("%d", &discipline.courseId);
        pCoursesFile = fopen("courses.txt", "rb");
        while (fscanf(pCoursesFile, "%i %*s %i", &courseId, &courseWorkTime) != -1){
            if (courseId == discipline.courseId){
                courseExists = true;
            }
        }
        system("cls");
    } while (courseExists == false);

    /*vai incrementando a carga horaria do curso.
    fclose(pCoursesFile);
    pCoursesFile = fopen("courses.txt", "ab");
    int newWorkTime = courseWorkTime+=discipline.workTime;
    fprintf(pCoursesFile, "%i %s %i", 2, "calcNew", newWorkTime);
    printf("\n\nINCREMENTADO -> %d\n\n", newWorkTime);
    system("pause");
    fclose(pCoursesFile);*/

    // armazena no arquivo disciplines.txt
    fprintf(pDisciplineFile, "%i %s %i\n", discipline.id, discipline.name, discipline.workTime);
    fclose(pDisciplineFile);
    fclose(pCoursesFile);

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

bool showCourses(){
    system("cls");
    int id, workTime;
    char name[31];
    FILE* pFile;
	if ((pFile = fopen("courses.txt", "rb"))==NULL)
		return false;

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

	while (fscanf(pFile, "%i %s %i %i\n", &id, name, &workTime, &courseId) != -1){
        printf("%i %s %i %i\n", id, name, workTime, courseId);
	}
	system("pause");

	fclose(pFile);
    return true;
}

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

	// obs.: %*i ou %*s , faz o programa ignorar a captura do dado

	while (fscanf(pFile, "%i %*s %i %s\n", &typeUser, &targetId, targetPassword) != -1){
		if (sourceId == targetId){
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
	// por padr�o, considera-se que nao ha administrador
	char type;
	// se o primeiro caracter do arquivo users.txt for 0, entao h� adm e deve mandar para menu de escolha
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
    printf("Enter de search key (student id): ");
    int searchId, id, courseId;
    char name[31], birthDate[10];
    scanf("%d", &searchId);

    FILE* pFile = fopen("students.txt", "rb");

    while (fscanf(pFile, "%i %s %s %i\n", &id, name, birthDate, &courseId) != -1){
        if (id == searchId){
            printf("Student finded!\n\t%i %s %s %i\n\n", id, name, birthDate, courseId);
            system("pause");
            return true;
        }
	}
	return false;
}

void commonMenu(){
    int option;
    do{
        system("cls");
        printf("\nMenu - Common:\n\n");
        printf("Choose one option\n\t1-Record student\n\t2-Show students\n\t3-Find student by ID");
        printf("\n\t4-Show disciplines\n\t5-Show courses\n\t9-Exit\n: ");
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
                if(!showStudent())
                    printf("Couldn't show the students, try again..\n\n");
                break;
            case 3:
                if(!findStudentByKey())
                    printf("Couldn't find the student, try again..\n\n");
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
                if(!showCourses())
                        printf("Couldn't show the courses, try again..\n\n");
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
                break;
            case 5:
                // se nao tiver curso cadastrado, nao permite cadastrar disciplina
                if (hasCourse()){
                    if(!showDisciplines())
                        printf("Couldn't show the disciplines, because there's no courses..\n\n");
                } else {
                    printf("Couldn't show the disciplines, becas..\n\n");
                }
                system("pause");
                break;
            case 6:
                if(!showCourses())
                    printf("Couldn't show the courses, try again..\n\n");
                break;
            case 7:
                if(!showStudent())
                    printf("Couldn't show the students, try again..\n\n");
                break;
            case 8:
                //if(!findStudentByKey())
                  //  printf("Couldn't find the student, try again..\n\n");
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
    // garantindo que haver� arquivo criado:
	// criando um arquivo txt com o nome de "users"
	FILE* pFile = fopen(file, "ab");
	fclose(pFile);
}

int main(){
    /*Criando arquivos*/
    createFile("users");
    createFile("students");
    createFile("courses");
    createFile("disciplines");
    //createFile("sequenceUser");
    //createFile("sequenceStudent");
    //createFile("sequenceCourse");
    //createFile("sequenceDiscipline");

	/* VER SE O ARQUIVO DE USU�RIOS POSSUI CADASTROS */
	// abre o arquivo que armazena os usuarios em modo leitura binaria
	FILE* pFile = fopen("users.txt", "rb");
	// por padr�o, considera-se que nao ha administrador
	bool hasAdm = false;
	char type;
	// se o primeiro caracter do arquivo users.txt for 0, entao h� adm e deve mandar para menu de escolha
	while ((char(type = getc(pFile)))!=EOF){
		if (type == '0'){
			hasAdm = true;
		}
		// break para pegar apenas o primeiro caracter
		break;
	}
	fclose(pFile);

	// Caso tenha adm cadastrado, deve-se fazer login (ou sair),
	// caso n�o, deve mandar para a fauncao recordUser passando o type
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
					// se login � false (!), avise que deu erro de login
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


