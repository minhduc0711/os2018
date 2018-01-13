#include <stdio.h>
#include <unistd.h>

int main(){
	int pid1 = fork();
	if (pid1 == 0){
		int pid2 = fork();	
		if (pid2 == 0){
			char *args[] = { "free", "-h" , NULL};
			execvp("free", args);
		} else{
			char *args[]= { "/bin/ps", "-ef" , NULL};
			execvp("/bin/ps", args);
		}
	}
	return 0;
}