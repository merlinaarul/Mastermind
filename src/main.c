#include "controleur.c"

int main() {
    mindset_game d;
    mastermind_initialiser(&d.game);
    d.ui.help_count = 0;
    afficher(&d.ui);
    return 0;
}
