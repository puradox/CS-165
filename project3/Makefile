
default:
	$(MAKE) -C decode release
	$(MAKE) -C encode release
	-mv encode/LZ LZ
	-mv decode/EXPAND EXPAND

clean:
	$(MAKE) -C decode clean
	$(MAKE) -C encode clean
	-rm -f LZ
	-rm -f EXPAND
