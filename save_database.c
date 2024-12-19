#include "inverted_index.h"


int save_DB (main_node_t **head, char *fname)		//function to save the database
{
    char name [NAMELENGTH];
    strncpy (name, fname, NAMELENGTH);

    int ret = check_name (fname);
    if (ret == FAILURE)		
    {
	strncat(name, ".txt", 3);
    }

    FILE* fptr = fopen (name, "w");
    if (fptr == NULL)		
    {
	printf ("ERROR: Unable to open the File %s.\n", name);
	return FAILURE;
    }

    int i = 0;

    while (i < SIZE)		
    {
	if (head [i] != NULL)	
	{
	    main_node_t* temp1 = head [i];
	    fprintf (fptr, "#%d;\n", i);

	    while (temp1 != NULL)			
	    {
		fprintf (fptr, "%s;", temp1->word);
		fprintf (fptr, "%d;", temp1->f_count);

		sub_node_t* temp2 = temp1->sub_link;

		while (temp2 != NULL)		
		{
		    fprintf (fptr, "%s;", temp2->f_name);
		    fprintf (fptr, "%d;", temp2->w_count);
		    temp2 = temp2->link;	
		}

		fprintf (fptr, "#\n");
		temp1 = temp1->link;		
	    }
	}

	i += 1;		
    }

    fclose (fptr);		
    return SUCCESS;
}


int check_name (char* fname)				//to check if the file has some extension
{
    char* str = strstr (fname, ".");	

    if (str == NULL)
	return FAILURE;
    else
	return SUCCESS;
}
