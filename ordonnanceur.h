#ifndef __ORDONNANCEUR_H__
#define __ORDONNANCEUR_H__

#include "processus.h"

// ================================ EXEMPLE A DEUX PROCESSUS ======================
// // Table des processus activablesssss
// extern processus_t* table_processus[2];

// // ================================ Generalisation a N processus ======================
// #define N 8 // Nombre maximum de processus

// extern processus_t* table_processus[N]; // Table des processus activables

// // Prototype de la fonction d'ordonnancement
// void ordonnance(void);
// void ajouter_processus(processus_t* proc);

// ============== Utilisation de listes de processus =====================

// Liste des processus activables
extern processus_t* tete_activables;
extern processus_t* queue_activables;

// Fonctions pour la gestion des processus activables
void ajouter_queue_activables(processus_t* proc);
processus_t* retirer_tete_activables(void);

// Fonction d'ordonnancement
void ordonnance(void);

// ======================== ORDONNANCEMENT PREEMPTIF ===========================

void pit_handler(void);


#endif
