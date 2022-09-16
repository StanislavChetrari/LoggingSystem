rm -r Bin

if [ ! -d Bin ]; then
	mkdir Bin
fi

cmake --install Builds --prefix Bin

