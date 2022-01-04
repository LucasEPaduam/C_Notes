#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <sys/types.h>
#include <sys/stat.h>

#define tamanho_limite 4096


void desenho_superior_programa();
void desenho_finalizacao();
void menu_categorias();
void digitar_informacao();
int salvar_arquivo(char nome_pasta[], char nome_arquivo[], char conteudo_arquivo[]);
int salvar_arquivo_novacat(char conteudo_arquivo[]);
int erros_na_gravacao = 0;
int salvar_nota = 0;
char string_de_trabalho[tamanho_limite] = "";
char nome_do_arquivo[255] = "";
char nome_da_pasta[255] = "";
char* informacao_total_digitada;
char resposta_salvar = 'S';




int main(void){

    char escolha1;

    do
    {

        system("cls");

        desenho_superior_programa();

        printf("  1 - Criar Nota\n\n");
        printf("  2 - Ler Nota\n\n");
        printf("  3 - SAIR\n\n");

        printf("  Digite o número da categoria desejada: ",setlocale(LC_ALL,""));
        scanf(" %c", &escolha1);


        switch (escolha1)
        {
        case '1':
            menu_categorias();
            break;
        case '2':
            menu_lernotas();
            break;
        case '3':
            desenho_finalizacao ();
            break;
        default:
            printf ("\n\n  OPÇÃO INVÁLIDA. ESCOLHA UMA DAS OPÇÕES VÁLIDAS PARA CONTINUAR.\n\n");
            system ("  pause");
            break;
        }
    }
    while (escolha1 != '3');


    return 0;
}

void desenho_superior_programa(){

    printf("  ************************************\n");
    printf("  *                                  *\n");
    printf("  *              C NOTES             *\n");
    printf("  *                                  *\n");
    printf("  ************************************\n\n");
    printf("    O seu bloquinho de notas digital\n\n\n");

}

void desenho_finalizacao (){

    printf("\n\n**********************\n");
    printf("*                    *\n");
    printf("*    ATÉ MAIS!!! :)  *\n");
    printf("*                    *\n");
    printf("**********************\n\n");

}

void menu_lernotas(){

    char escolha_lercategorias;
    char nova_categoria[1024];

    do
    {
        system("cls");

        desenho_superior_programa();

        printf("*  EM QUAL CATEGORIA ESTÁ A SUA NOTA?  *\n\n\n", setlocale(LC_ALL,""));
        printf("  1 - Minhas Ideias\n\n");
        printf("  2 - Livros, Músicas e Filmes\n\n");
        printf("  3 - CheckList\n\n");
        printf("  4 - Minhas Categorias\n\n");
        printf("  5 - VOLTAR\n\n");

        printf("  Digite o numero da categoria desejada.\n");
        printf("  Todas as notas desta categoria serão listadas abaixo: ");
        scanf(" %c", &escolha_lercategorias);
        printf ("\n");


        switch (escolha_lercategorias)
        {
        case '1':
        case '2':
        case '3':
        case '4':

            if (escolha_lercategorias == '1')
            {
                strcpy (nome_da_pasta, "MINHAS IDEIAS");
            }
            else if (escolha_lercategorias == '2')
            {
                strcpy (nome_da_pasta, "LIVROS_MUSICAS E FILMES");
            }
            else if (escolha_lercategorias == '3')
            {
                strcpy (nome_da_pasta, "CHECKLIST");
            }
            else if (escolha_lercategorias == '4')
            {
                printf ("  * MINHAS CATEGORIAS *\n");
                printf ("   *******************\n\n");
                ler_arquivo_info_pasta (nome_da_pasta);
                fflush(stdin);
                printf("\n  Digite o Nome da categoria desejada: ");
                scanf("%[^\n]", &nome_da_pasta);
                strcpy(nova_categoria, "MINHAS CATEGORIAS\\");
                strcat(nova_categoria, nome_da_pasta);
                strcpy(nome_da_pasta, nova_categoria);


                fflush(stdin);
                printf ("\n");
                fflush(stdin);
                printf("\n  * NOTAS DA CATEGORIA INDICADA *\n");
                printf("   *****************************\n\n");
            }

            ler_arquivo_info(nome_da_pasta);


            fflush(stdin);
            printf("\n  Digite o Nome da nota que deseja ler: ");
            scanf("%[^\n]", &nome_do_arquivo);
            fflush(stdin);
            system("cls");




            if (strlen(string_de_trabalho) > 0)
            {
                strcpy(string_de_trabalho, "");
            }

            ler_arquivo(nome_da_pasta, nome_do_arquivo, &string_de_trabalho);

            if (strlen(string_de_trabalho) > 0)
            {
                printf("\n\n SEGUE ABAIXO CONTEÚDO DA NOTA '%s\\%s'\n\n", nome_da_pasta, nome_do_arquivo);

                printf("*****************************\n");
                printf("*****************************\n\n");
                printf("  %s\n", string_de_trabalho);
                printf("*****************************\n");
                printf("*****************************\n\n");
            }
            else
            {
                printf("  Arquivo Nao Encontrado.\n\n");
                printf("  Por favor, Tente novamente.\n\n");
            }

            printf("\n\n  Aperte Qualquer Tecla Para Voltar ao Menu...");
            getch();
            break;

        case '5':
            break;

        default:
            break;
        }

    }
    while (escolha_lercategorias != '5');


}

