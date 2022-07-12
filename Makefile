NAME		= fdf

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
LDFLAGS		= -lmlx -lft -lm -L$(MLX_DIR) -L$(LIBFT_DIR)

RM 			= rm
RMFLAGS		= -rf

LIBFT		= $(LIBFT_DIR)libft.a
LIBFT_DIR	= ./libft/

MLX		= $(MLX_DIR)libmlx.dylib
MLX_DIR = ./minilibx/

SRCS_DIR 	= ./srcs/
INCLUDE_DIR = ./include/

SRCS 		=	fdf.c			\
				utils.c			\
				parse.c			\
				get_next_line.c	\
				isometric.c		\
				draw.c			\

OBJS_DIR	= objects/
OBJS 		= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(LIBFT) $(MLX) $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) $(OBJS) -o $(NAME)

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)

%.o : $(SRCS_DIR)%.c $(INCLUDE_DIR)%.h
	@$(CC) $(CFLAGS) -c -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) $< -o $@

$(LIBFT) :
	@$(MAKE) bonus -C $(LIBFT_DIR)

$(MLX) :
	@$(MAKE) -C $(MLX_DIR)

clean :
	@$(RM) $(RMFLAGS) $(OBJS_DIR) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean


fclean : clean
	$(RM) $(RMFLAGS) $(MLX)
	$(RM) $(RMFLAGS) $(LIBFT)
	$(RM) $(RMFLAGS) $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re
