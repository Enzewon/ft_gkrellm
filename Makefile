# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/30 08:45:06 by dvdovenk          #+#    #+#              #
#    Updated: 2018/03/06 20:15:27 by dvdovenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_gkrellm

SRCS =	main.cpp \
		KernelModule.cpp \
		CPUModule.cpp \
		NetworkModule.cpp \
		RAMModule.cpp \
		InfoModule.cpp \
		DateModule.cpp \
		Ncurses.cpp

CC_FLAGS = -Wall -Werror -Wextra
C = clang++

OBJ = $(SRCS:.cpp=.o)

NOC=\033[0m
OKC=\033[32m
ERC=\033[31m
WAC=\033[33m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(OKC)$(NAME): Compiling objectives $(NAME)$(NOC)"
	@$(C) $(CC_FLAGS) -o $(NAME) $(OBJ) -lncurses
	@echo "$(OKC)$(NAME): Compilation success!$(NOC)"

%.o: %.cpp
	@$(C) $(CC_FLAGS) -o $@ -c $^

clean:
	@rm -rf $(OBJ)
	@echo "$(WAC)$(NAME): Removing $(NAME) objectives$(NOC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(WAC)$(NAME): Removing executable$(NOC)"

re: fclean all