void ler_arquivo_info_pasta(char nome_da_pasta[]){

    FILE* arquivo;
    char caminho_final_arquivo[tamanho_limite] = "";
    char conteudo_lido[tamanho_limite] = "";

    strcat(caminho_final_arquivo, ".\\");
    strcat(caminho_final_arquivo, "MINHAS CATEGORIAS");
    strcat(caminho_final_arquivo, "\\infopasta.txt");

    arquivo = fopen(caminho_final_arquivo, "r");

    if(arquivo == NULL)
    {
        printf("  Nenhuma nota nesta categoria.\n\n");
        printf("\n\n  Aperte Qualquer Tecla Para Voltar ao Menu...");
        getch();
        system ("cls");
        return 1;

    }

    while(fgets(conteudo_lido, tamanho_limite, arquivo) != NULL)
    {
        printf("  %s\n", conteudo_lido);
    }

    fclose(arquivo);

}

void ler_arquivo_info(char nome_da_pasta[]){

    FILE* arquivo;
    char caminho_final_arquivo[tamanho_limite] = "";
    char conteudo_lido[tamanho_limite] = "";

    strcat(caminho_final_arquivo, ".\\");
    strcat(caminho_final_arquivo, nome_da_pasta);
    strcat(caminho_final_arquivo, "\\info.txt");

    arquivo = fopen(caminho_final_arquivo, "r");

    if(arquivo == NULL)
    {
        printf("  Nenhuma nota nesta categoria.\n\n");
        printf("\n\n  Aperte Qualquer Tecla Para Voltar ao Menu...");
        getch();
        system ("cls");
        return 1;

    }

    while(fgets(conteudo_lido, tamanho_limite, arquivo) != NULL)
    {
        printf("  %s\n", conteudo_lido);
    }

    fclose(arquivo);

}


void ler_arquivo(char nome_pasta[], char nome_arquivo[], char* conteudo_do_arquivo){

    FILE* arquivo;
    char caminho_final_arquivo[tamanho_limite] = "";
    char conteudo_lido[tamanho_limite] = "";

    strcat(caminho_final_arquivo, ".\\");
    strcat(caminho_final_arquivo, nome_pasta);
    strcat(caminho_final_arquivo, "\\");
    strcat(caminho_final_arquivo, nome_arquivo);
    strcat(caminho_final_arquivo, ".txt");

    arquivo = fopen(caminho_final_arquivo, "r");

    if(arquivo == NULL)
    {
        printf("\n  Erro ao Abrir a nota. \n");
    }

    while(fgets(conteudo_lido, tamanho_limite, arquivo) != NULL)
    {
        strcat(conteudo_do_arquivo, conteudo_lido);
    }

    fclose(arquivo);
}

