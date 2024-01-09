NAME = fractol

CC = cc

SOURCES = fractol.c fractol_utils.c libx_utils.c

OBJECTS = $(SOURCES:.c=.o)

$(NAME) : $(OBJECTS)
	$(CC) -fsanitize=address -g3 -Wall -Wextra -Werror $(OBJECTS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
all :  $(NAME)

clean : 
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all