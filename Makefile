NAME = fractol

CC = cc

CFLAGS = -Wall -Wextra -Werror

SOURCES = fractol.c fractol_utils.c fractol_utils2.c fract_iterators.c libx_utils.c math_utils.c

OBJECTS = $(SOURCES:.c=.o)

$(NAME) : $(OBJECTS)
	$(CC) -fsanitize=address -g3 $(CFLAGS) $(OBJECTS) -lmlx -framework OpenGL -framework AppKit -o $(NAME) 
all :  $(NAME)

clean : 
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all