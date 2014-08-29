#! /bin/bash
#$ -cwd 
echo "Running script to transform ppm files to png's"
i=0
while [ -s ./image$i.ppm ]
do
	pnmtopng image$i.ppm > image$i.png;
	echo generated image$i.png;
	i=$((i+1));
done
