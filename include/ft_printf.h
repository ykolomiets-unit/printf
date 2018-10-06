/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolomie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:37:01 by ykolomie          #+#    #+#             */
/*   Updated: 2018/10/05 17:37:03 by ykolomie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int	ft_printf(const char *restrict fmt, ...);
int	ft_dprintf(const int fd, const char *restrict fmt, ...);
int	ft_snprintf(char *buf, const int size, const char *restrict fmt, ...);
int	ft_vdprintf(const int fd, const char *restrict fmt, va_list *ap);
int	ft_vsnprintf(char *buf, const int size, const char *restrict fmt, va_list *ap);

#endif
