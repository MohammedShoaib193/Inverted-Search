#include "inverted_index.h"

int update_DB (file_node_t** files_h, main_node_t** head, char* f_name)		//function to update the database 
{
    int ret;

    if ((IsFileValid (f_name)) == SUCCESS)		
    {
	if ((IsFileDuplicate (f_name, files_h)) == FAILURE)	
	{
	    ret = store_filenames_to_list (f_name, files_h);
	    if (ret == SUCCESS)		
	    {
		printf ("INFO: The File %s is added to the List successfully.\n", f_name);

		read_datafile (head, f_name);		

		printf ( "INFO: Database creation for the File %s Successful.\n", f_name);

		return SUCCESS;
	    }
	}
    }

    return FAILURE;
}
