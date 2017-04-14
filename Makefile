libwcwidth-icons.so: wcwidth-icons.c
	$(CC) -shared -ldl -fPIC -Wl,-z,defs -Wl,--as-needed -o $@ $^
