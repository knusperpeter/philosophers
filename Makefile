# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caigner <caigner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/10 20:04:47 by miheider          #+#    #+#              #
#    Updated: 2024/06/12 15:57:11 by caigner          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo
CC		= cc
AR		= ar
RM		= rm
CFLAGS	= -Wall -Wextra -Werror
HDRS	= include/philo.h

SOURCES	=	main.c \
			utils_1.c \
			utils_2.c \
			init.c \
			routine.c \
			tasks.c \

OBJECTS = $(SOURCES:.c=.o)

all		: $(NAME)

$(NAME)	: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(NAME)
	@if [ $$? -eq 0 ]; then echo "\033[1;32mphilo [OK]\033[0m"; else echo "\033[1;31mphilo [KO]\033[0m"; fi

%.o		: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean	:
	$(RM) -rf $(OBJECTS)

fclean	: clean
	$(RM) -rf $(NAME)

re		: fclean all

# .SILENT:
.PHONY: all clean fclean re