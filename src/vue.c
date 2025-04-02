#include "vue.h"
#include "controleur.h"

// Implémentation des fonctions de vue.c


// Désactiver un bouton de jeu
void desactiver(GtkWidget* b) {
    gtk_widget_set_sensitive(b, FALSE);
}

// Activer un bouton de jeu 
void activer(GtkWidget* b) {
    gtk_widget_set_sensitive(b, TRUE);
}


// fonction pou charger le fichier ccs 
void apply_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    const gchar *css_file = "vue.css";
    GError *error = NULL;

    gtk_css_provider_load_from_path(provider, css_file, &error);
    if (error) {
        g_warning("Error loading CSS file: %s", error->message);
        g_clear_error(&error);
    }

    g_object_unref(provider);
}


// Affichage de la fenetre de victoire 
void afficher_fenetre_victoire(mindset_ui *d) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Victoire",
        GTK_WINDOW(d->f),
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        "REJOUER",
        GTK_RESPONSE_ACCEPT,
        NULL); 

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *label = gtk_label_new("FELICITATIONS VOUS AVEZ GAGNÉ, VOUS ÊTES FORT");
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_widget_show_all(dialog); // affichage du dialogue de victoire 

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT) {
        reinitialiser_jeu((mindset_game *)d); // permet de réinitialiser le jeu après l'interaction avec l'utilisateur 
        gtk_widget_hide(d->f);
        gtk_widget_show_all(d->f1);
    }
    gtk_widget_destroy(dialog);
}


// Affichage fenetre de defaite 
void afficher_fenetre_defaite(mindset_ui *d) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("Défaite",
        GTK_WINDOW(d->f),
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        "RECOMMENCER",
        GTK_RESPONSE_ACCEPT,
        NULL);

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *label = gtk_label_new("VOUS AVEZ PERDU, RÉESSAYER");
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_widget_show_all(dialog);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_ACCEPT) {
        reinitialiser_jeu((mindset_game *)d);
        gtk_widget_hide(d->f);
        gtk_widget_show_all(d->f1);
    }
    gtk_widget_destroy(dialog);
}




