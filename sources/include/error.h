/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:13:58 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 17:25:43 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ET_SYNTAX "syntax"

# define EM_UNEXPECTED_EOF "unexpected end of file"
# define EM_TOO_MANY_ARGS "too many args"

# define EM_CMD_NOT_FOUND "command not found"
# define EM_NO_SUCH_FILE_DIR "No such file or directory"
# define EM_IS_DIR "Is a directory"
# define EM_PERM_DENIED "Permission denied"

# define OK 0
# define ERR 1
# define UCMD 127
# define ISDIR 126

# endif