#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic_structs.h"
#include "modo_historia.h"
#include <windows.h>
#include <locale.h>

static void imprimirLentamente(const char *texto)
{
    for (int i = 0; texto[i] != '\0'; i++)
    {
        printf("%c", texto[i]);
        fflush(stdout);
        Sleep(30);
    }
}

static void mostrarAbertura()
{
    const char *title_art = "                                    UNIFIGHT\n";

    printf("%s", title_art); // Imprime a arte de uma vez
    imprimirLentamente("               A Jornada do Herói Começa...\n\n");
    Sleep(2000);
}

void salvarProgresso(const char *personagem, int fase)
{
    char nomeArquivo[100];
    sprintf(nomeArquivo, "progresso_%s.txt", personagem);
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL)
    {
        printf("Erro ao salvar progresso!\n");
        return;
    }

    fprintf(arquivo, "Fase: %d\n", fase);
    fclose(arquivo);
    printf("\nProgresso salvo com sucesso.\n");
}

void carregarProgresso(char *personagem, int *fase)
{
    char nomeArquivo[100];
    sprintf(nomeArquivo, "progresso_%s.txt", personagem);

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL)
    {
        printf("Nenhum progresso salvo encontrado.\n");
        *fase = 1;
        return;
    }

    if (fscanf(arquivo, "Fase: %d\n", fase) != 1)
    {
        printf("Arquivo de progresso corrompido para %s. Reiniciando para fase 1.\n", personagem);
        *fase = 1;
    }
    else if (*fase > 3 || *fase < 1)
    {
        printf("Progresso inválido para %s. Reiniciando para fase 1.", personagem);
        *fase = 1;
    }
    fclose(arquivo);
    printf("📄 Progresso carregado: %s - Fase %d\n", personagem, *fase);
}

