for ((i=0; i<=$2; i++)); do
	#../philo_one 4 410 200 200 > tmp.txt
	RES=$(../philo_one 4 410 200 200)
	echo "$RES" > tmp.txt
	tail -1 tmp.txt | awk '{print $1}' >> $1.txt
	echo -n "Test $i:" 
	sleep 2
	tail -1 $1.txt
done
