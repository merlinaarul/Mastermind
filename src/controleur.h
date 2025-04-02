#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include "vue.h"
#include "mastermind.h"
#include <stdbool.h>

typedef struct {
    mindset_ui ui;
    mastermind game;
} mindset_game;

void reinitialiser_jeu(mindset_game *d);
bool ligne_complete(mindset_game *d, int ligne);
void basculer_jeu(GtkWidget *widget, gpointer data);
void on_fullscreen_button_clicked(GtkWidget *button, gpointer data);
void on_return_button_clicked(GtkWidget *button, gpointer data);
void on_help_button_clicked(GtkWidget *button, gpointer data);
void on_quit_button_clicked(GtkWidget *button, gpointer data);
void on_pion_button_clicked(GtkWidget *button, gpointer data);
void on_jeu_button_clicked(GtkWidget *button, gpointer data);

#endif

