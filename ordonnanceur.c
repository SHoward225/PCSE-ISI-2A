#include "ordonnanceur.h"
#include "processus.h"
#include "ctx_sw.h"
#include <stddef.h>


// // Table des processus contenant des pointeurs vers les structures de processus
// processus_t* table_processus[2];

// processus_t* processus_actuel;
// processus_t* idle_process;
// processus_t* proc1_process;


// //--------------- Ajouter un processus dans la table des processus activables
// void ajouter_processus(processus_t* proc) {
//     for (int i = 0; i < 2; i++) {
//         if (table_processus[i] == NULL) {
//             table_processus[i] = proc;
//             return;
//         }
//     };  
// }


// //--------------- Ordonnancement lors du passage d´un processus à l´autre

// void ordonnance(void) {
//     if (processus_actuel == idle_process) {
//         processus_actuel = proc1_process;
//     } else {
//         processus_actuel = idle_process;
//     }

//     // Changement de contexte
//     ctx_sw((uint32_t*)&(idle_process->regs), (uint32_t*)&(proc1_process->regs));
// }


//--------------- Ordonnancement selon l´algorithme du Tourniquet ----------

// void ordonnance(void) {
//     //Sauvegarder lr processus actuel
//     processus_t* ancien_processus=processus_actuel;

//     // Alterner entre idle et proc1
//     if (processus_actuel == idle_process) {
//         processus_actuel = proc1_process;  // Passer à proc1
//     } else {
//         processus_actuel = idle_process;  // Passer à idle
//     }

//     ancien_processus->etat = ACTIVABLE;
//     processus_actuel->etat = ELU;

//     // Changement de contexte vers le nouveau processus
//     ctx_sw((uint32_t*)&(ancien_processus->regs), (uint32_t*)&(processus_actuel->regs));
// }


// ======================== Generalisation a N processus ===========================

processus_t* table_processus[N] = {NULL};
processus_t* processus_actuel;

void ordonnance(void) {
    processus_t* ancien_processus = processus_actuel;

    // Rechercher le prochain processus activable
    int prochain_pid = (ancien_processus->pid + 1) % N;
    for (int i = 0; i < N; i++) {
        int index = (prochain_pid + i) % N;
        if (table_processus[index] != NULL && table_processus[index]->etat == ACTIVABLE) {
            processus_actuel = table_processus[index];
            break;
        }
    }

    ancien_processus->etat = ACTIVABLE;
    processus_actuel->etat = ELU;

    ctx_sw((uint32_t*)&(ancien_processus->regs), (uint32_t*)&(processus_actuel->regs));
}