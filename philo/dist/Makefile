# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welee <welee@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/07 04:39:46 by welee             #+#    #+#              #
#    Updated: 2024/09/18 17:04:32 by welee            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Directory Variables -------------------------------------------------------- #
SRCS_DIR = srcs
OBJS_DIR = objs
INCS_DIR = includes
TEST_DIR = tests
DIST_DIR = dist
LIBS_DIR = libs
BINS_DIR = bin
DOCS_DIR = docs
# ---------------------------------------------------------------------------- #

# Library Variables ---------------------------------------------------------- #
# ---------------------------------------------------------------------------- #

# Macro Variables ------------------------------------------------------------ #
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCS_DIR)
LIBC = ar rcs
RM = rm -f
MKDIR = mkdir -p
MAKE = make
CD = cd
CP = cp -r
ECHO = echo
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	SED := sed -i
else ifeq ($(UNAME_S),Darwin)
	SED := sed -i ''
else
	$(error Unsupported OS)
endif
WHOAMI = $(shell whoami)
# ---------------------------------------------------------------------------- #

# Tools Variables ------------------------------------------------------------ #
NORM = norminette
NORM_FLAGS = -R CheckForbiddenSourceHeader -R CheckDefine

DOXYGEN = doxygen
DOXYGEN_CONF = Doxyfile
# ---------------------------------------------------------------------------- #

# Rules Definitions ---------------------------------------------------------- #
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@$(ECHO) "\033[32m$(NAME) compiled\033[0m"

$(BINS_DIR):
	$(MKDIR) $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCS)
	$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -I $(INCS_DIR) -c -o $@ $<
	@$(ECHO) "\033[33m$@\033[0m"

clean:
	$(RM) $(OBJS)
	@$(ECHO) "\033[31m$(NAME) object files removed\033[0m"

fclean: clean
	$(RM) $(NAME)
	@$(ECHO) "\033[31m$(NAME) removed\033[0m"

re: fclean all

norm:
	$(NORM) $(NORM_FLAGS) $(SRCS_DIR) $(INCLUDES_DIR)
	@$(ECHO) "\033[32mNorm check completed\033[0m"

dist: fclean
	$(MKDIR) $(DIST_DIR)
	$(CP) $(SRCS_DIR) $(INCS_DIR) $(DIST_DIR)
	$(CP) Makefile $(DIST_DIR)
	$(SED) 's|^NAME = $$(BINS_DIR)/philo$$|NAME = philo|' $(DIST_DIR)/Makefile
	$(SED) '/^\$$(NAME):/ s/ | $$(BINS_DIR)//' $(DIST_DIR)/Makefile

.PHONY: all clean fclean re norm tests dist
# ---------------------------------------------------------------------------- #
