#include <stdio.h>
#include <assert.h> 
#include <string.h> /*  for strcmp, strchr   */
#include <stdlib.h> /*  for malloc   */
#include "ext2.h"

#define SUPER_BLOCK_OFFSET 1024
#define BLOCK_SIZE 4096
#define ROOT_INODE 2



/*  
	commands to create the ram disk:
	sudo modprobe brd rd_size=512000 rd_nr=1 max_part=1
	sudo mkfs.ext2 /dev/ram0 
	sudo mount /dev/ram0 /mnt/parsing_ext
*/
 
void PrintSuperBlock(char *device_name)
{
	struct ext2_super_block super_block_struct = {0};
	
	assert(NULL != device_name);
	
	super_block_struct = GetSuperBlock(device_name);
			
	printf("\n\nReading super-block from device\n"
	       "Inodes count            : %u\n"
	       "Blocks count            : %u\n"
	       "Reserved blocks count   : %u\n"
	       "Free blocks count       : %u\n"
	       "Free inodes count       : %u\n"
	       "First data block        : %u\n"
	       "Block size              : %u\n"
	       "Blocks per group        : %u\n"
	       "Inodes per group        : %u\n"
	       "Creator OS              : %u\n"
	       "First non-reserved inode: %u\n"
	       "Size of inode structure : %hu\n\n\n"
	       ,
	       super_block_struct.s_inodes_count,  
	       super_block_struct.s_blocks_count,
	       super_block_struct.s_r_blocks_count,     
	       super_block_struct.s_free_blocks_count,
	       super_block_struct.s_free_inodes_count,
	       super_block_struct.s_first_data_block,
	       super_block_struct.s_log_block_size,
	       super_block_struct.s_blocks_per_group,
	       super_block_struct.s_inodes_per_group,
	       super_block_struct.s_creator_os,
	       super_block_struct.s_first_ino,         
	       super_block_struct.s_inode_size);       
}


struct ext2_super_block GetSuperBlock(char *device_name)
{
	FILE *fp = NULL;
    	struct ext2_super_block super_block_struct = {0};
    	
	assert(NULL != device_name);
	
    	fp = fopen(device_name, "r");
	if (fp == NULL)
	{
		return super_block_struct;
   	}

	if (fseek(fp, SUPER_BLOCK_OFFSET, SEEK_SET) != 0) /* superblock appears olways after offset of 1024  */
	{
		return super_block_struct;
	}

	if (fread(&super_block_struct, sizeof(struct ext2_super_block), 1, fp) != 1)
	{
		return super_block_struct;
	}
		       
	fclose(fp);
		
	return super_block_struct;
}


void PrintGroupDescriptor(char *device_name)
{
	struct ext2_group_desc my_group_descriptor;
	
	assert(NULL != device_name);
	
	my_group_descriptor  = GetGroupDescriptor(device_name);
	
	printf("Reading Group descriptor from device\n"
	       "block_bitmap            : %u\n"
	       "inode_bitmap            : %u\n"
	       "inode_table		: %u\n"
	       "Free blocks count       : %u\n"
	       "Free inodes count       : %u\n"
	       "used_dirs_count         : %u\n"
	       "pad	                : %u\n\n\n"
	       ,
	       my_group_descriptor.bg_block_bitmap,  
	       my_group_descriptor.bg_inode_bitmap,
	       my_group_descriptor.bg_inode_table,     
	       my_group_descriptor.bg_free_blocks_count,
	       my_group_descriptor.bg_free_inodes_count,
	       my_group_descriptor.bg_used_dirs_count,
	       my_group_descriptor.bg_pad);
}



struct ext2_group_desc GetGroupDescriptor(char *device_name)
{
	FILE *fp = NULL;
	struct ext2_group_desc my_group_descriptor = {0};
		
	assert(NULL != device_name);
	
	fp = fopen(device_name, "r");
	if (fp == NULL)
	{
		perror("GetGroupDescriptor: fopen failed");
		return my_group_descriptor;
   	}

		
	if (fseek(fp, BLOCK_SIZE, SEEK_SET) != 0) /* Group Descriptor appears after at the begining of the second block  */
	{
		perror("GetGroupDescriptor: fseek failed");
		fclose(fp);
		return my_group_descriptor;
	}
	
	if (fread(&my_group_descriptor, sizeof(struct ext2_group_desc), 1, fp) != 1)
	{
		perror("GetGroupDescriptor: fread failed");
		fclose(fp);
		return my_group_descriptor;
	}
	
	fclose(fp);
	return my_group_descriptor;
}

struct ext2_inode GetInodeTable(FILE *fp, size_t len)
{
	
	struct ext2_inode my_inode = {0};
	
	assert(NULL != fp);
	
	if (fseek(fp,len, SEEK_SET) != 0) /* jump to the inode table at inode 2-root dir */
	{
		perror("GetFIleContent: fseek failed");
		fclose(fp);
		return my_inode;
	}
	
