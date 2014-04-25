#!/bin/bash

function play()
{
	echo "+----------------------------------------------+";
	echo "Start FM transmission on $frequence MHz";
	echo "+----------------------------------------------+";

	for musique in `ls "$dossier"*.mp3 "$dossier"*.wav "$dossier"*.flac "$dossier"*.mov $option 2>/dev/null`
	do
		echo "";
		echo "--> Now playing ${musique##*/}";
		ffmpeg -v 0 -i $musique -f s16le -ar 22.05k -ac 1 - | sudo ./pifm - "$frequence";
	done
	echo "";
	echo "+----------------------------------------------+";
	echo "End of transmission ...";
	echo "+----------------------------------------------+";
}

frequence="104.2";
dossier="/home/"`whoami`"/.pifm-improved/";
option="";

if [ ! -e "$dossier" ]
then
	sudo mkdir "$dossier";
fi

#analyse et traitement des paramètres
while [ $# -ne 0 ]
do
	if [ "$1" = "-d" ]
	then
		if [ -e "$2" -a -d "$2" ]
		then
			dossier="$2";
			shift 2;
		else
			echo "Le dossier \"$2\" n'existe pas :-(";
			exit 2;
		fi
	elif [ "$1" = "-r" ]
	then
		option="-R";
		shift 1;
	elif [ "$1" = "-f" ]
	then
		if [ $(echo "$2 - 80" | bc | tr -d .) -ge 0 -a $(echo "108 - $1" | bc | tr -d .) -ge 0 ]
		then
			frequence="$2";
			shift 2;
		else
			echo "La fréquence n'est pas valide (90 <= f <= 108) :-(";
			exit 3;
		fi
	else
		#if [ "$1" != "" ]
		#then
			echo "Le paramètre \"$1\" est inconnu :-(";
			exit 1;
		#fi
	fi
done

play;

exit 0;
