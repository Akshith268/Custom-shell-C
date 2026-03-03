#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

void handle_sigint(int sig){
printf("\nCaught signal %d.Use 'exit' to quit.\n",sig);
}

void handle_sigchld(int sig){
while(waitpid(-1,NULL,WNOHANG)>0);
}

int main() {
    char input[100];
    char *args[10];
    
struct sigaction sa;
sa.sa_handler=&handle_sigchld;
sigemptyset(&sa.sa_mask);
sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
if(sigaction(SIGCHLD,&sa,NULL) == -1){
perror("sigaction");
exit(1);
}


   signal(SIGINT, handle_sigint);

    while (1) {
        printf("pro_shell> "); 
                
        // 1. READ: Get the command from the user
        if (fgets(input, 100, stdin) == NULL) break;
        
        // 2. CLEAN: Remove the '\n' that fgets adds when you hit Enter
        input[strcspn(input, "\n")] = 0;

        // 3. EXIT: If you type exit, stop the loop
        if (strcmp(input, "exit") == 0) break;
        int i=0;
args[i]=strtok(input," ");
 while(args[i]!=NULL && i<9){
i++;
args[i] =strtok(NULL," ");
}

args[i]=NULL;

if(args[0]==NULL) continue;

int background=0;
if(i>0&& strcmp(args[i-1], "&") ==0){
background=1;
args[i-1]=NULL;
}

int out_file =-1;

for(int j=0;args[j]!=NULL;j++){

if(strcmp(args[j],">")==0){
out_file = open(args[j+1], O_WRONLY| O_CREAT |O_TRUNC, 0644);
if(out_file<0) { perror("File error"); break;}
args[j]=NULL;
break;
}
}
        // 4. PROCESS: The Fork/Exec magic
        pid_t pid = fork(); // Create a clone

       // if (pid < 0) {
       //     perror("Fork failed");
       // } 
       // else if (pid == 0) {
            // This is the CHILD process
            // We put our command in an array for the OS to understand
          //  char *args[] = {input, NULL};
            
            // execvp looks for the command (like 'ls') and runs it
           // if (execvp(args[0], args) == -1) {
             //   printf("Command not found!\n");
           // }
           // exit(0); // Kill the child so it doesn't loop back to the top
       // } 
       // else {
         //     if(background){
           //     printf("[Background process started: PID %d]n",pid);
            // }
            // else{
            // This is the PARENT (the main shell)
        //    waitpid(pid,NULL,0); // Wait here until the child finishes printing
       // }
      // }

        if(pid==0){
if(out_file!=-1){
dup2(out_file, STDOUT_FILENO);
close(out_file);
}

if(execvp(args[0], args) == -1){
printf("command not found\n");
}
exit(0);
}
else{

if(out_file!=-1) close(out_file);
waitpid(pid, NULL,0);
}
   }
    return 0;
}
