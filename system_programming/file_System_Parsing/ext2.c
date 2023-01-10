#include <stdio.h>
#include <unistd.h> /* only for using close, lseek */
#include <fcntl.h> /* only for using open */
#include <assert.h> 
#include <string.h> 
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

	if (fseek(fp, SUPER_BLOCK_OFFSET, SEEK_SET) != 0) /* superblock appears olways after offset of 1024  */
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
		
		printf("size of the superblock struct is: %lu\n",sizeof(struct ext2_super_block));

		return 0;
	
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

int GetFIleContent(char *path, char *device_name)
{
	struct ext2_group_desc my_group_descriptor = {0};
	struct ext2_inode my_inode = {0};
	
	FILE *fp = NULL;
	
	assert(NULL != path);
	assert(NULL != device_name);
	
	my_group_descriptor = GetGroupDescriptor(device_name); /*  get the    */
	
	fp = fopen(device_name, "r");
	if (fp == NULL)
	{
		perror("GetFIleContent: fopen failed");
		return -1;
   	}
   	
   	if (fseek(fp, (BLOCK_SIZE * my_group_descriptor.bg_inode_table) + (sizeof(struct ext2_inode) *ROOT_INODE), SEEK_SET) != 0) /* junp to the inode table at inode 2-root dir */
	{
		perror("GetFIleContent: fseek failed");
		fclose(fp);
		return -1;
	}
	
	printf("the bg inode table is: %u\n", my_group_descriptor.bg_inode_table);
   	
   	if (fread(&my_inode, sizeof(struct ext2_inode), 1, fp) != 1) /* get the content of the inode table */
	{
		perror("GetFIleContent: fread failed");
		fclose(fp);
		return -1;
	}
					
	
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
	
	/*while (NULL != strchr(path,'/'))
	{
		
	
	}*/
	
	for (i = 0; i <  my_inode.i_blocks; i++)
	{
		if (fseek(fp, (BLOCK_SIZE * my_inode.i_block[i]), SEEK_SET) != 0) /* junp to the inode table at inode 2-root dir */
		{
			perror("GetFIleContent: fseek failed");
			fclose(fp);
			return -1;
		}
		
		
	
	}
	
	
	
	return 0;
}


int main(int argc, char *argv[])
{
	char *disk_name =NULL;
	
	assert(argc>=2); /* after adding path to file is should be 3   */
	
	disk_name =argv[1];
	
	printf("the disk name is: %s\n", argv[1]);
	printf("the count argc is: %d\n", argc);
	
	GetSuperBlock(disk_name);
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