   	if (fread(&my_inode, sizeof(struct ext2_inode), 1, fp) != 1) /* get the content of the inode table of root directory */
	{
		perror("GetFIleContent: fread failed");
		fclose(fp);
		return my_inode;
	}

	
	return my_inode;
}

void PrintInodeTable(struct ext2_inode my_inode)
{
	printf("\n\nReading inode table:\n"
	       "i_mode            : %u\n"
	       "i_uid             : %u\n"
	       "i_size            : %u\n"
	       "i_atime 	  : %u\n"
	       "i_ctime           : %u\n"
	       "i_mtime           : %u\n"
	       "i_dtime           : %u\n"
	       "i_gid 	  	  : %u\n"
	       "i_links_count 	  : %u\n"
	       "i_blocks 	  : %u\n"
	       "i_flags 	  : %u\n"
	       "point to block    : %u\n"
	       ,
	       my_inode.i_mode,  
	       my_inode.i_uid,
	       my_inode.i_size,     
	       my_inode.i_atime,
	       my_inode.i_ctime,
	       my_inode.i_mtime,
	       my_inode.i_dtime,
	       my_inode.i_gid,
	       my_inode.i_links_count,
	       my_inode.i_blocks,
	       my_inode.i_flags,
	       my_inode.i_block[0]);

}

struct ext2_dir_entry_2 GetDirEntry(FILE *fp, size_t len)
{
	struct ext2_dir_entry_2 my_dir_entry = {0};
	
	assert(NULL != fp);
	
	if (fseek(fp,len,SEEK_SET) != 0) /* jump to the inode table at inode 2-root dir */
	{
		perror("GetFIleContent: fseek failed");
		fclose(fp);
		return my_dir_entry;
	}
	
	if (fread(&my_dir_entry, sizeof(struct ext2_dir_entry_2), 1, fp) != 1) /* get the content of the dir entries */
	{
		perror("GetFIleContent: fread failed");
		fclose(fp);
		return my_dir_entry;
	}
		
	return my_dir_entry;	
}

void PrintDirEntry(struct ext2_dir_entry_2 my_dir_entry)
{
		  
	printf("\n\nReading dir entry :\n"
	       "inode               : %u\n"
	       "rec_len             : %u\n"
	       "name_len            : %u\n"
	       "file_type 	    : %u\n"
	       "name	 	    : %s\n"
	       ,
	       my_dir_entry.inode,
	       my_dir_entry.rec_len,
	       my_dir_entry.name_len,
	       my_dir_entry.file_type,
	       my_dir_entry.name); 
}


struct ext2_dir_entry_2 FindDirEntry(char *dir_name,FILE * fp, struct ext2_inode my_inode, int file_type)
{
	int dir_entry_len = 0;
	struct ext2_dir_entry_2 my_dir_entry = {0};
	
	while (dir_entry_len < BLOCK_SIZE)  									/*  iterate on the dir entries untill you find the desired directory-name */
		{
			
			my_dir_entry = GetDirEntry(fp, (BLOCK_SIZE * my_inode.i_block[0]+dir_entry_len));  	/*  iterate on the dir entries untill you find the desired directory-name */
			if (0 == strcmp(dir_name, my_dir_entry.name) && my_dir_entry.file_type == file_type)
			{
				return my_dir_entry;
			}
		      	dir_entry_len += my_dir_entry.rec_len; 							/*  sum the records entry to start every itarate from the next record */
		}
		
			perror("path doesn't exist");
			exit(0);	
}


