/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:13:58 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/11 18:56:39 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

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
