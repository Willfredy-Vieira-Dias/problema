// ================================ BIBLIOTECAS INCLUÍDAS ============================

// Biblioteca personalizada para operações específicas do dicionário.
#include "dicionario.h"

// Biblioteca padrão do C para funções gerais, como alocação de memória, gerenciamento de processos, entre outros.
#include <stdlib.h>

// Biblioteca padrão do C para entrada e saída de dados.
#include <stdio.h>

// Biblioteca padrão de strings do C para manipulações de strings, como cópia, concatenação, comparação e outras operações com strings.
#include <string.h>

// Biblioteca para configurar as definições locais/regional do sistema.
#include <locale.h>

// ================================ FUNÇÕES DO DICIONÁRIO ============================
// As implementações das funções declaradas no arquivo 'dicionario.h' ocorrem aqui.

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void printTST(NoTST *no) {
    if (no == NULL) return;

    printTST(no->esquerda);

    if (no->fim_palavra == true)
        printf("%c (fim de palavra)\n", no->caractere);
    else
        printf("%c\n", no->caractere);

    printTST(no->centro);
    printTST(no->direito);
}


void destruirNo(NoTST *no) {
    if (no == NULL) {
        return;
    }

    destruirNo(no->esquerda);
    destruirNo(no->centro);
    destruirNo(no->direito);

    free(no);
}

