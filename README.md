# Checksum-Calculator

**Overview**

This project implements a command-line program to calculate the checksum of a given text file using 8-bit, 16-bit, or 32-bit checksum sizes. The program reads the input file, processes its content, and prints both the formatted input text and the calculated checksum to the terminal.  

**Features**

* Supports three checksum sizes: 8-bit, 16-bit, and 32-bit.  
* Reads an input text file and displays its content in rows of exactly 80 characters per line.  
* Pads the input with 'X' characters if necessary to align with the selected checksum size.  
* Outputs the calculated checksum along with the total number of characters processed.  
* Displays an error message if an invalid checksum size is provided.  

**Input File Format**

* The input file can contain any standard ASCII characters including punctuation, numbers, special characters, and whitespace.  
* The LF (Line Feed, 0A in hex) character is included in checksum calculations.  

**Output Format**

1. The input file content is echoed to the terminal, formatted into lines of 80 characters per row.  
2. If necessary, the file content is padded with 'X' characters to align with the chosen checksum size.  
3. The calculated checksum is displayed using the following format: <checksum_size> bit checksum is <checksum_value> for all <char_count> chars  

* <checksum_size>: The selected checksum size (8, 16, or 32 bits).  
* <checksum_value>: The computed checksum value in hexadecimal.  
* <char_count>: The total number of characters processed, including padding.  

**Implementation Details**

* The checksum is computed by summing blocks of 1, 2, or 4 bytes (depending on the chosen size) and then masking the result to ensure only the relevant bits are used.
* The final checksum is printed in hexadecimal format with proper zero-padding.

**How to Run**

1. Compile the program with: gcc -o pa02 pa02.c
2. Execute the program with: ./pa02 <Test Case>.txt <Checksum Size>
