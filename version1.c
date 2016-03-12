// Created by Itar Mehak 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

int main (int argc, char *argv[])
{

int i, y, pid, status, n, result, result2, result3;
pid_t ppid;
write(1, "\nEnter exit/EXIT at any time to exit the shell\n", 46);
ppid = getpid();

while(1)
	{
			
		char buffer[255];
		write(1, "\nmyBash-1.0:$\n" , 13);
		int i = 0;

		memset(buffer, 0, sizeof(buffer));  
 
		read(0, buffer, 100); 		 // Reading the command line argument 
		
		int count = strlen(buffer);
				if(count == 1)
				{
				write(1, "myBash-1.0:$ Error: No command entered. Try again.\n", 51); 
				continue;
	            }

					
char *token;
char *keywords[255];

memset(keywords, 0, sizeof(keywords));    

token = strtok(buffer, " \n");   // Extracting the command line arguments for manipulation 

int y =0;
while(token != NULL)
   {
        keywords[y] = token;           // Storing the tokens separately in form of strings
        y++;
        token = strtok(NULL, " \n");
      
    }


result2 = strcmp(keywords[0], "exit");     // Checking for the Exit or exit command
result3 = strcmp(keywords[0], "EXIT");

     if(result2 == 0 || result3 == 0)
     {
     printf("\nTerminating...\n");
     sleep(1);
      printf("\nGoodbye!\n");
     kill(ppid,SIGINT);
     }
  

pid = fork();    

if(pid == 0)                             // Child Process
{
     
    if(keywords[1] == NULL)           // In case of one word commands
    {
       keywords[1] = 0;   // Setting second argument as zero for execvp 
       if(execvp(keywords[0], keywords) == -1)
        {
        printf("myBash: %s : Command not found\n", keywords[0]);
       
        }

        exit(1);
    }
  
 
   else if(execvp(keywords[0], keywords) == -1)
    {
       printf("myBash: %s : Command not found\n", keywords[0]);
      
    }
   
    exit(2);
   
}

else if (pid > 0)
{
 						// Parent Process  
wait(&status);

}

else					// Unable to fork
{
    
	perror("myBash: Issue with fork ");
}
	
	}    // while closed

} // main closed


