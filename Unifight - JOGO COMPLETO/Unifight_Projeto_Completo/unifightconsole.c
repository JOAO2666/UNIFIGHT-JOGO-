#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic_structs.h"
#include <locale.h>
#include <windows.h>
#include <time.h>
#include "modo_historia.h"

void InicializarPersonagem(Personagem *p, const char *nome, const char *habilidade)
{
    strcpy(p->nome, nome);
    strcpy(p->habilidade, habilidade);
    p->vidaMaxima = 250;
    p->vidaAtual = 250;
    p->poderMaximo = 100;
    p->poderAtual = 100;
    p->danoSoco = 20;
    p->danoChute = 30;
    p->danoPoder = 50;
    p->isDefendendo = 0;
}

void MostrarStatus(Personagem *p)
{
    printf("%s - Vida: %d/%d | Poder: %d/%d\n", p->nome, p->vidaAtual, p->vidaMaxima, p->poderAtual, p->poderMaximo);
}

void ExecutarAtaque(Personagem *atacante, Personagem *alvo, TipoPose ataque)
{
    int dano = 0;
    const char *tipo = "";

    switch (ataque)
    {
    case POSE_SOCO:
        dano = atacante->danoSoco;  // dano de 20 na vida do oponente
        atacante->poderAtual += 10; // aumenta em 10 o poder
        tipo = "Soco";
        break;
    case POSE_CHUTE:
        dano = atacante->danoChute; // dano de 20 na vida do oponente
        atacante->poderAtual += 15; // aumenta em 15 o poder
        tipo = "Chute";
        break;
    case POSE_PODER:
        if (atacante->poderAtual >= 50)
        { // se o poder estiver carregado
            dano = atacante->danoPoder;
            atacante->poderAtual = 0; // inicializa o poder do jogador
            tipo = "Poder Especial";
        }
        else
        { // se não estiver carregado
            printf(" %s tentou usar o poder especial mas não tem poder suficiente!\n", atacante->nome);
            return;
        }
        break;
    default:
        return;
    }

    if (alvo->isDefendendo)
    {
        printf(" %s estava se defendendo e reduziu o dano!\n", alvo->nome);
        dano *= 0.5; // Reduz o dano em 50%
    }

    if (atacante->poderAtual > atacante->poderMaximo)
        atacante->poderAtual = atacante->poderMaximo;

    alvo->vidaAtual -= dano;
    if (alvo->vidaAtual < 0)
        alvo->vidaAtual = 0;

    printf(" %s usou %s e causou %d de dano em %s!\n", atacante->nome, tipo, dano, alvo->nome);
}

void ExecutarDefesa(Personagem *p)
{
    p->isDefendendo = 1;
    p->poderAtual += 20;
    if (p->poderAtual > p->poderMaximo)
    {
        p->poderAtual = p->poderMaximo;
    }
    printf(" %s está se defendendo e recuperou 20 de poder!\n", p->nome);
}

void ExecutarCura(Personagem *p)
{
    int cura = 25;
    p->vidaAtual += cura;
    if (p->vidaAtual > p->vidaMaxima)
    {
        p->vidaAtual = p->vidaMaxima;
    }
    printf(" %s se concentrou e recuperou %d de vida!\n", p->nome, cura);
}

TipoPose EscolherAtaque(const char *nomeJogador)
{
    int escolha;
    printf("\n%s, escolha sua ação:\n", nomeJogador);
    printf("1 - Soco (20 de dano)\n");
    printf("2 - Chute (30 de dano)\n");
    printf("3 - Poder Especial (50 de dano, custa 50 de poder)\n");
    printf("4 - Curar (recupera 25 de vida)\n");
    printf("5 - Defender (reduz o próximo dano e gera 20 de poder)\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1:
        return POSE_SOCO;
    case 2:
        return POSE_CHUTE;
    case 3:
        return POSE_PODER;
    case 4:
        return POSE_CURA;
    case 5:
        return POSE_DEFESA;
    default:
        printf("Escolha inválida! Usando soco.\n");
        return POSE_SOCO;
    }
}

static TipoPose EscolherAtaqueInimigo(Personagem *p)
{
    printf("\n%s está decidindo seu próximo movimento...\n", p->nome);
    Sleep(1500);

    if (p->poderAtual >= 50)
    {
        int chance = rand() % 4;
        if (chance < 2)
        {
            return POSE_PODER;
        }
        else if (chance == 2)
        {
            return POSE_SOCO;
        }
        else
        {
            return POSE_CHUTE;
        }
    }

    // Adiciona chance de defesa para a IA
    if (p->vidaAtual < p->vidaMaxima * 0.4)
    { // Se a vida estiver baixa
        if (rand() % 4 == 0)
        { // 25% de chance de defender
            return POSE_DEFESA;
        }
    }

    if (rand() % 2 == 0)
    {
        return POSE_SOCO;
    }
    else
    {
        return POSE_CHUTE;
    }
}

