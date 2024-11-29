NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I/usr/include -Imlx
MLXFLAGS = -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz

SRCS = main.c checker.c mandelbrot.c julia.c \
		utils.c burningship.c img_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLXFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
