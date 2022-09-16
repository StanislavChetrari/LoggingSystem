if [ ! -d Builds ]; then
	mkdir Builds
fi

cmake -S . -B Builds -DBUILD_SHARED_LIBS=ON

