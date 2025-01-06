# Minishell

An interesting project. The goal of this project is to create a simple shell that will serve as our own small bash (see the subject for details).

## How to use it

```
  1. git clone this repository
  2. cd this repository
  3. make
  4. ./minishell
```
output:
```
  minishell> <write your command-line here>
```

## Features Implemented

  **A command history feature:**
You can navigate with the up and down key.

  **Built-in Commands**

```
   echo:   Supports the -n option (prevents a newline at the end).
   cd:     Changes the directory; only accepts relative or absolute paths.
   pwd:    Prints the absolute path of the current directory, without options.
   export: Sets environment variables, without options.
   unset:  Removes environment variables, without options.
   env:    Displays environment variables, without options or arguments.
   exit:   Exits the shell, without options.
```
No built-in commands can also be executed : ls, touch, mkdir, clear...

  **Redirection Handling**

```
  >:  Redirects output to a file (overwrites the file if it exists).
  >>: Redirects output to a file in append mode.
  <:  Redirects input from a file.
  <<: Here-doc, reads input until a specific delimiter is reached (does not        update the history).
```

  **Pipe and Signal Handling:**
```
  |:      Connects the output of one command to the input of the next command (pipeline).

  ctrl-C: Interrupts the current command and displays a new prompt on a new line.
  ctrl-D: Closes the shell (equivalent to exit).
  ctrl-\: Does nothing.
```

**Environment Variables and Quote Handling:**
```
  $VARNAME: Expands the value of the environment variable.
  $?:       Expands to the exit status of the most recently executed foreground pipeline.

  ' : Disables interpretation of all meta-characters in the quoted sequence.
  " : Disables interpretation of meta-characters, except for $ (variables).
```