int GetFIleContent(char *path, char *device_name)
{
	struct ext2_super_block super_block_struct = {0};
	struct ext2_group_desc my_group_descriptor = {0};
	struct ext2_inode my_inode = {0};
	struct ext2_dir_entry_2 my_dir_entry = {0};
	unsigned int block_group = 0; 									/* to verify the block group for a specific inode */
	
	FILE *fp = NULL;
	char *my_buffer = NULL; 									/* to print the file content */
	int count_chars = 0;										/* to find the next directory name */
	char *dir_name = NULL;

	assert(NULL != path);
	assert(NULL != device_name);
	
	super_block_struct = GetSuperBlock(device_name);
	my_group_descriptor = GetGroupDescriptor(device_name); 						/*  get the  Group Descriptor to jump to the inode table using bg_inode_table  */
	
	fp = fopen(device_name, "r");
	if (fp == NULL)
	{
		perror("GetFIleContent: fopen failed");
		return -1;
   	}
   	
   	

	my_inode = GetInodeTable(fp,(BLOCK_SIZE * my_group_descriptor.bg_inode_table) + (sizeof(struct ext2_inode) * ROOT_INODE)); /*  get inode table for root directory  */
			
	path = path+1;
	
	dir_name = malloc(strlen(path)*sizeof(char));
	
	while (NULL != strchr(path,'/'))								/*  entrting loop to enter the last subdir in the path  */
	{
			
		count_chars = 0;
		while ('/' != *path)									/* get the numer of characters until the next '/' */
		{
			++count_chars;
			path+=1;
		}
		path-= count_chars;
		dir_name = realloc(dir_name,count_chars+1);						/* change the size of dir_name according to the name od the directory */
		memcpy(dir_name,path,count_chars);							/* memcpy to the dir_name according to the counter we did */
		*(dir_name+count_chars) = '\0'; 							/* make sure the directory name ends properly with null-byte */
		
		my_dir_entry = FindDirEntry(dir_name,fp, my_inode,2);
		
		
		PrintDirEntry(my_dir_entry);
		path+= count_chars + 1;									/*  advance path to get the next directory name (+1 for '/') */
		printf("check path is: %s\n",path);
		
		
	
		block_group = (my_dir_entry.inode -1) / super_block_struct.s_inodes_per_group;		/* check the relevant block-group for this specific inode   */
		my_dir_entry.inode = (my_dir_entry.inode - 1) % super_block_struct.s_inodes_per_group;  /* update the inode number to be relative to the block group  */

					
		my_inode = GetInodeTable(fp,(block_group * (super_block_struct.s_blocks_per_group * BLOCK_SIZE )) + (BLOCK_SIZE * my_group_descriptor.bg_inode_table) + (super_block_struct.s_inode_size*(my_dir_entry.inode))); 						/* go back to the inode table to get the data block of the desired inode   */
		
		PrintInodeTable(my_inode);
		
	}												/*  enf of iterating for directories */ 
	
	     
		my_dir_entry = FindDirEntry(path,fp, my_inode,1);					/*  find the dir entry for the target - file */ 
		
		PrintDirEntry(my_dir_entry);
		       	
		block_group = (my_dir_entry.inode -1) / super_block_struct.s_inodes_per_group;		/* check the relevant block-group for this specific inode   */	
		my_dir_entry.inode = (my_dir_entry.inode - 1) % super_block_struct.s_inodes_per_group;	/* update the inode number to be relative to the block group  */

							
		my_inode = GetInodeTable(fp,(block_group * (super_block_struct.s_blocks_per_group * BLOCK_SIZE )) + (BLOCK_SIZE * my_group_descriptor.bg_inode_table) + (super_block_struct.s_inode_size*(my_dir_entry.inode))); 						/*  get the inode table of the file to find it's data blocks  */
		
		PrintInodeTable(my_inode);
	

	my_buffer = malloc(my_inode.i_size+1);								/*  set the buffer to the size of the desired file-content  */

	if (fseek(fp, (BLOCK_SIZE * my_inode.i_block[0]), SEEK_SET) != 0) 				/* jump to the data block to get it   */
		{
			perror("GetFIleContent: fseek failed");
			fclose(fp);
			return -1;
		}
		
	if (fread(my_buffer, my_inode.i_size, 1, fp) != 1) 						/* get the data blocks  */				
	{
		perror("GetFIleContent: fread failed");
		fclose(fp);
		return -1;
	}	
		
	printf("content of file is: %s\n",my_buffer);

	free(my_buffer);
	free(dir_name);
	
	fclose(fp);
		
	return 0;
}


int main(int argc, char *argv[])
{

	
	assert(argc>=3);
	
	
	printf("the disk name is: %s\n", argv[1]);
	printf("the path is: %s\n", argv[2]);
	printf("the count argc is: %d\n", argc);
	
	PrintSuperBlock(argv[1]);
	PrintGroupDescriptor(argv[1]);
	GetFIleContent(argv[2],argv[1]);

	return 0;
}



	

	/*******************************************************************************
	printf("print group descriptors:\n\n\n");
	
	for (i = 3; i < 4; i++){
	printf("group descriptor number %u\n",i+1);
	
	if (fseek(fp, (2* (super_block_struct.s_blocks_per_group * BLOCK_SIZE )) +BLOCK_SIZE, SEEK_SET) != 0) 
	{
		perror("GetGroupDescriptor: fseek failed");
		fclose(fp);
		
	}
	
	if (fread(&my_group_descriptor, sizeof(struct ext2_group_desc), 1, fp) != 1)
	{
		perror("GetGroupDescriptor: fread failed");
		fclose(fp);
		
	}
	
	printf("Reading Group descriptor\n"
	       "block_bitmap            : %u\n"
	       "inode_bitmap            : %u\n"
	       "inode_table		: %u\n"
	       "Free blocks count       : %u\n"
	       "Free inodes count       : %u\n"
	       "used_dirs_count         : %u\n"
	       "pad	                : %u\n\n\n"
	       ,
	       my_group_descriptor.bg_block_bitmap,  
	       my_group_descriptor.bg_inode_bitmap,
	       my_group_descriptor.bg_inode_table,     
	       my_group_descriptor.bg_free_blocks_count,
	       my_group_descriptor.bg_free_inodes_count,
	       my_group_descriptor.bg_used_dirs_count,
	       my_group_descriptor.bg_pad);}
	       
	
	
	******************************************************************************/
	