int jogarFase(int fase, const char *personagem)
{
    EstadoJogo estado;
    estado.roundAtual = 1;
    estado.maxRounds = 12;

    if (strcmp(personagem, "Dandara") == 0)
    {
        switch (fase)
        {
        case 1:
            printf("\n[Dandara - Fase 1] Desfiladeiro de Irkall: Lixão dos mercenários.\n");
            printf("Missão: Limpar a rota de mercenários corrompidos.\n");
            InicializarPersonagem(&estado.jogador1, "Dandara", "Punhos");
            InicializarPersonagem(&estado.jogador2, "Brutus", "Martelos");
            break;
        case 2:
            printf("\n[Dandara - Fase 2] Cidade montanhosa.\n");
            printf("Missão: Investigar o desaparecimento de civis.\n");
            InicializarPersonagem(&estado.jogador1, "Dandara", "Espada");
            InicializarPersonagem(&estado.jogador2, "Alira", "Veneno Congelante");
            break;
        case 3:
            printf("\n[Dandara - Fase 3] Fortaleza final.\n");
            printf("Missão: Enfrentar a líder rebelde e salvar os prisioneiros.\n");
            InicializarPersonagem(&estado.jogador1, "Dandara", "Espada e Gelo");
            InicializarPersonagem(&estado.jogador2, "Raven", "Lança Flamejante");
            break;
        default:
            printf("[Fase inválida para Dandara]\n");
            return 0;
        }
    }
    else if (strcmp(personagem, "Kayk") == 0)
    {
        switch (fase)
        {
        case 1:
            printf("\n[Kayk - Fase 1] Vila em cinzas\n");
            printf("Missão: Encontrar sobreviventes e eliminar os incendiários.\n");
            InicializarPersonagem(&estado.jogador1, "Kayk", "Punhos");
            InicializarPersonagem(&estado.jogador2, "Ignaroth", "Chamas");
            break;
        case 2:
            printf("\n[Kayk - Fase 2] Templo esquecido\n");
            printf("Missão: Despertar o poder do Machados Ancestrais.\n");
            InicializarPersonagem(&estado.jogador1, "Kayk", "Machado");
            InicializarPersonagem(&estado.jogador2, "Sentinela Rubra", "Golem Arcano");
            break;
        case 3:
            printf("\n[Kayk - Fase 3] Vulcão final\n");
            printf("Missão: Dominar o Fogo Primordial e derrotar Pyralis.\n");
            InicializarPersonagem(&estado.jogador1, "Kayk", "Fogo Primordial");
            InicializarPersonagem(&estado.jogador2, "Pyralis", "Entidade de Fogo");
            break;
        default:
            printf("[Fase inválida para Kayk]\n");
            return 0;
        }
    }
    else if (strcmp(personagem, "Valéria") == 0)
    {
        switch (fase)
        {
        case 1:
            printf("\n[Valéria - Fase 1] Enigma nas ruínas\n");
            printf("Missão: Investigar os restos de uma civilização antiga que guardava códigos secretos.\n");
            InicializarPersonagem(&estado.jogador1, "Valéria", "Infiltradora");
            InicializarPersonagem(&estado.jogador2, "Sentinela", "Código Ancestral");
            break;
        case 2:
            printf("\n[Valéria - Fase 2] Templo oculto\n");
            printf("Missão: Invadir o templo escondido e recuperar o artefato sombrio.\n");
            InicializarPersonagem(&estado.jogador1, "Valéria", "Faca Silenciosa");
            InicializarPersonagem(&estado.jogador2, "Guarda Sombrio", "Visão Tática");
            break;
        case 3:
            printf("\n[Valéria - Fase 3] Segredo final\n");
            printf("Missão: Enfrentar o Oráculo e descobrir a verdade sobre o passado de Valéria.\n");
            InicializarPersonagem(&estado.jogador1, "Valéria", "Espada Rúnica");
            InicializarPersonagem(&estado.jogador2, "Oráculo", "Controle Mental");
            break;
        default:
            printf("[Fase inválida para Valéria]\n");
            return 0;
        }
    }
    else if (strcmp(personagem, "Zephyr") == 0)
    {
        switch (fase)
        {
        case 1:
            printf("\n[Zephyr - Fase 1] Campo de treinamento\n");
            printf("Missão: Aprimorar suas habilidades com o Mestre Ryu.\n");
            InicializarPersonagem(&estado.jogador1, "Zephyr", "Vento Ágil");
            InicializarPersonagem(&estado.jogador2, "Mestre Ryu", "Punhos Sábios");
            break;
        case 2:
            printf("\n[Zephyr - Fase 2] Floresta dos Ventos Sussurrantes\n");
            printf("Missão: Investigar a corrupção e purificar a floresta.\n");
            InicializarPersonagem(&estado.jogador1, "Zephyr", "Lâminas de Vento");
            InicializarPersonagem(&estado.jogador2, "Sylph Corrompida", "Sussurros Negros");
            break;
        case 3:
            printf("\n[Zephyr - Fase 3] Cume da Tempestade Eterna\n");
            printf("Missão: Enfrentar Tempestus e restaurar o equilíbrio dos ventos.\n");
            InicializarPersonagem(&estado.jogador1, "Zephyr", "Fúria da Tempestade");
            InicializarPersonagem(&estado.jogador2, "Tempestus", "Trovão Eterno");
            break;
        default:
            printf("[Fase inválida para Zephyr]\n");
            return 0;
        }
    }
    else
    {
        printf("[Personagem não reconhecido: %s]\n", personagem);
        return 0;
    }

    // Execução da luta
    while (estado.roundAtual <= estado.maxRounds &&
           estado.jogador1.vidaAtual > 0 &&
           estado.jogador2.vidaAtual > 0)
    {
        RodadaModoHistoria(&estado);
        estado.roundAtual++;
    }

    DeclararVencedor(&estado);

    if (estado.jogador1.vidaAtual > estado.jogador2.vidaAtual)
    {
        return 1; // Vitória
    }
    else
    {
        return 0; // Derrota ou Empate
    }
}

