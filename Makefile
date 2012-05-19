ifeq ($(MAKECMDGOALS),)
MAKECMDGOALS = all
endif

$(MAKECMDGOALS):
	make -C pvr $@
