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

NAME			= rt

HEADER 			= $(shell find Includes -type f) $(shell find libraries/include -type f 2>/dev/null || true)

SRC_PATH		= $(shell find Sources -type d)

INC_PATH 		= $(shell find Includes -type d) $(shell find libft -type d) $(shell find libraries/include -type d 2>/dev/null || true) \

OBJ_PATH		= OBJ

SRC				=	main.c										\
					flag_parameter.c							\
					flag_help.c									\
					createpxl.c									\
					data.c										\
					filldata.c									\
					rot.c										\
					tga_main.c									\
					uncompress.c								\
					init.c										\
					init_sdl.c									\
					icon.c										\
					init_font.c									\
					init_cam.c									\
					init_cam_ext.c								\
					rot_init_cam.c								\
					ask_screenshot.c							\
					mutex.c										\
					check.c										\
					loading.c									\
					quit.c										\
					clear.c										\
					clear_texture.c								\
					clear_thread.c								\
					get_point.c									\
					parse.c										\
					header.c									\
					parse_texture.c								\
					fill_obj.c									\
					fill_other_obj.c							\
					type_tool.c									\
					camera.c									\
					object.c									\
					light.c										\
					files.c										\
					find.c										\
					find_normal.c								\
					color.c										\
					texture.c									\
					find_size.c									\
					ray.c										\
					setup_ray_effect.c							\
					input.c										\
					input_tool.c								\
					screen.c									\
					single_screen.c								\
					loop.c										\
					show_button.c								\
					create_thread.c								\
					create_thread2.c							\
					create_thread3.c							\
					create_thread_aux.c							\
					init_thread.c								\
					init_thread_obj.c							\
					init_thread_txt.c							\
					quality.c									\
					thread_function.c							\
					thread_load.c								\
					pthread_timedjoin.c							\
					shape.c										\
					extra_shape.c								\
					box.c										\
					cone.c										\
					cylinder.c									\
					tolight.c									\
					type_of_light.c								\
					init_vec.c									\
					mat_vec2.c									\
					math_vec_float.c							\
					float.c										\
					math_vec.c									\
					vec_tool.c									\
					normal_map.c								\
					switch_vec.c								\
					ang.c										\
					reflexion.c									\
					refraction.c								\
					rot_cam.c									\
					rot_matrice.c								\
					move_type.c									\
					move_triangle.c								\
					move_obj.c									\
					light_cursor.c								\
					input_obj.c									\
					input_light.c								\
					input_move_cam.c							\
					input_textures.c							\
					screenshot.c								\
					screenshot_bmp.c							\
					screenshot_framed.c							\
					resize_screen.c								\
					create_type.c								\
					shape_cartoon.c								\
					antialiasing.c								\
					filters.c									\
					filters_2.c									\
					check_filter.c								\
					cartoon.c									\
					input_hud.c									\
					menu_texture.c								\
					input_filter.c								\
					damier.c									\
					create_specular.c							\
					find_dir.c									\
					diapo.c										\
					mix_color.c									\
					draw_rect.c									\
					perlin.c									\
					perlin2.c									\
					perlin_colors.c								\
					perlin_init.c								\
					perlin_gen.c								\
					preview.c									\
					mini_rt.c									\
					draw_circle.c								\
					fade_color.c								\
					color_picker.c								\
					read_input.c								\
					filter_interface.c							\
					button_normals.c							\
					button_show.c								\
					button_quality.c							\
					button_aa.c									\
					button_stand.c								\
					button_diapo.c								\
					button_refresh.c							\
					button_advance.c							\
					button_slider.c								\
					click_button.c								\
					init_slider.c								\
					preview_2.c									\
					mini_rt_specular.c							\
					fade_color_2.c								\
					switchcolor.c								\
					input_move_cam_2.c							\
					input_move_cam_3.c							\
					input_2.c									\
					loop_draw.c									\
					loop_draw2.c								\
					loop_extra.c								\
					button_shadow.c								\



OBJ 			= $(addprefix $(OBJ_PATH)/, $(SRC:%.c=%.o))

LIBS 			= SDL2 ft

LIB_PATH 		= ./libft \
				  ./libraries/lib \

FRAMEWORK 		= OpenGL AppKit

CC 				= gcc -g -std=c99

vpath %.c $(foreach dir, $(SRC_PATH), $(dir):)

IFLAG			= $(foreach dir, $(INC_PATH), -I$(dir) )

CFLAG 			= -Wall -Wextra -Werror -pthread -Ofast -flto -march=native -g3

LFLAG 			= $(foreach dir, $(LIB_PATH), -L $(dir) ) $(foreach lib, $(LIBS), -l$(lib) ) $(foreach fmw, $(FRAMEWORK), -framework $(fmw) )

LIBFTA			= ./libft \

IMAGE 			= ./libraries \

DEBUG			= -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(IMAGE) $(OBJ)
	@echo "${vertfonce}Compiling $@ ...${neutre}\c"
	@$(CC) $(CFLAG) -g -o $(NAME) $(OBJ) $(LFLAG) $(DEBUG)
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

image: libraries/lib/libSDL2.dylib

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
