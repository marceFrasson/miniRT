# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marce <marce@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/13 11:46:29 by marce             #+#    #+#              #
#    Updated: 2021/06/13 18:49:20 by marce            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	./parsing/miniRT.c ./parsing/parsing_I.c ./parsing/parsing_II.c \
			./parsing/parsing_III.c ./parsing/parsing_utils_I.c \
			./render/bitmap.c ./render/check_elem_I.c \
			./render/check_elem_II.c ./render/check_elem_III.c \
			./render/obj_intersec_I.c ./render/obj_intersec_II.c \
			./render/obj_intersec_III.c ./render/phong.c \
			./render/ray_tracer_I.c ./render/ray_tracer_II.c \
			./render/ray_tracer_III.c ./render/window.c \
			./utils/vector_oper_I.c ./utils/vector_oper_II.c \
			./utils/vector_oper_III.c ./parsing/parsing_utils_II.c

OBJ		=	${SRC:.c=.o}
#--------------------------------------//---------------------------------------

NAME		=	miniRT

INCLUDE		=	-I includes -I libft

MODULE		=	./libft/libft.a

FLAGS		=	-Wall -Wextra -Werror

MLX_FLAGS	=	-lbsd -lmlx -lXext -lX11 -lm

CC			=	clang
#--------------------------------------//---------------------------------------
.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}
#--------------------------------------//---------------------------------------
all:		$(NAME)

$(MODULE):
	@make -C libft

$(NAME):	$(MODULE) $(OBJ)
	@$(CC) $(OBJ) $(FLAGS) $(INCLUDE) $(MODULE) $(MLX_FLAGS) -o $(NAME)
	@echo ""
	@echo "|             miniRT criado            |"
	@echo ""
#--------------------------------------//---------------------------------------
clean:
	@rm -rf $(OBJ)
	@make clean -C libft

fclean:		clean
	@rm -rf $(NAME)
	@make fclean -C libft
	@echo ""
	@echo "|            miniRT deletado           |"
	@echo ""
#--------------------------------------//---------------------------------------

re:			fclean all

git:
	git add .
	git status
	git commit -m "$m"
	git push

.PHONY:		all clean fclean re git