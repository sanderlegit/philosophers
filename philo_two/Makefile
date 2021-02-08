# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: averheij <averheij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/01 15:31:38 by averheij      #+#    #+#                  #
#    Updated: 2021/02/05 15:29:26 by averheij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_two
CFILES	=	main.c a_philo.c parse_args.c time.c util_1.c util_2.c
OBJDIR	=	objects
OFILES	=	$(CFILES:%.c=$(OBJDIR)/%.o)
FLAGS	=	-Werror -Wall -Wextra -O3
LIB		=	-lpthread
CC		=	gcc

#FLAGS	=	-O3
#FLAGS	+=	-g
#FLAGS	+=	-fsanitize=address
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

