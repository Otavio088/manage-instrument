#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct instrumento {
    int codigo;
    char nomeInstrumento[25];
    int quantidade;
    float preco;
};
typedef struct instrumento Instrumento;

struct elemento {
    Instrumento dados;
    struct elemento *proximo;
};
typedef struct elemento* Lista;
typedef struct elemento Elemento;

Lista* criarLista();
void mostrarLista(Lista *listaInstrumentos);
void opcoes(Lista *listaInstrumentos, int *escolha);
int buscarInstrumentos(Elemento *elementoBusca, int *codigo);
int inserirLista(Lista *listaInstrumentos, Instrumento novoInstrumento);
int cadastrarInstrumento(Lista *listaInstrumentos);
int alterarInstrumento(Lista *listaInstrumentos);
int removerInstrumento(Lista *listaInstrumentos);

int main() {

    Lista *lista = criarLista();
    
    Instrumento inst1 = {20, "Violao", 33, 850.00}, inst2 = {25, "Violino", 8, 425.00}, inst3 = {35, "Teclado", 20, 1499.99};

    inserirLista(lista, inst1), inserirLista(lista, inst2), inserirLista(lista, inst3);

    int op = 0;
    while (op != 4) {
        mostrarLista(lista);

        printf("[1] - Cadastrar novo Instrumento\n");
        printf("[2] - Alteracao no Instrumento\n");
        printf("[3] - Remover instrumento da Lista\n");
        printf("[4] - Fechar Programa\n");
        printf("=================================================\n");
        printf("Escolha uma Opcao: ");
        scanf(" %d", &op);

        system("cls");

        opcoes(lista, &op);
    }


    return 0;
}

Lista* criarLista() {
    Lista *listaInstrumentos = (Lista*) malloc(sizeof(Lista)); //aloca espaço do tamanho Lista

    if (listaInstrumentos != NULL) { //se o endereço de listaInstrumentos != NULL:
        *listaInstrumentos = NULL; //aponta para NULL
    }

    return listaInstrumentos;
}

void mostrarLista(Lista *listaInstrumentos) {
    if (listaInstrumentos == NULL) {
        return 0; //lista não existe
    }

    Elemento *elemento = *listaInstrumentos; //elemento que vai apontar para onde a "cabeça da lista" aponta
    //isso para a mesma não ser perdida ao percorrer a lista.

    printf("=================================================\n");
    printf("CODIGO\tINSTRUMENTO\tQUANTIDADE\tPRECO\n");
    printf("=================================================\n"); 
    while (elemento != NULL) {
        printf("%d\t%-12s\t%d\t\t%0.2f\n", elemento->dados.codigo, elemento->dados.nomeInstrumento, elemento->dados.quantidade, elemento->dados.preco);
        elemento = elemento->proximo; //vai percorrento a lista até o endereço ser igual a NULL
    }
    printf("=================================================\n");

}

void opcoes(Lista *listaInstrumentos, int *escolha) {

    switch (*escolha) {
        case 1:
            mostrarLista(listaInstrumentos);
            cadastrarInstrumento(listaInstrumentos);
            break;
        case 2:
            mostrarLista(listaInstrumentos);
            alterarInstrumento(listaInstrumentos);
            break;
        case 3:
            mostrarLista(listaInstrumentos);
            removerInstrumento(listaInstrumentos);
            break;
        case 4:
            printf("*Programa encerrado!\n");
            exit(1);
            break;
        default:
            printf("Opcao Inexistente!\n");
            break;
    }
}

int buscarInstrumentos(Elemento *elementoBusca, int *codigo) {
	while (elementoBusca != NULL && *codigo != elementoBusca->dados.codigo) { //percorrer um por um para verificar se o codigo de instrumento ja existe
        elementoBusca = elementoBusca->proximo;
    }
    if  (elementoBusca != NULL && *codigo == elementoBusca->dados.codigo) { //ja existe
        return 0;
    }
    
    return 1;
}

int inserirLista(Lista *listaInstrumentos, Instrumento novoInstrumento) {
    if (listaInstrumentos == NULL) {
        return 0; //lista não existe
    }

    Elemento *elemento = (Elemento*) malloc(sizeof(Elemento)); //aloca novo epaço na memória para um instrumento

    if (elemento == NULL) {
        return 0; //não alocou memória
    }

    elemento->dados = novoInstrumento;

    if (*listaInstrumentos == NULL) { //quer dizer que a lista está vazia
        elemento->proximo = *listaInstrumentos; //aponta para onde "listaInstrumentos" está apontando, ou seja, para NULL
        *listaInstrumentos = elemento; //a "cabeça da lista" passa a apontar para o elemento (novo instrumento)
        return 1;
    } else {
        Elemento *anterior, *atual = *listaInstrumentos;

        while (atual != NULL && atual->dados.codigo < novoInstrumento.codigo) {
            anterior = atual; //anterios passa a ter endereço do atual
            atual = atual->proximo; //atual passa a ter o endereço do que ele aponta
        }
        if (atual == (*listaInstrumentos)) { //quer dizer que só tem 1 elemento (instrumento) na lista
            elemento->proximo = *listaInstrumentos; //ponteiro proximo do elemento aponta para NULL
            *listaInstrumentos = elemento; //listaInstrumento passa a apontar para o novo elemento
        } else {
            elemento->proximo = atual; //aponta para onde atual aponta (NULL ou maior código que ele)
            anterior->proximo = elemento; //anterior aponta para o novo elemento
        }
        return 1;
    }
}