void menu_categorias(){

    char escolha_categorias;
    char nova_categoria[1024];

    do
    {

        system("cls");

        desenho_superior_programa();

        printf("     * CATEGORIAS *\n\n\n");
        printf("  1 - Minhas Ideias\n\n");
        printf("  2 - Livros, Músicas e Filmes\n\n");
        printf("  3 - CheckList\n\n");
        printf("  4 - Criar Nova Categoria\n\n");
        printf("  5 - VOLTAR\n\n");


        printf("  Digite o numero da categoria desejada: ");
        scanf(" %c", &escolha_categorias);


        switch (escolha_categorias)
        {
        case '1':
        case '2':
        case '3':
        case '4':

            system("cls");

            if (escolha_categorias == '1')
            {

                printf("*******************\n");
                printf("*  MINHAS IDEIAS  *\n");
                printf("*******************\n\n");

                strcpy (nome_da_pasta, "MINHAS IDEIAS");

            }
            else if (escolha_categorias == '2')
            {

                printf("******************************\n");
                printf("*  LIVROS, MÚSICAS E FILMES  *\n");
                printf("******************************\n\n");

                strcpy (nome_da_pasta, "LIVROS_MUSICAS E FILMES");

            }
            else if (escolha_categorias == '3')
            {

                printf("*********************\n");
                printf("*     CHECKLIST     *\n");
                printf("*********************\n\n");

                strcpy (nome_da_pasta, "CHECKLIST");

            }
            else if (escolha_categorias == '4')
            {

                printf("  *********************\n");
                printf("  *                   *\n");
                printf("  *     ?????????     *\n");
                printf("  *                   *\n");
                printf("  *********************\n\n");

                printf("\n  Digite o nome da nova categoria: ");
                fflush(stdin);
                scanf("%[^\n]", &nome_da_pasta);

                salvar_arquivo_novacat(nome_da_pasta);


                system("cls");

                printf("******************************\n\n");
                printf("            %s               \n\n", nome_da_pasta);
                printf("******************************\n\n");

                strcpy(nova_categoria, "MINHAS CATEGORIAS\\");
                strcat(nova_categoria, nome_da_pasta);
                strcpy(nome_da_pasta, nova_categoria);


            }



            digitar_informacao(&string_de_trabalho);

            do
            {
                printf("\n  Deseja salvar nota? S ou N: ");
                scanf (" %c", &resposta_salvar);

                if (resposta_salvar == 'S' || resposta_salvar == 's')
                {

                    printf("\n\n  Digite o Nome do Arquivo: ");
                    fflush(stdin);
                    scanf("%[^\n]", &nome_do_arquivo);
                    system("cls");

                    erros_na_gravacao = salvar_arquivo(nome_da_pasta, nome_do_arquivo, string_de_trabalho);

                    if (erros_na_gravacao)
                    {
                        printf("\n\n  Gravacao Falhou. Tentar Novamente\n\n");
                    }
                    else
                    {
                        printf("\n\n  Gravacao Bem Sucedida!\n\n");
                    }
                    printf("\n\n  Aperte Qualquer Tecla Para Voltar ao Menu Categorias...");
                    getch();

                }
                else if (resposta_salvar == 'N' || resposta_salvar == 'n')
                {

                }
                else
                {
                    printf ("\n  CÓDIGO INVÁLIDO, TENTE NOVAMENTE\n.");
                }
            }
            while (resposta_salvar != 'S'&& resposta_salvar != 's' && resposta_salvar != 'N' && resposta_salvar != 'n');

            break;

        case '5':
            break;

        default:
            printf ("\n  OPÇÃO INVÁLIDA, TENTE NOVAMENTE.\n\n");
            system ("pause");
            break;
        }


    }
    while (escolha_categorias != '5');

}


void digitar_informacao(char* informacao_total_digitada){

    char linha_digitada[tamanho_limite] = "";
    char ultima_captura[tamanho_limite] = "";

    printf("  Digite sua nota abaixo!\n");
    printf("  Para finalizar a nota, tecle ENTER e digite FIM.\n\n");

    strcpy(informacao_total_digitada, "");
    while (strcmp(linha_digitada, "FIM") != 0 && strlen(informacao_total_digitada) < 4096)
    {

        printf("=>");
        fflush(stdin);
        scanf("%[^\n]", &linha_digitada);

        if (strcmp(linha_digitada, "FIM") != 0 && strcmp(linha_digitada, ultima_captura) != 0)
        {
            strcat(informacao_total_digitada, linha_digitada);
            strcat(informacao_total_digitada, "\n");
        }
        else if (strcmp(linha_digitada, ultima_captura) == 0)
        {
            strcat(informacao_total_digitada, "\n");
        }
        strcpy(ultima_captura, linha_digitada);
    }
}

int salvar_arquivo_novacat(char nome_nova_categoria[]){


    FILE* arquivo;
    char caminho_final_arquivo[tamanho_limite] = "";

    mkdir("MINHAS CATEGORIAS", 0777);

    strcpy(caminho_final_arquivo, "");
    strcat(caminho_final_arquivo, ".\\");
    strcat(caminho_final_arquivo, "MINHAS CATEGORIAS");
    strcat(caminho_final_arquivo, "\\infopasta.txt");

    arquivo = fopen(caminho_final_arquivo, "a");

    if(arquivo == NULL)
    {
        return 1;
    }

    fprintf (arquivo, "%s\n", nome_nova_categoria);

    fclose (arquivo);
    return 0;
}


int salvar_arquivo(char nome_pasta[], char nome_arquivo[], char conteudo_arquivo[]){



    FILE* arquivo;
    char caminho_final_arquivo[tamanho_limite] = "";


    strcat(caminho_final_arquivo, ".\\");
    strcat(caminho_final_arquivo, nome_pasta);
    strcat(caminho_final_arquivo, "\\");
    strcat(caminho_final_arquivo, nome_arquivo);
    strcat(caminho_final_arquivo, ".txt");

    mkdir(nome_pasta, 0777);

    arquivo = fopen(caminho_final_arquivo, "w");

    if(arquivo == NULL)
    {
        return 1;
    }

    fprintf(arquivo, "%s", conteudo_arquivo);

    fclose(arquivo);

    strcpy(caminho_final_arquivo, "");
    strcat(caminho_final_arquivo, ".\\");
    strcat(caminho_final_arquivo, nome_pasta);
    strcat(caminho_final_arquivo, "\\info.txt");

    arquivo = fopen(caminho_final_arquivo, "a");

    if(arquivo == NULL)
    {
        return 1;
    }

    fprintf (arquivo, "%s\n", nome_arquivo);

    fclose (arquivo);

    return 0;
}
