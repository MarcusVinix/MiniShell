# Funções parte 1

> **readline**  
>  
> `#included <stdio.h>`  
> `char *readline(const char *prompt)`  
> Le uma linha do terminal e retorna ela.  
> A linha recebida teve memoria alocada com malloc.  
> Uma linha em branco retorna uma string vazia.  
> Se tiver EOF em uma linha vazia, o retorno será NULL.  
> Se tiver EOF em uma linha não vazia, ele vai ser considerado uma nova linha.  
>  
>  
> **rl_clear_history**  
>  
> `void rl_clear_history(void)`  
> Limpa a lista de histórico suprimindo todas as entradas.  
> É semelhante a função clear_history.  
> Isso difere de clear_history porque libera dados privados  
> Readline salva na lista de historia.  
>  
>  
> **rl_on_new_line**  
>  
> `int rl_on_new_line(void)`  
> Informa as funções de atualização que passamos para uma nova linha(vazia),  
> geralmente após a saída de uma nova linha.  
>  
> **rl_replace_line**  
>  
> `void rl_replace_line(const char *text, int clear_undo)`  
> Substitua o conteúdo de rl_line_buffer por texto.  
> O ponto e a marca são preservados, se possivel.  
> Se clear_undo for diferente de zero, a lista de desfazer associada à linha atual é limpa.  
>  
>  
> **rl_redisplay**  
>  
> `void rl_redisplay(void)`  
> Muda o que está na tela para o conteúdo atual da rl_line_buffer.  
>  
>  
> **add_history**  
>  
> `void add_history(const char *string)`  
> Coloca a string no final da lista do histórico.  
> O campo de dados associado(se houver) é definido como NULL.  
>  
>  
> **access**  
>  
> `#include <unistd.h>`  
> `int access(const char *pathname, int mode)`  
> Verifica se o processo de chamada pode acessar o arquivo do pathname.  
> Se o pathname for um link simbólico, ele será desferenciado.  
>  Retorna 0  se tiver sucesso e -1 se houver falha.
>  
> **fork**  
>  
> `#include <unistd.h>`  
> `pid_t fork(void)`  
> Cria um novo processo duplicando o que está chamando fork.  
> O novo processo é chamado de child process. 
> O processo que está chamando fork é conhecido como parent process.  
> Com sucesso retorna o PID do child no parent, e retorna 0 no processo do child.  
> Em caso de falha retorna -1.  
>  
>  
> **wait, waitpid**  
>  
> `pid_t wait(int *wstatus)`  
> `pid_t waitpid(pid_t pid, int *wstatus, int option)`  
> O wait suspende a execução da thread de chamada até que um de seus filho seja encerrado.  
> O waitpid suspedende até que o pid especificado mude de status.  
> Com sucesso retorna o id do processo do child encerrado(mudança de status) e -1 no caso de falha.  
>  
>  
> **getcwd**  
>  
> `#include <unistd.h>`  
> `char *getcwd(char *buf, size_t size)`  
> Retorna um null-terminated string contendo o endereço absoluto pathname da pasta atual de onde o processo está sendo chamado.  
> O pathname é retornado como resultado da função e também é armazenado na argumento buf, se present.  
> Em caso de falha o retorno será NULL.  
>  
>  
> **chdir**  
> `#include <unistd.h>`  
> `int chdir(const char *path)`  
> Muda o diretorio atual de onde o processo é chamado para o diretorio especificado no path.  
> Em caso de sucesso 0 é retornado e -1 em caso de erro.  
>  

