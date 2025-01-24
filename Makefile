# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: theo <theo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/18 15:55:46 by ptheo             #+#    #+#              #
#    Updated: 2025/01/24 01:27:51 by theo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo

SRC	= ./src/
# START FILE
FILE	 = main.c
FILE	+= data.c
FILE	+= philo.c
FILE	+= utils.c
FILE	+= master.c
# END FILE
SRC_FILE = $(addprefix $(SRC), $(FILE))

OBJ      := $(SRC_FILE:.c=.o)
INCLUDES := ./includes/

CC      		:= cc
FLAGS 	  		:= -Wall -Werror -Wextra -g3 
PTHREAD_FLAGS	:= -lpthread

RM   := rm -rf

GREEN	:= \033[0;32m
WHITE	:= \033[0m

all : $(NAME)

$(NAME) : $(OBJ)
		@echo "${GREEN}COMPILATION OF PHILO FILE :${WHITE}"
		$(CC) -o $@ $^ $(CFLAGS) -I$(INCLUDES) $(PTHREAD_FLAGS)

clean :
	$(RM) $(OBJ)

fclean :
	$(RM) $(NAME) $(OBJ)

re : fclean all

.PHONY: all clean fclean re
