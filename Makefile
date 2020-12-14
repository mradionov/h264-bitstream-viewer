dist/h264bitstream.js: \
	src/wrapper/h264bitstream-wrapper.cpp \
	src/wrapper/h264naked-print.cpp \
	src/wrapper/reader.cpp \
	h264bitstream/.libs/libh264bitstream.so.0.0.0
	mkdir dist
	emcc \
		--bind \
		-O2  \
		-s ASSERTIONS=1 \
		-s EXTRA_EXPORTED_RUNTIME_METHODS='["setValue"]' \
		-Ih264bitstream/ \
		-Isrc/wrapper/ \
		-o $@ \
		$^

h264bitstream/.libs/libh264bitstream.so.0.0.0:
	cd h264bitstream && \
		autoreconf -i && \
 		emconfigure ./configure && \
		emmake make CFLAGS=-DHAVE_SEI
