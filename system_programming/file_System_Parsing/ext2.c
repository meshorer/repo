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
#define RESERVED_INODES 11


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
	struct ext2_group_desc my_group_descriptor = {0};
	struct ext2_inode my_inode = {0};
	struct ext2_dir_entry_2 my_dir_entry = {0};
	int dir_entry_len = 0;
	unsigned int block_group = 0; /* to verify the block group for a specific inode */
	
	FILE *fp = NULL;
	char *my_buffer = NULL; /* to print the file content */
	
	assert(NULL != path);
	assert(NULL != device_name);
	
	my_group_descriptor = GetGroupDescriptor(device_name); /*  get the  Group Descriptor to jump to the inode table using bg_inode_table  */
	
	fp = fopen(device_name, "r");
	if (fp == NULL)
	{
		perror("GetFIleContent: fopen failed");
		return -1;
   	}
   	
	
	my_inode = GetInodeTable(fp,(BLOCK_SIZE * my_group_descriptor.bg_inode_table) + (sizeof(struct ext2_inode) * ROOT_INODE)); /*  get inode table for root directory  */
	
	PrintInodeTable(my_inode);				

	
	/*while (NULL != strchr(path,'/'))
	{
		
	
	}*/
	
	/*	
		1. first - find the size until the next '/'
		2. memcpy(dir_name,path,count_chars);
		3. strcmp to find the entry
		4. go to the inode table of the directory inode  
		5. get tha data of next entry 
		5. repeat steps
		
		path = path+1;
		while (NULL != strchr(path,'/'))
		{
			while (*path != '/')
			{
				++count_chars;
				path+=1;
			}
			path-= count_chars;
			memcpy(dir_name,path,count_chars);
			path+= count_chars + 1;
			while (0 != strcmp(dir_name, my_dir_entry.name))
			{
				GetDirEntry of current directory
				dir_entry_len += my_dir_entry.rec_len;
			}
			GetInodeTable of next sub directory (like we did with root)
			GetDirEntry  
		}
		
	*/
	dir_entry_len = 0;
	
	while (0 != strcmp("test.txt", my_dir_entry.name)) /* add stopping condition  */
	{
	
		my_dir_entry = GetDirEntry(fp, (BLOCK_SIZE * my_inode.i_block[0]+dir_entry_len));

	      	dir_entry_len += my_dir_entry.rec_len; /*  iterate on the dir entries untill you find the target       */
	}
	
	PrintDirEntry(my_dir_entry);
	       
	/* go back to the inode table to get the data block if the desired inode   */
	
	block_group = my_dir_entry.inode / INODES_PER_GROUP;
	my_dir_entry.inode = ((my_dir_entry.inode) % INODES_PER_GROUP) + RESERVED_INODES;
	printf("block group number for this inode is: %u\n", block_group);
	printf("local inode is number for this group is: %u\n", my_dir_entry.inode);
						
	my_inode = GetInodeTable(fp,(BLOCK_SIZE * my_group_descriptor.bg_inode_table) + (sizeof(struct ext2_inode) *(my_dir_entry.inode))); /*        */
	
	PrintInodeTable(my_inode);
	       
	/*  enf of iterating for directories */      
	/* jump to the data block to print it   */
	my_buffer = malloc(my_inode.i_size+1);
	
	if (fseek(fp, (BLOCK_SIZE * my_inode.i_block[0]), SEEK_SET) != 0) /* junp to the data block of the file */
		{
			perror("GetFIleContent: fseek failed");
			fclose(fp);
			return -1;
		}
		
	if (fread(my_buffer, my_inode.i_size, 1, fp) != 1) /* read the file contetnt to our allocated buffer */
	{
		perror("GetFIleContent: fread failed");
		fclose(fp);
		return -1;
	}	
		
	printf("content of file is: %s\n",my_buffer);
	
	free(my_buffer);
	
	fclose(fp);
		
	return 0;
}


int main(int argc, char *argv[])
{
	char *disk_name =NULL;
	
	assert(argc>=2); /* after adding path to file is should be 3   */
	
	disk_name =argv[1];
	
	printf("the disk name is: %s\n", argv[1]);
	printf("the count argc is: %d\n", argc);
	
	PrintSuperBlock(disk_name);
	PrintGroupDescriptor(disk_name);
	GetFIleContent("sdds",disk_name);

	return 0;
}


/* if (S_ISDIR(inode.i_mode))  check that the path is a directory. */
	
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
