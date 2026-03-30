//Count Me Out

#include <stdio.h>
#define tamAL 3

typedef struct aluno{
    int matricula;
    char sexo;
} aluno;


int main(void){

    int listaAluno[tamAL];
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
                                    listaAluno[qtdAL] = matricula;
                                    qtdAL++;
                                    printf("Aluno cadastrado com sucesso")
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
                                    printf("Matrícula: %d\n", listaAluno[i]);
                        }
                    }
                        case 3:{
                            
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