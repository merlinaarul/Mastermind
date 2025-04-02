#ifndef VUE_H
#define VUE_H

#include <gtk/gtk.h>

#define NB_ESSAIS 12
#define NB_PIONS 4
#define NB_COULEURS 8

typedef struct {
    GtkWidget *f1;
    GtkWidget *bp1;
    GtkWidget *bmenu_1;
    GtkWidget *bmenu_2;
    GtkWidget *bmenu_3;
    GtkWidget *bmenu_verti1;
    GtkWidget *bmenu_verti2;
    GtkWidget *bmenu_verti3;
    GtkWidget *f;
    GtkWidget *bp;
    GtkWidget *bh1;
    GtkWidget *bh1_verti1;
    GtkWidget *bh1_verti2;
    GtkWidget *bh1_verti3;
    GtkWidget *bh1_verti4;
    GtkWidget *bh2;
    GtkWidget *bh3;
    GtkWidget *bs_vertical;
    GtkWidget *bs_vertical2;
    GtkWidget *labels_hbox;
    GtkWidget *vertical_labels_1;
    GtkWidget *vertical_labels_2;
    GtkWidget *b_jeu[NB_ESSAIS][NB_PIONS];
    GtkWidget *bouton_couleur[NB_COULEURS];
    GtkWidget *labels_couleurs_corrects[NB_ESSAIS];
    GtkWidget *labels_couleurs_bonne_place[NB_ESSAIS];
    GtkWidget *selected_pion;
    int current_line;
    int help_count;
} mindset_ui;

void afficher(mindset_ui *d);
void desactiver(GtkWidget* b);
void activer(GtkWidget* b);
void afficher_fenetre_victoire(mindset_ui *d);
void afficher_fenetre_defaite(mindset_ui *d);
void apply_css();

#endif

