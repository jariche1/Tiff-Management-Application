||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

This is a small guide to help with using the application.

The application is simple and straightforward to use. It's design is relatively intuitive. After 
running the tima executable, a user interface will display listing different operations to
be performed on any tiff file(s). Simply entering one of the numbers will launch a tiff 
operation. Steps will be provided, guiding the user to accomplishing a task.

1. REMOVE BLANKS FROM TIFF
	~ If you enter one, you will be prompted to type the name of a tiff file. Enter the name
	  the correct name of the tiff file. If you don't enter the correct name of the tiff file, the 
	  program will generate a TIFFOpen error followed by the program terminating.
	  
	~ If the correct name is entered the program will take over and do it's work. It will try to detect
	  blank pages in a multipage tiff. If blanks are found, they will be deleted. If not, the program 
	  will generate a message saying no blanks were found. After running through the program, the 
	  interface will reappear ready to perform another operation
	  
	  NOTE: If the tiff file is a single page tiff, the program will determine if it is blank. But it
	  		will terminate afterwards. It only deals with MULTIPAGE tiffs.

2. REMOVE PAGES FROM TIFF
	~ If you enter two, you will be prompted to enter the file name. Enter a correct name and press enter. Next, 
	  you will be prompted to specify how many pages you would like to delete. Do so and press enter. Next, you
	  will be prompted to type the pages of the multipage tiff that you want to delete. Type each number in with a 
	  space in between and press enter. Make sure the amount of numbers you enter corresponds with the number
	  of pages you want to remove. After completing these steps, the application will take over and do its work.
	 
	~ If you enter a number that is larger than the number of pages in your tiff file, the program will terminate
	  and not execute any operations. It will only delete pages if you specify pages that exist.

3. MERGE MULTIPLE TIFFS
	~ If you enter three, you will be prompted to enter the number of tiff files you would like to merge.
	  Enter a digit and press enter. You will then be prompted to enter the names of the files you would like
	  to merge. Type the name of a file then press enter. Type the name of another file and press enter.
	  Keep doing so until you reach the desired number of files to merge. Lastly, you will be prompted to
	  specify the name of the file you would like for it to merge to. Type a name and press enter. The program
	  will take over and perform its task.
	  
	~ If you enter an incorrect name when specifying files to merge, the program will still run. It will gloss
	  over the incorrect name you typed.
	  
4. List Tiff Files
	~ If you enter four, the tiff files in the TiMA directory will be displayed to the screen

|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
