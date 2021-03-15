#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define WIDTH 800
#define HEIGHT 600

#define BLACK al_map_rgb(0,0,0)

void erreur(const char* texte)
{
    ALLEGRO_DISPLAY *display;
    display = al_is_system_installed() ? al_get_current_display() : NULL;
    printf("Erreur:\n %s", texte);
}

int main() {

    // Déclarations
    ALLEGRO_DISPLAY* display1 = NULL;
    ALLEGRO_EVENT_QUEUE* queue = NULL;
    ALLEGRO_KEYBOARD_STATE* keyboard_state = NULL;
    ALLEGRO_MOUSE_STATE* mouse_state = NULL;
    ALLEGRO_BITMAP* bmp = NULL;
    ALLEGRO_FONT* DotGothic16 = NULL;

    // Installations
    srand(time(NULL));
    if(!al_init()) erreur("al_init()");

    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display1 = al_create_display(WIDTH, HEIGHT);
    if(!display1) erreur("al_create_display()");

    al_init_image_addon();

    bmp = al_load_bitmap("/Users/ilias/Desktop/calculatrice.png");
    if(!bmp) erreur("al_create_bitmap");

    al_init_ttf_addon();
    DotGothic16 = al_load_ttf_font("/Users/ilias/Desktop/DotGothic16/DotGothic16-Regular.ttf", 16, 0);
    if(!DotGothic16) erreur("al_load_ttf_font");

    if(!al_install_keyboard()) erreur("al_install_keyboard");
    if(!al_install_mouse()) erreur ("al_install_mouse");

    al_init_primitives_addon();

    // Premier affichage
    al_set_window_title(display1, "Mon premier programme");
    al_set_window_position(display1, 20, 0);
    al_flip_display();

    al_register_event_source(queue, al_get_display_event_source(display1));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    // Gestion des événements
    queue = al_create_event_queue();
    if (!queue) {
        erreur("al_create_event_queue");
        al_destroy_event_queue(queue);
        return 1;
    }

    // Boucle d'événements

    ALLEGRO_EVENT event = {0};
    int fin = 0;
    int repeint = 0;

    while (!fin) {
        al_wait_for_event(queue, &event);
        switch(event.type){
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fin = 1;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch(event.keyboard.keycode){
                    case ALLEGRO_KEY_ESCAPE:
                        fin = 1;
                        break;
                }
                al_flip_display();
        }

        if (repeint) {
            al_clear_to_color(BLACK);
            al_flip_display();
        }
    }
    al_destroy_display(display1);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(bmp);
    al_destroy_font(DotGothic16);
    return 0;
}
