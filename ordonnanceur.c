#include "ordonnanceur.h"
#include "processus.h"
#include "ctx_sw.h"
#include <stddef.h>


processus_t* processus_actuel;
processus_t* table_processus[2];


// Ajouter un processus dans la table des processus activables
void ajouter_processus(processus_t* proc) {
    for (int i = 0; i < 2; i++) {
        if (table_processus[i] == NULL) {
            table_processus[i] = proc;
            return;
        }
    }
}


// Fonction d'ordonnancement pour passer de idle à proc1
void ordonnance(void) {
    if (processus_actuel == idle_process) {
        processus_actuel = proc1_process;
    } else {
        processus_actuel = idle_process;
    }

    // Changement de contexte
    ctx_sw((uint32_t*)&(idle_process->regs), (uint32_t*)&(proc1_process->regs));
}
