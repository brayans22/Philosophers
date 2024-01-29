NAME 		= 	philo

PHILO 		= 	src/parser.c 		\
				src/philosopher.c   \
				src/init.c			\
				src/utils.c 		\
				src/set.c           \
				src/routine.c       \
				src/get.c			\
				src/program.c       \
				src/died.c			\
				src/protect.c 		
			
HEADERS 	= 	headers/

SRCS 		= ${PHILO}

OBJS 		= ${SRCS:.c=.o}

CC 			= gcc
# -fsanitize=thread
CFLAGS 		= -Wall -Werror -Wextra -g 


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