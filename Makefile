ifeq ($(MAKECMDGOALS),)
MAKECMDGOALS = all
endif

$(MAKECMDGOALS):
	$(MAKE) -C pvr $@
