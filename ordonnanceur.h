#ifndef __ORDONNANCEUR_H__
#define __ORDONNANCEUR_H__

#include "processus.h"

// ================================ EXEMPLE A DEUX PROCESSUS ======================
// // Table des processus activablesssss
// extern processus_t* table_processus[2];

// ================================ Generalisation a N processus ======================
#define N 8 // Nombre maximum de processus

extern processus_t* table_processus[N]; // Table des processus activables



// Prototype de la fonction d'ordonnancement
void ordonnance(void);
void ajouter_processus(processus_t* proc);

#endif
