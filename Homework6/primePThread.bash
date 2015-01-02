for ((i = 1; i <=10; i++))
do
	echo "$i proccesses for 500000000"
	primeMProc -q -c $i -m 500000000
done

for ((i = 1; i <=10; i++))
do
	echo "$i proccesses for 1000000000"
	primeMProc -q -c $i -m 1000000000
done

for ((i = 1; i <=10; i++))
do
	echo "$i proccesses for 1500000000"
	primeMProc -q -c $i -m 1500000000
done

for ((i = 1; i <=10; i++))
do
	echo "$i proccesses for 2000000000"
	primeMProc -q -c $i -m 2000000000
done

for ((i = 1; i <=10; i++))
do
	echo "$i proccesses for 2500000000"
	primeMProc -q -c $i -m 2500000000
done

for ((i = 1; i <=10; i++))
do
	echo "$i proccesses for 3000000000"
	primeMProc -q -c $i -m 3000000000
done

for ((i = 1; i <=10; i++))
do
	echo "$i proccesses for 3500000000"
	primeMProc -q -c $i -m 3500000000
done

for ((i = 1; i <=10; i++))
do
	echo "$i proccesses for 4000000000"
	primeMProc -q -c $i -m 4000000000
done

for ((i = 1; i <=10; i++))
do
	echo "$i proccesses for UINTMAX"
	primeMProc -q -c $i
done