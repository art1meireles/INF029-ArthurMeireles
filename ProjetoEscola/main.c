//Count Me Out

#include <stdio.h>
#define tamAL 3

typedef struct aluno{
    int matricula;
    char sexo;
    int ativo; //1 = ativo, -1 = inativo
} aluno;


int main(void){

    aluno listaAluno[tamAL];
    int opc;
    int sair = 0; //falso
    int qtdAL = 0;   

    
    while(!sair){
        printf("MENU INCIAL\n");
        printf("1 - Aluno\n");
        printf("2 - Professor\n");
        printf("3 - Disciplina\n");
        printf("0 - Sair\n");

        scanf("%d", &opc);

        switch(opc){
            case 0:{
                sair = 1; //encerra o programa
                break;
            }
            case 1:{

                int opcAL;
                int sairAL = 0;
                
                while(!sairAL){
                    printf("*MODULO ALUNO*\n");
                    printf("1 - Cadastro de alunos\n");
                    printf("2 - Lista de alunos\n");
                    printf("3 - Editar dados de alunos\n");
                    printf("4 - Exclusão de aluno\n");
                    printf("0 - Sair\n");  
                    
                    scanf("%d", &opcAL);

                    switch(opcAL){
                        case 0:{
                            sairAL = 1; //encerra o programa
                            break;
                        }
                        case 1:{
                            printf("CADASTRO DE ALUNOS\n");
                            if (qtdAL == tamAL){
                                printf("Lista de alunos cheia!\n");
                            }else{
                                printf("Digite a matricula:\n");
                                int matricula;
                                scanf("%d", &matricula);

                                if(matricula < 0){
                                    printf("Matricula invalida\n");
                                }else{                                    
                                    listaAluno[qtdAL].matricula = matricula;
                                    listaAluno[qtdAL].ativo = 1;                                    
                                    qtdAL++;
                                    printf("Aluno cadastrado com sucesso");
                                }
                            break;                           
                        }
                        }  
                        case 2:{
                            printf("LISTA DE ALUNOS\n");
                            if(qtdAL == 0){
                                printf("Lista vazia!\n");
                            }else{
                                for(int i =0; i < qtdAL; i++)
                                    if(listaAluno[i].ativo) //verifica se o aluno está ativo
                                        printf("Matrícula: %d\n", listaAluno[i].matricula);
                        }
                    }
                        case 3:{
                            break;
                        }
                        case 4:{
                                printf("Digite a matricula:\n");
                                int matricula;
                                scanf("%d", &matricula);
                                int achou = 0; //flag para verificar se encontrou o aluno
                                if(matricula < 0){
                                    printf("Matricula invalida\n");
                                }else{
                                    for(int i = 0; i < qtdAL; i++)
                                        if(listaAluno[i].matricula == matricula){ //exclusão lógica
                                            listaAluno[i].ativo = -1; //inativo
                                            achou = 1; //aluno encontrado
                                            break;
                                        }
                                    if(achou)
                                        printf("Aluno excluido com sucesso\n");
                                    else
                                    printf("Aluno não encontrado\n");
                                }
                                break;                          
                        }
                     
                } 
            }
            case 2:{
                printf("MODULO PROFESSOR\n");
                break;
            }
            case 3:{
                printf("MODULO DISCIPLINA\n");
                break;
            }default:{
                printf("Opcao invalida\n");                                             
        }
    }

}
}
}