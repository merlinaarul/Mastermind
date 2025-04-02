#include "controleur.h"


// Implémentation des fonctions de controleur.c


void reinitialiser_jeu(mindset_game *d) {
    for (int i = 0; i < NB_ESSAIS; i++) {
        for (int j = 0; j < NB_PIONS; j++) {
            gtk_widget_set_name(d->ui.b_jeu[i][j], "default_button");
            desactiver(d->ui.b_jeu[i][j]);
        }
    }
    for (int j = 0; j < NB_PIONS; j++) {
        activer(d->ui.b_jeu[NB_ESSAIS - 1][j]);
    }
    d->ui.current_line = NB_ESSAIS - 1;

    for (int i = 0; i < NB_ESSAIS; i++) {
        gtk_label_set_text(GTK_LABEL(d->ui.labels_couleurs_corrects[i]), "0");
        gtk_label_set_text(GTK_LABEL(d->ui.labels_couleurs_bonne_place[i]), "0");
    }

    d->ui.help_count = 0;
}

bool ligne_complete(mindset_game *d, int ligne) {
    for (int j = 0; j < NB_PIONS; j++) {
        if (strcmp(gtk_widget_get_name(d->ui.b_jeu[ligne][j]), "default_button") == 0) {
            return false;
        }
    }
    return true;
}


//Permet de basculer du menu principal à la fenetre de jeu 
void basculer_jeu(GtkWidget *widget, gpointer data) {
    mindset_game *d = (mindset_game *)data;
    mastermind_initialiser_avec_secret(&d->game);
    gtk_widget_hide(d->ui.f1);
    gtk_widget_show_all(d->ui.f);
    reinitialiser_jeu(d);
}


//fonction permettant de retourner au menu principal 
void on_return_button_clicked(GtkWidget *button, gpointer data) {
    mindset_game *d = (mindset_game *)data;
    reinitialiser_jeu(d);// Affichage boîtes de la fenêtre principale
    gtk_widget_hide(d->ui.f);
    gtk_widget_show_all(d->ui.f1);
}


//fonction pour les regles du jeu et les indices 
void on_help_button_clicked(GtkWidget *button, gpointer data) {
    mindset_game *d = (mindset_game *)data;
    GtkWidget *dialog;
    gchar message[256];

    if (d->ui.help_count == 0) {
        dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Commencez par placer 4 pions et notez le nombre de bonne couleur ayant été placé et le nombre de bonne couleur ayant été placé au bon endroit, Ensuite au prochain essai vous ferez un ou deux changements et en fonction des résultats que vous obtiendrez, vous pourrez en déduire quelle couleur est la bonne ainsi que la position où elle doit être placé");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        int indice = d->ui.help_count - 1;

        if (indice < NB_PIONS) {
            int couleur = d->game.plateau[NB_ESSAIS][indice];
            const char *couleur_name;

            switch (couleur) {
                case COULEUR_ROUGE:
                    couleur_name = "rouge";
                    break;
                case COULEUR_VERT:
                    couleur_name = "vert";
                    break;
                case COULEUR_BLEU:
                    couleur_name = "bleu";
                    break;
                case COULEUR_JAUNE:
                    couleur_name = "jaune";
                    break;
                case COULEUR_ORANGE:
                    couleur_name = "orange";
                    break;
                case COULEUR_MAUVE:
                    couleur_name = "violet";
                    break;
                case COULEUR_NOIR:
                    couleur_name = "noir";
                    break;
                case COULEUR_BLANC:
                    couleur_name = "blanc";
                    break;
                default:
                    couleur_name = "inconnue";
                    break;
            }

            snprintf(message, sizeof(message), "Indice: Placez la couleur %s à la position %d.", couleur_name, indice + 1);
            dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, message);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    }

    d->ui.help_count++;
}

//Pour quitter la fenetre de jeu 
void on_quit_button_clicked(GtkWidget *button, gpointer data) {
    gtk_main_quit();
}

//pour selectionner un pion de couleur 
void on_pion_button_clicked(GtkWidget *button, gpointer data) {
    mindset_game *d = (mindset_game *)data;
    d->ui.selected_pion = button;
}


void on_jeu_button_clicked(GtkWidget *button, gpointer data) {
    mindset_game *d = (mindset_game *)data;
    if (d->ui.selected_pion) {// recupere la couleur du pion 
        const gchar *css_class = gtk_widget_get_name(d->ui.selected_pion);
        gtk_widget_set_name(button, css_class); // applique la couleur au bouton du jeu 
        d->ui.selected_pion = NULL;

        if (ligne_complete(d, d->ui.current_line)) { // poour savoir si une ligne est complète 
            for (int j = 0; j < NB_PIONS; j++) {
                desactiver(d->ui.b_jeu[d->ui.current_line][j]);
            }

            combinaison essai;
            for (int j = 0; j < NB_PIONS; j++) {
                const gchar *color_class = gtk_widget_get_name(d->ui.b_jeu[d->ui.current_line][j]);
                if (strcmp(color_class, "rouge_button") == 0) {
                    essai[j] = COULEUR_ROUGE;
                } else if (strcmp(color_class, "vert_button") == 0) {
                    essai[j] = COULEUR_VERT;
                } else if (strcmp(color_class, "bleu_button") == 0) {
                    essai[j] = COULEUR_BLEU;
                } else if (strcmp(color_class, "yellow_button") == 0) {
                    essai[j] = COULEUR_JAUNE;
                } else if (strcmp(color_class, "orange_button") == 0) {
                    essai[j] = COULEUR_ORANGE;
                } else if (strcmp(color_class, "purple_button") == 0) {
                    essai[j] = COULEUR_MAUVE;
                } else if (strcmp(color_class, "black_button") == 0) {
                    essai[j] = COULEUR_NOIR;
                } else if (strcmp(color_class, "white_button") == 0) {
                    essai[j] = COULEUR_BLANC;
                }
            }
            
            // pour comparer la combinaison entrée par le joueur avec la combinaison secrète
            int nb_correct = combinaison_cmp_ensembliste(essai, d->game.plateau[NB_ESSAIS]);
            int nb_correct_place = combinaison_cmp_ordonnee(essai, d->game.plateau[NB_ESSAIS]);

            char correct_str[3];
            char correct_place_str[3];
            snprintf(correct_str, 3, "%d", nb_correct);
            snprintf(correct_place_str, 3, "%d", nb_correct_place);

            gtk_label_set_text(GTK_LABEL(d->ui.labels_couleurs_corrects[d->ui.current_line]), correct_str);
            gtk_label_set_text(GTK_LABEL(d->ui.labels_couleurs_bonne_place[d->ui.current_line]), correct_place_str);

            if (nb_correct_place == 4) {
                afficher_fenetre_victoire(&d->ui);
                return;
            }

            if (d->ui.current_line > 0) {
                d->ui.current_line--;
                for (int j = 0; j < NB_PIONS; j++) {
                    activer(d->ui.b_jeu[d->ui.current_line][j]);
                }
            } else {
                afficher_fenetre_defaite(&d->ui);
            }
        }
    }
}

