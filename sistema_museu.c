#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

#define QUANTIDADE 200
#define INTEIRA 10.00
#define GRATUITO 0.00
#define MEIA 5.00
#define SENHA 9653
#define ANO 2023
#define N 11

struct cliente{
    char nome[QUANTIDADE][50];
    char email[QUANTIDADE][50];
    char data_Nascimento[QUANTIDADE][N];
    char telefone[QUANTIDADE][50];
    int ativo;
    int numeroTicket;
    float valorIngresso;
};
int numeroTicketsEmitidos = 1;
float faturamentoTotal = 0.0;
int sessao;
int senha;
int op;
int i;

struct cliente Cliente[QUANTIDADE];

/* Protótipo de função */
void menu();
void comprar();
void numeroTicket();
void imprimirTicket();
void faturamento();
bool validar();
void administracao();
void cadastrar();
void remover();
void lista();
void pesquisar();
void salvarCSV();
void lerCSV();

int main(void) {
    setlocale(LC_ALL, "portuguese");

    lerCSV();

    menu();

    salvarCSV();

    return 0;
}
void menu(){
    do{
        printf("\n -------------Menu Cliente-------------");
        printf("\n 1- Comprar\t 2- Validar\t");
        printf("\n 4- administracao\t\n ");
        printf("3- Sair\t\n ");
        scanf("%d",&op);
        getchar();
        switch(op){
         case 1:
            comprar();
            break;
         case 2:
            validar();
            break;
         case 4:
             printf(" Digite a senha: ");
             scanf("%d", &senha);
             if(senha == SENHA){
                administracao();
             }
             else{
                printf("\n A senha inserida está incorreta\n");
             }
            break;
        }

    }while(op != 3);
}

