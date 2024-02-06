NAME 		= 	philo

PHILO 		= 	src/parser.c 		\
				src/philosopher.c   \
				src/init.c			\
				src/free.c          \
				src/utils.c 		\
				src/set.c           \
				src/get.c			\
				src/program.c       
			
HEADERS 	= 	headers/

SRCS 		= ${PHILO}

OBJS 		= ${SRCS:.c=.o}

CC 			= gcc

CFLAGS 		= -Wall -Werror -Wextra -g -fsanitize=thread

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