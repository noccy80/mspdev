LIBINCL ?= *.h

install:
ifeq ($(DEST),)
	echo "You must define DEST before installing"
	exit 1
endif
	test -d $(DEST)/include || mkdir $(DEST)/include
	test -d $(DEST)/lib || mkdir $(DEST)/lib
	cp -R $(LIBINCL) $(DEST)/include
	cp $(TARGET).a $(DEST)/lib
	printf "Installed"
