MIPS Binary Instruction File Generator
===================================

This command-line applet allows you to create the binaries needed to test your MIPS Simulator. As of now all the commands listed in the specifications have been implemented into this application.

Instructions
----------------

If you are using a UNIX bases system (i.e. Linux or MacOS) you can simply cd into the directory of .cpp file and use the "make parser" command to build and then "bin/parser" to run it. Windows systems are a bit more tricky, but if you have installed g++ onto your computer you may also have the "make" command already available.  

The application will convert assembly code into machine binary, pretty much synonmous with coding in VisUAL, except you're using MIPS instead of ARM. In case of an error, i.e. entering the wrong number of operands for a given instruction, the program will tell you the instruction at fault.   

You have the choice of using a text file or console input line by line. If you wish to use a file, please pass it in as an initial argument. In this case the generated binary will have the same name as the input .txt file (obviously with .bin instead of .txt). If you want to chose the output file name, you can pass it as the second intial argument. If "prefix" is passed as a 3rd argument, the 2nd argument will be a prefix to the default file name.  

If using the console, exit input by using the command "exit". You will then be able to name the .bin file.

![Parser Demo](parser_demo.gif)

Comments don't work and will return an error (pls don't use them).  

Example input:
--------------  

lw     $t0, 4($gp)        
mult   $t0, $t0  
lw     $t1, 4($gp)       
ori    $t2, $zero, 3      
mult   $t1, $t1      
add    $t2, $t0, $t1  
sh     $t2, 0($gp)  
jr     $zero  

This will generate the binary shown below:  

8F880004   
01080018   
8F890004   
340A0003   
01290018   
01095020   
A78A0000   
00000008  

(It is left as an exercise to prove that this is the correct binary)  

Footnote
--------

"nop" is a valid command in this parser and may be used after a jump or branch to implement a branch delay.  
Sorry if there are any bugs, raise an issue or just come tell us thx.
