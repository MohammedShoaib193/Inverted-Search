#include "inverted_index.h"

int search_DB (main_node_t** head, char* word)		//function to search particular word in database
{
    int index = get_key (word [0]);			

    int ret = check_word (word, head [index]);	
    if (ret == REPEATED)				
    {
	main_node_t* temp = head [index];
	while (temp != NULL)
	{
	    if (strncmp (temp->word, word, BUFF_SIZE) == 0)
	    {
		printf ("INFO: Word"  " \"%s\""  " is found in the Database and is present in" " %d"  " File(s).\n" , word, temp->f_count);
		display_files (temp->sub_link);
		printf ("\n");
		return SUCCESS;
	    }

	    temp = temp->link;
	}
    }
    else	
    {
	printf ( "ERROR: Word"  " \"%s\""  " is not present in the Database.\n" , word);
	return FAILURE;
    }
}
