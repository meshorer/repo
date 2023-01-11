	/**************************************************************************/
		dir_entry_len = 0;
		while ( dir_entry_len < BLOCK_SIZE)  							/*  iterate on the dir entries untill you find the desired directory-name */
		{
			
			my_dir_entry = GetDirEntry(fp, (BLOCK_SIZE * my_inode.i_block[0]+dir_entry_len));  	/*  iterate on the dir entries untill you find the desired directory-name */
			if (0 == strcmp(dir_name, my_dir_entry.name) && my_dir_entry.file_type == 2)
			{
				is_found = 1;
				break;
			}
		      	dir_entry_len += my_dir_entry.rec_len; 						/*  sum the records entry to start every itarate from the next record */
		}
		
		if (0 == is_found)
		{
			perror("no such directory");
			exit(0);
		}
		is_found = 0;
		/**************************************************************************/
