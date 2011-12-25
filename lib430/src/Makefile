all: libhal libcomm

libhal:
	@echo "Building libhal ..."
	@cd libhal; $(MAKE) $(MFLAGS) lib; cd ..

libcomm:
	@echo "Building libcomm ..."
	@cd libcomm; $(MAKE) $(MFLAGS) lib; cd ..

clean: force
	@cd libcc1101; $(MAKE) $(MFLAGS) clean; cd ..
	@cd libairproto; $(MAKE) $(MFLAGS) clean; cd ..

force:
	@true
	
install:
	@echo "No install yet. Please do it manually for now :s"

uninstall:
	@echo "No uninstall yet. Please do it manually for now :s"

dist:
	@echo "No dist yet. Please do it manually for now :s"
