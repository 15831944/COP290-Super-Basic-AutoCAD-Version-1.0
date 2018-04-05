#include <stdio.h>
#include <stdlib.h>
#include "gtk/gtk.h"
#define PI 3.1415926
// #include "my_display.hpp"
// #include "file_operators.hpp"
#include <math.h>
//#include <iostream>

using namespace std;

static GtkWidget *input1 = 0;
static GtkWidget *input2 = 0;
static GtkWidget *input3 = 0;
static GtkWidget *input4 = 0;

gint delete_event( GtkWidget *widget)
{
    gtk_widget_destroy(GTK_WIDGET(widget));
    return(FALSE);
}
gint delete_event2( GtkWidget *widget, GdkEvent  *event, gpointer   data )
{
    gtk_main_quit();
    return(FALSE);
}

static void quit_child(GtkWidget* w, GtkWidget* data)
{
    gtk_widget_destroy(data);
}

static void disp3d(GtkWidget* w, GtkWidget* entry)
{   
    gchar* active="active.txt";
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (input1));
    printf ("Entry contents: %s\n", entry_text);
    // copy_file(entry_text,active);
}

static void isometric(GtkWidget* w, GtkWidget* entry)
{   
    gchar* active="active.txt";
    gchar* temporary="temporary.txt";
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (input1));
    printf ("Entry contents: %s\n", entry_text);
    // copy_file(active,temporary);
    // copy_file(entry_text,active);
    // rotate(temporary,0,35.264,-45);
    // frontview(temporary);
}

static void orthographic(GtkWidget* w, GtkWidget* entry)
{   
    gchar* active="active.txt";
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY (input1));
    printf ("Entry contents: %s\n", entry_text);
    // copy_file(entry_text,active);
    // orthographic_display(active);
}

static void angle(GtkWidget* w, GtkWidget* entry)
{   
    // gtk_container_child_get (box, )
    gchar* active="active.txt";
    gchar* temporary="temporary.txt";

    const gchar* entry_file;
    const gchar* angle1;
    const gchar* angle2;
    const gchar* angle3;

    entry_file = gtk_entry_get_text (GTK_ENTRY (input1));
    angle1 = gtk_entry_get_text (GTK_ENTRY (input2));
    angle2 = gtk_entry_get_text (GTK_ENTRY (input3));
    angle3 = gtk_entry_get_text (GTK_ENTRY (input4));

    printf ("Entry contents: %s\n", angle1);
    printf ("Entry contents: %s\n", angle2);
    printf ("Entry contents: %s\n", angle3);
    float alpha,beta,gamma;
    float a,b,c;
    float normalise;
    // float f1, f2;
    a = atof(angle1);
    b = atof(angle2);
    c = atof(angle3);

    normalise= sqrt(b*b + a*a);
    beta=atan(c/normalise);
    beta= (beta*180)/PI;
    gamma= -1*atan(b/a);
    gamma= (gamma*180)/PI;    
    // copy_file(entry_file,active);
    // copy_file(active,temporary);
    // rotate(temporary,0,beta,gamma);
    // frontview(temporary);
}

static void rotator(GtkWidget* w, GtkWidget* entry)
{   
    gchar* active="active.txt";
    gchar* temporary="temporary.txt";

    const gchar* entry_file;
    const gchar* angle1;
    const gchar* angle2;
    const gchar* angle3;

    entry_file = gtk_entry_get_text (GTK_ENTRY (input1));
    angle1 = gtk_entry_get_text (GTK_ENTRY (input2));
    angle2 = gtk_entry_get_text (GTK_ENTRY (input3));
    angle3 = gtk_entry_get_text (GTK_ENTRY (input4));

    printf ("Entry contents: %s\n", angle1);
    printf ("Entry contents: %s\n", angle2);
    printf ("Entry contents: %s\n", angle3);
    float alpha,beta,gamma;
    float a,b,c;
    float normalise;
    // float f1, f2;
    a = atof(angle1);
    b = atof(angle2);
    c = atof(angle3);
    
    // copy_file(user_input,active);
    // rotate(active,a,b,c);  
}

