BUILDLIBS=libcore libhal libcomm libsound libmidi liblcd

all: $(BUILDLIBS)

libcore: force
	@cd libcore; $(MAKE) $(MFLAGS) lib; cd ..

libsound: force
	@cd libsound; $(MAKE) $(MFLAGS) lib; cd ..

libmidi: force
	@cd libmidi; $(MAKE) $(MFLAGS) lib; cd ..

libhal: force
	@cd libhal; $(MAKE) $(MFLAGS) lib; cd ..

libcomm: force
	@cd libcomm; $(MAKE) $(MFLAGS) lib; cd ..

liblcd: force
	@cd liblcd; $(MAKE) $(MFLAGS) lib; cd ..

clean: force
	@cd libhal; $(MAKE) $(MFLAGS) clean; cd ..
	@cd libcomm; $(MAKE) $(MFLAGS) clean; cd ..
	@cd libcore; $(MAKE) $(MFLAGS) clean; cd ..
	@cd libsound; $(MAKE) $(MFLAGS) clean; cd ..
	@cd libmidi; $(MAKE) $(MFLAGS) clean; cd ..

force:
	@true

install: $(BUILDLIBS)
	@echo "No install yet. Please do it manually for now :s"

uninstall: $(BUILDLIBS)
	@echo "No uninstall yet. Please do it manually for now :s"

dist:
	@echo "No dist yet. Please do it manually for now :s"
