#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
char command[100];
printf("Enter Linux command: ");
fgets(command, sizeof(command), stdin);
pid_t pid = fork();
if (pid < 0){
printf("Fork failed\n");
return 1;
}
if (pid == 0){
printf("Child PID: %d\n", getpid());
execl("/bin/sh", "sh", "-c", command, NULL);
printf("Command execution failed\n");
}
else{
printf("Parent PID: %d\n", getpid());
wait(NULL);
printf("Child process completed\n");
}
return 0;
}
