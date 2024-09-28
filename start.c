#include <cpu.h>
#include <inttypes.h>
#include "ecran.h"

// on peut s'entrainer a utiliser GDB avec ce code de base
// par exemple afficher les valeurs de x, n et res avec la commande display

void kernel_start(void)
{

    //------------------------- GESTION DE L'ECRAN -------------------------
    
    efface_ecran();
    ecrit_car(10, 35,'S', 1,15, 0);
    // ecrit_car(10, 36,'T', 1,15, 0);
    // ecrit_car(10, 37,'E', 1,15, 0);
    // ecrit_car(10, 38,'P', 1,15, 0);
    // ecrit_car(10, 39,'H', 1,15, 0);
    // ecrit_car(10, 40,'A', 1,15, 0);
    // ecrit_car(10, 41,'N', 1,15, 0);
    // ecrit_car(10, 42,'E', 1,15, 0);

    // -------------------------  GESTION DU TEMPS ---------------------------


    // place_curseur(0,0);

    // place_curseur(0,0);
    // traite_car('a');
    // defilement();
    // console_putbytes("Bonjour, Je suis KOUADIO Stephane !", 40);

}

