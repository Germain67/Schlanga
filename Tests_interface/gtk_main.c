#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <string.h>

int dir = 0;

gboolean on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  switch (event->keyval)
  {
    case GDK_KEY_Up:
      dir = 0;
      printf("Haut\n");
      break;
    
    case GDK_KEY_Right:
      dir = 1;
      printf("Droite\n");
      break;
    case GDK_KEY_Down:
      dir = 2;
      printf("Bas\n");
      break;
    case GDK_KEY_Left:
      dir = 3;
      printf("Gauche\n");
      break;

    default:
      return FALSE; 
  }

  return FALSE; 
}

/* Pixmap d'arrière-plan pour la zone de dessin */
 static GdkPixmap *pixmap = NULL;
 
 /* Création d'un nouveau pixmap d'arrière-plan de la taille voulue */
 static gint
 configure_event (GtkWidget *widget, GdkEventConfigure *event)
 {
   if (pixmap)
     {
       gdk_pixmap_destroy(pixmap);
     }
   pixmap = gdk_pixmap_new(widget->window,
                           widget->allocation.width,
                           widget->allocation.height,
                           -1);
   gdk_draw_rectangle (pixmap,
                       widget->style->white_gc,
                       TRUE,
                       0, 0,
                       widget->allocation.width,
                       widget->allocation.height);
 
   return TRUE;
 }

  /* Remplit l'écran à partir du pixmap d'arrière-plan */
 static gint
 expose_event (GtkWidget *widget, GdkEventExpose *event)
 {
   gdk_draw_pixmap(widget->window,
                   widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                   pixmap,
                   event->area.x, event->area.y,
                   event->area.x, event->area.y,
                   event->area.width, event->area.height);
 
   return FALSE;
 }
 
/* Dessine un rectangle à l'écran */
 static void
 draw_brush (GtkWidget *widget, gdouble x, gdouble y)
 {
   GdkRectangle update_rect;
 
   update_rect.x = x - 5;
   update_rect.y = y - 5;
   update_rect.width = 10;
   update_rect.height = 10;
   gdk_draw_rectangle (pixmap,
                       widget->style->black_gc,
                       TRUE,
                       update_rect.x, update_rect.y,
                       update_rect.width, update_rect.height);
   gtk_widget_draw (widget, &update_rect);
 }

static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Snake VS Schalnga");
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);

  //Rectangle
  GtkWidget *drawing_area = gtk_drawing_area_new();
  draw_brush(drawing_area , 10 , 10);

  //Mappage des touches
  g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (on_key_press), NULL);

  //Affichage des widgets
  gtk_widget_show_all (window);
}

int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}