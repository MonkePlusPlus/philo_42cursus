# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/18 15:55:46 by ptheo             #+#    #+#              #
#    Updated: 2025/01/24 19:58:34 by ptheo            ###   ########.fr        #
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
FILE	+= launch.c
# END FILE
SRC_FILE = $(addprefix $(SRC), $(FILE))

OBJ      := $(SRC_FILE:.c=.o)

INCLUDES := ./includes/

FLAGS 	  		:= -Wall -Werror -Wextra -g3 
PTHREAD_FLAGS	:= -lpthread

RM   := rm -rf

GREEN	:= \e[0;32m
WHITE	:= \e[0m

%.o : %.c 
	@echo "Compiling $<"
	@$(CC) -c $< -o $@ $(CFLAGS) -I $(INCLUDES)



all : $(NAME)

$(NAME) : $(OBJ)
		@echo "${GREEN}COMPILATION OF PHILO FILE${WHITE}"
		@$(CC) $^ -o $@  $(CFLAGS) -I $(INCLUDES) $(PTHREAD_FLAGS)


clean :
	$(RM) $(OBJ)

fclean :
	$(RM) $(NAME) $(OBJ)

re : fclean all

.PHONY: all clean fclean re
