Mehmet Çağatay Barın - mbarin

In kufs.c, commands are parsed using parseCommand command from Project 1 and 
appropriate functions are called. exit, ls, stats, 
and rd doesn't have any arguments while md, cd, display, create, and rm have file or directory names.

In kufs.h, functions display, create, and rm are defined.

The function display takes fname as input and checks if a file with the name fname is in the current directory. 
To do this, each possible three blocks of the current directory are checked (first for loop). 
For each block, there are four possible directory entries (second for loop). 
In this inside for loop, fname and the data type (file or directory) is checked and 
the data of the file from the related block is displayed.

The function create takes fname as input, and checks if fname (must be non-empty) 
already exists in the directory (this is also checked, it the current inode entry doesn't start with DI, 
then exit() is called), and if there is no available space for a new file. If so, an error message is showed. 
Then, user puts input with maximum size of 3072 characters since each file can take 3 blocks 
(with the size of 1024 bytes).

For the part 3 (rm), possible three blocks for the current inode entry are checked just like in display function. 
The difference is in deleting file and directory. Possible three blocks of the current inode entry is checked. 
For each block, the possible four directory entries are checked if their name is what we're looking for, 
and if that entry is used. If it's used, we increment the counter of used entries for the current block so that 
we can decide whether we can return that block or not (if the file that we're looking for is the only one in that block, 
we can return that block). If the file is found, the directory entry's set in not used (F='0'), 
and the blocks (XX, or YY, or ZZ) that carry information of this file is set to '00' which means not used. 
Then, related blocks are updated according to the changes explained above.

If what we're looking for is a directory, we called removeDirectory recursively. 
removeDirectory does pretty much the same thing as rm but, of course, by deleting every single file in the directory 
without checking the name of the file.

You can compile with "gcc -lm -o kufs kufs.c",
and run with "./kufs".
(without -lm , pow function in the header file gives error. That's what we found as a solution from stackoverflow.com)
Also you can find the screenshots of our run in the zip file since there is no demo for this project. 
I tested every functionality of this project and all of them works perfectly.
Since we do the write operations immediately, 
seperate instances of the KUFS works simultaneously without any problem which we tested different operations to see this.