//aFFICHAGE DE LA FENETRE PRINCIPALE DE JEU 
void afficher(mindset_ui *d) {
    gtk_init(NULL, NULL);   // Initialiser GTK
    apply_css(); // Appel de la fonction pour charger le fichier css


    d->f1 = gtk_window_new(GTK_WINDOW_TOPLEVEL); // // Créer fenêtre de menu
    gtk_window_set_title(GTK_WINDOW(d->f1), "mastermind");
    gtk_window_set_default_size(GTK_WINDOW(d->f1), 800, 800);
    gtk_container_set_border_width(GTK_CONTAINER(d->f1), 10);
    gtk_widget_set_name(d->f1, "window1");
    g_signal_connect(d->f1, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    d->bp1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);  // Boîte principale du menu
    gtk_container_add(GTK_CONTAINER(d->f1), d->bp1);

    // Créer trois boîtes horizontales pour pouvoir mettre le bouton start dans la 3ème
    d->bmenu_1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bp1), d->bmenu_1, TRUE, TRUE, 0);

    d->bmenu_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bp1), d->bmenu_2, TRUE, TRUE, 0);

    d->bmenu_3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bp1), d->bmenu_3, TRUE, TRUE, 0);

    d->bmenu_verti1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bmenu_3), d->bmenu_verti1, TRUE, TRUE, 0);

    d->bmenu_verti2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bmenu_3), d->bmenu_verti2, TRUE, TRUE, 0);

    d->bmenu_verti3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bmenu_3), d->bmenu_verti3, TRUE, TRUE, 0);
    
    // Créer un bouton
    GtkWidget *button1 = gtk_button_new();
    gtk_box_pack_start(GTK_BOX(d->bmenu_verti2), button1, FALSE, TRUE, 0);
    gtk_widget_set_size_request(button1, 50, 50);
    g_signal_connect(button1, "clicked", G_CALLBACK(basculer_jeu), d);
    gtk_widget_set_name(button1, "fond_button");
    gtk_widget_show(button1);

    d->f = gtk_window_new(GTK_WINDOW_TOPLEVEL);  // Créer de la fenêtre jeu 
    gtk_window_set_title(GTK_WINDOW(d->f), "mastermind");
    gtk_window_set_default_size(GTK_WINDOW(d->f), 800, 800);
    gtk_widget_set_name(d->f, "pastel_button");
    gtk_container_set_border_width(GTK_CONTAINER(d->f), 10);
    g_signal_connect(d->f, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    d->bp = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); // Boite principale 
    gtk_container_add(GTK_CONTAINER(d->f), d->bp);

    d->bh1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10); // Boîte horizontale 1
    gtk_box_pack_start(GTK_BOX(d->bp), d->bh1, TRUE, TRUE, 0);

    // Creation des boites vertical pour pouvoir mettre des boutons et des images
    d->bh1_verti1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bh1), d->bh1_verti1, TRUE, TRUE, 0);

    d->bh1_verti2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bh1), d->bh1_verti2, TRUE, TRUE, 0);

    d->bh1_verti3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bh1), d->bh1_verti3, TRUE, TRUE, 0);

    d->bh1_verti4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bh1), d->bh1_verti4, TRUE, TRUE, 0);

    // Boutons options en haut de la fenêtre avec des images
    GtkWidget *return_button = gtk_button_new(); // bouton pour retourner au menu principal
    gtk_box_pack_start(GTK_BOX(d->bh1_verti1), return_button, FALSE, TRUE, 0);
    gtk_widget_set_size_request(return_button, 50, 50);
    g_signal_connect(return_button, "clicked", G_CALLBACK(on_return_button_clicked), d);
    gtk_widget_set_name(return_button, "return_button");
    gtk_widget_show(return_button);

    GtkWidget *help_button = gtk_button_new();// bouron pour les regles du jeu et les indices
    gtk_widget_set_size_request(help_button, 50, 50);
    gtk_box_pack_start(GTK_BOX(d->bh1_verti3), help_button, FALSE, TRUE, 0);
    g_signal_connect(help_button, "clicked", G_CALLBACK(on_help_button_clicked), d);
    gtk_widget_set_name(help_button, "aide_button");
    gtk_widget_show(help_button);

    GtkWidget *quit_button = gtk_button_new();// bouton pour quitter la fenetre de jeu 
    gtk_box_pack_start(GTK_BOX(d->bh1_verti4), quit_button, FALSE, FALSE, 0);
    gtk_widget_set_size_request(quit_button, 50, 50);
    g_signal_connect(quit_button, "clicked", G_CALLBACK(on_quit_button_clicked), d);
    gtk_widget_set_name(quit_button, "quitter_button");
    gtk_widget_show(quit_button);
    
    //boite horizontale 2
    d->bh2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bp), d->bh2, TRUE, TRUE, 0);
    
    // Boîte secondaire pour mettre les 12 ESSAIS pour les pions
    d->bs_vertical = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bh2), d->bs_vertical, TRUE, TRUE, 0);
    
    
    // Ajouter les boîtes verticales pour les labels
    d->bs_vertical2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bh2), d->bs_vertical2, TRUE, FALSE, 0);

    d->labels_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bs_vertical2), d->labels_hbox, TRUE, TRUE, 0);

    d->vertical_labels_1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(d->labels_hbox), d->vertical_labels_1, TRUE, TRUE, 0);

    d->vertical_labels_2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(d->labels_hbox), d->vertical_labels_2, TRUE, TRUE, 0);
    
    // Ajouter les labels à la première boîte verticale
    GtkWidget *label = gtk_label_new("nombre de couleurs correct");
    gtk_box_pack_start(GTK_BOX(d->vertical_labels_1), label, TRUE, TRUE, 0);

    for (int i = 0; i < NB_ESSAIS; i++) {
        label = gtk_label_new("0");
        d->labels_couleurs_corrects[i] = label;
        gtk_box_pack_start(GTK_BOX(d->vertical_labels_1), label, TRUE, TRUE, 0);
    }
    
    // Ajouter les labels à la deuxième boîte verticale
    label = gtk_label_new("nb de couleur à la bonne place");
    gtk_box_pack_start(GTK_BOX(d->vertical_labels_2), label, TRUE, TRUE, 0);

    for (int i = 0; i < NB_ESSAIS; i++) {
        label = gtk_label_new("0");
        d->labels_couleurs_bonne_place[i] = label;
        gtk_box_pack_start(GTK_BOX(d->vertical_labels_2), label, TRUE, TRUE, 0);
    }
    
    // Boîte horizontale 3
    d->bh3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(d->bp), d->bh3, TRUE, TRUE, 0);

    // Boutons de couleur sans images
    const char *button_names[NB_COULEURS] = {
        "rouge_button",
        "vert_button",
        "bleu_button",
        "yellow_button",
        "orange_button",
        "purple_button",
        "black_button",
        "white_button"
    };

    for (int i = 0; i < NB_COULEURS; i++) {
        GtkWidget *button = gtk_button_new();
        gtk_widget_set_name(button, button_names[i]);
        g_signal_connect(button, "clicked", G_CALLBACK(on_pion_button_clicked), d);
        gtk_widget_set_size_request(button, 100, 100);
        gtk_box_pack_start(GTK_BOX(d->bh3), button, TRUE, TRUE, 0);

        gtk_widget_show(button);
        d->bouton_couleur[i] = button;
    }

    d->current_line = NB_ESSAIS - 1;
    for (int i = 0; i < NB_ESSAIS; i++) {
        GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
        gtk_box_pack_start(GTK_BOX(d->bs_vertical), hbox, TRUE, TRUE, 0);
        gtk_widget_show(hbox);

        for (int j = 0; j < NB_PIONS; j++) {
            d->b_jeu[i][j] = gtk_button_new();
            gtk_widget_set_name(d->b_jeu[i][j], "default_button");
            gtk_widget_set_size_request(d->b_jeu[i][j], 10, 10);
            gtk_box_pack_start(GTK_BOX(hbox), d->b_jeu[i][j], TRUE, TRUE, 0);
            g_signal_connect(d->b_jeu[i][j], "clicked", G_CALLBACK(on_jeu_button_clicked), d);
            gtk_widget_show(d->b_jeu[i][j]);

            if (i != NB_ESSAIS - 1) {
                desactiver(d->b_jeu[i][j]);
            }
        }
    }
    
    // Affichage boîtes de la 1ère fenêtre
    gtk_widget_show(d->f1);
    gtk_widget_show(d->bp1);
    gtk_widget_show(d->bmenu_1);
    gtk_widget_show(d->bmenu_2);
    gtk_widget_show(d->bmenu_3);
    gtk_widget_show(d->bmenu_verti1);
    gtk_widget_show(d->bmenu_verti2);
    gtk_widget_show(d->bmenu_verti3);
    
    // Affichage boîtes de la fenêtre principale
    gtk_widget_show(d->bp);
    gtk_widget_show(d->bh1);
    gtk_widget_show(d->bh1_verti1);
    gtk_widget_show(d->bh1_verti2);
    gtk_widget_show(d->bh1_verti3);
    gtk_widget_show(d->bh1_verti4);
    gtk_widget_show(d->bh2);
    gtk_widget_show(d->bh3);
    gtk_widget_show(d->bs_vertical);
    gtk_widget_show(d->bs_vertical2);
    gtk_widget_show(d->labels_hbox);
    gtk_widget_show(d->vertical_labels_1);
    gtk_widget_show(d->vertical_labels_2);


    gtk_main();
}



