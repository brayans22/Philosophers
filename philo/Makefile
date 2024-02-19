# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/09 15:42:55 by brayan            #+#    #+#              #
#    Updated: 2024/02/19 17:39:19 by bsaiago-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	philo

PHILO 		= 	src/parser.c 		\
				src/philosopher.c   \
				src/init.c			\
				src/free.c          \
				src/monitor.c       \
				src/utils.c 		\
				src/set.c           \
				src/get.c			\
				src/logic.c       
			
HEADERS 	= 	headers/

SRCS 		= ${PHILO}

OBJS 		= ${SRCS:.c=.o}

CC 			= gcc

CFLAGS 		= -Wall -Werror -Wextra # -fsanitize=thread 

%.o:%.c 	Makefile headers/philosopher.h
			${CC} ${CFLAGS} -I ${HEADERS} -c $< -o $@

${NAME}: 	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all: 		${NAME}

clean:
			rm -f ${OBJS}

fclean: 	clean
			rm -f ${NAME}

re: 		fclean all

.PHONY: 	all clean fclean re