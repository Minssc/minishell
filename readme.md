## 팀원 구성
####	minsunki, tjung

## 프로젝트 설명
```
minishell. 작고 귀여운 쉘 만들기.
```

## Dependency 
#### libreadline-dev
```sh
sudo apt install libreadline-dev
```

## 프로젝트 구조
```bash
.
├── Makefile
├── bonus					#TODO?
├── libft					#libft 
├── readme.md
└── sources
    ├── builtin				# 빌트인 함수들 
    │   ├── cd.c
    │   ├── echo.c
    │   ├── env.c
    │   ├── exit.c
    │   ├── export.c
    │   ├── pwd.c
    │   └── unset.c
    ├── msfunc				# minishell functions. 유틸 함수들
    ├── include				# 헤더 파일들
    │   └── minishell.h
    ├── main.c				
    ├── meta.c				
    └── mexit.c
```
## TODO
```
argv를 < << > >> | delim으로 잘라서 보관. list사용? delim type 저장 필요
모든 list에 대하여
	앞뒤로 공백 trim?
	"" '' $("미포함?) 선행 처리. 문자열 대체. ()는 서브젝트 포함인가?

	syntax에 맞는지 먼저 확인해야 함.

	처리된 문자열을 기반으로 exec.
	delim type에 따라 exec 결과물 처리
		redirection, pipe 

builtin 함수들 작성하기.
environment 알아보기 
ctrl-C ctrl-D ctrl-\ 시그널 관련 알아보기 

7일 내로 일단 mandatory 평가 받기	<3.9 
10일 내로 수정 및 평가 완료하기		~3.12
```
