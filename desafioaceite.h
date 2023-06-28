// ================================ GUARDA DE INCLUSÃO ================================
// A guarda de inclusão evita problemas de inclusões múltiplas de um mesmo arquivo.
#ifndef DICIONARIO_H
#define DICIONARIO_H

// ================================ CONSTANTES ============================

// Essa constante representa o tamanho máximo que uma palavra do dicionário pode ter.
#define MAX_TAMANHO_PALAVRA 100

// ================================ BIBLIOTECAS INCLUÍDAS ============================

// Biblioteca para o uso do tipo bool.
#include <stdbool.h>

// Biblioteca padrão do C para entrada e saída de dados.
#include <stdio.h>

// ================================== ESTRUTURAS =====================================

// Struct que define um nó na árvore Ternary Search Trie (TST).
typedef struct no_tst
{
    char caractere;                             // Caractere armazenado no nó.
    bool fim_palavra;                           // Flag para marcar o fim de uma palavra.
    struct no_tst *esquerda, *centro, *direito; // Ponteiros para os nós filhos esquerdo, central e direito.
} NoTST;

// Struct que define o dicionário completo.
typedef struct
{
    NoTST *raiz;         // Ponteiro para a raiz da Trie.
    char *hash_ficheiro; // Hash do ficheiro carregado na Trie.
} Dicionario;

// ================================ FUNÇÕES DO DICIONÁRIO ============================
// As funções são declaradas aqui, mas suas implementações ocorrerão no arquivo 'manipuladorDoDicionario.c'.

// Inicializa o dicionário.
Dicionario *inicializarDicionario();

// Inicializa um novo nó da Trie com o caractere fornecido.
NoTST *inicializarNo(char caractere);

// Insere uma palavra no dicionário.
void inserirPalavra(Dicionario *dicionario, const char *palavra);

// Consulta se uma palavra existe no dicionário.
bool consultarPalavra(Dicionario *dicionario, const char *palavra);

// Remove uma palavra do dicionário.
void removerPalavra(Dicionario *dicionario, const char *palavra);

// Atualiza uma palavra existente no dicionário.
void atualizarPalavra(Dicionario *dicionario, const char *palavraAntiga, const char *palavraNova);

// Imprime todas as palavras com o prefixo fornecido.
void palavrasComPrefixo(Dicionario *dicionario, const char *prefixo);

// Retorna o prefixo mais longo de uma palavra que existe no dicionário.
char *prefixoMaisLongo(Dicionario *dicionario, const char *palavra);

// Imprime todas as palavras que estão a uma certa distância de edição de uma palavra base.
void palavrasPorDistanciaMinima(Dicionario *dicionario, const char *palavraBase, int distancia);

// Verifica a ortografia de um ficheiro de texto usando o dicionário.
void verificarOrtografia(Dicionario *dicionario, const char *ficheiroTexto);

// Imprime todas as palavras no dicionário em ordem.
void imprimirIndice(Dicionario *dicionario);

// Verifica a integridade do ficheiro com o hash armazenado no dicionário.
bool verificarIntegridadeFicheiro(Dicionario *dicionario, const char *nomeFicheiro);

// ================================ FUNÇÕES DE HASH ==================================
// As funções relacionadas ao hash do ficheiro são declaradas aqui.

// Gera o hash de um ficheiro.
char *gerarHashFicheiro(const char *nomeFicheiro);

// Compara o hash armazenado no dicionário com um hash fornecido.
bool compararHashFicheiro(Dicionario *dicionario, const char *hashComparacao);

// ================================ FUNÇÕES AUXILIARES ==================================
// Estas funções são usadas como auxiliares para evitar a sobrecarga das funções principais.

// Função auxiliar para inserir um nó na árvore.
NoTST *inserirNo(NoTST *raiz, const char *palavra, int indice);

// Função auxiliar para consultar uma palavra na árvore.
bool consultarPalavraRecursivo(NoTST *raiz, const char *palavra, int indice);

// Função auxiliar para verificar se um nó está vazio (ou seja, não tem filhos).
bool noEstaVazio(NoTST *no);

// Função auxiliar para remover uma palavra na árvore.
NoTST *removerPalavraRecursivo(NoTST *raiz, const char *palavra, int indice);

// Função auxiliar para imprimir todas as palavras na TST que começam com o prefixo fornecido.
void palavrasComPrefixoAuxiliar(NoTST *no, char *buffer, int profundidade);

// Função auxiliar que encontra todas as palavras que estão a uma certa distância de edição de uma palavra base.
void palavrasPorDistanciaMinimaAux(NoTST *no, char *buffer, int profundidade, const char *palavraBase, int distancia);

// Função que retorna o menor de três números.
int min(int a, int b, int c);

// Função que calcula a distância de edição entre duas palavras.
int distanciaEdicao(const char *palavra1, int comprimento1, const char *palavra2, int comprimento2);

// Função para tratar palavra não encontrada no dicionário
void tratarPalavraNaoEncontrada(Dicionario *dicionario, FILE *fileOutput, const char *palavra);

// Função auxiliar para percurso em ordem na TST
void percursoEmOrdem(NoTST *no, char *buffer, int profundidade);

// ================================ FUNÇÕES PARA O MENU ==================================
// Estas funções são usadas para ajudar nas funcionalidades do menu.

// Função para carregar as palavras do ficheiro e preenchê-las na TRIE TST
void carregarPalavrasDoFicheiro(Dicionario *dicionario, const char *nomeFicheiro);

// Função para executar a opção escolhida no Menu Principal
void executarOpcao(Dicionario *dicionario, int opcao, const char *nomeFicheiro);

// Função para exibir as opções disponíveis ao usuário
void menu(int opcao_selecionada);

// Função para carregar e controlar o Menu Principal
void menuPrincipal(Dicionario *dicionario, const char *nomeFicheiro);

// ================================ FUNÇÕES DO MAIN ==================================
// Estas funções são usadas para inicializar o programa ou parte dele.

// Função que dá início ao programa
void iniciarPrograma();

// ================================ FIM DA GUARDA DE INCLUSÃO ========================
#endif // DICIONARIO_H
