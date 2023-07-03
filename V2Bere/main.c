#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

///struct dos itens
struct produtos
{
    char nome[20];
    int estoque;
    float valor;
    int contador;
};

struct produtos padaria[5] =
{
    {"Pão de Forma", 0, 7.5, 0},
    {"Pão de Centeio", 0, 8.69, 0},
    {"Broa de Milho", 0, 5, 0},
    {"Sonho", 0, 4.5, 0},
    {"Tubaína", 0, 3.25, 0}
};

///-----------------------------------------------------------------------------------------------------------
///Cadastrar os produtos
void cadastro()
{
    system("cls");
    int item, menu, compras = 0;

    printf("Selecionado: Cadastrar estoque\n\n");

///Lista de produtos para cadasatro
    printf("   CÓDIGO    |       ITEM\n");
    for(int i = 0; i < 5; i++)
        printf("      %d         %-14s\n", i + 1, padaria[i].nome);

    do
    {
        printf("\nSelecione o código do item que deseja alterar o estoque: ");
        scanf("%d", &item);
        item--;
        if((item < 0) || (item > 4))
            printf("Código inválido\n");
        else
        {
            printf("Selecionado: %s\n", padaria[item].nome);
            puts("\n\nPressione [ENTER] para continuar");
            getchar();
        }
    }
    while((item < 0) || (item > 4));

///Atribuição de valor do estoque no padaria[].estoque e no padaria[].contador
    do
    {
        system("cls");
        printf("Digite a quantidade do estoque: ");
        scanf("%d", &padaria[item].estoque);

        if(padaria[item].estoque < 0)
        {
            printf("Quantidade inválida, a mesma deve ser maior ou igual a zero\n\n");
            puts("\n\nPressione [ENTER] para continuar");
            getchar();
        }
    }
    while(padaria[item].estoque < 0);

///Menu para novo cadastro, volta ao menu e sair
    do
    {
        system("cls");
        printf("Escolha:\n   CÓDIGO    |       OPÇÃO\n      1         Cadastrar mais itens\n      2         Voltar ao menu\n      3         Sair\nDigite o código: ");
        scanf("%d", &menu);
        printf("\n");
        if(menu == 1)
            cadastro();

        else if(menu == 2)
            main();

        else if(menu == 3)
            saida();

        else
            printf("Código inválido");
    }
    while(menu < 1 || menu > 3);
}

///-----------------------------------------------------------------------------------------------------------
///Função de visualizar o estoque
void visualizar()
{
    system("cls");
    printf("Selecionado: Visualizar estoque\n\n");

///Lista de estoque registrado
    printf("   CÓDIGO    |        NOME        |   PREÇO   |   ESTOQUE\n");
    for(int i = 0; i < 5; i++)
        printf("      %d         %-14s       R$%.2f        %3d\n", i + 1, padaria[i].nome, padaria[i].valor, padaria[i].estoque);

    puts("\n\nPressione [ENTER] para continuar");
    getchar();
    getchar();
///Chamada da função opção para selecionar se quer voltar ao menu inicial ou sair do programa
    opcao();
}

