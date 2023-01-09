#include <stdio.h>
#include <unistd.h> /* only for using close, lseek */
#include <fcntl.h> /* only for using open */
#include "ext2.h"

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
    	struct ext2_super_block super_struct;
    	

    	fp = fopen(device_name, "r");
	if (fp == NULL)
	{
		return -1;
   	}

	if (fseek(fp, 1024, SEEK_SET) != 0)
	{
		return -1;
	}

	if (fread(&super_struct, sizeof(struct ext2_super_block), 1, fp) != 1)
	{
		return -1;
	}
		
	printf("Reading super-block from device\n"
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
	       "Size of inode structure : %hu\n"
	       ,
	       super_struct.s_inodes_count,  
	       super_struct.s_blocks_count,
	       super_struct.s_r_blocks_count,     
	       super_struct.s_free_blocks_count,
	       super_struct.s_free_inodes_count,
	       super_struct.s_first_data_block,
	       super_struct.s_log_block_size,
	       super_struct.s_blocks_per_group,
	       super_struct.s_inodes_per_group,
	       super_struct.s_creator_os,
	       super_struct.s_first_ino,         
	       super_struct.s_inode_size);
	
	return 0;
	
}




int main()
{
	char name[] ="/dev/ram0";
	GetSuperBlock(name);
	

	return 0;
}
