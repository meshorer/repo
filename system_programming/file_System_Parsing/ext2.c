#include <stdio.h>
#include <unistd.h> /* only for using close, lseek */
#include <fcntl.h> /* only for using open */
#include <assert.h> 
#include <string.h> 
#include <stdlib.h> /*  for malloc   */
#include "ext2.h"

#define SUPER_BLOCK_OFFSET 1024
#define BLOCK_SIZE 4096
#define ROOT_INODE 2
#define INODES_PER_GROUP 32000
#define RESERVED_INODES 10


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


int GetFIleContent(char *path, char *device_name)
{
	struct ext2_super_block super_block_struct = {0};
	struct ext2_group_desc my_group_descriptor = {0};
	struct ext2_inode my_inode = {0};
	struct ext2_dir_entry_2 my_dir_entry = {0};
	int dir_entry_len = 0;
	unsigned int block_group = 0; /* to verify the block group for a specific inode */
	
	FILE *fp = NULL;
	char *my_buffer = NULL; /* to print the file content */
	int count_chars = 0;
	char *dir_name = NULL;
	assert(NULL != path);
	assert(NULL != device_name);
	
	super_block_struct = GetSuperBlock(device_name);
	my_group_descriptor = GetGroupDescriptor(device_name); /*  get the  Group Descriptor to jump to the inode table using bg_inode_table  */
	
	fp = fopen(device_name, "r");
	if (fp == NULL)
	{
		perror("GetFIleContent: fopen failed");
		return -1;
   	}
   	
   	
	printf("\nprinting inode table for root directory:\n");
	my_inode = GetInodeTable(fp,(BLOCK_SIZE * my_group_descriptor.bg_inode_table) + (sizeof(struct ext2_inode) * ROOT_INODE)); /*  get inode table for root directory  */
	
	PrintInodeTable(my_inode);				
	printf("\n\n");
		
	path = path+1;
	
	dir_name = malloc(strlen(path)*sizeof(char));
	
	while (NULL != strchr(path,'/'))
	{
		printf("entrting loop to enter the last subdir in the path! :\n\n");
		
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
		
		
		dir_entry_len = 0;
		while (0 != strcmp(dir_name, my_dir_entry.name) && dir_entry_len < BLOCK_SIZE)  	/*  iterate on the dir entries untill you find the desired directory-name */
		{
		
			my_dir_entry = GetDirEntry(fp, (BLOCK_SIZE * my_inode.i_block[0]+dir_entry_len));  	/*  iterate on the dir entries untill you find the desired directory-name */
			
		      	dir_entry_len += my_dir_entry.rec_len; 						/*  sum the records entry to start every itarate from the next record */
		}
		PrintDirEntry(my_dir_entry);
		path+= count_chars + 1;									/*  advance path to get the next directory name (+1 for '/') */
		printf("check path is: %s\n",path);
		
		
	
		block_group = (my_dir_entry.inode -1) / super_block_struct.s_inodes_per_group;		/* check the relevant block-group for this specific inode   */
		my_dir_entry.inode = (my_dir_entry.inode - 1) % super_block_struct.s_inodes_per_group;  /* update the inode number to be relative to the block group  */
		printf("block group number for this inode is: %u\n", block_group);
		printf("local inode is number for this group is: %u\n", my_dir_entry.inode);
		
		printf("print the inode of the directory:\n");					
		my_inode = GetInodeTable(fp,(block_group * (super_block_struct.s_blocks_per_group * BLOCK_SIZE )) + (BLOCK_SIZE * my_group_descriptor.bg_inode_table) + (super_block_struct.s_inode_size*(my_dir_entry.inode))); 						/* go back to the inode table to get the data block of the desired inode   */
		
		PrintInodeTable(my_inode);
		
	}
	
	
	/*  enf of iterating for directories */      
	dir_entry_len = 0;
	if (NULL == strchr(path,'/'))
	{
		printf("\nfile name lastly  is: %s\n",path);
		while (0 != strcmp(path, my_dir_entry.name) && dir_entry_len < BLOCK_SIZE)
		{
		
			my_dir_entry = GetDirEntry(fp, (BLOCK_SIZE * my_inode.i_block[0]+dir_entry_len));
			
		      	dir_entry_len += my_dir_entry.rec_len; 						/*  iterate on the dir entries untill you find the target       */
		}
		
		PrintDirEntry(my_dir_entry);
		       
		
		
		block_group = (my_dir_entry.inode -1) / super_block_struct.s_inodes_per_group;
		my_dir_entry.inode = (my_dir_entry.inode - 1) % super_block_struct.s_inodes_per_group;
		printf("block group number for this inode is: %u\n", block_group);
		printf("local inode is number for this group is: %u\n", my_dir_entry.inode);
							
		my_inode = GetInodeTable(fp,(block_group * (super_block_struct.s_blocks_per_group * BLOCK_SIZE )) + (BLOCK_SIZE * my_group_descriptor.bg_inode_table) + (super_block_struct.s_inode_size*(my_dir_entry.inode))); /*   inode of the file     */
		
		PrintInodeTable(my_inode);
	}
	
	
	my_buffer = malloc(my_inode.i_size+1);

	printf("i_size is: %u\n",my_inode.i_size);
	printf("block pointer is: %u\n",my_inode.i_block[0]);

	if (fseek(fp, (BLOCK_SIZE * my_inode.i_block[0]), SEEK_SET) != 0) 
		{
			perror("GetFIleContent: fseek failed");
			fclose(fp);
			return -1;
		}
		
	if (fread(my_buffer, my_inode.i_size, 1, fp) != 1) 						/* jump to the data block to print it   */
	{
		perror("GetFIleContent: fread failed");
		fclose(fp);
		return -1;
	}	
		
	printf("content of file is: %s\n",my_buffer);
	puts(my_buffer);
	

	free(my_buffer);
	
	

	free(dir_name);
	fclose(fp);
		
	return 0;
}


