# <div align="center">⚙️ minishell (a [42](https://42perpignan.fr/) project) ⚙️</div>
## 📑 Introduction
School 42's `minishell` is the first two-person big project. The goal is to create a basic working shell inspired by bash.
All the features of this `minishell` :
- Custom prompt showing the current directory.
- A working history with the up arrow.
- Searching the $PATH variable to execute commands.
- Handle single quote and not interpreting the metacharacters in the quoted sequence.
- Handle double quote and not interpreting the metacharacters in the quoted sequence except for dollar sign.
- Redirections :
	- Output redirection `>`
	- Output redirection append mode `>>`
	- Input redirection `<`
	- Here document `<<`
- Pipes `|`.
- Environment variables with `$`.
- Handle `$?` which expand to the exit status of the most recently executed foreground pipeline.
- Handle signals :
	- `ctrl-C` Kills the running program and display a new prompt.
	- `ctrl-D` Closes the standard input if readed, exits minishell otherwise.
	- `ctrl-\` Does nothing.
- Some builtins
	- `echo` with option -n.
	- `cd` with `.`, `..` and `-` arguments.
	- `pwd` without options.
	- `export` without options.
	- `unset` without options.
	- `env` without options.
	- `exit` without options.
- `&&` and `||` operators with parenthesis.
- Wildcards `~` and `*`.

Special mention to [Arawyn](https://github.com/Arawyn42) for doing this big project with me.

Subject : <a href=asset/en.subject.pdf>en.minishell_subject.pdf<a/>
### My grade
[![nsalles's 42 minishell Score](https://badge42.coday.fr/api/v2/clshyl91d071301p436jjiyqr/project/3440809)](https://github.com/Coday-meric/badge42)

## Usage
Download `minishell` and enter the repo :
```sh
git clone https://github.com/Floperatok/42-minishell.git && cd 42-minishell
```
Compile the project :
```sh
make && make clean
```
Run `minishell`
```sh
./minishell
```
It is also possible to use the -c flag, to execute only one command line into the minishell :
```sh
./minishell -c "..."
```