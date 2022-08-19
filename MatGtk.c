#include<gtk/gtk.h>

#define MAX_ROW 100
#define MAX_COL 100

//_________________________________________________________________________________________________

GtkWidget *window;
GtkWidget *workArea;
GtkWidget *row, *col;
GtkWidget *bNext;
GtkWidget *lab, *data;
GtkWidget *matGrid;
GtkWidget *gLab[MAX_ROW][MAX_COL];
GtkWidget *rev[MAX_ROW][MAX_COL];

int mat_done=0;

int A[MAX_ROW][MAX_COL];
int r,c;
int i,j,k,l,n,I=0,J=0;
int utd=0, ltr=0, btu=0, rtl=0;

//_________________________________________________________________________________________________

/*This function
create new workArea*/
void workArea_new()
{
	workArea = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), workArea);
}

/*This function
destroy workArea*/
void clrscr()
{
	gtk_widget_destroy(workArea);
	workArea_new();
}

/*This function
reveal numbers*/
gboolean getRev()
{
	if(!mat_done)
		return TRUE;
		
	if(n>0)
	{	
		if(i<r && j==I)
		{
			gtk_revealer_set_reveal_child(GTK_REVEALER(rev[i++][j]), TRUE);
			n--;
			//i++;
		}
		else if(j<c && i==r)
		{
			if(j==I)
				j+=1;
			j++;
			gtk_revealer_set_reveal_child(GTK_REVEALER(rev[i-1][j-1]), TRUE);
			n--;
		}

		else if(i>I && j==c)
		{
			if(i==r)
				i-=1;
			gtk_revealer_set_reveal_child(GTK_REVEALER(rev[i-1][j-1]), TRUE);
			n--;
			i--;
		}
		else if(j>I && i==I)
		{
			if(j==c)
				j-=1;
			gtk_revealer_set_reveal_child(GTK_REVEALER(rev[i][j-1]), TRUE);
			n--;
			j--;
			
			if(j==I+1)
			{
				r--;
				c--;
				I++;
				i=I;
				j=I;
			}
		}
	}
	else
		return FALSE;

	return TRUE;
}

/*This function
display matrix
as per task*/
void display()
{	
	gtk_widget_destroy(workArea);
	
	char no[MAX_ROW];
		
	matGrid = gtk_grid_new();
	
	gtk_grid_insert_row(GTK_GRID(matGrid), r);
	gtk_grid_insert_column(GTK_GRID(matGrid), c);

	gtk_grid_set_row_homogeneous(GTK_GRID(matGrid), TRUE);
	gtk_grid_set_row_spacing(GTK_GRID(matGrid), 5);
	
	gtk_grid_set_column_homogeneous(GTK_GRID(matGrid), TRUE);
	gtk_grid_set_column_spacing(GTK_GRID(matGrid), 5);
	
	gtk_container_add(GTK_CONTAINER(window), matGrid);
	
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
		{
			rev[i][j] = gtk_revealer_new();

			sprintf(no,"%d",A[i][j]);
			
			gLab[i][j] = gtk_label_new(no);

			gtk_container_add(GTK_CONTAINER(rev[i][j]), gLab[i][j]);
			gtk_grid_attach(GTK_GRID(matGrid), rev[i][j], j, i, 1, 1);
			gtk_revealer_set_reveal_child(GTK_REVEALER(rev[i][j]), FALSE);
		}

	gtk_widget_show_all(matGrid);
	n = r*c;
	i=0;
	j=0;
	mat_done=1;
}

/*This is a
helping function
of mat_entry()*/
void data_entry()
{
	if(i<r)
	{
		if(j>=c)
		{
			j=0;
			i++;
		}

		A[i][j] = atoi(gtk_entry_get_text(GTK_ENTRY(data)));
		gtk_entry_set_text(GTK_ENTRY(data), "");
		gtk_widget_grab_focus(data);
		
		if(i==r-1 && j==c-1)
		{
			clrscr();

			lab = gtk_label_new("DATA CAPTURED SUCCESSFULLY!");
			gtk_fixed_put(GTK_FIXED(workArea), lab, 100, 70);
			
			bNext = gtk_button_new_with_label("next");
			gtk_fixed_put(GTK_FIXED(workArea), bNext, 200, 100);
			g_signal_connect(G_OBJECT(bNext), "clicked", G_CALLBACK(display), NULL);
			
			gtk_widget_show_all(window);
		}
		
		j++;
	}
}

/*This function
takes matrix input*/
void mat_entry()
{
	r = atoi(gtk_entry_get_text(GTK_ENTRY(row)));	
	c = atoi(gtk_entry_get_text(GTK_ENTRY(col)));

	clrscr();
	
	GtkWidget *bOk;
	
	lab = gtk_label_new("Enter Data: ");
	gtk_fixed_put(GTK_FIXED(workArea), lab, 60, 75);

	data = gtk_entry_new();
	gtk_fixed_put(GTK_FIXED(workArea), data, 150, 70);
	gtk_widget_grab_focus(data);
	
	bOk = gtk_button_new_with_label(">>>");
	gtk_fixed_put(GTK_FIXED(workArea), bOk, 330, 70);
	g_signal_connect(G_OBJECT(bOk), "clicked", G_CALLBACK(data_entry), NULL);
	
	gtk_widget_show_all(window);
}

//_________________________________________________________________________________________________

int main()
{
	gtk_init(NULL, NULL);
	
	GtkWidget *rlabel, *clabel;
//-----------------------------------------------------------------------------window--------------
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Snake in Matrix");
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 175);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	workArea_new();
//-----------------------------------------------------------------------------first-page----------
	rlabel = gtk_label_new("Enter Number of Rows: ");
	gtk_fixed_put(GTK_FIXED(workArea), rlabel, 25, 25);
	
	row = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(row), "ex: 2, 22, 222");
	gtk_entry_set_max_length(GTK_ENTRY(row), 3);
	gtk_fixed_put(GTK_FIXED(workArea), row, 220, 20);
	
	clabel = gtk_label_new("Enter Number of Columns: ");
	gtk_fixed_put(GTK_FIXED(workArea), clabel, 25, 70);
	
	col = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(col), "ex: 2, 22, 222");
	gtk_entry_set_max_length(GTK_ENTRY(col), 3);
	gtk_fixed_put(GTK_FIXED(workArea), col, 220, 65);
	
	bNext = gtk_button_new_with_label("next");
	gtk_fixed_put(GTK_FIXED(workArea), bNext, 340, 125);
	g_signal_connect(G_OBJECT(bNext), "clicked", G_CALLBACK(mat_entry), NULL);
	
	g_timeout_add_seconds(1, getRev, NULL);
//-----------------------------------------------------------------------------end-of-code---------
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}

