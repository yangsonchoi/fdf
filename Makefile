NAME		= fdf

CC			= gcc -g
CFLAGS		= -Wall -Werror -Wextra
LDFLAGS		= -lmlx -lft -lm -L$(MLX_DIR) -L$(LIBFT_DIR)
INCLUDES	= -I$(HDRS_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

RM 			= rm
RMFLAGS		= -rf

LIBFT		= $(LIBFT_DIR)libft.a
LIBFT_DIR	= ./libft/

MLX			= $(MLX_DIR)libmlx.dylib
MLX_DIR 	= ./minilibx/

HDRS_LIST	= $(patsubst %.c, %.h, $(SRCS_LIST))
HDRS_DIR	= ./include/
HDRS		= $(addprefix $(HDRS_DIR), $(HDRS_LIST))

SRCS_DIR	= ./srcs/
SRCS_LIST	=	fdf.c			\
				utils.c			\
				parse.c			\
				get_next_line.c	\
				isometric.c		\
				draw.c			\
				color_utils.c
SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR	= objects/
OBJS_LIST	= $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS	= $(addprefix $(OBJS_DIR), $(OBJS_LIST))

all : $(NAME)

$(NAME) : $(LIBFT) $(MLX) $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(OBJS_DIR) :
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HDRS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT) :
	$(MAKE) bonus -C $(LIBFT_DIR)

$(MLX) :
	$(MAKE) -C $(MLX_DIR)
	cp $(MLX) .

clean :
	$(RM) $(RMFLAGS) $(OBJS_DIR) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean : clean
	$(RM) $(RMFLAGS) $(MLX)
	$(RM) $(RMFLAGS) libmlx.dylib
	$(RM) $(RMFLAGS) $(LIBFT)
	$(RM) $(RMFLAGS) $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re
