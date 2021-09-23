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

  **execve**
  ```c
 #include <unistd.h>
 int dup(int oldfd);
 int dup2(int oldfd, int newfd);
 ```
 > o dup cria uma copia do fd passado por parametro usando um fd de menor valor e que não esteja em uso;
 > o dup3 é a mesma coisa, entretanto ele marca o novo fd pelo segundo parametro passado, caso esse fd ja esteja em uso, ele vai fecha-lo e deixar ele pronto para uso (isso tudo automaticamente); 
 >
 > `RETORNO: `se for um sucesso, ele vai retornar o novo file descriptor (fd), retorna -1 se der ruim;

  **execve**
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