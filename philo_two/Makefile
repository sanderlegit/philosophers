# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: averheij <averheij@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/01 15:31:38 by averheij      #+#    #+#                  #
#    Updated: 2021/02/11 14:50:00 by averheij      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_two
CFILES	=	main.c a_philo.c parse_args.c time.c util_1.c util_2.c threads.c
OBJDIR	=	objects
OFILES	=	$(CFILES:%.c=$(OBJDIR)/%.o)
FLAGS	=	-Werror -Wall -Wextra -O3
LIB		=	-lpthread
CC		=	gcc

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

