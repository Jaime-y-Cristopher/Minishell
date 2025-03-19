### Joint Project @ja1m3st && @vikingokvist

## Description

Minishell is a simple, yet powerful shell that combines built-in commands with the ability to run any external program. It’s designed to work a lot like BASH, featuring things like variable expansion, multiple pipes, and flexible redirections.



![Mi-película](https://github.com/user-attachments/assets/1953df78-07da-4774-b517-cbe4224d716d)




### Features
- Maintains a history of previously entered commands.  
- Finds and executes the correct program using the `PATH` variable, supporting both relative and absolute paths.  
- Can execute any command using an absolute or relative path.  
- Expands environment variables (`$VAR`) to their values.  
- Handles `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` similarly to Bash.  
- Supports quoting:  
  - Single quotes (`'`) prevent interpretation of meta-characters.  
  - Double quotes (`"`) prevent interpretation except for `$`.  
- `$?` expands to the last command’s exit status.  
- Supports pipes (`|`) to connect commands, passing output from one command to the next.  
- Implements logical operators `&&` and `||`, with support for grouping using parentheses.  
- Includes a simple implementation of `here_doc`.  
- Includes `setcolour [name/] colour` to change command prompt colours.

### Built-in Commands
- `echo` with `-n` option.  
- `cd` with support for:  
  - Relative and absolute paths.  
  - `-` to switch to `OLDPWD`.  
  - No argument defaults to `HOME`.  
- `pwd` (prints the working directory) without options.  
- `export` without options.  
- `unset` without options.  
- `env` without options.  
- `exit [exit_status]` without options.  

### Redirections  
Redirections can optionally specify a file descriptor (`[n]`). If not specified, `stdin`/`stdout` are used by default.  
- `< file` (input redirection) — Reads input from a file.  
- `<< delimiter ` (here doc) — Reads input until `limiter` is encountered.  
- `> file` (output redirection) — Writes output to a file, overwriting it.  
- `>> file` (output redirection append mode) — Appends output to a file instead of overwriting.  



### Compilation
```
git clone git@github.com:T-D-A-H/Minishell.git minishell
cd minishell && make
./minishell
```
