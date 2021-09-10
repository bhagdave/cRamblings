/*
 * The simplest possible GTK app that does nothing
 *
 * to compile you will need to do the following
 * gcc `pkg-config --cflags gtk+-3.0` -o bin/gtkSimple gtkSimple.c  `pkg-config --libs gtk+-3.0`
*/
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Simple Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    gtk_widget_show_all(window);
}

int main(int argc, char** argv)
{
    GtkApplication *app = gtk_application_new(
            "dgill.developer.simple", 
            G_APPLICATION_FLAGS_NONE
            );
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}


