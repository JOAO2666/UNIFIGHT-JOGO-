#ifndef LOGIC_STRUCTS_H
#define LOGIC_STRUCTS_H

typedef enum
{
    POSE_IDLE,
    POSE_SOCO,
    POSE_CHUTE,
    POSE_PODER,
    POSE_CURA,
    POSE_DEFESA
} TipoPose;

typedef struct
{
    char nome[50];
    char habilidade[30];
    int vidaMaxima;
    int vidaAtual;
    int poderMaximo;
    int poderAtual;
    int danoSoco;
    int danoChute;
    int danoPoder;
    int isDefendendo;
} Personagem;

typedef struct
{
    Personagem jogador1;
    Personagem jogador2;
    int roundAtual;
    int maxRounds;
} EstadoJogo;

#endif
