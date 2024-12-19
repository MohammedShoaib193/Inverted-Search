#include "inverted_index.h"

void validate_n_store_filenames (file_node_t** files_h, char* filenames[])
{
    int i = 1, ret;	

    while (filenames [i] != NULL)			//The loop shall run to Validate each File name passed through Command Line.
    {
	ret = IsFileValid (filenames [i]);
	if (ret == SUCCESS)			//check if File name is valid
	{
	    ret = IsFileDuplicate (filenames [i], files_h);		//chcek if file is duplicate
	    if (ret == FAILURE)	       //if file name is not present add it file list
	    {
		ret = store_filenames_to_list (filenames [i], files_h);
		if (ret == SUCCESS)	//if file name is present the print message
		{
		    printf ("INFO: The File %s is added to the List Successfully.\n", filenames [i]);
		}
	    }
	}
	i = i + 1;	
    }

    if (*files_h == NULL)					
    {
	printf ("ERROR: There is no Valid File passed as Input.\n" "INFO: Please enter names of Valid Files only.\n");

	exit (0);	
    }

    return;
}



int IsFileValid (char* filename)
{
    FILE* fptr = fopen (filename, "r");
    if (fptr == NULL)			//to check if file exist or not
    {
	printf ("ERROR: The File %s is not present.\n"  "INFO: So, this File cannot be added into the Database.\n", filename);
	return NOT_PRESENT;
    }
    else			
    {
	fseek (fptr, 0L, SEEK_END);	//condition to check if file is empty
	int pos = ftell (fptr);

	if (pos == 0)	
	{
	    printf ( "ERROR: The File %s is an Empty File.\n" "INFO: So, this File cannot be added into the Database.\n" , filename);
	    return FILE_EMPTY;
	}
	else
	{
	    fclose (fptr);		//to close the file
	    return SUCCESS;
	}
    }
}


int IsFileDuplicate (char* filename, file_node_t** head)
{
    file_node_t* temp = *head;

    while (temp != NULL)			//to check till end of file list and comapre each filename
    {
	if ((strncmp (filename, temp->f_name, NAMELENGTH)) == 0)	//to avoid readdition of same files 
	{
	    printf ( "ERROR: The File %s is repeated.\n"  "INFO: So, this File cannot be added into the Database.\n" , filename);
	    return REPEATED;
	}

	temp = temp->link;
    }

    return FAILURE;
}



int store_filenames_to_list (char* f_name, file_node_t** head)
{
    int ret = insert_at_last_file (head, f_name);			//if filename is not added terminate process
    if (ret == FAILURE)		
    {
	printf ("ERROR: Unable to add the File %s into the File List.\n", f_name);
	return FAILURE;
    }

    return SUCCESS;
}



int get_key (char f_char)			//to find the key for the given word and and add the word in hash table
{

    if (isalpha (f_char))		
    {
	f_char = (char) toupper (f_char);
	return (f_char % 65);
    }
    else if (isdigit (f_char))	
    {
	return 26;
    }
    else				
    {
	return 27;
    }
}


int check_word (char* word, main_node_t* head)		//function to chcek if the word is already present in hash table
{
    while (head != NULL)		
    {
	if (strncmp (head->word, word, BUFF_SIZE) == 0)		
	    return REPEATED;

	head = head->link;	
    }

    return FAILURE;
}



int check_file (char* f_name, char* word, main_node_t* head)		//to chcek the file deatils are already present 
{
    while (head != NULL)	
    {
	if (strncmp (head->word, word, BUFF_SIZE) == 0)	
	{
	    sub_node_t* temp = head->sub_link;
	    while (temp != NULL)	
	    {
		if (strncmp (temp->f_name, f_name, NAMELENGTH) == 0)	
		    return REPEATED;

		temp = temp->link;	
	    }
	}

	head = head->link;		
    }

    return FAILURE;
}

int insert_at_last_file (file_node_t** head, char* f_name)		//function to insert at last 
{
    file_node_t* new = (file_node_t*) malloc (sizeof (file_node_t));	
    if (new == NULL)		
	return FAILURE;

    strncpy (new->f_name, f_name, (strlen (f_name) + 1));			
    new->link = NULL;		

    if (*head == NULL)		
    {
	*head = new;
	return SUCCESS;
    }

    file_node_t* temp = *head;
    while (temp->link != NULL)	
    {
	temp = temp->link;	
    }

    temp->link = new;		

    return SUCCESS;
}
