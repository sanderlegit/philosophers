# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: averheij <averheij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/01 15:31:38 by averheij      #+#    #+#                  #
#    Updated: 2021/02/05 12:02:42 by averheij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_one
CFILES	=	main.c a_philo.c parse_args.c time.c util_1.c
OFILES	=	$(CFILES:%.c=objects/%.o)
#FLAGS	=	-Werror -Wall -Wextra
LIB		=	-lpthread
CC		=	gcc
OBJDIR	=	./objects
OS		=	$(shell uname)

ifeq ($(OS),Linux)
	EXTRA_FLAGS	=	
else
	EXTRA_FLAGS	=	
endif

FLAGS	+=	-g
FLAGS	+=	-fsanitize=address
CFILES	+=	print_util.c
OFILES	=	$(CFILES:%.c=objects/%.o)

#BOLD	=	\033[1m
#CLEAR	=	\033[0m

all: $(NAME)
	echo $(OFILES)

$(OBJDIR):
	mkdir -p $@

objects/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ $(DEFINE)

$(NAME): $(OBJDIR) $(OFILES)
	$(CC) $(FLAGS) -o $(NAME) $(OFILES) $(LIB) $(EXTRA_FLAGS)

bonus: all

clean:
	@echo "Cleaning objects:"
	rm -f $(OFILES)

fclean: clean
	@echo "Cleaning binary:"
	rm -f $(NAME)

re: fclean all

