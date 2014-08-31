#! /bin/bash
BASEDIR=$(dirname $0)
echo "Running script to transform ppm files to png's"
i=0
while [ -s $BASEDIR/sdfs/scene$i.sdf ]
do
	echo "rendering $i"
	$BASEDIR/raytracer $BASEDIR/sdfs/scene$i.sdf nogui
	echo "rendered $i"
	if [[ -s $BASEDIR/tmp/image$i.ppm ]]; then
		echo "converting $i"
		pnmtopng $BASEDIR/tmp/image$i.ppm > $BASEDIR/pngs/image$i.png;
		echo "generated $BASEDIR/pngs/image$i.png";
	fi
	i=$((i+1));
done