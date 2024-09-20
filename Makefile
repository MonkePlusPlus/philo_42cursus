# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/18 15:55:46 by ptheo             #+#    #+#              #
#    Updated: 2024/09/20 21:41:35 by ptheo            ###   ########.fr        #
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
		$(CC) $(FLAGS) $(OBJ) -o $(NAME) -I$(INCLUDES) $(PTHREAD_FLAGS)

clean :
	$(RM) $(OBJ)

fclean :
	$(RM) $(NAME) $(OBJ)

re : fclean all

.PHONY: all clean fclean re