void historiaValeria()
{
    int faseAtual = 1;
    char personagem[50] = "Valéria";
    int vitoria = 0;
    carregarProgresso(personagem, &faseAtual);

    printf("\nValéria - Caçadora de segredos");
    for (int fase = faseAtual; fase <= 3; fase++)
    {
        switch (fase)
        {
        case 1:
            imprimirLentamente("\n[Valéria - Fase 1]");
            imprimirLentamente("\nMissão: Por anos, Valéria viveu nas sombras dos poderosos, vendendo informações, segredos e mentiras.\nSua reputação como caçadora de segredos não vinha apenas de sua astúcia, mas da habilidade de manipular o gelo.\nMas agora, algo ameaça não apenas seu trabalho, mas todo o equilíbrio das informações. Um artefato antigo, capaz de\napagar memórias, registros e segredos, foi dividido em três partes.\nSe for reunido, ele pode reescrever a história ou apagá-la para sempre. Valéria não permitirá que isso aconteça.\nSeu caminho começa agora.\n");
            imprimirLentamente("\nNas ruínas de uma cidade esquecida, Valéria encontra a primeira Sentinela. A criatura, feita de pura energia, protege o segredo ancestral com uma fúria silenciosa. A batalha será um teste de agilidade e inteligência.\n");
            break;
        case 2:
            imprimirLentamente("\n[Valéria - Fase 2]");
            imprimirLentamente("\nMissão: Com a primeira peça em mãos, Valéria segue até as montanhas geladas do norte.\nNo topo, um castelo abandonado abriga Guarda Sombrio, um ex-nobre que trocou títulos por sangue.\nSua lâmina corta não apenas carne, mas também rastros. Ninguém sabe quantas mortes ele já apagou da história,\nquantas verdades foram silenciadas por sua mão.\n");
            imprimirLentamente("\nO ar é rarefeito e o frio corta os ossos. O Guarda Sombrio a espera no pátio do castelo, sua presença é uma mancha na neve imaculada. Ele não diz uma palavra, apenas desembainha sua espada tática.\n");
            break;
        case 3:
            imprimirLentamente("\n[Valéria - Fase 3]");
            imprimirLentamente("\nMissão: Duas peças estão seguras, mas a última pertence a alguém que não pertence mais ao mundo dos vivos... ou, talvez,nunca tenha\npertencido.\nOráculo, o Tecelão de Memórias, é uma entidade antiga, um ser moldado pelas lembranças esquecidas, pelos segredos enterrados e pelas verdades jamais reveladas.\n");
            imprimirLentamente("\nNo coração de um labirinto mental, o Oráculo aguarda. Ele não luta com armas, mas com o poder da mente, testando a força de vontade de Valéria. Para vencer, ela terá que confrontar seus próprios medos.\n");
            break;
        }
        vitoria = jogarFase(fase, personagem);

        if (vitoria)
        {
            printf("\nVocê venceu a fase %d!\n", fase);
            if (fase < 3)
            {
                salvarProgresso(personagem, fase + 1);
            }
            else
            {
                printf("\nParabéns! Você completou a história de %s!\n", personagem);
                salvarProgresso(personagem, 1); // Reinicia o progresso
            }
        }
        else
        {
            printf("\nVocê foi derrotado! Fim de jogo.\n");
            break; // Sai do loop de fases
        }
    }
}

