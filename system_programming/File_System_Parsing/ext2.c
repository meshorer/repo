#include <stdio.h>
#include <unistd.h> /* only for using close, lseek */
#include <fcntl.h> /* only for using open */
#include <assert.h> 
#include "ext2.h"

#define SUPER_BLOCK_OFFSET 1024
 
/*int GetSuperBlock(char *device_name)
{
	int handler = 0;
	struct ext2_super_block super_struct; 
	off_t descriptor = -1;
	int block_size = 0;
	
	handler = open(device_name,O_RDONLY);
	if (0 > handler)
	{
		return -1;
	}
	printf("handler is : %d\n",handler);
	descriptor = lseek(handler, 1024, SEEK_SET);
	if ( -1 == descriptor)
	{
		return -1;
	}
	
	read(handler,&super_struct,sizeof(struct ext2_super_block));
	
	return 0;
	
}*/


int GetSuperBlock(char *device_name)
{
	FILE *fp = NULL;
    	struct ext2_super_block super_block_struct;
    	
	assert(NULL != device_name);
	
    	fp = fopen(device_name, "r");
	if (fp == NULL)
	{
		return -1;
   	}

	if (fseek(fp, SUPER_BLOCK_OFFSET, SEEK_SET) != 0)
	{
		return -1;
	}

	if (fread(&super_block_struct, sizeof(struct ext2_super_block), 1, fp) != 1)
	{
		return -1;
	}
		
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
	       
		fclose(fp);
		

		return 0;
	
}

int GetGroupDescriptor(char *device_name)
{
	FILE *fp = NULL;
	struct ext2_group_desc my_group_descriptor;
		
	assert(NULL != device_name);
	
	fp = fopen(device_name, "r");
	if (fp == NULL)
	{
		return -1;
   	}

	fseek(fp,0, SEEK_SET); /* should return the file descriptor to the begining of the file */

	
	if (fseek(fp, 4*SUPER_BLOCK_OFFSET, SEEK_SET) != 0)
	{
		return -1;
	}
	
	if (fread(&my_group_descriptor, sizeof(struct ext2_group_desc), 1, fp) != 1)
	{
		return -1;
	}
	
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
	
	fclose(fp);
	
	return 0;
}


int main(int argc, char *argv[])
{
	char *name =NULL;
	
	assert(argc>=2); /* after adding path to file is should be 3   */
	
	name =argv[1];
	
	printf("the disk name is: %s\n", argv[1]);
	printf("the count argc is: %d\n", argc);
	
	GetSuperBlock(name);
	GetGroupDescriptor(name);

	return 0;
}
