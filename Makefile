# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/25 13:41:44 by qsymond           #+#    #+#              #
#    Updated: 2021/01/25 16:04:40 by qsymond          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=clang++
CFLAGS=-Wall -Wextra -Werror -std=c++98
SRCS=tests/*.c
OBJ_NAME = $(SRCS:.c=.o)
OBJ = $(addprefix , $(OBJ_NAME))
EXECUTABLE=ft_test_containers
GREEN		= "\033[1;32m"

all:	ft_test_containers

ft_test_containers:	tests/main.o tests/list_test.o tests/map_test.o tests/queue_test.o tests/stack_test.o tests/vector_test.o tests/deque_test.o
	$(CC) $(CFLAGS) $(OBJ) -o ft_test_containers
	@echo ${GREEN}${CR}"┌─┐┬ ┬┌─┐┌─┐┌─┐┌─┐┌─┐"
			@echo 		  	   "└─┐│ ││  │  ├┤ └─┐└─┐"
			@echo 		  	   "└─┘└─┘└─┘└─┘└─┘└─┘└─┘"

compile:	$(SRCS)
	$(CC) $(CFLAGS) -o tests/main.o -c tests/main.cpp
	$(CC) $(CFLAGS) -o tests/list_test.o -c tests/list_test.cpp
	$(CC) $(CFLAGS) -o tests/map_test.o -c tests/map_test.cpp
	$(CC) $(CFLAGS) -o tests/queue_test.o -c tests/queue_test.cpp
	$(CC) $(CFLAGS) -o tests/stack_test.o -c tests/stack_test.cpp
	$(CC) $(CFLAGS) -o tests/vector_test.o -c tests/vector_test.cpp
	$(CC) $(CFLAGS) -o tests/deque_test.o -c tests/deque_test.cpp
clean:
	rm -rf tests/*.o

fclean:
	rm -rf tests/*.o $(EXECUTABLE)

re		: fclean all

.PHONY: all clean fclean re