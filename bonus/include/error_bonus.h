/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:13:58 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/12 12:06:45 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_BONUS_H
# define ERROR_BONUS_H

# define ET_SYNTAX "syntax"

# define EM_UNEXPECTED_TOKEN "syntax error near unexpected token"

# define EM_UNEXPECTED_EOF "unexpected end of file"
# define EM_TOO_MANY_ARGS "too many arguments"

# define EM_NO_ODLPWD "OLDPWD not set"
# define EM_NUMERIC_REQUIR "Numeric argument required"

# define EM_CMD_NOT_FOUND "command not found"
# define EM_NO_SUCH_FILE_DIR "No such file or directory"
# define EM_IS_DIR "Is a directory"
# define EM_NOT_DIR "Not a directory"
# define EM_PERM_DENIED "Permission denied"

# define EM_INVALID_IDENT "Not a valid identifier"
# define EM_INVALID_OPT "Invalid option"

# define OK 0
# define ERR 1
# define UCMD 127
# define ISDIR 126

#endif
