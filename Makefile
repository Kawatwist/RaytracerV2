# **************************************************************************** #
#																			  #
#														 :::	  ::::::::	#
#	Makefile										   :+:	  :+:	:+:	#
#													 +:+ +:+		 +:+	  #
#	By: luwargni <luwargni@student.42.fr>		  +#+  +:+	   +#+		 #
#												 +#+#+#+#+#+   +#+			#
#	Created: 2018/11/06 19:24:01 by lomasse		   #+#	#+#			  #
#	Updated: 2019/12/08 14:58:52 by luwargni		 ###   ########.fr		#
#																			  #
# **************************************************************************** #

violetfonce=\033[0;35m
violetclair=\033[1;35m
neutre=\033[0m
cyanfonce=\033[0;36m
cyanclair=\033[1;36m
vertfonce=\033[0;32m
vertclair=\033[1;32m
rouge=\033[31m

NAME			= rtv1

HEADER 			= $(shell find includes -type f) $(shell find libraries/include -type f 2>/dev/null || true)

SRC_PATH		= $(shell find sources -type d)

INC_PATH 		= $(shell find includes -type d) $(shell find libft -type d) $(shell find libraries/include -type d 2>/dev/null || true) \

OBJ_PATH		= OBJ

SRC				=	main.c										\
					createpxl.c									\
					data.c										\
					filldata.c									\
					rot.c										\
					tga_main.c									\
					uncompress.c								\
					init.c										\
					init_sdl.c									\
					init_cam.c									\
					rot_init_cam.c								\
					quit.c										\
					get_point.c									\
					parse.c										\
					header.c									\
					parse_texture.c								\
					camera.c									\
					object.c									\
					light.c										\
					files.c										\
					find.c										\
					color.c										\
					texture.c									\
					ray.c										\
					send.c										\
					input.c										\
					input_tool.c								\
					loop.c										\
					shape.c										\
					tolight.c									\
					init_vec.c									\
					mat_vec2.c									\
					math_vec_float.c							\
					math_vec.c									\
					vec_tool.c									\
					find_normal.c								\
					switch_vec.c								\
					ang.c										\
					reflexion.c									\
					refraction.c								\
					rot_matrice.c								\
					move_type.c									\
					light_cursor.c								\
					input_obj.c									\
					input_light.c								\
					input_cam.c									\
					input_textures.c							\
					create_type.c								\
					fill_obj.c									\

OBJ 			= $(addprefix $(OBJ_PATH)/, $(SRC:%.c=%.o))

LIBS 			= SDL2 SDL2_mixer SDL2_ttf freetype ft

LIB_PATH 		= ./libft \
				  ./libraries/lib \

FRAMEWORK 		= OpenGL AppKit

CC 				= gcc -g -std=c99

vpath %.c $(foreach dir, $(SRC_PATH), $(dir):)

IFLAG			= $(foreach dir, $(INC_PATH), -I$(dir) )

CFLAG 			= -Wall -Wextra -Werror

LFLAG 			= $(foreach dir, $(LIB_PATH), -L $(dir) ) $(foreach lib, $(LIBS), -l$(lib) ) $(foreach fmw, $(FRAMEWORK), -framework $(fmw) )

LIBFTA			= ./libft \

IMAGE 			= ./libraries \

DEBUG			= -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(IMAGE) $(OBJ)
	@echo "${vertfonce}Compiling $@ ...${neutre}\c"
	@$(CC) $(CFLAG) -o $(NAME) $(OBJ) $(LFLAG)
	@echo "${vertclair}DONE${neutre}"

$(OBJ_PATH)/%.o: %.c $(HEADER) $(LIBFTA)
	@mkdir -p $(OBJ_PATH)
	@echo "${violetfonce}Creating $@ ...${neutre}\c"
	@$(CC) $(CFLAG) -o $@ -c $< $(IFLAG)
	@echo "${rose}DONE${neutre}"

$(IMAGE): FORCE
	@if [ -d "./libraries" ]; then \
		echo "${vertfonce}SDL2 is installed.${neutre}"; \
	else \
		make image; \
	fi

$(LIBFTA): FORCE
	@make -C libft

FORCE:

clean :
	@echo "${rouge}Cleaning the project ...${neutre}\c"
	@make clean -C libft
	@rm -rf $(OBJ_PATH)
	@echo "${rose}DONE${neutre}"

fclean : clean
	@echo "${rouge}Fcleaning the project ...${neutre}\c"
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "${rose}DONE${neutre}"

re : fclean all

relib:
	@make re -C libft

resdl:
	@echo "${cyanfonce}Deleting ./libraries ...${neutre}\c"
	@rm -rf ./libraries
	@echo "${cyanclair}DONE${neutre}"
	@make image

image: libraries/lib/libSDL2_mixer.dylib

libraries/lib/libSDL2_mixer.dylib: libraries/lib/libSDL2_ttf.dylib
	@echo "${cyanfonce}Installing SDL2_mixer ...${neutre}\c"
	@mkdir -p libraries
	@curl -s https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz -o libraries/SDL2_mixer-2.0.4.tar.gz
	@tar -xf ./libraries/SDL2_mixer-2.0.4.tar.gz -C libraries
	@cd libraries/SDL2_mixer-2.0.4 ; ./configure --prefix=$(shell pwd)/libraries
	@make -C ./libraries/SDL2_mixer-2.0.4
	@make -C ./libraries/SDL2_mixer-2.0.4 install
	@echo "${cyanclair}DONE${neutre}"

libraries/lib/libSDL2_ttf.dylib: libraries/lib/libfreetype.dylib
	@echo "${cyanfonce}Installing SDL2_ttf ...${neutre}\c"
	@mkdir -p libraries
	@curl -s https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.tar.gz -o libraries/SDL2_ttf-2.0.15.tar.gz
	@tar -xf ./libraries/SDL2_ttf-2.0.15.tar.gz -C libraries
	@cd libraries/SDL2_ttf-2.0.15 ; FT2_CONFIG=$(shell pwd)/libraries/bin/freetype-config ./configure --prefix=$(shell pwd)/libraries
	@make -C ./libraries/SDL2_ttf-2.0.15
	@make -C ./libraries/SDL2_ttf-2.0.15 install
	@echo "${cyanclair}DONE${neutre}"

libraries/lib/libfreetype.dylib: libraries/lib/libSDL2.dylib
	@echo "${cyanfonce}Installing freetype2 ...${neutre}\c"
	@mkdir -p libraries
	@curl -s https://download.savannah.gnu.org/releases/freetype/freetype-2.4.11.tar.gz -Lo libraries/freetype-2.4.11.tar.gz
	@tar -xf ./libraries/freetype-2.4.11.tar.gz -C libraries
	@cd libraries/freetype-2.4.11 ; ./configure --prefix=$(shell pwd)/libraries
	@make -C ./libraries/freetype-2.4.11
	@make -C ./libraries/freetype-2.4.11 install
	@echo "${cyanclair}DONE${neutre}"


libraries/lib/libSDL2.dylib:
	@echo "${cyanfonce}Installing SDL2 ...${neutre}\c"
	@mkdir -p libraries
	@curl -s https://www.libsdl.org/release/SDL2-2.0.8.tar.gz -o libraries/SDL2-2.0.8.tar.gz
	@tar -xf libraries/SDL2-2.0.8.tar.gz -C libraries
	@cd libraries/SDL2-2.0.8 ; ./configure --prefix=$(shell pwd)/libraries
	@make -C ./libraries/SDL2-2.0.8
	@make -C ./libraries/SDL2-2.0.8 install
	@echo "${cyanclair}DONE${neutre}"

.PHONY: all clean fclean re image