void historiaDandara()
{
    int faseAtual = 1;
    char personagem[50] = "Dandara";
    int vitoria = 0;
    carregarProgresso(personagem, &faseAtual);

    printf("\nDandara - Caçadora de recompensas");
    for (int fase = faseAtual; fase <= 3; fase++)
    {
        switch (fase)
        {
        case 1:
            imprimirLentamente("\n[Dandara - Fase 1]");
            imprimirLentamente("\nMissão: Em uma missão, Dandara descobre que foi traída por seu grupo.\nAgora sozinha, ela jura vingança por todos os silenciados e esquecidos.\n");
            imprimirLentamente("\nNo desfiladeiro onde foi deixada para morrer, Dandara encontra Brutus, um mercenário cuja lealdade tem o peso do ouro. Ele foi pago para garantir que ela não saísse viva dali.\n");
            break;
        case 2:
            imprimirLentamente("\n[Dandara - Fase 2]");
            imprimirLentamente("\nMissão: Dandara sobe a montanha para confrontrar Alira,\nex-companheira que a apunhalou.\n");
            imprimirLentamente("\nAlira a aguarda no pico, o vento gelado chicoteando seus cabelos. 'Você deveria ter ficado morta', diz ela, com um veneno em sua voz que rivaliza com o que ela usa em suas lâminas.\n");
            break;
        case 3:
            imprimirLentamente("\n[Dandara - Fase 3]");
            imprimirLentamente("\nMissão: Dandara chega como um fantasma, ninguém acreditava que ela ainda vivia.\nEla quer o líder Ráven, o homem que a abandonou.\n");
            imprimirLentamente("\nRaven está em sua fortaleza, surpreso, mas não intimidado. 'Sempre soube que seu ódio a traria de volta para mim', ele diz, pegando sua lança em chamas. 'Vamos terminar o que começamos.'\n");
            break;
        }
        vitoria = jogarFase(fase, personagem);

        if (vitoria)
        {
            printf("\nVocê venceu a fase %d!\n", fase);
            if (fase < 3)
            {
                salvarProgresso(personagem, fase + 1);
            }
            else
            {
                printf("\nParabéns! Você completou a história de %s!\n", personagem);
                salvarProgresso(personagem, 1);
            }
        }
        else
        {
            printf("\nVocê foi derrotado! Fim de jogo.\n");
            break;
        }
    }
}

void historiaKayk()
{
    int faseAtual = 1;
    char personagem[50] = "Kayk";
    int vitoria = 0;
    carregarProgresso(personagem, &faseAtual);

    printf("\nKayk - Domador do fogo");
    for (int fase = faseAtual; fase <= 3; fase++)
    {
        switch (fase)
        {
        case 1:
            imprimirLentamente("\n[Kayk - Fase 1]");
            imprimirLentamente("\nMissão: Há décadas, um evento conhecido como o Dilúvio destruiu templos e espalhou o caos pelo mundo.\nOs antigos mestres dos elementos desapareçam, e com eles, a sabedoria sobre as chamas.\nAgora, Kayk parte em uma jornada solitária caçando monstros, em busca de respostas pelo fogo que vive em sua alma. \n");
            imprimirLentamente("\nEm uma vila reduzida a cinzas, Kayk confronta Ignaroth, um elemental de fogo que se deleita com a destruição. A criatura não tem inteligência, apenas um apetite insaciável por queimar tudo em seu caminho.\n");
            break;
        case 2:
            imprimirLentamente("\n[Kayk - Fase 2]");
            imprimirLentamente("\nMissão: A alma vibra com o calor ao se aproximar de forças arcanas esquecidas.\nKayk adentra o templo para encontrar o guerreiro corrompido, Sentinela.\n");
            imprimirLentamente("\nA Sentinela Rubra, um golem forjado para proteger o templo, agora está corrompido por uma magia sombria. Seus ataques são lentos, mas devastadores. Kayk precisa ser rápido para sobreviver.\n");
            break;
        case 3:
            imprimirLentamente("\n[Kayk - Fase 3]");
            imprimirLentamente("\nMissão: Kayk agora domina a sua chama interior.\nCom fogo nas veias, he adentra a câmara final onde Pyralis, a entidade flamejante, desperta de seu sono.\n");
            imprimirLentamente("\n'Então, um novo mestre do fogo ousa me desafiar?', a voz de Pyralis ecoa pelo vulcão. 'Mostre-me o que aprendeu, mortal. Sua alma alimentará minha chama eterna!'\n");
            break;
        }
        vitoria = jogarFase(fase, personagem);

        if (vitoria)
        {
            printf("\nVocê venceu a fase %d!\n", fase);
            if (fase < 3)
            {
                salvarProgresso(personagem, fase + 1);
            }
            else
            {
                printf("\nParabéns! Você completou a história de %s!\n", personagem);
                salvarProgresso(personagem, 1);
            }
        }
        else
        {
            printf("\nVocê foi derrotado! Fim de jogo.\n");
            break;
        }
    }
}

