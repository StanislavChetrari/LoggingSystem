if [ $# -eq 0 ]
	then
		nix-shell -p gcc cmake
	else
		nix-shell -p gcc cmake --command "$@"
fi