///-----------------------------------------------------------------------------------------------------------
///Função para atribuir uma quantidade, calcular o valor total e realizar as vendas
float venda()
{
    system("cls");
    int item = 0, quantidade = 0, vendas = 0, menu;
    float vendido[20][3], valor_total = 0;

    printf("Selecionado: Realizar venda\n\n");

///A variavel "repete" serve para repetir sempre que quiser fazer uma nova compra
    for(int repete = 1; repete == 1;)
    {

///Esse "do" é para repetir caso o cliente queira continuar a compra, após ela dar errado
        do
        {
///Lista de produtos com código, nome, preço e estoque
            printf("   CÓDIGO    |        NOME        |   PREÇO   |   ESTOQUE\n");
            for(int i = 0; i < 5; i++)
                printf("      %d         %-14s       R$%.2f        %3d\n", i + 1, padaria[i].nome, padaria[i].valor, padaria[i].estoque);

            do
            {
                printf("\nSelecione o código do item: ");
                scanf("%d", &item);
                item--;

                if((item < 0) || (item > 4))
                    printf("\nCódigo inválido\n");

                else
                    printf("Selecionado: %s\n", padaria[item].nome);
            }
            while((item < 0) || (item > 4));

            printf("\nSelecione a quantidade: ");
            scanf("%d", &quantidade);

            if((padaria[item].estoque < quantidade)||(quantidade < 0))
            {
                system("cls");
                printf("\nQuantidade inválida ou estoque insuficiente\n\n");

///Lista para escolher se deseja continuar a compra, voltar ao menu ou sair do código
                do
                {
                    system("cls");
                    printf("Escolha:\n   CÓDIGO    |       OPÇÃO\n      1         Continuar a compra\n      2         Voltar ao menu\n      3         Sair\nDigite o código: ");
                    scanf("%d", &menu);
                    if(menu == 1)
                        printf("\n");

                    else if(menu == 2)
                        main();

                    else if(menu == 3)
                        saida();

                    else
                    {
                        printf("Código inválido");
                        puts("\n\nPressione [ENTER] para continuar");
                        getchar();
                    }
                }
                while(menu < 1 || menu > 3);
            }
        }
///Caso o cliente queira continuar a compra após ela dar errado, esse "while" levará ele ao início
        while((padaria[item].estoque < quantidade) || (quantidade < 0));

///Subtração do estoque por quantidade comprada
        padaria[item].estoque -= quantidade;
        padaria[item].contador += quantidade;

        vendido[vendas][0] = item, vendido[vendas][1] = quantidade, vendido[vendas][2] = padaria[item].valor * quantidade;

        valor_total += padaria[item].valor * quantidade;

        system("cls");
        printf("Valor total da compra: %.2f\n", valor_total);

///se a quantidade for diferente de zero, adiciona uma venda (na variável "vendas") na nota fiscal
        if(quantidade != 0)
            vendas++;

        printf("\nDeseja realizar outra venda?\n   CÓDIGO    |       OPÇÃO\n      1               Sim\n      2               Não\nDigite o código: ");
        do
        {
            scanf("%d", &repete);
            if((repete > 2) || (repete < 1))
                printf("\nCódigo inválido\n\nDigite o código novamente: ");
        }
        while((repete > 2) || (repete < 1));
    }

///o vetor "vendido" tem o proposito de salvar as vendas e ordenar em ordem crescente de acordo com o valor
///das vendas

///Essa sequência de "for" serve para colocar "vendido" em ordem crescente usando bubble sort
    for(int i = 0; i < vendas - 1; i++)
    {
        if(vendido[i][2] < vendido[i + 1][2])
        {
            for(int j = 0; j < 3; j++)
            {
                int aux = vendido[i][j];
                vendido[i][j] = vendido[i + 1][j];
                vendido[i + 1][j] = aux;
            }
        }
    }

    system("cls");
///Nota fiscal
    printf("\n   ITEM    |        NOME        |   VALOR UNITÁRIO   |   QUANTIDADE   |   SUBTOTAL\n");

    for(int i = 0; i < vendas; i++)
    {
        printf("     %d         %-14s           R$%.2f              %3.0f           R$%.2f\n",
               i + 1, padaria[(int)vendido[i][0]].nome, padaria[(int)vendido[i][0]].valor, vendido[i][1], vendido[i][2]);
    }
    printf("                                                             TOTAL:   |   R$%.2f\n", valor_total);

    puts("\n\nPressione [ENTER] para continuar");
    getchar();
///A função está retornando o valor total
    return valor_total;
}

///-----------------------------------------------------------------------------------------------------------
///Esta função está calculando e dando o troco, caso a pessoa necessite de troco
void valor_troco(float valor_total)
{
    system("cls");
///a variável "valor_pago" serve para colocar o quanto o cliente pagou
    float valor_pago, troco;

    printf("Valor total: %.2f\n", valor_total);
    printf("Digite o valor pago: ");
    scanf("%f", &valor_pago);
    troco = valor_pago - valor_total;

    if (troco >= 0)
        printf("\nTroco: %.2f\n", troco);
    else
    {
        printf("\nValor insuficiente\n");
        puts("\n\nPressione [ENTER] para continuar");
        getchar();
        valor_troco(valor_total);
    }
    printf("\nCompra finalizada\n");
    puts("\n\nPressione [ENTER] para continuar");
    getchar();
    opcao();
}

///-----------------------------------------------------------------------------------------------------------
///Função para caso o pagamento seja à vista
void vista(float valor_total)
{
    system("cls");
///"diferença" é a variável que tem o objetivo de calcular o desconto ou acréscimo
    int troco;
    float total = 0, diferenca = 0;

    if (valor_total < 50)
    {
        printf ("Desconto de 5%%\n");
        diferenca = valor_total * 0.05;
    }

    else if (valor_total >= 50 && valor_total < 100)
    {
        printf ("Desconto de 10%%\n");
        diferenca = valor_total * 0.1;
    }

    else
    {
        printf ("Desconto de 18%%\n");
        diferenca = valor_total * 0.18;
    }
///valor_total = valor_total - diferenca para calcular quanto foi a compra
    valor_total -= diferenca;
    printf("Valor total: %.2f\n", valor_total);

    do
    {
        printf("\nTroco é necessário?\n   CÓDIGO    |       OPÇÃO\n      1               Sim\n      2               Não\nDigite o código: ");
        scanf("%d", &troco);

        if(troco == 1)
            valor_troco(valor_total);

        else if(troco == 2)
            opcao();

        else
            printf("\nCódigo incorreto\n");
    }
    while(troco < 1 || troco > 2);
}