void historiaZephyr()
{
    int faseAtual = 1;
    char personagem[50] = "Zephyr";
    int vitoria = 0;
    carregarProgresso(personagem, &faseAtual);

    printf("\nZephyr - O Mestre dos Ventos");
    for (int fase = faseAtual; fase <= 3; fase++)
    {
        switch (fase)
        {
        case 1:
            imprimirLentamente("\n[Zephyr - Fase 1]");
            imprimirLentamente("\nMissão: Zephyr sempre viveu nas montanhas, aprendendo a dançar com o vento. Seu mestre, um antigo monge, desapareceu misteriosamente.\nAgora, ele busca respostas e aprimora suas habilidades no campo de treinamento, enfrentando o experiente Mestre Ryu.\n");
            imprimirLentamente("\nMestre Ryu o observa com um sorriso sereno. 'O vento é seu aliado, Zephyr', ele diz. 'Mostre-me como você o controla'.\n");
            break;
        case 2:
            imprimirLentamente("\n[Zephyr - Fase 2]");
            imprimirLentamente("\nMissão: Uma energia sombria começou a corromper a Floresta dos Ventos Sussurrantes, um lugar sagrado para os habitantes da montanha.\nZephyr sente o vento enfraquecer e decide investigar, encontrando uma Sylph corrompida, outrora uma guardiã da natureza, agora consumida pela magia negra.\n");
            imprimirLentamente("\nA Sylph Corrompida flutua em meio à vegetação retorcida, seus sussurros outrora suaves transformados em murmúrios ameaçadores. A batalha exigirá que Zephyr use toda a sua conexão com o vento para purificar a floresta.\n");
            break;
        case 3:
            imprimirLentamente("\n[Zephyr - Fase 3]");
            imprimirLentamente("\nMissão: A fonte da corrupção na floresta leva Zephyr ao Cume da Tempestade Eterna, onde reside Tempestus, o Lorde da Tempestade.\nA lenda diz que Tempestus perdeu o controle de seus poderes, causando desequilíbrio nos ventos do mundo.\n");
            imprimirLentamente("\nTempestus paira no alto, envolto em raios e ventos furiosos. 'Você ousa desafiar o poder da tempestade, mortal?', sua voz troveja. 'Prepare-se para ser varrido pela fúria dos céus!'\n");
            break;
        }
        vitoria = jogarFase(fase, personagem);

        if (vitoria)
        {
            printf("\nVocê venceu a fase %d!\n", fase);
            if (fase < 3)
            {
                salvarProgresso(personagem, fase + 1);
            }
            else
            {
                printf("\nParabéns! Você completou a história de %s!\n", personagem);
                salvarProgresso(personagem, 1);
            }
        }
        else
        {
            printf("\nVocê foi derrotado! Fim de jogo.\n");
            break;
        }
    }
}

void modoHistoria()
{
    int escolha;
    mostrarAbertura();
    printf("\n-----PERSONAGENS-----\n");
    printf("\n1- Valéria");
    printf("\n2- Dandara");
    printf("\n3- Kayk");
    printf("\n4- Zephyr");
    printf("\nDigite a opção desejada: ");

    while (scanf("%d", &escolha) != 1)
    {
        printf("Entrada inválida. Por favor, digite um número.\n");
        while (getchar() != '\n')
            ; // Limpa o buffer de entrada
        printf("\nDigite a opção desejada: ");
    }
    getchar();

    switch (escolha)
    {
    case 1:
        historiaValeria();
        break;
    case 2:
        historiaDandara();
        break;
    case 3:
        historiaKayk();
        break;
    case 4:
        historiaZephyr();
        break;
    default:
        printf("\nOpção inválida.\n");
    }
}