void destruirDicionario(Dicionario *dicionario) {
    destruirNo(dicionario->raiz);
    free(dicionario);
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// ********************************* INICIALIZAÇÃO ***********************************

Dicionario *inicializarDicionario() {
    // Alocação de memória para o novo dicionario
    Dicionario *novoDicionario = (Dicionario *) malloc(sizeof(Dicionario));

    // Verificação de sucesso da alocação de memória
    if (novoDicionario == NULL) {
        printf("[Falha na alocação de memória para o novo dicionário]\n");
        return NULL;
    }

    // Inicialização dos membros do novo objeto Dicionario
    novoDicionario->raiz = NULL;
    novoDicionario->hash_ficheiro = NULL;

    // Retorno do novo objeto Dicionario
    printf("[Alocação de memória feita com sucesso!\nDicionário inicializado com sucesso!]\n");
    return novoDicionario;
}

// Implementação da função inicializarNo
NoTST *inicializarNo(char caractere)
{
    // Alocar memória para o novo nó
    NoTST *novoNo = (NoTST *)malloc(sizeof(NoTST));

    // Verificar se a alocação de memória foi bem-sucedida
    if (novoNo == NULL)
    {
        printf("[Falha na alocação de memória para o novo nó].\n");
        return NULL;
    }

    // Inicializar o caractere do nó e a flag de fim de palavra
    novoNo->caractere = caractere;
    novoNo->fim_palavra = false;

    // Inicializar todos os ponteiros dos nós filhos com NULL
    novoNo->esquerda = NULL;
    novoNo->centro = NULL;
    novoNo->direito = NULL;

    // Retornar o novo nó
    return novoNo;
}

// *********************************** INSERÇÃO ***********************************

// Função auxiliar para inserir um nó na árvore.
NoTST *inserirNo(NoTST *raiz, const char *palavra, int indice) {
    // Se a raiz é NULL, cria um novo nó.
    if (raiz == NULL) {
        raiz = inicializarNo(palavra[indice]);
    }

    // Se o caractere da palavra é menor que o caractere do nó,
    // então a nova palavra deve ser inserida no nó à esquerda.
    if (palavra[indice] < raiz->caractere) {
        raiz->esquerda = inserirNo(raiz->esquerda, palavra, indice);
    }
    // Se o caractere da palavra é maior que o caractere do nó,
    // então a nova palavra deve ser inserida no nó à direita.
    else if (palavra[indice] > raiz->caractere) {
        raiz->direito = inserirNo(raiz->direito, palavra, indice);
    }
    // Se o caractere da palavra é igual ao caractere do nó,
    // então a nova palavra deve ser inserida no nó do centro.
    else {
        // Se o fim da palavra ainda não foi alcançado, continue para o próximo caractere.
        if (indice + 1 < (int)strlen(palavra)) {
            raiz->centro = inserirNo(raiz->centro, palavra, indice + 1);
        }
        // Se o fim da palavra foi alcançado, marque o fim da palavra como verdadeiro.
        else {
            raiz->fim_palavra = true;
        }
    }
    return raiz;
}

// Insere uma palavra no dicionário.
void inserirPalavra(Dicionario *dicionario, const char *palavra) {
    // Verifica se o dicionário é válido.
    if (dicionario == NULL) {
        printf("Dicionario invalido.\n");
        return;
    }

    // Chama a função auxiliar para inserir a palavra.
    dicionario->raiz = inserirNo(dicionario->raiz, palavra, 0);
}

// *********************************** CONSULTA ***********************************

// Função auxiliar para consultar uma palavra na árvore.
bool consultarPalavraRecursivo(NoTST *raiz, const char *palavra, int indice)
{
    if (raiz == NULL)
    {
        printf("Chegamos a um nó NULL, interrompendo a busca.\n");
        return false; // A palavra não foi encontrada.
    }

    // Se o caractere atual é menor que o caractere do nó, vá para a esquerda.
    if (palavra[indice] < raiz->caractere)
    {
        printf("Vamos para a esquerda, caractere = %c, nó = %c\n", palavra[indice], raiz->caractere);
        return consultarPalavraRecursivo(raiz->esquerda, palavra, indice);
    }
    // Se o caractere atual é maior que o caractere do nó, vá para a direita.
    else if (palavra[indice] > raiz->caractere)
    {
        printf("Vamos para a direita, caractere = %c, nó = %c\n", palavra[indice], raiz->caractere);
        return consultarPalavraRecursivo(raiz->direito, palavra, indice);
    }
    // Se o caractere atual é igual ao caractere do nó:
    else
    {
        if (indice < (int)strlen(palavra) - 1)
        {
            printf("Vamos para o centro, caractere = %c, nó = %c\n", palavra[indice], raiz->caractere);
            return consultarPalavraRecursivo(raiz->centro, palavra, indice + 1); // Vá para o próximo caractere.
        }
        else
        {
            printf("Chegamos ao final da palavra, fim_palavra = %d, caractere = %c, nó = %c\n", raiz->fim_palavra, palavra[indice], raiz->caractere);
            return raiz->fim_palavra; // Se estamos no fim da palavra, retorne o valor da flag fim_palavra.
        }
    }
}


// Função para consultar uma palavra no dicionário.
bool consultarPalavra(Dicionario *dicionario, const char *palavra)
{
    // Verificar se a palavra é válida.
    if (palavra == NULL || strlen(palavra) == 0)
    {
        printf("Palavra inválida.\n");
        return false;
    }

    // Chamar a função auxiliar consultarPalavraRecursivo para consultar a palavra na árvore.
    if(consultarPalavraRecursivo(dicionario->raiz, palavra, 0)){
        printf("Encontrado!!");
        system("pause");
    }else{
        printf("Não encontrado!!");
        system("pause");
    }
    return consultarPalavraRecursivo(dicionario->raiz, palavra, 0);
}

// *********************************** REMOÇÃO ***********************************

// Função auxiliar para verificar se um nó está vazio (ou seja, não tem filhos).
bool noEstaVazio(NoTST *no)
{
    return no->esquerda == NULL && no->centro == NULL && no->direito == NULL;
}

// Função auxiliar para remover uma palavra na árvore.
NoTST *removerPalavraRecursivo(NoTST *raiz, const char *palavra, int indice)
{
    if (raiz == NULL)
    {
        return NULL; // A palavra não foi encontrada.
    }

    // Se o caractere atual é menor que o caractere do nó, vá para a esquerda.
    if (palavra[indice] < raiz->caractere)
    {
        raiz->esquerda = removerPalavraRecursivo(raiz->esquerda, palavra, indice);
    }
    // Se o caractere atual é maior que o caractere do nó, vá para a direita.
    else if (palavra[indice] > raiz->caractere)
    {
        raiz->direito = removerPalavraRecursivo(raiz->direito, palavra, indice);
    }
    // Se o caractere atual é igual ao caractere do nó:
    else
    {
        if (indice < (int)strlen(palavra) - 1)
        {
            raiz->centro = removerPalavraRecursivo(raiz->centro, palavra, indice + 1); // Vá para o próximo caractere.
        }
        else
        {
            // Chegamos ao fim da palavra. Marcar o fim da palavra como false.
            raiz->fim_palavra = false;
        }
    }

    // Se o nó atual está vazio e não é o fim de uma palavra, podemos removê-lo.
    if (noEstaVazio(raiz) && !raiz->fim_palavra)
    {
        free(raiz);
        printf("[Palavra removida com sucesso!].\n");
        printf("[Como a palavra já foi removida, portanto, ela já não está na TRIE TST criada!].");
        raiz = NULL;
    }

    return raiz;
}

// Função para remover uma palavra do dicionário.
void removerPalavra(Dicionario *dicionario, const char *palavra)
{
    // Verificar se a palavra é válida.
    if (palavra == NULL || strlen(palavra) == 0)
    {
        printf("Palavra inválida.\n");
        return;
    }

    // Chamar a função auxiliar removerPalavraRecursivo para remover a palavra da árvore.
    dicionario->raiz = removerPalavraRecursivo(dicionario->raiz, palavra, 0);
}

// *********************************** ACTUALIZAÇÃO ***********************************

// Função para atualizar uma palavra existente no dicionário.
void atualizarPalavra(Dicionario *dicionario, const char *palavraAntiga, const char *palavraNova)
{
    // Verificar se as palavras são válidas.
    if (palavraAntiga == NULL || strlen(palavraAntiga) == 0 || palavraNova == NULL || strlen(palavraNova) == 0)
    {
        printf("Palavra inválida.\n");
        return;
    }

    // Remover a palavra antiga do dicionário.
    removerPalavra(dicionario, palavraAntiga);

    // Inserir a nova palavra no dicionário.
    inserirPalavra(dicionario, palavraNova);
}

// *********************************** IMPRESSÃO DE TODAS AS PALAVRAS COM O MESMO PREFIXO DE ENTRADA ***********************************

// Função auxiliar para imprimir todas as palavras na TST que começam com o prefixo fornecido.
void palavrasComPrefixoAuxiliar(NoTST *no, char *buffer, int profundidade)
{
    if (no == NULL)
        return;

    // Armazenar o caractere neste nó.
    buffer[profundidade] = no->caractere;

    // Se o nó atual marca o fim de uma palavra, imprimi-la.
    if (no->fim_palavra)
    {
        buffer[profundidade + 1] = '\0';
        printf("%s\n", buffer);
    }

    // Percorrer os nós filhos.
    palavrasComPrefixoAuxiliar(no->esquerda, buffer, profundidade + 1);
    palavrasComPrefixoAuxiliar(no->centro, buffer, profundidade + 1);
    palavrasComPrefixoAuxiliar(no->direito, buffer, profundidade + 1);
}

// Função para imprimir todas as palavras no dicionário que começam com o prefixo fornecido.
void palavrasComPrefixo(Dicionario *dicionario, const char *prefixo)
{
    int i;

    // Verificar se o prefixo é válido.
    if (prefixo == NULL || strlen(prefixo) == 0)
    {
        printf("Prefixo inválido.\n");
        return;
    }

    // Buffer para armazenar a palavra enquanto a trie é percorrida.
    char buffer[MAX_TAMANHO_PALAVRA];

    // Nó atual para percorrer a trie.
    NoTST *noAtual = dicionario->raiz;

    // Procurar o nó que corresponde ao último caractere do prefixo.
    for (i = 0; i < (int)strlen(prefixo); i++)
    {
        while (noAtual != NULL)
        {
            if (prefixo[i] < noAtual->caractere)
                noAtual = noAtual->esquerda;
            else if (prefixo[i] > noAtual->caractere)
                noAtual = noAtual->direito;
            else
            {
                // Se este for o último caractere do prefixo, chamar a função auxiliar.
                if (i == (int)strlen(prefixo) - 1)
                    palavrasComPrefixoAuxiliar(noAtual->centro, buffer, 0);
                else
                    noAtual = noAtual->centro;
                break;
            }
        }
    }
}

// *********************************** IMPRESSÃO DA PALAVRA COM O PREFIXO MAIS LONGO ***********************************

// Função para retornar o prefixo mais longo de uma palavra que existe no dicionário.
char *prefixoMaisLongo(Dicionario *dicionario, const char *palavra)
{

    int i;

    if (palavra == NULL || strlen(palavra) == 0)
    {
        printf("Palavra inválida.\n");
        return NULL;
    }

    // Buffer para armazenar o prefixo enquanto a trie é percorrida.
    char buffer[MAX_TAMANHO_PALAVRA];
    int comprimento = 0;

    // Nó atual para percorrer a trie.
    NoTST *noAtual = dicionario->raiz;

    // Procurar o nó que corresponde ao último caractere da palavra.
    for (i = 0; i < (int)strlen(palavra); i++)
    {
        while (noAtual != NULL)
        {
            if (palavra[i] < noAtual->caractere)
                noAtual = noAtual->esquerda;
            else if (palavra[i] > noAtual->caractere)
                noAtual = noAtual->direito;
            else
            {
                buffer[comprimento] = noAtual->caractere;
                comprimento++;

                if (noAtual->fim_palavra)
                    buffer[comprimento] = '\0';

                noAtual = noAtual->centro;
                break;
            }
        }
    }

    char *prefixo = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(prefixo, buffer);
    return prefixo;
}

// *********************************** IMPRESSÃO DE TODAS AS PALAVRAS COM A MESMA DISTÂNCIA DE EDIÇÃO ***********************************

// Função que retorna o menor de três números.
int min(int a, int b, int c) {
    if (a < b) return (a < c)? a : c;
    else return (b < c)? b : c;
}

// Função que calcula a distância de edição entre duas palavras.
int distanciaEdicao(char *palavra1, char *palavra2) {
    int comprimento1 = strlen(palavra1);
    int comprimento2 = strlen(palavra2);
    
    int matriz[comprimento1+1][comprimento2+1];

    for (int i=0; i<=comprimento1; i++) {
        for (int j=0; j<=comprimento2; j++) {
            if (i == 0)
                matriz[i][j] = j;
            else if (j == 0)
                matriz[i][j] = i;
            else if (palavra1[i-1] == palavra2[j-1])
                matriz[i][j] = matriz[i-1][j-1];
            else
                matriz[i][j] = 1 + min(matriz[i][j-1],  // Inserção
                                       matriz[i-1][j],  // Remoção
                                       matriz[i-1][j-1] // Substituição
                                      );
        }
    }

    return matriz[comprimento1][comprimento2];
}


// Função auxiliar que encontra todas as palavras que estão a uma certa distância de edição de uma palavra base.
void palavrasPorDistanciaMinimaAux(NoTST *no, char *buffer, int profundidade, const char *palavraBase, int distancia) {
    if (no == NULL)
        return;
    
    // Vai para o nó esquerdo
    palavrasPorDistanciaMinimaAux(no->esquerda, buffer, profundidade, palavraBase, distancia);

    // Adiciona o caractere do nó no buffer e verifica se o nó é o fim de uma palavra
    buffer[profundidade] = no->caractere;
    if (no->fim_palavra) {
        buffer[profundidade + 1] = '\0';
        if (distanciaEdicao(buffer, strlen(buffer), palavraBase, strlen(palavraBase)) == distancia) {
            printf("%s\n", buffer);
        }
    }

    // Vai para o nó do meio
    palavrasPorDistanciaMinimaAux(no->centro, buffer, profundidade + 1, palavraBase, distancia);

    // Vai para o nó direito
    palavrasPorDistanciaMinimaAux(no->direito, buffer, profundidade, palavraBase, distancia);
}

// Imprime todas as palavras que estão a uma certa distância de edição de uma palavra base.
void palavrasPorDistanciaMinima(Dicionario *dicionario, const char *palavraBase, int distancia) {
    // Verifica se o dicionário é válido
    if (dicionario == NULL || dicionario->raiz == NULL) {
        printf("Dicionario vazio ou invalido.\n");
        return;
    }

    // Buffer para armazenar a palavra enquanto percorre a Trie
    char buffer[MAX_TAMANHO_PALAVRA];
    palavrasPorDistanciaMinimaAux(dicionario->raiz, buffer, 0, palavraBase, distancia);
}


// *********************************** VERIFICAÇÃO ORTOGRÁFICA DO FICHEIRO DE TEXTO ***********************************

// Função para tratar palavra não encontrada no dicionário
void tratarPalavraNaoEncontrada(Dicionario *dicionario, FILE *fileOutput, const char *palavra)
{
    // Imprimir a palavra
    printf("A palavra '%s' não foi encontrada no dicionário.\n", palavra);
    // Perguntar ao usuário se ele deseja adicionar a palavra ao dicionário
    char opcao;
    printf("Deseja adicionar '%s' ao dicionario? (s/n): ", palavra);
    scanf(" %c", &opcao);
    // Se o usuário responder afirmativamente
    if (opcao == 's' || opcao == 'S')
    {
        // Adicionar a palavra ao dicionário
        inserirPalavra(dicionario, palavra);
        // Imprimir uma mensagem indicando que a palavra foi adicionada
        printf("A palavra '%s' foi adicionada ao dicionário.\n", palavra);
        // Escrever a palavra no ficheiro de saída
        fprintf(fileOutput, "%s ", palavra);
    }
    else
    {
        // Se o usuário responder negativamente, imprimir uma mensagem indicando que a palavra foi marcada como errada
        printf("A palavra '%s' foi marcada como errada.\n", palavra);
        // Escrever a palavra no ficheiro de saída entre colchetes para indicar que está errada
        fprintf(fileOutput, "[%s] ", palavra);
    }
}

// Função para verificar a ortografia de um ficheiro de texto usando o dicionário
void verificarOrtografia(Dicionario *dicionario, const char *ficheiroTexto)
{
    // Abrir o ficheiro para leitura
    FILE *file = fopen(ficheiroTexto, "r");
    // Se o ficheiro não puder ser aberto, imprimir uma mensagem de erro e retornar
    if (file == NULL)
    {
        printf("Não foi possível abrir o ficheiro %s.\n", ficheiroTexto);
        return;
    }

    // Criar um novo ficheiro para a saída
    FILE *fileOutput = fopen("ficheiroTexto_atualizado.txt", "w");
    // Se o ficheiro de saída não puder ser criado, imprimir uma mensagem de erro, fechar o ficheiro de entrada e retornar
    if (fileOutput == NULL)
    {
        printf("Não foi possível criar o ficheiro de saída.\n");
        fclose(file);
        return;
    }

    // Criar um buffer para armazenar cada palavra
    char palavra[MAX_TAMANHO_PALAVRA];
    // Ler palavras do ficheiro uma de cada vez
    while (fscanf(file, "%s", palavra) == 1)
    {
        // Se a palavra não estiver no dicionário
        if (!consultarPalavra(dicionario, palavra))
        {
            tratarPalavraNaoEncontrada(dicionario, fileOutput, palavra);
        }
        else
        {
            // Se a palavra estiver no dicionário, escrevê-la no ficheiro de saída
            fprintf(fileOutput, "%s ", palavra);
        }
    }

    // Fechar os ficheiros
    fclose(file);
    fclose(fileOutput);
    // Imprimir uma mensagem indicando que a verificação de ortografia foi concluída e o nome do ficheiro de saída
    printf("Verificação de ortografia concluída. O ficheiro atualizado foi salvo como 'ficheiroTexto_atualizado.txt'.\n");
}

// *********************************** IMPRESSÃO DE TODAS AS PALAVRAS EM ORDEM ***********************************

// Função auxiliar para percurso em ordem na TST
void percursoEmOrdem(NoTST *no, char *buffer, int profundidade)
{
    if (no == NULL)
    {
        return;
    }

    // Percorrer a subárvore esquerda
    percursoEmOrdem(no->esquerda, buffer, profundidade);

    // Armazenar o caractere deste nó
    buffer[profundidade] = no->caractere;

    // Se este nó marca o fim de uma palavra, imprimir a palavra
    if (no->fim_palavra)
    {
        buffer[profundidade + 1] = '\0';
        printf("%s\n", buffer);
    }

    // Percorrer a subárvore do meio
    percursoEmOrdem(no->centro, buffer, profundidade + 1);

    // Percorrer a subárvore direita
    percursoEmOrdem(no->direito, buffer, profundidade);
}

// Função para imprimir todas as palavras no dicionário em ordem
void imprimirIndice(Dicionario *dicionario)
{
    char buffer[MAX_TAMANHO_PALAVRA];
    percursoEmOrdem(dicionario->raiz, buffer, 0);
    system("pause");
}

// *********************************** VERIFICAÇÃO DA INTEGRIDADE DO FICHEIRO DE TEXTO ***********************************

// Verifica a integridade do ficheiro comparando o hash atual do ficheiro com o hash armazenado no dicionário.
bool verificarIntegridadeFicheiro(Dicionario *dicionario, const char *nomeFicheiro)
{
    // Gera o hash atual do ficheiro.
    char *hashAtual = gerarHashFicheiro(nomeFicheiro);

    // Compara o hash atual com o hash armazenado.
    // Se a função compararHashFicheiro retorna verdadeiro, a integridade do ficheiro está preservada.
    // Se retorna falso, o ficheiro foi alterado desde a última verificação.
    bool integridadePreservada = compararHashFicheiro(dicionario, hashAtual);

    // Libera a memória alocada para o hash atual.
    free(hashAtual);

    return integridadePreservada;
}

// ================================ FUNÇÕES DE HASH ==================================
// As funções relacionadas ao hash do ficheiro são implementadas aqui.

// *********************************** GERANDO O HASH PARA O ARQUIVO DE TEXTO ***********************************

// Esta função gera um hash para um arquivo especificado
char *gerarHashFicheiro(const char *nomeFicheiro)
{
    // Abre o arquivo no modo de leitura
    FILE *ficheiro = fopen(nomeFicheiro, "r");
    // Se o arquivo não pôde ser aberto, imprime um erro e retorna NULL
    if (ficheiro == NULL)
    {
        printf("Erro ao abrir o ficheiro: %s\n", nomeFicheiro);
        return NULL;
    }

    // Inicia a variável hash com o valor 5381, que é um valor inicial comum para este algoritmo de hash
    unsigned long hash = 5381;
    int c;

    // Lê o arquivo caractere por caractere até o final
    while ((c = fgetc(ficheiro)) != EOF)
    {
        // Calcula o hash usando o algoritmo djb2
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    // Fecha o arquivo
    fclose(ficheiro);

    // Aloca memória para a string que vai guardar o hash
    // O tamanho máximo de um unsigned long em decimal é 20 caracteres
    // Mais um para o caractere nulo no final
    char *hashStr = malloc(21 * sizeof(char));
    // Se a alocação falhar, imprime um erro e retorna NULL
    if (hashStr == NULL)
    {
        printf("Erro ao alocar memória para o hash.\n");
        return NULL;
    }

    // Converte o valor do hash para uma string
    sprintf(hashStr, "%lu", hash);

    // Retorna a string com o hash do arquivo
    return hashStr;
}

// *********************************** COMPARANDO O HASH ARMAZENADO DO FICHEIRO DE TEXTO ***********************************

// Esta função compara o hash armazenado no dicionário com um hash fornecido
bool compararHashFicheiro(Dicionario *dicionario, const char *hashComparacao)
{
    // Se ambos os hashes são NULL, eles são considerados iguais
    if (dicionario->hash_ficheiro == NULL && hashComparacao == NULL)
    {
        return true;
    }

    // Se apenas um dos hashes é NULL, eles são considerados diferentes
    if (dicionario->hash_ficheiro == NULL || hashComparacao == NULL)
    {
        return false;
    }

    // Compara os dois hashes
    // Se a função strcmp retorna 0, significa que as strings são iguais
    if (strcmp(dicionario->hash_ficheiro, hashComparacao) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// ================================ FUNÇÕES DO MENU ==================================
// As funções relacionadas ao menu principal são implementadas aqui.

// *********************************** CARREGANDO AS PALAVRAS DO FICHEIRO PARA A TRIE TST (O DICIONÁRIO) ***********************************

// Função para carregar as palavras do ficheiro e preenchê-las na TRIE TST
void carregarPalavrasDoFicheiro(Dicionario *dicionario, const char *nomeFicheiro)
{
    // Abrir o ficheiro em modo de leitura
    FILE *file = fopen(nomeFicheiro, "r");

    // Verificar se o ficheiro foi aberto com sucesso
    if (file == NULL)
    {
        // Imprimir uma mensagem de erro se o ficheiro não puder ser aberto
        printf("Não foi possível abrir o ficheiro %s.\n", nomeFicheiro);
        perror("Erro");
        system("pause");
        return;
    }

    char palavra[MAX_TAMANHO_PALAVRA];

    // Ler palavras do ficheiro até que não haja mais palavras para ler
    while (fscanf(file, "%s", palavra) == 1)
    {
        // Inserir cada palavra lida na TRIE TST
        inserirPalavra(dicionario, palavra);
    }

    // Fechar o ficheiro
    fclose(file);

    // Gerar e armazenar o hash do ficheiro
    char *hash = gerarHashFicheiro(nomeFicheiro);
    dicionario->hash_ficheiro = hash;

    // Imprimir uma mensagem de sucesso
    printf("As palavras foram carregadas com sucesso do ficheiro %s.\n", nomeFicheiro);
    system("pause");
}

// *********************************** EXECUÇÃO DO MENU PRINCIPAL ***********************************

// Função para executar a opção escolhida no Menu Principal
void executarOpcao(Dicionario *dicionario, int opcao, const char *nomeFicheiro)
{
    // Variáveis para armazenar as palavras fornecidas pelo usuário
    char palavra[MAX_TAMANHO_PALAVRA], novaPalavra[MAX_TAMANHO_PALAVRA];

    // Variável para armazenar distância minima fornecida pelo usuário
    int distancia;

    // Estrutura switch-case para lidar com a opção escolhida pelo usuário
    switch (opcao)
    {
    case 1: // Opção para inserir nova palavra
        printf("Insira a nova palavra: ");
        scanf(" %s", palavra);  // Lê uma palavra do teclado, ignorando espaços em branco iniciais
        inserirPalavra(dicionario, palavra);
                system("pause");

        break;
    case 2: // Opção para consultar uma palavra
        printf("Insira a palavra a ser consultada: ");
        scanf(" %s", palavra);  // Lê uma palavra do teclado, ignorando espaços em branco iniciais
        consultarPalavra(dicionario, palavra);
       
        break;
    case 3: // Opção para remover uma palavra
        printf("Insira a palavra a ser removida: ");
        scanf(" %s", palavra);  // Lê uma palavra do teclado, ignorando espaços em branco iniciais
        removerPalavra(dicionario, palavra);
                system("pause");

        break;
    case 4: // Opção para atualizar uma palavra
        printf("Insira a palavra a ser atualizada: ");
        scanf(" %s", palavra);  // Lê uma palavra do teclado, ignorando espaços em branco iniciais

        printf("Insira a nova palavra: ");
        scanf(" %s", novaPalavra);  // Lê uma palavra do teclado, ignorando espaços em branco iniciais

        atualizarPalavra(dicionario, palavra, novaPalavra);
               system("pause");

        break;
    case 5: // Opção para exibir palavras com o mesmo prefixo
        printf("Insira o prefixo: ");
        scanf(" %s", palavra);  // Lê uma palavra do teclado, ignorando espaços em branco iniciais
        palavrasComPrefixo(dicionario, palavra);
        system("pause");
        break;
    case 6: // Opção para exibir o prefixo mais longo
        printf("Insira a palavra: ");
        scanf(" %s", palavra);  // Lê uma palavra do teclado, ignorando espaços em branco iniciais
        prefixoMaisLongo(dicionario, palavra);
        system("pause");
        break;
    case 7: // Opção para exibir palavras similares por distanciamento mínimo
        printf("Insira a palavra: ");
        scanf(" %s", palavra);  // Lê uma palavra do teclado, ignorando espaços em branco iniciais
        
        printf("Insira a distância mínima: ");
        scanf("%d", &distancia);

        palavrasPorDistanciaMinima(dicionario, palavra, distancia);
        system("pause");
        break;
    case 8: // Opção para verificar ortografia
        verificarOrtografia(dicionario, nomeFicheiro);
                system("pause");

        break;
    case 9: // Opção para imprimir o índice do dicionário
        imprimirIndice(dicionario);
        system("pause");
        break;
    case 10: // Opção para verificar a integridade do arquivo
        if(verificarIntegridadeFicheiro(dicionario, nomeFicheiro)){
            printf("Preservado!");
        }else{
            printf("Alterado");
        }
                system("pause");

        break;
    default:
        printf("Opção inválida! Por favor, escolha uma opção válida.\n");
    }
}

// Função para exibir as opções disponíveis ao usuário
void menu(int opcao_selecionada)
{
    // Limpar a tela
    system("clear || cls");

    // Exibir o cabeçalho do menu
    printf("\n");
    printf("\033[1;36m");
    printf("===================================================================\n");
    printf("=              DICIONÁRIO (TRIE TST/ HASH/ FICHEIRO)              =\n");
    printf("===================================================================\n");
    printf("\033[0m");

    // Exibir as opções de menu. A opção selecionada é destacada.
    printf("\n");
    printf("%s[1] Inserir nova palavra\n", opcao_selecionada == 1 ? "\033[1;32m->\033[0m" : "  ");
    printf("%s[2] Consultar palavra\n", opcao_selecionada == 2 ? "\033[1;32m->\033[0m" : "  ");
    printf("%s[3] Remover palavra\n", opcao_selecionada == 3 ? "\033[1;32m->\033[0m" : "  ");
    printf("%s[4] Atualizar palavra\n", opcao_selecionada == 4 ? "\033[1;32m->\033[0m" : "  ");
    printf("%s[5] Palavras com o mesmo prefixo\n", opcao_selecionada == 5 ? "\033[1;32m->\033[0m" : "  ");
    printf("%s[6] Prefixo mais longo\n", opcao_selecionada == 6 ? "\033[1;32m->\033[0m" : "  ");
    printf("%s[7] Palavras similares por distanciamento mínimo\n", opcao_selecionada == 7 ? "\033[1;32m->\033[0m" : "  ");
    printf("%s[8] Verificador ortográfico\n", opcao_selecionada == 8 ? "\033[1;32m->\033[0m" : "  ");
    printf("%s[9] Índice\n", opcao_selecionada == 9 ? "\033[1;32m->\033[0m" : "  ");
    printf("%s[10] Verificar integridade do ficheiro\n", opcao_selecionada == 10 ? "\033[1;32m->\033[0m" : "  ");
    printf("%s[0] Sair\n", opcao_selecionada == 0 ? "\033[1;32m->\033[0m" : "  ");
    printf("\n");
}

// Função para carregar e controlar o Menu Principal
void menuPrincipal(Dicionario *dicionario, const char *nomeFicheiro)
{
    // Carregar as palavras do ficheiro para a estrutura de dados
    carregarPalavrasDoFicheiro(dicionario, nomeFicheiro);
    printTST(dicionario->raiz);
    system("pause");

    // Variável para armazenar a opção escolhida pelo usuário
    int opcao = -1; // Inicializando a opção com um valor inválido

    do
    {
        // Exibir o menu com a opção selecionada
        menu(opcao);

        // Pedir ao usuário para escolher uma opção
        printf("Digite o número da opção desejada: ");
        scanf("%d", &opcao);

        if(opcao == 0){
            printf("entrei!");
            system("pause");
            destruirDicionario(dicionario);
        }

        // Limpar a tela
        system("clear || cls");

        // Exibir o menu novamente com a nova opção selecionada
        menu(opcao);

        // Executar a ação com base na opção escolhida
        executarOpcao(dicionario, opcao, nomeFicheiro);
    } while (opcao != 0); // Continuar o loop do menu até que a opção seja '0'
}

// Função que dá início ao programa
void iniciarPrograma()
{
    // Inicializar o dicionário
    Dicionario *dicionario = inicializarDicionario();
    system("pause");
    // Obtendo o nome do arquivo passando o caminho até ele.
    const char *nomeFicheiro = "dictionary.txt";
    // Chamar a função do menu principal

    system("pause");
    menuPrincipal(dicionario, nomeFicheiro);
    system("pause");
    /*// Depois que o menuPrincipal retornar, você pode assumir que o programa terminou
    // Portanto, você pode liberar a memória do dicionário aqui, se necessário
    destruirDicionario(dicionario);*/
}