int main(int argc, char *argv[])
{
	char *disk_name =NULL;
	
	/*assert(argc>=2);*/ /* after adding path to file is should be 3   */
	
	/*disk_name =argv[1];*/
	disk_name = "/dev/ram0";
	
	printf("the disk name is: %s\n", argv[1]);
	printf("the count argc is: %d\n", argc);
	
	PrintSuperBlock(disk_name);
	/*PrintGroupDescriptor(disk_name);*/
	GetFIleContent("/subdir/another/third.txt",disk_name);

	return 0;
}



	
	/*  The root directory is always located at inode 2. */
	
	/* bg_inode_table contains the block number where the inode table begins for the group */
	
	/* 
	1. check the number of '/' and assign it to a variable. *(maybe -  while (NULL != strchr('/',path)) 
	2. get the bg_inode_table from the first group descriptor, and go there
	3. find inode number 2 (root directory) and check jump to it's data block (i_block) to find the dir-entries
	4. use a function to get the next dir-name (until the next /) and look for it in the dir-entry to find it's inode number
	5. use the inode number to understand on which block group it is (inode number / blocks-per-group), then jump to its block group
	6. repeat steps (from step 2) until you find the file name 	 
	
	Creating filesystem with 128000 4k blocks and 128000 inodes
	Filesystem UUID: fea03f6a-33f6-4de2-a522-e88d5b28e9de
	Superblock backups stored on blocks: 
	32768, 98304

	*/
	
	
	/*******************************************************************************
	printf("\n\ntest starts:\n\n\n");
	
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
	       
	
	       
	while (0 != strcmp(dir_name, my_dir_entry.name) && dir_entry_len < BLOCK_SIZE)  	
		{
		
			my_dir_entry = GetDirEntry(fp, (BLOCK_SIZE * my_inode.i_block[0]+dir_entry_len));  	
			
		      	dir_entry_len += my_dir_entry.rec_len; 						
		}
		
	******************************************************************************/
	
