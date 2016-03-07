#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <string.h>

static void print_hello (GtkWidget *widget, gpointer data)
{
  g_print ("Hello\n");
}

gboolean on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  switch (event->keyval)
  {
    case GDK_Up:
      printf("Haut\n");
      break;
    
    case GDK_Right:
      printf("Droite\n");
      break;
    case GDK_Down:
      printf("Bas\n");
      break;
    case GDK_Left:
      printf("Gauche\n");
      break;

    default:
      return FALSE; 
  }

  return FALSE; 
}

static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (on_key_press), NULL);
  gtk_container_add (GTK_CONTAINER (button_box), button);

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