///-----------------------------------------------------------------------------------------------------------
///Função para caso o pagamento for a prazo
void prazo(float valor_total)
{
    system("cls");
///"diferença" é a variável que tem o objetivo de calcular o desconto ou acréscimo
    int parcela;
    float diferenca = 0, valor_mensal;

    printf("Digite quantas parcelas: ");
    scanf("%d", &parcela);

    if ((parcela >= 1)&&(parcela <= 3))
    {
        printf ("\nAcréscimo de 5%%\n");
        diferenca = valor_total * 0.05;

        valor_total += diferenca;
        valor_mensal = valor_total / parcela;

        printf ("\nValor total: %.2f\n", valor_total);
        printf ("Valor parcela: %.2f\n", valor_mensal);
    }

    else if (parcela > 3)
    {
        printf ("\nAcréscimo de 8%%\n");
        diferenca = valor_total * 0.08;

        valor_total += diferenca;
        valor_mensal = valor_total / parcela;

        printf ("\nValor total: %.2f\n", valor_total);
        printf ("Valor parcela: %.2f\n", valor_mensal);
    }
    else
    {
        printf("\nNúmero de parcelas inválido, digite um valor igual ou acima de 1 parcela\n");
        puts("\n\nPressione [ENTER] para continuar");
        getchar();
        prazo(valor_total);
    }
    printf("\nCompra finalizada\n");

    opcao();
}

///-----------------------------------------------------------------------------------------------------------
///Função para escolher a forma de pagamento, se à vista ou a prazo
void pagamento(float valor_total)
{
    system("cls");
    int modo_pagamento;

    printf("\nFormas de pagamento\n   CÓDIGO    |       OPÇÃO\n      1             À vista\n      2             A prazo\nDigite o código: ");
    scanf("%d", &modo_pagamento);

    if (modo_pagamento == 1)
    {
        printf("\nPagamento à vista\n");
        vista(valor_total);
    }

    else if (modo_pagamento == 2)
    {
        printf("\nPagamento a prazo\n");
        prazo(valor_total);
    }
    else
    {
        printf("\nOpção de pagamento inválida\n");
        puts("\n\nPressione [ENTER] para continuar");
        getchar();
        pagamento(valor_total);
    }
}

///-----------------------------------------------------------------------------------------------------------
///Função de saída para apresentar um relatório de vendas, mostrando a quantidade de vendas por item
/// e finalização do programa
void saida()
{
    system("cls");
    printf("Selecionado: Sair\n\n");
    printf("        NOME        |   VENDIDOS\n");
    for(int i = 0; i < 5; i++)
        printf("  %-14s          %3d\n", padaria[i].nome, padaria[i].contador);

    exit(0);
}

///-----------------------------------------------------------------------------------------------------------
///Função que traz a opção de menu inicial ou saída do programa
void opcao()
{
    system("cls");
    int menu;

    printf("Escolha:\n   CÓDIGO    |       OPÇÃO\n      1         Retornar ao menu\n      2         Sair\nDigite o código: ");
    scanf("%d", &menu);
    puts("");

    if(menu == 1)
        main();
    else if (menu == 2)
        saida();
    else
    {
        printf("Código inválido");
        puts("\n\nPressione [ENTER] para continuar");
        getchar();
        opcao();
    }
}
///-----------------------------------------------------------------------------------------------------------
///Função main, tem o menu inicial
int main()
{
    setlocale(LC_ALL, "Portuguese");

    system("cls");
    int menu = 0;

    printf("   CÓDIGO    |       OPÇÃO\n      1         Cadastrar estoque\n      2         Visualizar estoque\n      3         Realizar venda\n      4         Sair\n\nDigite o código: ");
    do
    {
        scanf("%d", &menu);
        printf("\n");

        switch(menu)
        {
        case 1:
            cadastro();
            break;

        case 2:
            visualizar();
            break;

        case 3:
            pagamento(venda());
            break;

        case 4:
            saida();
            break;

        default:
            printf("Código inválido\n\nDigite novamente: ");
        }
    }
    while(menu < 0 || menu > 4);
    return 0;
}
