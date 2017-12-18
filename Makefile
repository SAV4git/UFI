.PHONY: clean All

All:
	@echo "----------Building project:[ UFI_Constructor - Debug ]----------"
	@cd "UFI_Constructor" && "$(MAKE)" -f  "UFI_Constructor.mk"
clean:
	@echo "----------Cleaning project:[ UFI_Constructor - Debug ]----------"
	@cd "UFI_Constructor" && "$(MAKE)" -f  "UFI_Constructor.mk" clean
