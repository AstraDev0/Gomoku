##
## EPITECH PROJECT, 2023
## B-PDG-300-BER-3-1-PDGD06-matthis.brocheton
## File description:
## Makefile
##

BUILD_DIR = build

name = pbrain-gomoku-ai

all: 
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..
	$(MAKE) -C $(BUILD_DIR)
	cp $(BUILD_DIR)/$(name) .

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(name)

fclean: clean

re: fclean all

.PHONY: all clean fclean re tests_run