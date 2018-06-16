INTRO: This version of the Tiff Management Application (TiMA) is crude. The purpose was to obtain functionality.
        The code works and has a simple user interface. Moreover, it gets the job done. 
		
		There are essentially four operations TiMA can perform. Their name and description are as follows:
		
		remove blanks [filename]: Takes a multipage tif file and removes any blank pages
		remove page(s) [filename][numberofpages][pagenumbers]: Removes any page that a user specifies from a multipage tif file
		merge [numberofpages][file1...fileN]: merges any number of tif files provided more than one tif file is given
		help: displays text to terminal showing how to use the application

REQUIREMENTS:
		To use this application, make sure you have libtiff installed on your computer. This application was written
		for a linux operating system so at the very least you should have a virtual machine running the latest version
		of Ubuntu. Also, the application is written in C and compiled via the latest GNU gcc compiler. So that should be 
		installed on your machine as well
		
DESCRIPTION: To use this version of the application is straightforward. Just type the name of the executables
			 and provide appropriate arguments. When working with any tif file, just ensure that they are 
			 located within the same directory as the TiMA executable. Below describes in detail how to use
			 each operation as well as some of the logic
				
	1-REM_BLNKS:
		
			This operation works by reading in a tif file provided by the user. It iterates through the
			the multipage tif file and determines which files are blank. 
			
			"Blankness" is assumed to be a page that is monochromatic in nature. To exploit this characteristic,
			we map each RGB value to its luminance. Once we have the luminance, the standard deviation of
			the file's luminance is calculated. If it falls at or  below a certain threshold, then the page
			is assumed to be blank. The idea is that the luminance of a blank tiff file doesn't change much
			from pixel to pixel and would thus have a low standard deviation value.
			
			If blank files are detected it 
			records the corresponding page numbers in a text file called "blank.txt". It stores the 
			remaining page numbers in a text file called "remain.txt". If blanks are detected, the file is
			split into separate tif files. The split files are individually deleted according to what's
			stored in blank.txt. Once the blanks are deleted, the remaining files are merged back together.
			Lastly, the program cleans up by deleting the lingering tif files as well as the text files.
			
	2-REM_PAGE:
		
			This program works by reading in a tif file as well as numerical arguments provided by the user
			specifying which programs to be deleted. A text file called "remain.txt" is generated to store
			the pages that are not to be deleted. Once the program determines what's not to be deleted,
			it splits the file into individual tif files and deletes necessary files. The remaining files
			are merged back together.Lastly, the program cleans up by deleting the lingering tif files as 
			well as the text files.
			
	3-MERGE:
		
			This program is self-explanatory. It takes the arguments provided by the user (provided the files exist) 
			and runs the tiffcp command. It uses the lzw compression method to produce the resulting merged tiff file.
		
   *4-LIST TIFF FILES:
		
			If you can't remember the names of the files you want to perform operations on, you can list them
			out to the terminal
		
		
NOTE: Some tif files have been added into the folder to use as an example. However, the user is free to add
	  any other tiff files to the folder. The tiff files are stored in a folder called tiff_folder for
	  organization purposes. However, if there is a file you would like to alter, move that file into the TiMA
	  directory.
	  
	  The source code has been included. If something goes wrong or you feel the need to make edits to existing
	  code, navigate to the TiMA directory and run the following command in the terminal to compile the editted code 
	  and produce the executable:
	  
	  gcc -Wall TiMA.c tiff_op.c -ltiff -lm -o tima
	  
	  To run the code simply type
	  
	  ./tima
	  
	  No command line arguments are necessary to supply to the code for execution.
	  
EXAMPLE: To demonstrate the functionality of the application, try 
			1. Removing the blanks from ex_blank.tif
			2. Removing pages from ex1.tif and ex2.tif
			3. Merging all the colored tiff files into a single file
		

		
		