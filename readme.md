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
├── bonus				#sources/와 내용물 동일, _bonus suffix 추가
├── libft
├── readline-master		#GNU readline 8.1
│   └── readline
├── readme.md
├── run.sh
├── sources				#Mandatory 소스
│   ├── builtin
│   │   ├── cd.c
│   │   ├── cd_sub.c
│   │   ├── echo.c
│   │   ├── env.c
│   │   ├── exit.c
│   │   ├── export.c
│   │   ├── export_sub.c
│   │   ├── pwd.c
│   │   └── unset.c
│   ├── env
│   │   ├── env.c
│   │   └── env_util.c
│   ├── exec
│   │   ├── argv.c
│   │   ├── bin.c
│   │   ├── bin_util.c
│   │   ├── exec.c
│   │   └── exec_util.c
│   ├── fd.c
│   ├── include
│   │   ├── error.h
│   │   └── minishell.h
│   ├── main.c
│   ├── meta.c
│   ├── mexit.c
│   ├── msfunc
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
│   ├── parse
│   │   ├── asterisk.c
│   │   ├── asterisk_compare.c
│   │   ├── asterisk_util.c
│   │   ├── cleanup.c
│   │   ├── expand.c
│   │   ├── expand_util.c
│   │   ├── parse.c
│   │   ├── parse_util.c
│   │   └── sort.c
│   ├── redir
│   │   ├── heredoc.c
│   │   ├── heredoc_util.c
│   │   └── redir.c
│   ├── rlmsg
│   │   └── rl_set_msg.c
│   ├── signal.c
│   ├── syntax.c
│   └── token
│       ├── token.c
│       └── token_util.c
└── val.sh

```
## TODO
```
3.12 평가 완료! 
```
