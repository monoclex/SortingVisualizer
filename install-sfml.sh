echo "You may need to run this script with sudo!"

. /etc/os-release

if [[ $NAME == "Gentoo" ]]
then
	emerge -av media-libs/libsfml
elif [[ $NAME == "Debian" || $NAME = "Ubuntu" ]]
then
	apt-get install libsfml-dev
else
	echo "Unknown distro"
	exit 1
fi
