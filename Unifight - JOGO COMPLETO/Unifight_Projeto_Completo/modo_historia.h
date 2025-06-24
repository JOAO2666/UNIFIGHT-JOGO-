#ifndef MODO_HISTORIA_H
#define MODO_HISTORIA_H

#include "logic_structs.h"

void modoHistoria();
int jogarFase(int nivel, const char *nomeJogador);
void salvarProgresso(const char *nomeJogador, int fase);
void carregarProgresso(char *nomeJogador, int *fase);
void RodadaModoHistoria(EstadoJogo *estado);
void InicializarPersonagem(Personagem *personagem, const char *nome, const char *arma);
void RodadaModoHistoria(EstadoJogo *estado);
void DeclararVencedor(EstadoJogo *estado);


#endif
