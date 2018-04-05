#include <gtk/gtk.h>

static gint delete_event_cb(GtkWidget* w, GdkEventAny* e, gpointer data);
static void button_click_cb(GtkWidget* w, gpointer data);

int main(int argc, char* argv[])
{
  GtkWidget* window;
  GtkWidget* button1;
  GtkWidget* label1;
  GtkWidget* button2;
  GtkWidget* label2;
  gtk_init(&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  button1 = gtk_button_new();
  label1 = gtk_label_new("3D file");
  button2 = gtk_button_new();
  label2 = gtk_label_new("2D file");
  gtk_container_add(GTK_CONTAINER(button1), label1);
  gtk_container_add(GTK_CONTAINER(window), button1);
  gtk_container_add(GTK_CONTAINER(button2), label2);
  gtk_container_add(GTK_CONTAINER(window), button2);
  gtk_window_set_title(GTK_WINDOW(window), "Super Basic AutoCAD Version 1.0");
  gtk_container_set_border_width(GTK_CONTAINER(button1), 10);
  gtk_container_set_border_width(GTK_CONTAINER(button2), 10);

  gtk_signal_connect(GTK_OBJECT(window),"delete_event", GTK_SIGNAL_FUNC(delete_event_cb), NULL);
  gtk_signal_connect(GTK_OBJECT(button1),"clicked",GTK_SIGNAL_FUNC(button_click_cb),label1);
  gtk_widget_show_all(window);
  gtk_main();
  return 0;
}
static gint delete_event_cb(GtkWidget* window, GdkEventAny* e, gpointer data)
{
  gtk_main_quit();
  return FALSE;
}
static void button_click_cb(GtkWidget* w, gpointer data)
{
  GtkWidget* label1;
  gchar* text;
  gchar* tmp;
  label1 = GTK_WIDGET(data);
  gtk_label_get(GTK_LABEL(label1), &text);
  tmp = g_strdup(text);
  g_strreverse(tmp);
  gtk_label_set_text(GTK_LABEL(label1), tmp);
  g_free(tmp);
}