NAME = fractol

CC = cc

SOURCES = fractol.c fractol_utils.c

OBJECTS = $(SOURCES:.c=.o)

$(NAME) : $(OBJECTS)
	$(CC) -Wall -Wextra -Werror $(OBJECTS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
all :  $(NAME)

clean : 
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all