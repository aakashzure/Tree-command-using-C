						Tree command implementation in linux using C
						
Aakash V. Zure
MIS : 141603015
**********************************************************************************************************************************************

This project is to impement the tree command using C language. This command displays the contents of a directory recursively in hierarchical 
format. The command does work with combination with each other too. There are 5 options developed till now. The options are as follows:

	Options:
	1)no option - 	in this mode the command displays the directories and the files
			in the manner such that the directories are shown at an indented
			distance of |----- and the files in that directory are shown 
			below the directory.		
		Usage 	: ./project 
			
	2) -d -		This option displays only the directories inside the given directory path.
		Usage	 : ./project pathname -d
		
	3) -f -		This option prints the directories and files in hierarchical order. but instead of just printing the name of 
			the directory or file, it prints the complete path of the file or folder.  
		Usage 	: ./project pathname -f      
  	
	4) -l -         Follow symbolic links like directories.           		
		Usage 	: ./project pathanme -l

	5) -i -         This option displays the files and folders name without any indentation. i.e. not in hierarchical structure.
			this command is more effective when used in combination with -f option 
		Usage	: ./project pathanme -i

	6) -h -		Displays help.
		Usage 	:/project -h

	COLOR Codes:
	1) Directories are displayed in BLUE color.
	2) the graphic files like jpg, png, tif, bmp, mp4, avi, mkv, flv etc are displayed in MAGNETA color.
	3) The archives and compressed file types are displayed with RED color.
	4) The text based documents files like pdf, ppt, doc, docx and executables are displayed in GREEn color.
