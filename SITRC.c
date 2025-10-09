#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAX_PRODUTOS 100

void limparBufferDeEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void pagamentoDinheiro(double valorCompra)
{
    double valorPago = 0.0;
    double troco = 0.0;
    int op;

    printf("\nPrecisa de troco?\n");
    printf("1 - Sim\n");
    printf("2 - Nao\n");
    scanf("%d", &op);

    if (op == 1)
    {
        printf("Digite o valor pago:\nR$ ");
        scanf("%lf", &valorPago);
        limparBufferDeEntrada();

        troco = valorPago - valorCompra;

        if (troco < 0)
            printf("\nValor pago insuficiente! Falta R$ %.2lf\n", -troco);
        else
            printf("\n*** TROCO: R$ %.2lf ***\n", troco);
    }
    else
    {
        printf("\nPagamento exato recebido. Sem troco.\n");
    }
}

struct produto
{
    char nome[50];
    double preco;
    int ref;
    int quantidade;
};

void cadastrarProduto(struct produto *produtos, int *total)
{
    int opcao;
    do
    {
        printf("\n=== MENU DE CADASTRO DE PRODUTOS ===\n");
        printf("1 - Adicionar novo produto\n");
        printf("2 - Sair para o Menu principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBufferDeEntrada();

        switch (opcao)
        {
        case 1:
            printf("\nCadastrando novo produto...\n");

            printf("Nome: ");
            fgets(produtos[*total].nome, sizeof(produtos[*total].nome), stdin);
            produtos[*total].nome[strcspn(produtos[*total].nome, "\n")] = '\0'; // remove o \n

            printf("Preço: R$ ");
            scanf("%lf", &produtos[*total].preco);

            printf("Referência (número inteiro): ");
            scanf("%d", &produtos[*total].ref);

            printf("Quantidade: ");
            scanf("%d", &produtos[*total].quantidade);
            limparBufferDeEntrada();

            (*total)++; // incrementa o total
            printf("\n Produto cadastrado com sucesso!\n");
            break;

        case 2:
            printf("\nVoltando ao menu principal...\n");
            break;

        default:
            printf("\nOpção inválida!\n");
        }
    } while (opcao != 2);
}

int main()
{
    setlocale(LC_ALL, "Portuguese");

    struct produto produtos[MAX_PRODUTOS];
    int totalProdutos = 0;
    int opcao;

    do
    {
        printf("\n==============================\n");
        printf("  SUPERMERCADO C - MENU\n");
        printf("==============================\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Realizar nova venda\n");
        printf("4 - Mostrar total de vendas\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBufferDeEntrada();

        switch (opcao)
        {
        case 1:
            cadastrarProduto(produtos, &totalProdutos);
            break;

        case 2:
            printf("\n=== LISTA DE PRODUTOS ===\n");
            for (int i = 0; i < totalProdutos; i++)
            {
                printf("%d. %s - R$ %.2lf - Ref: %d - Qtde: %d\n",
                       i + 1,
                       produtos[i].nome,
                       produtos[i].preco,
                       produtos[i].ref,
                       produtos[i].quantidade);
            }
            if (totalProdutos == 0)
                printf("Nenhum produto cadastrado ainda.\n");
            break;

        case 3: {

            double valorCompra = 0;

            printf("Insira o valor da compra:\nR$ ");
            scanf("%lf", &valorCompra);
            limparBufferDeEntrada();

            int opcao;
            printf("\nForma de pagamento:\n");
            printf("1 - Dinheiro\n");
            printf("2 - Cartao (Debito)\n");
            printf("3 - Cartao (Credito)\n");
            scanf("%d", &opcao);

            switch (opcao)
            {
            case 1:
            {
                pagamentoDinheiro(valorCompra);
                break;
            }

            case 2:
                printf("\nPagamento no débito realizado com sucesso.\n");
                break;

            case 3:
                printf("\nPagamento no crédito realizado com sucesso.\n");
                break;

            default:
                printf("\nOpção inválida.\n");
                break;
            }
            break; }

        case 4:
            printf("\nFunção de total de vendas ainda não implementada.\n");
            break;

        case 0:
            printf("\nSaindo do sistema...\n");
            break;

        default:
            printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}