static void box2_click(GtkWidget* w, gpointer data)
{
    GtkWidget *window;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *box3;
    GtkWidget *box4;
    GtkWidget *box5;
    GtkWidget *box6;
    GtkWidget *box7;
    GtkWidget *separator1;
    GtkWidget *separator2;
    GtkWidget *separator3;
    GtkWidget *label;
    GtkWidget *label2;
    GtkWidget *quitbox;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_signal_connect (GTK_OBJECT (window), "delete_event", GTK_SIGNAL_FUNC (delete_event), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
    box1 = gtk_vbox_new (TRUE, 0);

    label = gtk_label_new ("Choose input file : "); 
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);
    gtk_widget_show (label);
    
    // add menu for choosing file
    input1 = gtk_entry_new();
    gtk_box_pack_start (GTK_BOX (box1), input1, FALSE, FALSE, 0);
    gtk_widget_show (input1);

    separator1 = gtk_hseparator_new ();
    gtk_box_pack_start (GTK_BOX (box1), separator1, FALSE, TRUE, 5);
    gtk_widget_show (separator1);

    box5 = gtk_button_new_with_label ("Display 3D");
    gtk_box_pack_start (GTK_BOX (box1), box5, FALSE, FALSE, 0);
    gtk_widget_show (box5);

    box2 = gtk_button_new_with_label ("Isometric View");
    gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
    gtk_widget_show (box2);

    box3 = gtk_button_new_with_label ("Orthographic View");
    gtk_box_pack_start (GTK_BOX (box1), box3, FALSE, FALSE, 0);
    gtk_widget_show (box3);

    separator3 = gtk_hseparator_new ();
    gtk_box_pack_start (GTK_BOX (box1), separator3, FALSE, TRUE, 5);
    gtk_widget_show (separator3);
    
    // add menu for choosing angles

    label2 = gtk_label_new ("Input angles as x,y,z"); 
    gtk_label_set_justify(GTK_LABEL(label2), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start (GTK_BOX (box1), label2, FALSE, FALSE, 0);
    gtk_widget_show (label2);

    box7 = gtk_hbox_new (FALSE, 0);
    
    input2 = gtk_entry_new();
    gtk_box_pack_start (GTK_BOX (box7), input2, FALSE, FALSE, 0);
    gtk_widget_show (input2);

    input3 = gtk_entry_new();
    gtk_box_pack_start (GTK_BOX (box7), input3, FALSE, FALSE, 0);
    gtk_widget_show (input3);

    input4 = gtk_entry_new();
    gtk_box_pack_start (GTK_BOX (box7), input4, FALSE, FALSE, 0);
    gtk_widget_show (input4);

    gtk_box_pack_start (GTK_BOX (box1), box7, FALSE, FALSE, 0);
    gtk_widget_show (box7);

    box4 = gtk_button_new_with_label ("View From an Angle");
    gtk_box_pack_start (GTK_BOX (box1), box4, FALSE, FALSE, 0);
    gtk_widget_show (box4);

    box6 = gtk_button_new_with_label ("Rotate");
    gtk_box_pack_start (GTK_BOX (box1), box6, FALSE, FALSE, 0);
    gtk_widget_show (box6);

    separator2 = gtk_hseparator_new ();
    gtk_box_pack_start (GTK_BOX (box1), separator2, FALSE, TRUE, 5);
    gtk_widget_show (separator2);

    quitbox = gtk_hbox_new (FALSE, 0);

    button2 = gtk_button_new_with_label ("Home");
    gtk_signal_connect_object (GTK_OBJECT (button2), "clicked", GTK_SIGNAL_FUNC (quit_child), window);
    gtk_box_pack_start (GTK_BOX (quitbox), button2, TRUE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (box1), quitbox, FALSE, FALSE, 0);

    button1 = gtk_button_new_with_label ("Quit");
    gtk_signal_connect_object (GTK_OBJECT (button1), "clicked",
                               GTK_SIGNAL_FUNC (gtk_main_quit),
                               GTK_OBJECT (window));
    gtk_box_pack_start (GTK_BOX (quitbox), button1, TRUE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (box1), quitbox, FALSE, FALSE, 0);

    gtk_container_add (GTK_CONTAINER (window), box1);
    
    // gtk_widget_show (button);
    // gtk_widget_show (quitbox);  
    // gtk_widget_show (box1);
    // gtk_widget_show (window);
    gtk_widget_show_all(window);

    gtk_signal_connect (GTK_OBJECT(box5),"clicked",GTK_SIGNAL_FUNC(disp3d),box7);
    gtk_signal_connect (GTK_OBJECT(box2),"clicked",GTK_SIGNAL_FUNC(isometric),box7);
    gtk_signal_connect (GTK_OBJECT(box3),"clicked",GTK_SIGNAL_FUNC(orthographic),box7);
    gtk_signal_connect (GTK_OBJECT(box4),"clicked",GTK_SIGNAL_FUNC(angle),box7);
    gtk_signal_connect (GTK_OBJECT(box6),"clicked",GTK_SIGNAL_FUNC(rotator),box7);
}

static void box3_click(GtkWidget* w, gpointer data)
{
    GtkWidget *window;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *box3;
    GtkWidget *input;
    GtkWidget *separator1;
    GtkWidget *separator2;
    GtkWidget *label;
    GtkWidget *quitbox;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_signal_connect (GTK_OBJECT (window), "delete_event", GTK_SIGNAL_FUNC (delete_event), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
    box1 = gtk_vbox_new (TRUE, 0);

    label = gtk_label_new ("Choose input file : "); 
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);
    gtk_widget_show (label);
    
    // add menu for choosing file
    input = gtk_entry_new();
    gtk_box_pack_start (GTK_BOX (box1), input, FALSE, FALSE, 0);
    gtk_widget_show (input);

    separator1 = gtk_hseparator_new ();
    gtk_box_pack_start (GTK_BOX (box1), separator1, FALSE, TRUE, 5);
    gtk_widget_show (separator1);

    box2 = gtk_button_new_with_label ("Display");
    gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
    gtk_widget_show (box2);

    box3 = gtk_button_new_with_label ("3-D View");
    gtk_box_pack_start (GTK_BOX (box1), box3, FALSE, FALSE, 0);
    gtk_widget_show (box3);

    // box4 = gtk_button_new_with_label ("View From an Angle");
    // gtk_box_pack_start (GTK_BOX (box1), box4, FALSE, FALSE, 0);
    // gtk_widget_show (box4);

    separator2 = gtk_hseparator_new ();
    gtk_box_pack_start (GTK_BOX (box1), separator2, FALSE, TRUE, 5);
    gtk_widget_show (separator2);

    quitbox = gtk_hbox_new (FALSE, 0);
    
    button2 = gtk_button_new_with_label ("Home");
    gtk_signal_connect_object (GTK_OBJECT (button2), "clicked", GTK_SIGNAL_FUNC (quit_child), window);
    gtk_box_pack_start (GTK_BOX (quitbox), button2, TRUE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (box1), quitbox, FALSE, FALSE, 0);

    button1 = gtk_button_new_with_label ("Quit");
    gtk_signal_connect_object (GTK_OBJECT (button1), "clicked",
                               GTK_SIGNAL_FUNC (gtk_main_quit),
                               GTK_OBJECT (window));
    gtk_box_pack_start (GTK_BOX (quitbox), button1, TRUE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (box1), quitbox, FALSE, FALSE, 0);

    gtk_container_add (GTK_CONTAINER (window), box1);
    
    // gtk_widget_show (button);
    // gtk_widget_show (quitbox);  
    // gtk_widget_show (box1);
    // gtk_widget_show (window);
     gtk_widget_show_all(window);
}

int main( int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *box3;
    GtkWidget *separator;
    GtkWidget *label;
    GtkWidget *quitbox;

    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_signal_connect (GTK_OBJECT (window), "delete_event", GTK_SIGNAL_FUNC (delete_event2), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
    box1 = gtk_vbox_new (TRUE, 0);

    label = gtk_label_new ("Select the file you want to input");
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);
    gtk_widget_show (label);
    
    box2 = gtk_button_new_with_label ("3D");
    gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, FALSE, 0);
    gtk_widget_show (box2);

    box3 = gtk_button_new_with_label ("2D");
    gtk_box_pack_start (GTK_BOX (box1), box3, FALSE, FALSE, 0);
    gtk_widget_show (box3);

    separator = gtk_hseparator_new ();
    gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 5);
    gtk_widget_show (separator);

    quitbox = gtk_hbox_new (FALSE, 0);
    button = gtk_button_new_with_label ("Quit");
    gtk_signal_connect_object (GTK_OBJECT (button), "clicked", GTK_SIGNAL_FUNC (gtk_main_quit), GTK_OBJECT (window));

    gtk_box_pack_start (GTK_BOX (quitbox), button, TRUE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (box1), quitbox, FALSE, FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), box1);
    
    // gtk_widget_show (button);
    // gtk_widget_show (quitbox);
    // gtk_widget_show (box1);
    // gtk_widget_show (window);
    gtk_widget_show_all(window);

    gtk_signal_connect(GTK_OBJECT(box2),"clicked",GTK_SIGNAL_FUNC(box2_click),0);

    gtk_signal_connect(GTK_OBJECT(box3),"clicked",GTK_SIGNAL_FUNC(box3_click),0);
    
    gtk_main ();

    return(0);
}

