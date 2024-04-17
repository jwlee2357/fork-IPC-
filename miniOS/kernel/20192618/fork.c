#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<wait.h>
int main() {
pid_t pid;/*forkachildprocess*/
pid = fork();//pid(p)>0:pid ofchildprocess;pid(c):0
if (pid < 0) {/*erroroccurred.Childstartshere */
fprintf(stderr,"ForkFailed");
return 1;}
else if (pid ==0) {/*childprocess*/
execlp("/bin/ls","ls",NULL);//child ≠ parentnow
}
else {/*parentprocess*/
/*parentwillwaitforthechildtocomplete*/
wait(NULL);//transittowaitstate
printf("ChildComplete\n");
}
return 0;
}


