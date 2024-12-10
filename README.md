# GET_NEXT_LINE ⏭️

## What it is ❓
   This project of the 42 curriculum was to write a function, that reads from a file descriptor and returns all the characters until the next newline character as a string.
   
## How it works ❗
  This functions recieves a file descriptor that it is supposed to read from. A buffersize is defined in the headerfile if not defined during compilation. 
  This function uses a static pointer to keep track of dynamically allocated memory for the buffer. It reads from fd BUFFER_SIZE characters until it finds a newline charqacter and joins it into one string.
  then it duplicates the part if it until the newline character and rearranges the buffer so that the first character after the newline is now the first in the buffer.
  It adds a newline to the duplicated string and returns that one. If there is no newline in the file it returns the string without one. If the file is empty or has been read fully or any error occurred, it returns NULL.

## Things that were interesting to me 🧙‍♂️
This was the first time i worked with filedescriptors actively which was a fairly new concept to me. Also it introduced me to static variables and their use in a program,
which was also quite interesting since i had learned about static functions already in the libft project.

Now that a some months have passed since i wrote this function and i have seen quite many other projects of my peers, i am everytime anew astounded how many different ways there are to solve this problem are, 
even with the constraints given by the subject.

Additionally it is incredible how useful such a function turned out to be. I used it in several other Project and every time it was a joy since i coded this fundamental fuction myself and could understand what happens in it.
