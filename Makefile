LIBDIR ?= /usr/lib

libwcwidth-icons.so: wcwidth-icons.c
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -ldl -fPIC -Wl,-z,defs -Wl,--as-needed -o $@ $^

clean:
	rm -f *.so

install: libwcwidth-icons.so
	install -D libwcwidth-icons.so $(DESTDIR)$(LIBDIR)/libwcwidth-icons.so