int cadastrarInstrumento(Lista *listaInstrumentos) {
    if (listaInstrumentos == NULL) {
        return 0; //nao existe
    }

    Elemento *elementoBusca = *listaInstrumentos; //aponta para a "cabeça da lista"
    Instrumento novoInstrumento; //onde vai armazenar os dados de um novo instrumento

    printf("======Informe os dados do novo instrumento======\n");
    printf("Codigo: ");
    scanf("%d", &novoInstrumento.codigo);

	if (buscarInstrumentos(elementoBusca, &novoInstrumento.codigo) == 0) {
		system("cls");
        printf("Erro! Codigo ja existente!\n");
		return 0;
	}
    
    printf("Nome: ");
    setbuf(stdin, NULL); //limpa o buffer
    fgets(novoInstrumento.nomeInstrumento, 25, stdin);
    novoInstrumento.nomeInstrumento[strcspn(novoInstrumento.nomeInstrumento, "\n")] = '\0'; //remove caractere "\n" da string e coloca o "\0" no lugar.   

    printf("Quantidade: ");
    scanf("%d", &novoInstrumento.quantidade);
    
    printf("Preco: ");
    scanf("%f", &novoInstrumento.preco);

	system("cls");
	
    inserirLista(listaInstrumentos, novoInstrumento);
    
    return 1;
}

int alterarInstrumento(Lista *listaInstrumentos) {
    int codigoBusca = 0, op = 0;
    Elemento *elementoBusca = *listaInstrumentos; //aponta para a cabeça da lista

    printf("Codigo do Instrumento: ");
    scanf("%d", &codigoBusca); //vai buscar instrumento pelo codigo
    
    if (buscarInstrumentos(elementoBusca, &codigoBusca) == 0) {
	
		while (codigoBusca != elementoBusca->dados.codigo) {
	            elementoBusca = elementoBusca->proximo;
	    }
	
	    system("cls");
	
	    printf("=================================================\n");
	    printf("[1] - Alterar Nome\n");
	    printf("[2] - Alterar Quantidade\n");
	    printf("[3] - Alterar Preco\n");
	    printf("=================================================\n");
	    printf("Escolha uma opcao: ");
	    scanf("%d", &op);
	
	    system("cls");
	
	    switch (op) {
	        case 1:
	            mostrarLista(listaInstrumentos);
	            printf("Informe o novo Nome: ");
	            setbuf(stdin, NULL);
	            fgets(elementoBusca->dados.nomeInstrumento, 25, stdin);
	            elementoBusca->dados.nomeInstrumento[strcspn(elementoBusca->dados.nomeInstrumento, "\n")] = '\0';
	            system("cls");
	        break;
	        case 2:
	            mostrarLista(listaInstrumentos);
	            printf("Informe a nova Quantidade: ");
	            scanf("%d", &elementoBusca->dados.quantidade);
	            system("cls");
	        break;
	        case 3:
	            mostrarLista(listaInstrumentos);
	            printf("Informe o novo Preco: ");
	            scanf("%f", &elementoBusca->dados.preco);
	            system("cls");
	        break;
	        default:
	            printf("Opcao Inexistente!\n");
	            mostrarLista(listaInstrumentos);
	        break;
	    }
	
	    return 1;
	}
	
    system("cls");
	printf("Instrumento inexistente!\n");
	return 0;
}

int removerInstrumento(Lista *listaInstrumentos) {
    int codigoBusca = 0;
    Elemento *anterior = NULL, *elementoBusca = *listaInstrumentos;

    printf("Codigo do Instrumento: ");
    scanf("%d", &codigoBusca);

	while (codigoBusca != elementoBusca->dados.codigo) {
        if (codigoBusca < elementoBusca->dados.codigo) {
            system("cls");
            printf("Instrumento inexistente!\n");
            return 0;
        }
		if (elementoBusca->proximo == NULL) {
            system("cls");
            printf("Instrumento inexistente!\n");
            return 0;
        } else {
            anterior = elementoBusca;
            elementoBusca = elementoBusca->proximo;
        }
    }

    if (elementoBusca == (*listaInstrumentos)) {
        (*listaInstrumentos) = elementoBusca->proximo;
    } else {
        anterior->proximo = elementoBusca->proximo;
    }

    free(elementoBusca); //desaloca espaço na memória

    system("cls");

    return 1;
}