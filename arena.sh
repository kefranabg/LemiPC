if [ "null$1" == "null" ]
then
    echo "USAGE: ./arena.sh [FILE]"
else
    while read player
    do
	./lemipc $player &
    done < $1
    ./graphic &
fi
