Atividade 3 pontos

Programa para cadastrar alunos, cursos e disciplinas.

Alunos {
	id, nome, data de nascimento e curso (id ??)
}


Curso {
	codigo-id, nome, carga horaria
}

Disciplinas{
	id, nome, carga horaria, curso	
}

Sistema{
	S� PODER� acessado apenas por usuarios cadastrados - LOGIN E SENHA - adm e comum [flag?][ADM PODE CADASTRAR ALUNOS, CURSOS E DISCIPLINAS,  CONSULTALOS E CRIAR NOVOS USUARIOS]

	os comuns nao podem cadastarr cursos, disciplinas e novos usuarios
}

ARQUIVOS (ARMAZENADO EM BIN�RIO)


IDS E CODIGOS DEVEM SER GERADOS SEQUENCIALMENTE

IMPLEMENTAR INTEGRIDADE REFERENCIAL ENTRE (ALUNO E CURSO  & ENTRE CURSO E DISCIPLINA)

cadastrar usuario (apenas adm)
cadastrar aluno
cadastrar curso (apenas adm)
cadastrar disciplina (apenas adm)
listar aluno
listar disciplina
listar curso
consultar aluno por codigo
sair

4arquivos: users[login]; students; courses; disciplines.



metodos:


bool VerifyCourseIdExistence()






FILES:

USER{
	type name id password
	
}

STUDENT {

}



menus:
->para adm:
Cadastrar usu�rio (apenas adm)
Cadastrar aluno
Cadastrar curso (apenas adm)
Cadastrar disciplina (apenas adm)
Listar aluno
Listar disciplina
Listar curso
Consultar aluno por c�digo
Sair			

->para usuario comum:

-cadastrar aluno
-listar aluno
-listar disciplina
-listar curso
-consultar aluno por codigo 
-sair



SE O PRIMEIRO CARACTER FOR 0 -> FALSE
SE O PRIMEIRO CARACTER N�O FOR 0 -> TRUE