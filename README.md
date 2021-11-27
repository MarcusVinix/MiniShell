# MiniShell
My 8th project at the 42sp and the most huge one rsrs. This is the first project that i do with a partner, that was [Jhonatam estevam lima](https://github.com/jhonatan229), and was so cool training my teamwork skills with him.

# Introduction
The existence of shells is linked to the very existence of IT. At the time, all coders agreed
that communicating with a computer using aligned 1/0 switches was seriously
irritating. It was only logical that they came up with the idea to communicate with
a computer using interactive lines of commands in a language somewhat close
to english.
With Minishell, you’ll be able to travel through time and come back to problems
people faced when Windows didn’t exist.

# Builtins Implemented
| Command  | Description                                                     |
|:--------:|:---------------------------------------------------------------:|
| *echo*   | Print the string in standart output. Flag -n remove break line. |
| *cd*     | Change the current directory to the path passed.                |
| *pwd*    | Print the current directory in standart output.                 |
| *export* | Create or change an environment variable.                       |
| *unset*  | Remove an environment or local variable.                        |
| *env*    | Print all environment variable in standart output.              |
| *exit*   | Close the shell with the exit status specified.                 |

## Signals
| Signal    | Description                                           |
|:---------:|:-----------------------------------------------------:|
| *CTRL-C*  | Print a new prompt on a newline.                      |
| *CTRL-D*  | Exit the shell when the command line is empty.        |
| *CTRL-\\* | Quit a process in execution with `quit (core dumped)` |

## Redirections
| Side | description                                                    |
|:----:|:--------------------------------------------------------------:|
| *<*  | Redirect input.                                                |
| *>*  | Redirect output.                                               |
| *<<* | Read input until a line containing only the delimiter is seen. |
| *>>* | Redirect output with append mode.                              |


## MindMap(Flux)

My partner [Jhonatam estevam lima](https://github.com/jhonatan229) make a flux in the miro to this project, [click here](https://miro.com/app/board/o9J_lghFXQU=/?invite_link_id=874120899640) if you fell interesting.

# How use
> Clone the repository  
>  
> Install `libreadline` with `make install`  
>  
> Compile the shell with `make`  
>  
> Execute the project `./minishell`  
> 
> Have fun!  
