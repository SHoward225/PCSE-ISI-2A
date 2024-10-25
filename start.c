#include "ecran.h"  // Pour la gestion de l'ecran
#include "init.h"   // Pour la gestion du temps
#include "processus.h"  // Pour la gestion des processus
#include "cpu.h"

// on peut s'entrainer a utiliser GDB avec ce code de base
// par exemple afficher les valeurs de x, n et res avec la commande display

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


    efface_ecran();

    // =========================  GESTION DU TEMPS =========================


    // Initialiser le système : PIT, interruptions, etc.
    init_system();

    // Boucle infinie pour maintenir le noyau actif
    while (1) {
        // Attendre les interruptions, par exemple celles du PIT pour gérer le temps
        hlt();
    }

    // =========================  GESTION DES PROCESSUS =========================



    // init_processus();  // Initialise la table des processus
    // idle();  // Démarre avec le processus idle

}

