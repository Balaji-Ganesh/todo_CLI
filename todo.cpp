// Example program
#include <iostream>			// for all I/O related operations..
#include <string>			// to use string
#include <cstring>			// to perform C-string related opreations. Used strcmp()
#include <fstream>			// for file-related operations..
#include <ctime>			// to get the current system date..
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

/*  ----------------------Global Declarations..--------------------*/
// //// Function declarations(prototyping) ////
// main_task functions..
void show_help();
void add_item(const char *item_name);
void list_todo_items();
void delete_todo_item(char*item_number, bool suppress_output=false);
void item_done(const char* item_number);
void show_report();
// Helping functions to the main_task functions..
int items_count_in_file(const char * file_name);
//void transfer_file_data(const char *src_file_name, int src_open_flag, const char*dst_file_name, int dst_open_flag);
// Variable Declarations..
const char *todo_file_name = "../plans/todo.txt";
const char *done_file_name = "../plans/done.txt";
const char *temp_file_name = "temp.txt";
/*-----------------------------------------------------------------*/

/* ---------------------------------------------------- main() ---------------------------------------------- */
int main(int argc, char **argv){
	mkdir("../plans");
	/// Check whether the directories are present of not..
	//if(mkdir("../plans") == -1)			// Creates the "plans" directory if not present, else simply skips..
	//	cerr << "Error: " << strerror(errno) << endl;
	//else
	//	cout << "Directory created";
  // Here let's parse the arguments passed..
  // argv[0] will be the file name..
  // lets parse the argv[1] -- it contains the command what the todo would like do..
    if (strcmp(argv[1], "help") == 0)
    	show_help();    
    
	else if(strcmp(argv[1], "add") == 0)
        add_item(argv[2]);
        
    else if(strcmp(argv[1], "ls") == 0)
        list_todo_items();
        
    else if(strcmp(argv[1], "del") == 0) 
        delete_todo_item(argv[2]); // Here argv[2] will contain the NUMBER
        
    else if(strcmp(argv[1], "done") == 0)
        item_done(argv[2]);
        
    else if(strcmp(argv[1], "report") == 0)
        show_report();
    else
    	cout << "ERROR: Recieved invalid argument, please refer to the \"help\" and try again." << endl;
    return 0;
}
/* ----------------------------------------------- End of main() ----------------------------------------------*/

/* ------------------------------------Definition of the declared functions.. --------------------------------*/
// main_task functions..
void show_help(){
	cout << "Usage :- " << endl;
	cout << "todo add \"todo item\"\t# Add a new todo" << endl
		 <<"todo ls \t\t# Show remaining todos" << endl
		 << "todo del NUMBER\t\t# Delete a todo" << endl
		 << "todo done NUMBER\t# Complete a todo" << endl
		 << "todo help \t\t# Show usage" << endl
		 << "todo report \t\t# Statistics" << endl;
}

void add_item(const char *item_name)
{
    //cout << "In add_item";
    // Here we need to add the list_item to the file..   
    fstream todo_file;//(todo_file_name, ios::in | ios::app);			// Opening in appending mode, to preserve the contents of the file when called this function each time.. creates a new one if doesn't exist
    fstream temp_file;//(temp_file_name, ios::in | ios::out);		// Opening in read and write mode -- as -- to create a new file if not exists already -- and -- for purpose of writing in the stage_1, then later reading from it. Finally deleting this..
    string data;
    //fstream done_file = fopen("done.txt");

	// Write the contents of todo.txt to another file..
	todo_file.open(todo_file_name, ios::in);					// Opening in read mode, so as to transfer(read) the contents to another temp file...
	temp_file.open(temp_file_name, ios::out);					// Create the temp-file, if not exists... and also delete the file contents...	
	while(getline(todo_file, data))
		temp_file << data << endl;
	todo_file.close();
	temp_file.close();

    // Now we need to write into the file..
    todo_file.open(todo_file_name, ios::out);					// Opening in write mode, so as to delete all the contents present in it and keep ready for writing..
    temp_file.open(temp_file_name, ios::in);
    todo_file << item_name << endl;								// Write the new todo_item to the original_file (Which is now currently empty)
    // Add the remaining contents of the original file back..
    while(getline(temp_file, data))
    	todo_file << data << endl;
	
    // Display acknowledgement to the user..
    cout << "Added todo: \"" << item_name << "\"" << endl;
    
    // Close the file handles and remove temporary files created..
    todo_file.close();
    temp_file.close();
    remove(temp_file_name);
}

void list_todo_items(){
	ifstream todo_file (todo_file_name);		// Open the file in read mode... as we just need to display the contents of  the file
	int items_count=-1;
	string data="";
	
	// Get how many items in the file..
	items_count = items_count_in_file(todo_file_name);
	// Read the data from the file line by line..
	if (items_count != 0)						// If the list is not empty..
		while(getline(todo_file, data))
			cout << "[" << items_count-- << "] " << data << endl;
	else
		cout << "Todo list is empty, use \"add\" to create new tasks." << endl;
}

