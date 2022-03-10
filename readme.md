## 팀원 구성
####	minsunki, tjung

## 프로젝트 설명
```
minishell. 작고 귀여운 쉘 만들기.
```

## Dependency 
#### libreadline: GNU Readline Library v8.1 included


## 프로젝트 구조
```bash
.
├── Makefile
├── bonus               
├── libft               #libft
├── readline-master     #libreadline, libhistory
│   └── readline
├── readme.md
├── sources             #source folder for mandatory part
│   ├── builtin         #Builtin functions
│   │   ├── cd.c
│   │   ├── echo.c
│   │   ├── env.c
│   │   ├── exit.c
│   │   ├── export.c
│   │   ├── pwd.c
│   │   └── unset.c
│   ├── env             #env related functions
│   │   ├── env.c
│   │   └── env_util.c
│   ├── exec            #execution related functions
│   │   ├── argv.c
│   │   ├── bin.c
│   │   ├── bin_util.c
│   │   ├── exec.c
│   │   └── exec_util.c
│   ├── fd.c
│   ├── include         #headers 
│   │   ├── error.h
│   │   └── minishell.h
│   ├── main.c
│   ├── meta.c
│   ├── mexit.c
│   ├── msfunc          #misc minishell functions
│   │   ├── ms_argjoin.c
│   │   ├── ms_custom.c
│   │   ├── ms_find.c
│   │   ├── ms_free.c
│   │   ├── ms_isspace.c
│   │   ├── ms_puterr.c
│   │   ├── ms_set_es.c
│   │   ├── ms_stitch.c
│   │   ├── ms_substr.c
│   │   ├── ms_tolower.c
│   │   └── ms_trim.c
│   ├── parse           #parsing related functions
│   │   ├── cleanup.c
│   │   ├── expand.c
│   │   ├── expand_util.c
│   │   ├── parse.c
│   │   └── sort.c
│   ├── redir           #redirection related functions
│   │   ├── heredoc.c
│   │   ├── heredoc_util.c
│   │   └── redir.c
│   ├── signal.c
│   ├── syntax.c
│   └── token           #token related functions
│       ├── token.c
│       └── token_util.c
```
## TODO
```
Syntax 확인
$SHLVL
norminette
3.12 평가 예정
```