void Rodada(EstadoJogo *estado)
{
    printf("\n==================== RODADA %d de %d ====================\n", estado->roundAtual, estado->maxRounds);
    estado->jogador1.isDefendendo = 0;
    estado->jogador2.isDefendendo = 0;

    MostrarStatus(&estado->jogador1);
    MostrarStatus(&estado->jogador2);

    // Jogador 1
    printf("\n--- Turno de %s ---\n", estado->jogador1.nome);
    TipoPose acaoP1 = EscolherAtaque(estado->jogador1.nome);
    if (acaoP1 == POSE_CURA)
    {
        ExecutarCura(&estado->jogador1);
    }
    else if (acaoP1 == POSE_DEFESA)
    {
        ExecutarDefesa(&estado->jogador1);
    }
    else
    {
        ExecutarAtaque(&estado->jogador1, &estado->jogador2, acaoP1);
    }

    if (estado->jogador2.vidaAtual <= 0)
        return;

    // Jogador 2
    printf("\n--- Turno de %s ---\n", estado->jogador2.nome);
    TipoPose acaoP2 = EscolherAtaque(estado->jogador2.nome);
    if (acaoP2 == POSE_CURA)
    {
        ExecutarCura(&estado->jogador2);
    }
    else if (acaoP2 == POSE_DEFESA)
    {
        ExecutarDefesa(&estado->jogador2);
    }
    else
    {
        ExecutarAtaque(&estado->jogador2, &estado->jogador1, acaoP2);
    }
}

void RodadaModoHistoria(EstadoJogo *estado)
{
    printf("\n==================== RODADA %d de %d ====================\n", estado->roundAtual, estado->maxRounds);
    estado->jogador1.isDefendendo = 0;
    estado->jogador2.isDefendendo = 0;

    MostrarStatus(&estado->jogador1);
    MostrarStatus(&estado->jogador2);

    // Jogador 1 (Herói)
    printf("\n--- Seu Turno, %s ---\n", estado->jogador1.nome);
    TipoPose acaoP1 = EscolherAtaque(estado->jogador1.nome);
    if (acaoP1 == POSE_CURA)
    {
        ExecutarCura(&estado->jogador1);
    }
    else if (acaoP1 == POSE_DEFESA)
    {
        ExecutarDefesa(&estado->jogador1);
    }
    else
    {
        ExecutarAtaque(&estado->jogador1, &estado->jogador2, acaoP1);
    }

    if (estado->jogador2.vidaAtual <= 0)
        return;

    // Jogador 2 (Inimigo controlado pela IA)
    printf("\n--- Turno de %s ---\n", estado->jogador2.nome);
    if (estado->jogador2.vidaAtual > 0)
    {
        TipoPose acaoP2 = EscolherAtaqueInimigo(&estado->jogador2);
        if (acaoP2 == POSE_DEFESA)
        {
            ExecutarDefesa(&estado->jogador2);
        }
        else
        {
            ExecutarAtaque(&estado->jogador2, &estado->jogador1, acaoP2);
        }
    }
}

void DeclararVencedor(EstadoJogo *estado)
{
    printf("\n==================== FIM DO JOGO ====================\n");
    MostrarStatus(&estado->jogador1);
    MostrarStatus(&estado->jogador2);

    if (estado->jogador1.vidaAtual <= 0 && estado->jogador2.vidaAtual <= 0)
        printf("Empate!\n");
    else if (estado->jogador1.vidaAtual <= 0)
        printf("%s venceu!\n", estado->jogador2.nome);
    else if (estado->jogador2.vidaAtual <= 0)
        printf("%s venceu!\n", estado->jogador1.nome);
    else
    {
        // Se acabarem os rounds
        if (estado->jogador1.vidaAtual > estado->jogador2.vidaAtual)
            printf("%s venceu por pontos!\n", estado->jogador1.nome);
        else if (estado->jogador2.vidaAtual > estado->jogador1.vidaAtual)
            printf("%s venceu por pontos!\n", estado->jogador2.nome);
        else
            printf("Empate por esgotar os rounds!\n");
    }
}

Personagem SelecionarPersonagem(const char *nomeJogador)
{
    int escolha;
    printf("\n%s, escolha seu personagem:\n", nomeJogador);
    printf("1 - Kael (Fogo)\n");
    printf("2 - Dandara (Gelo)\n");
    printf("3 - Valéria (Gelo)\n");
    printf("Escolha: ");
    scanf("%d", &escolha);

    Personagem p;
    switch (escolha)
    {
    case 1:
        InicializarPersonagem(&p, "Kael", "Fogo");
        break;
    case 2:
        InicializarPersonagem(&p, "Dandara", "Gelo");
        break;
    case 3:
        InicializarPersonagem(&p, "Valéria", "Gelo");
        break;
    default:
        printf("Escolha inválida. Selecionado Kael.\n");
        InicializarPersonagem(&p, "Kael", "Fogo");
    }
    return p;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, " ");
    int escolha;

    printf("\n=================================");
    printf("\nBEM-VINDO AO UNIFIGHT!");
    printf("\n=================================\n");
    printf("\n1- Modo Luta");
    printf("\n2- Modo História");
    printf("\nEscolha o modo do jogo: ");
    scanf("%d", &escolha);
    getchar();
    if (escolha == 1)
    {
        EstadoJogo estado;
        estado.roundAtual = 1;
        estado.maxRounds = 12;

        estado.jogador1 = SelecionarPersonagem("Jogador 1");
        estado.jogador2 = SelecionarPersonagem("Jogador 2");

        // enquanto não atingirem o maximo de rounds e ambos os jogadores tiverem mais que 0 de vida
        while (estado.roundAtual <= estado.maxRounds &&
               estado.jogador1.vidaAtual > 0 &&
               estado.jogador2.vidaAtual > 0)
        {
            Rodada(&estado);
            estado.roundAtual++;
        }

        DeclararVencedor(&estado);
    }
    else if (escolha == 2)
    {
        modoHistoria();
    }
    else
    {
        printf("\nOpção inválida! Encerrando o jogo");
    }
    srand(time(NULL));
    return 0;
}
