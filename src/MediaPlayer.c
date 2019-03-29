#include <stdlib.h>
#include <gtk-3.0/gtk/gtk.h>

int main(int argc, char const *argv[])
{
    GtkWidget *p_Window;
    GtkWidget *p_Label;
    gchar *sUtf8;

    gtk_init(&argc, &argv);

    p_Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_Window), "GTK+ 2.10");
    gtk_window_set_default_size(GTK_WINDOW(p_Window), 260, 40);
    gtk_window_set_position(GTK_WINDOW(p_Window), GTK_WIN_POS_CENTER);
    g_signal_connect(G_OBJECT(p_Window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    sUtf8 = g_locale_to_utf8("La Bibliothèque GTK+ à bien été Installée !", -1, NULL, NULL, NULL);
    p_Label = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_container_add(GTK_CONTAINER(p_Window), p_Label);

    gtk_widget_show_all(p_Window);

    gtk_main();

    return EXIT_SUCCESS;
}

//export PKG_CONFIG_PATH="${PKG_CONFIG_PATH}:/usr/local/opt/libffi/lib/pkconfig"
//gcc $(pkg-config --libs --cflags gtk+-3.0) MediaPlayer.c -o MediaPlayer