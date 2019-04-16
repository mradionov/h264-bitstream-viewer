dist/h264bitstream.js: h264bistream-wrapper.cpp h264bitstream/.libs/libh264bitstream.so.0.0.0
	emcc \
		--bind \
		-O2  \
		-s ASSERTIONS=1 \
		-s EXTRA_EXPORTED_RUNTIME_METHODS='["setValue"]' \
		-Ih264bitstream/ \
		-o $@ \
		$^

h264bitstream/.libs/libh264bitstream.so.0.0.0:
	cd h264bitstream \
		&& emconfigure ./configure \
		&& emmake make
