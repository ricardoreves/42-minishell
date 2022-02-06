# 42 Minishell

## Preview
![](imgs/minishell.png)

- [readline](https://man7.org/linux/man-pages/man3/readline.3.html)
- [rl_clear_history]() Clear the history list by deleting all of the entries, in the same manner as the History library's clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list. 
- [rl_on_new_line]() Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline. 
- [rl_replace_line]() Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared. 
- [rl_redisplay]() If non-zero, Readline will call indirectly through this pointer to update the display with the current contents of the editing buffer. By default, it is set to rl_redisplay, the default Readline redisplay function (see section 2.4.6 Redisplay). 
- [add_history]()
- [printf]() 
- [malloc]() 
- [free]() 
- [write](https://man7.org/linux/man-pages/man2/write.2.html) 
- [access](https://man7.org/linux/man-pages/man2/access.2.html) 
- [fork](https://man7.org/linux/man-pages/man2/fork.2.html) 
- [open](https://man7.org/linux/man-pages/man2/open.2.html) 
- [read](https://man7.org/linux/man-pages/man2/read.2.html) 
- [close](https://man7.org/linux/man-pages/man2/close.2.html) 
- [wait](https://man7.org/linux/man-pages/man2/wait.2.html) 
- [waitpid]()  
- [wait3]()  
- [wait4]() 
- [signal]() 
- [sigaction]()  
- [kill]()  
- [exit]()  
- [getcwd]()  
- [chdir]()  
- [stat]() 
- [lstat]()  
- [fstat]()  
- [unlink](https://man7.org/linux/man-pages/man2/unlink.2.html)  
- [execve](https://man7.org/linux/man-pages/man2/execve.2.html)  
- [dup]()  
- [dup2]()  
- [pipe](https://man7.org/linux/man-pages/man7/pipe.7.html) 
- [opendir]()  
- [readdir]()  
- [closedir]()  
- [strerror]()  
- [perror](https://www.tutorialspoint.com/c_standard_library/c_function_perror.htm) 
- [isatty]()  
- [ttyname]()  
- [ttyslot]()  
- [ioctl]()  
- [getenv]()  
- [tcsetattr]() 
- [tcgetattr]()  
- [tgetent]()  
- [tgetflag]()  
- [tgetnum]()  
- [tgetstr]() 
- [tgoto]()  
- [tputs]() 

## References
- [paysdu42](http://i.paysdu42.fr/?page=minishell.c) le principe du minishell1


https://harm-smits.github.io/42docs/projects/minishell
https://percona.community/blog/2021/01/04/fork-exec-wait-and-exit/
https://linuxhint.com/using_pipe_function_c_language/
https://github.com/Swoorup/mysh
https://www.youtube.com/watch?v=l-UhKLdh4aY
https://stackoverflow.com/questions/50610781/implementing-pipe-and-redirection-together-in-c
https://thoughtbot.com/blog/input-output-redirection-in-the-shell
https://www.guru99.com/linux-redirection.html
https://linuxhint.com/c-execve-function-usage/
http://brunogarcia.chez.com/Unix/Docs/Signaux.html



https://en.wikipedia.org/wiki/ASCII#ASCII_control_characters
https://github.com/iciamyplant/Minishell
https://github.com/j53rran0/minishell


https://github.com/AbderrSfa/minishell/blob/main/minishell.c

https://patorjk.com/software/taag/#p=testall&f=Graffiti&t=Minishell
https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a


#include<stdio.h>
#include<unistd.h>
int main()
{
  char cwd[256];

  if (chdir("Your desired path") != 0)
    perror("chdir() error()");
  else {
    if (getcwd(cwd, sizeof(cwd)) == NULL)
      perror("getcwd() error");
    else
      printf("current working directory is: %s\n", cwd);
  }  
}


#include <unistd.h>
int main (void) {
    char * const argv[] = {"/bin/ls", NULL};
    char * const envp[] = {NULL};
    int rc = execve ("/bin/ls", argv, envp);
    return rc;
}

#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
  
extern int errno;
  
int main(int argc, const char *argv[]){
    int fd = access("sample.txt", F_OK);
    if(fd == -1){
            printf("Error Number : %d\n", errno);
        perror("Error Description:");
    }
        else
                printf("No error\n");
    return 0;
}




cd kklklk | grep hh


Your shell must implement the following builtins:
◦echo with option -n
◦cd with only a relative or absolute path
◦pwd with no options
◦export with no options
◦unset with no options
◦env with no options or arguments
◦exit with no options
The readline() function can cause memory leaks. You don’t have to fix them. But
that doesn’t mean your own code, yes the code you wrote, can have memory
leaks.
You should limit yourself to the subject description. Anything that
is not asked is not required.
If you have any doubt about a requirement, take bash as a reference.
6


bash: cd: fff: No such file or directory


echo " | 42 | " | cat -e | grep '42'

echo "$(cat data.txt)"


" ' | < >
bash: export: `42': not a valid identifier



implements redirections 

int main(int argc,char *argv[]) {
        int fd[2];
        pid_t cpid;
        close(1); /* so that output file should get file descriptor 1 */
        int file_dsptr = open(argv[3],O_CREAT|O_TRUNC |O_WRONLY , 0664); /* file should be exist in current directory, otherwise use O_CREAT | O_TRUNC */
        printf("[%d]\n",file_dsptr);

        if(argc == 4){
                if(pipe(fd) == -1){
                        perror("error in pipe creation");
                        exit(EXIT_FAILURE);
                }
                cpid = fork();
                if( cpid == 0 ){ /*child process */
                        close( fd[0] ); /* close read end of pipe */
                        if( -1 == dup2(fd[1] , file_dsptr)){ /* duplicate fd[1] to fd where data.txt points */
                                exit( EXIT_FAILURE );
                        }
                        if(-1 == execlp(argv[1] , argv[1] , NULL )){ /* executes the commands */
                                exit( EXIT_FAILURE );
                        }
                        close( fd[1] );
                        _exit( EXIT_SUCCESS );
                }
                else if(cpid > 0){
                        wait( NULL ); /* wait for child to completes */
                        close( fd[1] ); /* close write end of pipe */
                        if( -1 == dup2(fd[0] , STDIN_FILENO)) {
                                exit( EXIT_FAILURE );
                        }
                        if(-1 == execlp(argv[2] , argv[2], NULL )) {
                                exit( EXIT_FAILURE );
                        }
                        close( fd[0] );
                        _exit( EXIT_SUCCESS );
                }
                else{
                        fprintf(stderr, "fork failed\n");
                        exit(EXIT_FAILURE);
                }
        }
        else{
                fprintf(stderr, "Usage Msg :. ./a.out ls wc data.txt \n");
                exit(EXIT_FAILURE);
        }
        return 0;
}


int
main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char buf;

    assert(argc == 2);

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {    /* Le fils lit dans le tube */
        close(pipefd[1]);  /* Ferme l'extrémité d'écriture inutilisée */

        while (read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);

        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);

    } else {                    /* Le père écrit argv[1] dans le tube */
        close(pipefd[0]);       /* Ferme l'extrémité de lecture inutilisée */
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);       /* Le lecteur verra EOF */
        wait(NULL);             /* Attente du fils */
        exit(EXIT_SUCCESS);
    }
}

 

 void intHandler(int) {
    keepRunning = false;
}

int main(int argc, char *argv[]) {
    struct sigaction act;
    act.sa_handler = intHandler;
    sigaction(SIGINT, &act, NULL);

    while (keepRunning) {
        // main loop
    }
}



Ctrl+C - SIGINT
Ctrl+\ - SIGQUIT



int check_access(char *pathname)
{
    int fd = access(pathname, F_OK);
    if (fd == -1)
    {
        //perror("No such file or directory");
        printf("%s: %s: %s: %s\n", PROMPT_PREFIX, "cmd", pathname, strerror(errno));
        return (1);
    }
    return 0;
}