void delete_todo_item(char* item_number, bool suppress_output)
{
	ifstream todo_file(todo_file_name);			// Opening in read mode, so as to read the file contents and write in another file, then delete that and rename to origina file.
	ofstream temp_file(temp_file_name); 		// Opening in write mode, so as to write the contents which are read..
	string data="";
	int line_count=0, line_num=-1, item_num=atoi(item_number);

	if(item_num<=items_count_in_file(todo_file_name) && item_num>0)	// Check fo the valid item_number selected..
	{
		// Find the actual LINE-no. in the file to be deleted based on the item-no. selected.
		line_num = items_count_in_file(todo_file_name) + 1 - item_num;	// Just try it manually to understand the logic behind this expression..
	
		// Now delete the target line..
		while(getline(todo_file, data))
			if(++line_count != line_num)			// Write all the lines of the todo file to a temp file, EXCEPT the line which we would like to remove..
				temp_file << data << endl;
	
		// Close the file-handles..
		todo_file.close();
		temp_file.close();
		
		// Perform the actions as planned earlier.. i.e., Delete the original file (todo.txt) and rename the temp_file (temp.txt) to the original filename..
		remove(todo_file_name);					// Delete the original file..
		rename(temp_file_name, todo_file_name);	// Rename the name of temp file to the original file name..
			
		// Display acknowledgement to the user..
		if(!suppress_output)
			cout << "Deleted todo #"<< item_num << endl;
	}
	else	// In case of Invalid item_count..
		cout << "Error: todo #"<< item_num	<< " does not exist. Nothing deleted";
}


void item_done(const char *line_number)
{
	ifstream todo_file(todo_file_name);
	fstream done_file(done_file_name, ios::app);
	int done_item = atoi(line_number);				// Convert the item to be deleted from todo..
	int done_line_num = items_count_in_file(todo_file_name) +1 - done_item;	// Get the line no, where the done_item is present.. so that we can get that and add it to the done.txt
	string data="";
	int line_count=0;


	if (done_line_num>0)	//  If selected a valid item-no, it will be >0, else it will be <0. If not clear, please try out manually, becomes clear..
	{
		// Get the system date...
		time_t current_time = time(0);
		tm *local_time =localtime(&current_time);
		
		// Move to that line, and copy it to the done.txt file..
		while(getline(todo_file, data))	
			if(++line_count == done_line_num)					// ONLY that specific line, which is done, being written to the done.txt
				done_file <<"x " << 1900+local_time->tm_year << "-" << 1+local_time->tm_mon << "-" << local_time->tm_mday << " "<< data << endl;	// This format is as per the format given in the Readme.md

		// Close the file handles..
		todo_file.close();
		done_file.close();
		
		delete_todo_item(const_cast<char*>(line_number), true);

		
		// Give the acknowledgement to the user...
		cout << "Marked todo #" << done_item <<" as done." << endl;
	}
	else	// If selected a invalid item-no...
		cout << "Error todo #" << done_item << " does not exist.";
}

void show_report()
{
	time_t curr_time = time(0);
	tm *local_time = localtime(&curr_time);
	int pending_count = items_count_in_file(todo_file_name);
	int completed_count = items_count_in_file(done_file_name);
	
	cout << 1900+local_time->tm_year << "-" << 1+local_time->tm_mon << "-" <<local_time->tm_mday << " Pending : " << pending_count << " Completed : " << completed_count << endl;
}

/// Helping functions ///
int items_count_in_file(const char *file_name)
{
	ifstream todo_file(file_name);			// Opening in read mode, so as to count by reading each line of the file..
	int line_count=0;
	string data="";
	
	// Read the data from the file line by line.. and increment the count after each line read...
	while(getline(todo_file, data))
		line_count++;
	// Return the line_count..
	return line_count;
}


/* -----------------------------------End of Definitions of declared functions ----------------------------------*/
/*
void list_items()
{
    //fstream todo_file = fopen("todo.txt
    // pass..
}

void transfer_file_data(const char*src_file_name, int src_open_flag, const char*dst_file_name, int dst_open_flag)
{
	fstream src_file(src_file_name, (std::ios::ios_base::openmode)src_open_flag);
	fstream dst_file(dst_file_name, (std::ios::ios_base::openmode)dst_open_flag);
	string data;
	
	// Start transferring data..
	while(getline(src_file, data))
		dst_file << data << endl;
		
	// Close the opened file-handles to the process..
	src_file.close();
	dst_file.close();
}
*/

/*
$ ./todo help
Usage :-
$ ./todo add "todo item"  # Add a new todo  -- done with schematic
$ ./todo ls               # Show remaining todos -- currently running
$ ./todo del NUMBER       # Delete a todo
$ ./todo done NUMBER      # Complete a todo
$ ./todo help             # Show usage
$ ./todo report           # Statistics



*/


/*
	References:
		for date-and-time: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm

*/