void comprar() {
    int ingressos = 0;
    int i;
    char nome[100];
    char email[50];
    char data_Nascimento[11];
    char telefone[15];
    int op;

    printf("\n Bem vindo ao Terminal de Compras do Museu!\n ");

    do {
        printf("\n Essas são as sessões disponíveis:\n\n ");
        printf("1. Início às 12:00 e término às 13:00\n ");
        printf("2. Início às 15:00 e término às 16:00\n ");
        printf("3. Início às 19:00 e término às 20:00\n\n ");
        printf("Qual Sessão deseja assistir? (1, 2 ou 3)\n ");
        scanf("%d", &sessao);

        if (sessao >= 1 && sessao <= 3) {
            printf("\n Ótima escolha!\n ");
            printf("Abaixo os tipos de Ingresso disponíveis:\n ");
            printf("1. Inteira: %.2f\n ", INTEIRA);
            printf("2. Meia: %.2f\n ", MEIA);
            printf("3. Gratuito: À partir de 60 anos %.2f\n", GRATUITO);
            printf(" Selecione o tipo de ingresso: (1,2 ou 3)\n ");
            scanf("%d", &ingressos);

            if (ingressos >= 1 && ingressos <= 3) {
                printf("\n Cadastro \n");

                    // Limpar o buffer de entrada
                    while (getchar() != '\n');

                    printf("\n Digite seu nome: ");
                    fgets(nome, 100, stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    printf("\n Digite o seu E-mail: ");
                    scanf("%s", email);
                    printf("\n Digite sua data de nascimento (DD/MM/AAAA): ");
                    scanf("%s", data_Nascimento);
                    printf("\n Digite o seu telefone: ");
                    scanf("%s", telefone);

                    for (i = 0; i < QUANTIDADE; ++i) {
                        if (Cliente[i].ativo == 0){
                            Cliente[i].numeroTicket = numeroTicketsEmitidos++;
                            strcpy(Cliente[i].nome, nome);
                            strcpy(Cliente[i].email, email);
                            strcpy(Cliente[i].data_Nascimento, data_Nascimento);
                            strcpy(Cliente[i].telefone, telefone);
                            Cliente[i].ativo = 1;
                            Cliente[i].valorIngresso = (ingressos == 1) ? INTEIRA : ((ingressos == 2) ? MEIA : GRATUITO);
                            faturamentoTotal += Cliente[i].valorIngresso;
                            numeroTicket(Cliente[i]);
                            imprimirTicket(Cliente[i]);
                            break;
                            getchar();
                        }
                    }
                    getchar();
                    printf("\n 1- Comprar novo ingresso\n 0- Sair do cadastro para a tela de menu\n ");
                    scanf("%d", &op);
                }else {
                printf("Ingresso indisponível\n");
            }
            }
         else {
            printf("Sessão indisponível\n");
        }
    } while (op == 1);
}
void numeroTicket(struct cliente cliente){
    for(i = 0; i < QUANTIDADE; i++){
            printf("\n\n\n Cliente Cadastrado com Sucesso! Ticket: ");
            printf(" %04d\n\n\n", cliente.numeroTicket);
            break;
            if (i = 1) {
                printf("\n Aproveite e Valide seu Registro!\n ");
            }
    }
}
void imprimirTicket(struct cliente cliente)
{
    //função para imprimir os detalhes do ticket

    printf("\n ------------    Detalhes do Ticket    ------------\n");
    printf(" Tipo de Ingresso: ");
    if (cliente.valorIngresso == INTEIRA) {
        printf("Inteira\n");
    } else if (cliente.valorIngresso == MEIA) {
        printf("Meia\n");
    } else {
        printf("Gratuito\n");
    }
    printf(" Sessao Escolhida: ");
    switch (sessao) {
        case 1:
            printf("12:00 - 13:00");
            break;
        case 2:
            printf("15:00 - 16:00");
            break;
        case 3:
            printf("19:00 - 20:00");
            break;
        default:
            printf("Sessao Invalida");
            break;
    } printf(" | Cliente: %04d",cliente.numeroTicket);
    printf("\n --------------------------------------------------");
    printf("\n Nome: %s",cliente.nome);
    printf("\n E-mail: %s", cliente.email);
    printf("\n Data de Nascimento: %s", cliente.data_Nascimento);
    printf("\n Telefone: %s", cliente.telefone);
    /* Imprimir outros detalhes do ticket, como valorIngresso, sessao, etc.*/
    printf("\n --------------------------------------------------\n");
}
void faturamento(){

    printf("\n Faturamento total: R$ %.2f\n", faturamentoTotal);
    printf("\n Pressione Enter...\n");
    getchar();
}
bool validar() {
    int numeroTicket;
    char dataNascimento[N];
    int num;

    printf("Digite o código do ingresso: ");
    scanf("%d", &numeroTicket);

    // Loop para procurar o ticket
    for (int i = 0; i < QUANTIDADE; ++i) {
        if (Cliente[i].ativo == 1 && Cliente[i].numeroTicket == numeroTicket) {
            printf("\n Digite sua data de nascimento (DD/MM/AAAA): ");
            scanf("%s", dataNascimento);

            // Comparar a data de nascimento
            if (strcmp(Cliente[i].data_Nascimento, dataNascimento) == 0) {
                // Se a data de nascimento corresponder, imprimir os detalhes do ticket
                imprimirTicket(Cliente[i]);

                printf("\n Você deseja fazer a validação? (sim - 1 não - 0)\n ");
                scanf("%d", &num);

                if (num > 0) {
                    printf("\n Validação feita com sucesso!\n");
                    return true;  // Retorna true se a validação for bem-sucedida
                } else {
                    printf("\n Não foi feita a validação!\n");
                    return false;  // Retorna false se a validação não for concluída
                }
            } else {
                printf("\n Data de nascimento incorreta para o ticket %d\n", numeroTicket);
                return false;  // Retorna false se a data de nascimento não corresponder
            }
        }
    }

    // Se chegou aqui, o ticket não foi encontrado
    printf("\n Ticket %d não encontrado\n", numeroTicket);
    return false;  // Retorna false se o ticket não for encontrado
}
void administracao(){
    do{
        printf("\n ----Administracao----");
        printf("\n ----Menu Constate----\n");
        printf("\n 1- Cadastrar Clientes\n 2- Remover Clientes");
        printf("\n 3- Listar todos Clientes\n 4- Pesquisar Clientes");
        printf("\n 5- Faturamento\n");
        printf("                  6- Sair \n ");
        scanf("%d",&op);
        fflush(stdin); //limpar o buffer do teclado
        switch(op){
        case 1:
            cadastrar();
            break;
        case 2:
            remover();
            break;
        case 3:
            lista();
            break;
        case 4:
            pesquisar();
            break;
        case 5:
            faturamento();
            break;
        }
    }while(op!=6);
}
void cadastrar(){
    comprar();
}

void remover(){

    int ingressos;
    int Cadastro;
    int i;
    lista();

    printf(" Digite o numero do Cadastro do cliente que sera removido: ");
    scanf("%d",&Cadastro);
    getchar();

        if(Cadastro > 0 && Cadastro <= QUANTIDADE && Cliente[Cadastro - 1].ativo == 1){
            int ingressosDecrementado = --ingressos;
            float valorIngressoRemovido = Cliente[Cadastro - 1].valorIngresso;

            Cliente[Cadastro - 1].ativo = 0;

            faturamentoTotal -= valorIngressoRemovido;

            printf("\n Cliente foi excluido com sucesso!!\n");
        }else{
            printf("\n Numero de Cadastro 'Invalido!' ou Cliente 'Inativo!'!!\n");
    }
}
void lista(){

    int i;
    printf("\n\n Lista dos Clientes\n\n");

    for(i = 0; i < QUANTIDADE;  ++i){
        if(Cliente[i].ativo == 1){
            printf(" Ticket: %.4d\n", i + 1);
            printf(" --------------------");
            printf("\n Nome: %s", Cliente[i].nome);
            printf("\n E-mail: %s", Cliente[i].email);
            printf("\n Data de Nascimento: %s",Cliente[i].data_Nascimento);
            printf("\n Telefone: %s",Cliente[i].telefone);
            printf("\n --------------------\n");

            }

        }
        printf("\n Pressione Enter ...");
        getchar(); //Esperar a entrada do usuario
    }


void pesquisar(){

    char nome[50];
    char email[50];
    char telefone[15];

    do{
        printf("\n Digite: 1 para pesquisar pelo Nome");
        printf("\n Digite: 2 para pesquisar pelo E-mail");
        printf("\n Digite: 3 para pesquisar pelo Telefone\n ");
        scanf("%d", &op);
        getchar(); //limpar buff do teclado

        switch(op){
            case 1:
                //pesquisa pelo o nome
                printf("\n Digite o Nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0'; /* Remover a quebra de linha*/
                for(i = 0; i < QUANTIDADE; i++){
                    if (Cliente[i].ativo == 1 && strcmp(Cliente[i].nome, nome) == 0) {
                        printf("\n Nome: %s\n Email: %s\n Data de Nascimento: %s\n Telefone: %s\n",
                               Cliente[i].nome, Cliente[i].email, Cliente[i].data_Nascimento, Cliente[i].telefone);
                break;
                    }
                }
                break;
            case 2:
                printf("\n Digite o E-mail: ");
                fgets(email, sizeof(email), stdin);
                email[strcspn(email, "\n")] = '\0'; /* Remover a quebra de linha*/
                for(i = 0; i < QUANTIDADE; i++){
                    if (Cliente[i].ativo == 1 && strcmp(Cliente[i].email, email) == 0) {
                        printf("\n Nome: %s\n Email: %s\n Data de Nascimento: %s\n Telefone: %s\n",
                               Cliente[i].nome, Cliente[i].email, Cliente[i].data_Nascimento, Cliente[i].telefone);
                break;
                    }
                }
                break;
            case 3:
                printf("\n Digite o Telefone: ");
                fgets(telefone, sizeof(telefone), stdin);
                telefone[strcspn(telefone, "\n")] = '\0'; /* Remover a quebra de linha*/
                for(i = 0; i < QUANTIDADE; i++){
                    if (Cliente[i].ativo == 1 && strcmp(Cliente[i].telefone, telefone) == 0) {
                        printf("\n Nome: %s\n Email: %s\n Data de Nascimento: %s\n Telefone: %s\n",
                               Cliente[i].nome, Cliente[i].email, Cliente[i].data_Nascimento, Cliente[i].telefone);
                break;
                    }
                }
                break;
            default:
                printf("\n Numero de escolha 'Invalido'\n");
                break;
        }
        printf("\n Digite 4 para continuar Pesquisando!");
        printf("\n Digite qualquer outro valor para Sair!\n ");
        scanf("%d", & op);
        getchar();//limpar buffer do teclado
    }while(op == 4 );
    getchar();
}
void salvarCSV() {
    FILE *file = fopen("dados.csv", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    int i;
    for (i = 0; i < QUANTIDADE; ++i) {
        if (Cliente[i].ativo == 1) {
            fprintf(file, "%s,%s,%s,%s,%d\n",
                    Cliente[i].nome, Cliente[i].email,
                    Cliente[i].data_Nascimento, Cliente[i].telefone,
                    Cliente[i].numeroTicket);
        }
    }

    fclose(file);
}


void lerCSV() {
    int numCliente = 0;

    FILE *file = fopen("dados.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha[QUANTIDADE];
    while (fgets(linha, sizeof(linha), file) && numCliente < QUANTIDADE) {
        sscanf(linha, "%49[^,],%49[^,],%11[^,],%15[^,],%d",
               Cliente[numCliente].nome, Cliente[numCliente].email,
               Cliente[numCliente].data_Nascimento, Cliente[numCliente].telefone,
               &Cliente[numCliente].numeroTicket);
        numCliente++;
    }

    fclose(file);
}
