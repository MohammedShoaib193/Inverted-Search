/*Documentation
Name : Mohammed Shoaib
Date : 01/04/2023
Description: Inverted Index
 */

#include "inverted_index.h"

int main (int argc, char* argv [])
{
    if (argc < 2)			//The number of Arguments passed in Command Line should be at least 2
    {
	printf ("ERROR: Invalid number of Arguments.\n");
	printf ("INFO: Usage ./inverted_index <file.txt> <file1.txt> ...\n" );
    }
    else
    {
	validation (argv);
    }

    return 0;
}


int validation (char* argv [])
{
    file_node_t* files_H = NULL;			//To store the File Names whose Words are present in the Database.
    main_node_t* HT [SIZE] = {NULL};		//To store the Database.
    int ret, option, flag = 0;
    char choice;

    validate_n_store_filenames (&files_H, argv);	//To Validate the File Names passed as CLA and store them in the File List.


    do
    {
	printf ("-----------------------------------------------------------------------\n");
	printf ("INFO: The List of Operations are as follows:\n1. Create Database\n2. Display Database\n3. Search Database\n4. Update Database\n5. Save Database\n");
	printf ("INPUT: Enter the Operation to be performed: ");
	scanf ("%d", &option);			//Ask the User for Operation to be performed.

	switch (option)
	{
	    case 1:		
		{
		    if (flag == 0)
		    {
			ret = create_DB (files_H, HT);
			if (ret == SUCCESS)
			{
			    printf ("INFO: Database Creation Successful.\n");
			}
			flag = 1;	
		    }
		    else
		    {
			printf ( "ERROR: Create Database Operation can only be called once while passing the Command Line Arguments.\n" );
		    }
		}
		break;
	    case 2:		
		{
		    ret = display_DB (HT);			//Display Database Operation for all the Words present.
		    if (ret == FAILURE)
		    {
			printf ( "INFO: The Database is Empty.\n");
		    }
		}
		break;
	    case 3:		
		{
		    char word [BUFF_SIZE];			//Search Database Operation for a given Word entered by the User.
		    printf ( "INPUT: Enter the word to be searched: " );
		    scanf ("%s", word);	

		    ret = search_DB (HT, word);
		    if (ret == SUCCESS)
		    {
			printf ("INFO: Word Search Successful.\n");
		    }
		}
		break;
	    case 4:		
		{
		    if (flag == 1)				//Update Database Operation to fill the Words of a New File in the Database.
		    {
			char f_name [NAMELENGTH];
			printf ("INPUT: Enter the File Name to be Updated in the Database: ");
			scanf ("%s", f_name);	

			ret = update_DB (&files_H, HT, f_name);
			if (ret == SUCCESS)
			{
			    printf ("INFO: Database Update Successful.\n");
			}
		    }
		    else
		    {
			printf ("ERROR: Create Database Operation shall be called before trying to call the Update Database Operation.\n");
		    }
		}
		break;
	    case 5:
		{
		    char f_name [NAMELENGTH];		//To read the File Name in which the Current Database needs to be saved.
		    printf ("INPUT: Enter the File Name to which the Database will be stored: " );
		    scanf ("%s", f_name);	

		    ret = save_DB (HT, f_name);
		    if (ret == SUCCESS)
		    {
			printf ("INFO: Database Store Successful.\n");
		    }
		}
		break;
	    default: printf ("ERROR: Invalid Choice. Please enter a number between 1 to 5.\n" );
	}

	printf ("INPUT: Do you want to Continue? [y / Y]: ");
	scanf (" %c", &choice);		
    } while ((choice == 'y') || (choice == 'Y'));

    return SUCCESS;
}
