# Funções parte 2

**lstat/fstat**  
 
 ```c
 #include <unistd.h>
 int stat(const char *path, struct stat *buff);  
 int lstat(const char *pathname, struct stat *statbuf);
 int fstat(int fd, struct stat *statbuf);
 ```
> `stat()` Recupera informações sobre o arquivo apontado pelo path e preenche o buf.  
> retorna informações sobre um arquivo,
> armazendando ela em uma struct stat que é encontradano **<sys/stat.h>**
> A unica diferente das duas funções é o primeiro parametro, 
> que no lstat é passado o caminho do arquivo e no fstat é passado o fd do arquivo, (pego com o open).  
>
> `RETORNO:` 0 retorna se for um sucesso, -1 se der algum erro
> 
> 
**unlink**
 ```c
 #include <unistd.h>
 int unlink (const char *filename)
 ```
 > ele apaga um arquivo contido no caminho passado pelo filename  
 >
 > `RETORNO: `mesmo que o anterior.

 **execve**
  ```c
 #include <unistd.h>
 int execve(const char *pathname, char *const argv[], char *const envp[]);
 ```
 > roda um executavel pelo caminho pathname mandando o argc que é como se fosse um argv do main, e o envp que seria uma lista com chave=valor;  
 >
 > `RETORNO: `só retorna algo se der algum erro (-1)

  **dup, dup2**
  ```c
 #include <unistd.h>
 int dup(int oldfd);
 int dup2(int oldfd, int newfd);
 ```
 > o dup cria uma copia do fd passado por parametro usando um fd de menor valor e que não esteja em uso;
 > o dup3 é a mesma coisa, entretanto ele marca o novo fd pelo segundo parametro passado, caso esse fd ja esteja em uso, ele vai fecha-lo e deixar ele pronto para uso (isso tudo automaticamente); 
 >
 > `RETORNO: `se for um sucesso, ele vai retornar o novo file descriptor (fd), retorna -1 se der ruim;

  **pipe**
  ```c
 #include <unistd.h>
 int pipe(int pipefd[2]);
 ```
 > cria uma troca de dados entre processos, tendo uma unica direção,  
 > no caso o pipefd é um array com dois valores e esses valores são (fd)s  
 > o espaço 1 serve para guardar a informação para outro processo poder utilizar;  
 > o espaço 0 serve para leitura dos dados armazenados pelo outro processo;
 >
 > `RETORNO: ` retorna 0 se o der bom, e -1 se der ruim;


**pipe**
```c
 #include <unistd.h>
 int pipe(int pipefd[2]);
 ```
 > cria uma troca de dados entre processos, tendo uma unica direção,  
 > no caso o pipefd é um array com dois valores e esses valores são (fd)s  
 > o espaço 1 serve para guardar a informação para outro processo poder utilizar;  
 >video explicando melhor na pratica: [video](https://www.youtube.com/watch?v=Mqb2dVRe0uo&ab_channel=CodeVault)  
 > o espaço 0 serve para leitura dos dados armazenados pelo outro processo;
 >
 > `RETORNO: ` retorna 0 se o der bom, e -1 se der ruim;


**opendir**
```c
 #include <dirent.h>
 DIR *opendir(const char *name);
 ```
 > abre um diretorio correspondente ao nome dele passado pelo parametro
 >
 > `RETORNO: ` retorna um ponteiro para esse diretório, NULL caso houver falha ou ele não for um diretório;

 **readdir**
```c
 #include <dirent.h>
 struct dirent *readdir(DIR *dirp);
 ```
 > retorna uma struct dirent que representa a entrada do proximo diretório dentro do diretório passado pelo ponteiro dirp
 >
 > `RETORNO: ` retorna um ponteiro para essa struct, NULL caso houver falha ou ele não for um diretório;

  **closedir**
```c
 #include <dirent.h>
 int closedir(DIR *dirp);
 ```
 > fecha o diretório do tipo dir, que é criado no opendir;
 >
 > `RETORNO: ` retorna 0 se for um sucesso, caso contrario, retorna -1

  **strerror**
```c
 #include <string.h>
 char *strerror(int errnum);
 ```
 > retorna um ponteiro para uma string com o erro que eh descrito pelo codigo passado pelo parametro, errnum;
 >
 > `RETORNO: ` retorna uma string com o erro, ou "Unknown error nnn" se não for encontrado o codigo do erro;


  **perror**
```c
 #include <stdio.h>
 void perror(const char *s);
 ```
 > serve para printar na tela, pelo stderror, uma mensagem de erro dependendo do s que voce mandar, normalmente ele recebe o nome da função que deu erro;
 >
 > `RETORNO: ` não tem;

   **isatty**
```c
 #include <unistd.h>
 int isatty(int fd);
```
 > verifica se o fd é um arquivo aberto referente a um terminal
 >
 > `RETORNO: ` 1 se for verdade e 0 se for falso;  


 **ttyname**
```c
 #include <unistd.h>
 char *ttyname(int fd)
 ```
 > ele retorna uma string com o caminho do arquivo que esta estabelecido em fd se ele estiver conectado a um terminal.
 >
 > `RETORNO: ` retorna o caminho do carquivo ou null se der algum erro

 **ttyslot**
```c
 #include <unistd.h>
 int ttyslot(void);
 ```
 > busca o número do terminal de controle do processo atual
 >
 > `RETORNO: ` retorna o número da unidade do arquivo do dispositivo se encontrado; caso contrário, o valor zero é retornado.

**ioctl**
```c
 #include <sys/ioctl.h>
 int ioctl(int fd, unsigned long request, ...);
 ```
 > A chamada de sistema ioctl () manipula os parâmetros de dispositivo subjacentes de arquivos especiais. Em particular, muitas características operacionais de arquivos especiais de caracteres (por exemplo, terminais) podem ser controladas com solicitações ioctl (). O argumento fd deve ser um descritor de arquivo aberto
 >
 > `RETORNO: ` se der tudo certo, retorna 0, caso contrario, retorna -1

**getenv**
```c
 #include <stdlib.h>
 char *getenv(const char *name);
 ```
 > pesquisa pela lista de variaveis de ambiente pelo nome escrito no parametro name;
 >
 > `RETORNO: ` retorna um ponteiro para essa variavel de ambiente, NULL se ele não encontrar nada;


 **tcsetattr**
```c
 #include <termios.h>
 #include <unistd.h>
 int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
 ```
 > deve definir os parâmetros associados ao terminal referido pelo descritor de arquivo aberto fildes (um descritor de arquivo aberto associado a um terminal) a partir da estrutura termios;  
 > [link_doc](https://pubs.opengroup.org/onlinepubs/009696799/functions/tcsetattr.html)  
 >
 > `RETORNO: ` se der tudo certo, retorna 0, caso contrario, retorna -1;

 **getenv**
```c
 #include <curses.h>
 #include <term.h>
 int tgetent(char *bp, const char *name);
 int tgetflag(char *id);
 int tgetnum(char *id);
 char *tgetstr(char *id, char **area);
 char *tgoto(const char *cap, int col, int row);
 int tputs(const char *str, int affcnt, int (*putc)(int));
```
 > estas funçoes estão todas sendo explicadas no link abaixo:  
 > [link](https://nxmnpg.lemoda.net/3/tgetent)
 >
 > `RETORNO: ` retorna um ponteiro para essa variavel de ambiente, NULL se ele não encontrar nada;