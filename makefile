# This makefile is useful feature.
# It gives you possibility to control project building
# inside the source dir not the "build".

BUILD_DIR := build
PROJECT_NAME := simulation

# default
.PHONY: all
all: build compile

# build the project
build:
	@$(MAKE) building-rules

.PHONY: rebuild
rebuild: building-rules

.PHONY: building-rules
building-rules: rm-build
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) ; cmake ..

# compile the project
.PHONY: compile
compile:
	@$(MAKE) --no-print-directory -C $(BUILD_DIR)

# running
.PHONY: run
run: $(BUILD_DIR)/$(PROJECT_NAME)
	$(BUILD_DIR)/$(PROJECT_NAME)

.PHONY: test
test:
	@cd $(BUILD_DIR) ; $(MAKE) --no-print-directory test

# cleaning
.PHONY: rm-build
rm-build:
	@rm -rf $(BUILD_DIR)

