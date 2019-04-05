#include <stdlib.h>
#include <gtk-3.0/gtk/gtk.h>

int main(int argc, char const *argv[])
{
    system("xdg-open ../img/img1.jpg");

    return EXIT_SUCCESS;
}

//export PKG_CONFIG_PATH="${PKG_CONFIG_PATH}:/usr/local/opt/libffi/lib/pkconfig"
//gcc $(pkg-config --libs --cflags gtk+-3.0) MediaPlayer.c -o MediaPlayer