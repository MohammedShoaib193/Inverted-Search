#include "inverted_index.h"


int display_DB (main_node_t** head)			//function to display everything in database
{
    int i = 0, flag = 0;

    while (i < SIZE)		
    {
	if (head [i] != NULL)	
	{
	    display_words (head [i], i);
	    flag = 1;
	}

	i += 1; 		
    }

    if (flag == 0)			
	return FAILURE;
    else
	return SUCCESS;
}


void display_words (main_node_t* temp1, int index)	//function to display details of particular word
{
    while (temp1 != NULL)		
    {
	printf ("[%d]\t", index);
	printf ("[%-10s]\t", temp1->word);
	printf ("%d"  " File(s) :\t", temp1->f_count);

	display_files (temp1->sub_link);

	printf ("-> NULL\n");	
	temp1 = temp1->link;	
    }
}



void display_files (sub_node_t* temp2)			//to display details of the file
{
    while (temp2 != NULL)		
    {
	printf ("File :" " %s\t", temp2->f_name);
	printf ("%d" " time(s)\t", temp2->w_count);

	temp2 = temp2->link;	

	if (temp2 != NULL)	
	    printf (":\t");
    }
}
