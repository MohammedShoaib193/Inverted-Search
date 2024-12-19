#include "inverted_index.h"

int create_DB (file_node_t* file_head, main_node_t** head)	//to create the database for the given file list
{
    while (file_head != NULL)		
    {
	read_datafile (head, file_head->f_name);	

	printf ("INFO: Database creation for the File %s Successful.\n", file_head->f_name);
	file_head = file_head->link;	
    }

    return SUCCESS;
}

void read_datafile (main_node_t** head, char* f_name)		//to add all words into the hash table
{
    FILE* fptr = fopen (f_name, "r");
    if (fptr == NULL)	
	return;

    fseek (fptr, 0L, SEEK_SET);				//to start reading file from beginning

    char buffer [BUFF_SIZE];	
    int val;	
    int key;	
    int ret;

    do
    {
	memset (buffer, '\0', BUFF_SIZE);	
	val = fscanf (fptr, "%s", buffer);
	if (val != 0)	
	{
	    if ((strlen (buffer)) != 0)		
	    {
		key = get_key (buffer [0]);	

		ret = check_word (buffer, head [key]);
		if (ret == FAILURE)		
		{
		    ret = insert_at_last_main (&head [key], buffer, f_name);
		    if (ret == FAILURE)	
		    {
			printf ("ERROR: Unable to add the Word \"%s\" in the Database.\n" , buffer);
			return;
		    }
		}
		else	
		{
		    ret = check_file (f_name, buffer, head [key]);
		    if (ret == FAILURE)	
		    {
			ret = update_link_table (&head [key], buffer, f_name);
			if (ret == FAILURE)	
			{
			    printf ( "ERROR: Unable to add the File \"%s\" details for the Word \"%s\" in the Database.\n" , f_name, buffer);
			    return;
			}

		    }
		    else	
		    {
			ret = update_word_count (&head [key], buffer, f_name);
			if (ret == FAILURE)
			{
			    printf ("ERROR: Unable to Update the Word Count for the Word \"%s\" in the File \"%s\".\n", buffer, f_name);
			    return;
			}
		    }
		}
	    }
	}
    } while (val != EOF);	

    fclose (fptr);		
    return;
}


int update_link_table (main_node_t** head, char* word, char* f_name)		//function to insert file details in sub list 
{
    main_node_t* temp1 = *head;
    while (temp1 != NULL)		
    {
	if (strncmp (temp1->word, word, BUFF_SIZE) == 0)	
	{
	    sub_node_t* temp2 = temp1->sub_link;
	    while (temp2->link != NULL)	
	    {
		temp2 = temp2->link;	
	    }

	    temp2->link = create_sub_node (f_name);		
	    if (temp2->link == NULL)	
		return FAILURE;
	    else
		temp1->f_count += 1;	
	}

	temp1 = temp1->link;	
    }

    return SUCCESS;
}


int update_word_count (main_node_t **head, char* word, char* f_name)		//function to update word count
{
    main_node_t* temp1 = *head;
    while (temp1 != NULL)		
    {
	if (strncmp (temp1->word, word, BUFF_SIZE) == 0)	
	{
	    sub_node_t* temp2 = temp1->sub_link;
	    while (temp2 != NULL)			
	    {
		if (strncmp (temp2->f_name, f_name, NAMELENGTH) == 0)	
		{
		    temp2->w_count += 1;	
		    return SUCCESS;
		}

		temp2 = temp2->link;    	
	    }
	}

	temp1 = temp1->link;	
    }

    return FAILURE;
}


int insert_at_last_main (main_node_t** head, char* word, char* f_name)		//function to insert at last in main node
{
    main_node_t* new = (main_node_t*) malloc (sizeof (main_node_t));	
    if (new == NULL)		
	return FAILURE;

    strncpy (new->word, word, (strlen (word) + 1));				
    new->link = NULL;		
    new->sub_link = create_sub_node (f_name);				
    new->f_count = 1;		

    if (*head == NULL)		
    {
	*head = new;
	return SUCCESS;
    }

    main_node_t* temp = *head;
    while (temp->link != NULL)	
    {
	temp = temp->link;	
    }

    temp->link = new;		

    return SUCCESS;
}

sub_node_t* create_sub_node (char* f_name)
{
    sub_node_t* new = (sub_node_t*) malloc (sizeof (sub_node_t));	
    strncpy (new->f_name, f_name, (strlen (f_name) + 1));		
    new->w_count = 1;	
    new->link = NULL;	
    return new;
}
