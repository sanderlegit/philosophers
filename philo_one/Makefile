# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: averheij <averheij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/01 15:31:38 by averheij      #+#    #+#                  #
#    Updated: 2021/02/01 17:36:24 by averheij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_one
CFILES	=	main.c parse_args.c util_1.c
OFILES	=	$(CFILES:.c=.o)
FLAGS	=	-Werror -Wall -Wextra
LIB		=	-lpthread
CC		=	gcc
OBJDIR	=	./objects
OS		=	$(shell uname)

ifeq ($(OS),Linux)
	EXTRA_FLAGS	=	
else
	EXTRA_FLAGS	=	
endif

#FLAGS	+=	-g -fsanitize=address

#BOLD	=	\033[1m
#CLEAR	=	\033[0m

all: $(NAME)

$(NAME): $(OBJDIR) $(OFILES)
	$(CC) $(FLAGS) -o $(NAME) $(OFILES) $(LIB) $(EXTRA_FLAGS)

$(OBJDIR):
	mkdir -p $@

objects/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ $(DEFINE)

bonus: all

clean:
	@echo "Cleaning objects:"
	rm -f $(OFILES)

fclean: clean
	@echo "Cleaning binary:"
	rm -f $(NAME)

re: fclean all

