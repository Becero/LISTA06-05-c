#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int escolha;

typedef struct sPessoa
{
    char nome[100];
    int matricula;
}PESSOA;

typedef struct sCell{
    PESSOA info;
    struct sCell *next;
}CELULA;

CELULA* criarCelula()
{
    CELULA *nova = (CELULA *)malloc(sizeof(CELULA));
    return nova;
}

void inicializar_LISTA(CELULA **lista)
{
    (*lista) = NULL;
}

int verificar_LISTA_Vazia(CELULA **lista)
{
    if((*lista) == NULL)
    {
        return 1;
    }
    return 0;
}

int inserir_LISTA_fim(CELULA **lista, PESSOA elemento)
{
    CELULA *novaCELULA; //Armazena end. nova
    CELULA *auxiliar;   //Utilizando p/ percorrer

    //Aloca Espaço na mem. para novaCelula

    novaCELULA = criarCelula();
    if(novaCELULA == NULL)
    {
        printf("\nERRO: Memoria cheia");
        return 0;
    }
    //Colocando elemento dentro da célula
    novaCELULA->info = elemento;
    novaCELULA->next = NULL;

    //Se a lista estiver vazia
    if(verificar_LISTA_Vazia(lista))
    {
        (*lista) = novaCELULA;
        return 1;
    }

    //Auxiliar inicia busca pelo ultimo elemento;
    auxiliar = (*lista);

    //Procurar última célula
    while(auxiliar->next != NULL)
    {
        auxiliar = auxiliar->next;
    }

    auxiliar->next = novaCELULA;
    return 1;

}

int inserir_LISTA_inicio(CELULA **lista, PESSOA elemento)
{
    CELULA *novaCelula = criarCelula();
    if(novaCelula == NULL)
    {
        printf("\nERRO: memoria cheia");
        return 0;
    }

    if(verificar_LISTA_Vazia(lista))
    {
        //se a lista estiver vazia, chama função "Inserir Fim"
        return inserir_LISTA_fim(lista, elemento);
    }

    //preenche nova celula com elemento
    novaCelula->info = elemento;

    //next deve apontar pra primeira celula.
    novaCelula->next = (*lista);
    (*lista) = novaCelula;
    return 1;

}

void imprimir_ELEMENTO(PESSOA elemento)
{
    printf("\nMatricula: %d;\nNome: %s\n",elemento.matricula, elemento.nome);
}

void imprimir_LISTA(CELULA **lista)
{
    CELULA *auxiliar = (*lista);

    if(verificar_LISTA_Vazia(lista))
    {
        printf("\nLista Vazia.");
    }
    else
    {
        printf("\nLista: ");
        while(auxiliar != NULL)
        {
            imprimir_ELEMENTO(auxiliar->info);
            auxiliar = auxiliar->next;
        }
        printf("============================================\n");
    }
}

ZZZZPESSOA remover_LISTA_inicio(CELULA **lista)
{
    //ponteiro para armazenar o endereco da célula a ser removida
    CELULA *removida;

    //elemento vazio
    PESSOA EL_removido;
    strcpy(EL_removido.nome, " ");
    EL_removido.matricula = -1;

    if(verificar_LISTA_Vazia(&lista))
    {
        printf("ERRO! Lista Vazia");
        return EL_removido;
    }

    //guarda endereco do primeiro elemento
    removida = (*lista);
    EL_removido = removida->info;

    (*lista) = (*lista)->next;

    free(removida);
    return EL_removido;

}

PESSOA remover_LISTA_fim(CELULA **lista)
{
    //armazena o endereco do nó a ser removido
    CELULA *removida;

    //armazena o endereco do nó que será o último
    CELULA *anterior;

    PESSOA elem_removido;
    strcpy(elem_removido.nome, " ");
    elem_removido.matricula = -1;

    if(verificar_LISTA_Vazia(&lista))
    {
        printf("ERRO! LISTA VAZIA");
        return elem_removido;
    }
    //verifica se há apenas um elemento
    if((*lista)->next == NULL)
    {
        return remover_LISTA_inicio(&lista);
    }

    //O Ponteiro removida percorrerá a lista para encontrar a última posição
    removida = (*lista);
    while(removida->next != NULL)
    {
        anterior = removida;
        removida = removida->next;
    }

    elem_removido = removida->info;
    anterior->next = NULL;
    free(removida);
    return elem_removido;

}

