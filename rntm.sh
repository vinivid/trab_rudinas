count=$1

for i in {1..1}
do 
	for j in {2..12}
	do 
		./tsp_oti < ./casos_teste/c$count.in >> ./held.dat
		((count++))
	done
done
