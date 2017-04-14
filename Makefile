LIBDIR  ?= /usr/lib
CFLAGS  += -ldl
LDFLAGS += -Wl,-z,defs -Wl,--as-needed

libwcwidth-icons.so: wcwidth-icons.c
	$(CC) $(CFLAGS) $(LDFLAGS) -Wl,-soname,libwcwidth-icons.so -shared -fPIC -o $@ $^

clean:
	rm -f *.so

install: libwcwidth-icons.so
	install -D libwcwidth-icons.so $(DESTDIR)$(LIBDIR)/libwcwidth-icons.so
