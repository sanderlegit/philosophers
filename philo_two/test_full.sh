#make re
#if [ -z "$5" ]; then
	#RES=$(./philo_two $1 $2 $3 $4)
#else
	RES=$(./philo_two $1 $2 $3 $4 $5)
#fi

echo "$RES"

#for i in {1..$(($5))}; do
for ((i=1; i<=$1; i++)); do
	echo -n "$i ate "
	echo "$RES" | grep "$i is eating" | wc -l
done
