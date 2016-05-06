#include<stdio.h>
#include "journal_file_manager.h"

int main(){
	int p_id=0;//Process_ID/P_ID. Will be generated by NEW_ACTION
	int file_id=0;//Which file to edit. In this design a file can be allocated multiple blocks/cells
	int ret=0;//To check return flags
	int cell_no=0;//The cell/block to write. Possible only if the file owns that cell/block.
	char value_data[100]="First_Value";//A data to write in cell/block
	char *read_data=NULL;//To store the return of READ_CURRENT_VALUE. Possible only if the file owns that cell/block.

//Test Case #1	
//To check functionality of WRITE_NEW_VALUE, COMMIT and READ_CURRENT_VALUE
//Here we are trying to create an action/process. 
//Allocate a block to a file in cell storage system. 
//Write some string to block. Block Size limited to 1024 bytes. Can only hold 100 blocks in temp 
//Commit the changes for a particular file(All the blocks of the file will be commited in a go)
//Read the value from the block, and display the changed value.
	
	printf("\n-----------WITH COMMIT--------------");
	
	p_id=NEW_ACTION(file_id);
	
	ret=WRITE_NEW_VALUE(file_id,p_id,cell_no,value_data);
	if(ret!=0){
		printf("\nWrite Error");
		return 1;
	}
	ret=COMMIT(file_id,p_id);
	if(ret==1){
		printf("\nCommit Error");
		return 1;
	}
	read_data=READ_CURRENT_VALUE(file_id,p_id,cell_no);
	if(read_data==NULL){
		printf("\nRead Error");
		return 1;
	}
	printf("\nP_ID:%d F_ID:%d VALUE:%s",p_id,file_id,read_data);

//Test Case #2		
//To check the effect of COMMIT
//Next here we are trying to create an action/process. 
//Allocate a block to a file in cell storage system. 
//Write some string to block. Block Size limited to 1024 bytes. Can only hold 100 blocks in temp 
//DON'T Commit the changes for a particular file(NO blocks will be written back to Cell Storage System)
//Read the value from the block, and display the old value from Cell Storage System.

	
	printf("\n-----------DON'T COMMIT--------------");
	p_id=NEW_ACTION(file_id);
	strcpy(value_data,"Second_Value");
	ret=WRITE_NEW_VALUE(file_id,p_id,cell_no,value_data);
	if(ret==1){
		printf("\nWrite Error");
		return 1;
	}
	read_data=READ_CURRENT_VALUE(file_id,p_id,cell_no);
	if(read_data==NULL){
		printf("\nRead Error");
		return 1;
	}
	
	printf("\nP_ID:%d F_ID:%d CURRENT_VALUE:%s Tried for:%s",p_id,file_id,read_data,value_data);

//Test Case #3	
//To check the effect of ABORT
//Next here we are trying to create an action/process. 
//Allocate a block to a file in cell storage system. 
//Write some string to block. Block Size limited to 1024 bytes. Can only hold 100 blocks in temp 
//Now ABORT before Commit the changes for a particular file(NO blocks will be written back to Cell Storage System)
//Read the value from the block, and display the old value from Cell Storage System.

	printf("\n-----------ABORT----------------");
	p_id=NEW_ACTION(file_id);
	strcpy(value_data,"New Value");
	ret=WRITE_NEW_VALUE(file_id,p_id,cell_no,value_data);
	if(ret==1){
		printf("\nWrite Error");
		return 1;
	}
	ret=ABORT(file_id,p_id);
	if(ret==1){
		printf("\nAbort Error");
		return 1;
	}
	read_data=READ_CURRENT_VALUE(file_id,p_id,cell_no);
	if(read_data==NULL){
		printf("\nRead Error");
		return 1;
	}
	
	printf("\nP_ID:%d F_ID:%d VALUE:%s Tried:%s",p_id,file_id,read_data,value_data);

//Cleanup of state and temp files
	cleanup();
	printf("\n");
	return 0;
}