CELULA *pesquisar_por_MATRICULA(CELULA **lista, int mat)
{
    CELULA *auxiliar = NULL;
    if(verificar_LISTA_Vazia(lista))
    {
        printf("ERRO! 404!");
        return auxiliar;
    }

    auxiliar = (*lista); //recebe o primeiro elemento da lista;
    while(auxiliar != NULL)
    {
        if(auxiliar->info.matricula == mat) //Se encontrar uma matrícula igual, ele retorna a célula que encontrou
        {

            return auxiliar;
        }

        //se não encontrou, continua procurando
        auxiliar = auxiliar->next;
    }
    printf("\nERRO! MATRICULA NAO ENCONTRADA\n");
    return auxiliar; //caso não encontre o elemento procurado
}

PESSOA remover_LISTA_matricula(CELULA **lista, int mat)
{

    CELULA *removida;
    CELULA *anterior;

    PESSOA pRemover;
    pRemover.matricula = -1;

    if(verificar_LISTA_Vazia(lista))
    {
        printf("ERRO! Lista Vazia");
        return pRemover;
    }


    //Pesquisa pela matricula
    removida = pesquisar_por_MATRICULA(lista, mat);

    if(removida == NULL)
    {
        return pRemover;
    }
    //caso seja o primeiro elemento
    if(removida == (*lista))
    {
        return remover_LISTA_inicio(lista);
    }

    //compia o conteúdo da célula a ser removida

    pRemover = removida->info;

    anterior = (*lista);

    //encontra a célula anterior a que será removida

    while(anterior->next != removida)
    {

        anterior = anterior->next;
    }

    //movimenta o ponteiro. O anterior deve apontar para onde o removido aponta
    anterior->next = removida->next;
    free(removida);
    free(removida);

    return pRemover;
}

int main()
{
    do{
        printf("======================== MENU ========================\n");
        printf("| 0 ........................................... SAIR |\n");
        printf("| 1 ............................. VERIFICAR SE VAZIA |\n");
        printf("| 2 ...........................INSERIR PESSOA NO FIM |\n");
        printf("| 3 ........................INSERIR PESSOA NO INICIO |\n");
        printf("| 4 .......................IMPRIMIR LISTA DE PESSOAS |\n");
        printf("| 5 ........................REMOVER PESSOA NO INICIO |\n");
        printf("| 6 ...........................REMOVER PESSOA NO FIM |\n");
        printf("| 7 ..........................PESQUISAR POR MATRICULA|\n");
        printf("| 8............................REMOVER POR MATRICULA |\n");
        printf("======================================================\n");
        scanf("%d", &escolha);
        system("cls");
        switch (escolha)
        {
        case 0:
            printf("Obrigado por utilizar o Sistema!\n");
            break;
        case 1:
            verificar_LISTA_Vazia();
            break;
        case 2:
            Apre();
            break;
        /*case 3:
            printf("===================== BUSCAR CADASTRO ===================\n");
            printf("Entre com o nome a ser verificado: ");
            scanf(" %[^\n]", nomeAux);
            for (int i = 0; i < contUser; i++){
                if(strcmp(nome[i], nomeAux) == 0)
                Apre();
                }
            break;
        case 4:
            printf("======================== SOBRE =======================\n");
            printf("| Este software foi desenvolvido para fins didaticos.|\n");
            printf("| AUTOR: Eu Mesmo                              |\n");
            printf("| DATA: 01/09/2022                                   |\n");
            printf("======================================================\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    }while(escolha != 0);*/
    return 0;
}
