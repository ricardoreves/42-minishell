# 42 Minishell

## Preview
![](imgs/minishell.png)


## References
- [paysdu42](http://i.paysdu42.fr/?page=minishell.c) le principe du minishell1
= [n-pn](https://n-pn.fr/t/2318-c--programmation-systeme-execve-fork-et-pipe) programmation-systeme-execve-fork-et-pipe

https://www.rozmichelle.com/pipes-forks-dups/comment-page-1/
https://putaindecode.io/articles/maitriser-les-redirections-shell/
https://www.baeldung.com/linux/error-too-many-open-files

https://harm-smits.github.io/42docs/projects/minishell
https://percona.community/blog/2021/01/04/fork-exec-wait-and-exit/
https://linuxhint.com/using_pipe_function_c_language/
https://linuxhint.com/linux-pipe-command-examples/
https://github.com/Swoorup/mysh
https://www.youtube.com/watch?v=l-UhKLdh4aY
https://stackoverflow.com/questions/50610781/implementing-pipe-and-redirection-together-in-c
https://thoughtbot.com/blog/input-output-redirection-in-the-shell
https://www.guru99.com/linux-redirection.html
https://linuxhint.com/c-execve-function-usage/
http://brunogarcia.chez.com/Unix/Docs/Signaux.html


https://www.thegeekstuff.com/2010/10/linux-error-codes/
https://en.wikipedia.org/wiki/ASCII#ASCII_control_characters
https://github.com/iciamyplant/Minishell
https://github.com/j53rran0/minishell


https://github.com/AbderrSfa/minishell/blob/main/minishell.c

https://patorjk.com/software/taag/#p=testall&f=Graffiti&t=Minishell
https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a


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

echo " | 42 | " | cat -e | grep '42'
echo "$(cat data.txt)"
" ' | < >
cat < output.txt

cat <<EOF hello hello EOF
cat <<<'hello world'

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

https://tldp.org/LDP/abs/html/here-docs.html
cat <<-ENDOFMESSAGE
	This is line 1 of the message.
	This is line 2 of the message.
	This is line 3 of the message.
	This is line 4 of the message.
	This is the last line of the message.
ENDOFMESSAGE


cat << EOF > /tmp/yourfilehere
These contents will be written to the file.
        This line is indented.
EOF



## Tools
https://www.diagrameditor.com/