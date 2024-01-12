NAME = fractol

CC = cc

CFLAGS = -Wall -Wextra -Werror

SOURCES = fractol.c fractol_utils.c libx_utils.c math_utils.c

OBJECTS = $(SOURCES:.c=.o)

$(NAME) : $(OBJECTS)
	$(CC) -g3 -fsanitize=address $(CFLAGS) $(OBJECTS) -O3 -lmlx -framework OpenGL -framework AppKit -o $(NAME) 
all :  $(NAME)

clean : 
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all