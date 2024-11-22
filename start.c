#include "cpu.h"
#include "ecran.h"  // Pour la gestion de l'ecran
#include "init.h"   // Pour la gestion du temps
#include "ordonnanceur.h"
#include <stddef.h>


// on peut s'entrainer a utiliser GDB avec ce code de base
// par exemple afficher les valeurs de x, n et res avec la commande display

extern processus_t* processus_actuel;  // Définition réelle de la variable

void kernel_start(void)
{

    // // =========================  GESTION DE L'ECRAN ===============================
    
    // efface_ecran();
    // ecrit_car(10, 35,'S', BLANC, NOIR, 0);
    // ecrit_car(10, 36,'T', BLANC, NOIR, 0);
    // ecrit_car(10, 37,'E', BLANC, NOIR, 0);
    // ecrit_car(10, 38,'P', BLANC, NOIR, 0);
    // ecrit_car(10, 39,'H', BLANC, NOIR, 0);
    // ecrit_car(10, 40,'A', BLANC, NOIR, 0);
    // ecrit_car(10, 41,'N', BLANC, NOIR, 0);
    // ecrit_car(10, 42,'E', BLANC, NOIR, 0);

    // efface_ecran();

    // //------------------------------------------------------------

    // place_curseur(10,36);

    // traite_car('a');
    // defilement();
    // console_putbytes("Bonjour, Je suis KOUADIO Stephane !", 40);

    // efface_ecran();

    // // ---------------- Test de console_putbytes ----------------
    // // Affiche une chaîne à l'écran en testant console_putbytes
    // const char *str = "Test console_putbytes\n";
    // console_putbytes(str, 23);  // 23 étant la longueur de la chaîne

    // // ---------------- Test de traite_car ----------------
    // // Traiter un caractère de contrôle pour effacer l'écran
    // traite_car('\f'); // Efface l'écran (caractère form feed)

    // // Affiche à nouveau du texte après l'effacement
    // const char *str2 = "Apres traite_car('\\f')\n";
    // console_putbytes(str2, 23);

    // // // Test du caractère retour à la ligne
    // traite_car('\n');
    // const char *str3 = "Texte apres retour a la ligne";
    // console_putbytes(str3, 29);

    // // // // Test du caractère backspace
    // traite_car('\n');
    // console_putbytes("123456789", 9);
    // traite_car('\b');  // Supprime le dernier caractère

    // efface_ecran();


    // // ---------------- Test de defilement ----------------
    // // Remplir l'écran pour provoquer un défilement
    // for (int i = 0; i < 30; i++) {
    //     const char *ligne = "Remplissage de l'ecran pour defilement...\n";
    //     console_putbytes(ligne, 42);  // 42 étant la longueur de la chaîne
    // }

    // // Placer le curseur après le défilement
    // place_curseur(LIG_MAX - 1, 0);

    // =========================  GESTION DU TEMPS =========================

    // efface_ecran();
    
    // // Initialiser le système : PIT, interruptions, etc.
    // init_system();

    // // Boucle infinie pour maintenir le noyau actif
    // while (1) {
    //     // Attendre les interruptions, par exemple celles du PIT pour gérer le temps
    //     hlt();
    // }

    // =========================  GESTION DES PROCESSUS =========================

    // Nettoyer l'écran au démarrage
    efface_ecran(); 

// ------------------------------------------------------------------------------

    // // Initialisation des processus idle et proc1
    // init_processus_idle_proc1();

    // // Démarrage du processus par défaut (idle)
    // idle();

    // // Lancer l'ordonnanceur
    // while (1) {
    //     ordonnance();  // Passer au processus suivant
    // }

// ----------------------------------- Test Tourniquet -------------------------------------------

    // // Initialisation des processus idle et proc1
    // init_processus_idle_proc1();

    // // Démarrage du processus par défaut (idle)
    // idle();

// // ------------------------------ Generalisation a N processus --------------------------

//     // Créer les processus idle, proc1, proc2, etc.
//     creer_processus(idle, "idle");
//     creer_processus(proc1, "proc1");
//     creer_processus(proc2, "proc2");
//     creer_processus(proc3, "proc3");
//     creer_processus(proc4, "proc4");
//     creer_processus(proc5, "proc5");
//     creer_processus(proc6, "proc6");
//     creer_processus(proc7, "proc7");

//     processus_actuel = table_processus[0];

//     // Lancer le processus idle comme processus initial
//     idle();

// ------------------------------ Utilisation de listes de processus --------------------------
    
    // Initialiser les 8 processus
    init_processus_N();

    // Vérifiez que le processus actuel est bien initialisé
    if (processus_actuel == NULL) {
        printf("Erreur critique : processus_actuel est NULL après initialisation !\n");
        while (1);  // Boucle infinie pour arrêter l'exécution
    }

    // Démarrer le premier processus (idle)
    idle();

}

