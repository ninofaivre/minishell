# minishell

![Parsing Struct Diagram](https://github.com/ninofaivre/minishell/blob/master/minishell.jpg)

## Makefile

By default using make without any option or compiling this project yourself the prompt will be "minishell $> ".<br>
You can define the Prompt like this : make [re/clean/fclean/all] 'PROMPT="my custom PROMPT $$> "'.<br>
You can also define the Prompt at include/global.h
