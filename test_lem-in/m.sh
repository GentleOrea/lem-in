for map in `find ./maps`
do
	./lem-in.sh $map
	echo $map
done
