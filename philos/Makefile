NAME 		= 	philo

PUSH_SWAP 	= 	src/

HEADERS 	= 	headers/push_swap.h 

SRCS 		= ${PUSH_SWAP}

OBJS 		= ${SRCS:.c=.o}

CC 			= gcc
CFLAGS 		= -Wall -Werror -Wextra -g

%.o:%.c 	Makefile headers/push_swap.h
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