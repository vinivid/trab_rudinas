count=$1

for i in {1..1}
do 
	for j in {2..12}
	do 
		./koala < ./casos_teste/c$count.in >> ./fb_100.dat
		((count++))
	done
done
