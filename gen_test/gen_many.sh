qtd=$1
range=$2
por=$3
count=$4

for i in {1..qtd}
do 
	for j in {2..12}
	do 
		./rann $j $range $por > ../casos_teste/c$count.in
		((count++))
	done
done
