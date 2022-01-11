#!/bin/sh

# you probably want to call this with `time ./prob2.sh [custom_results_csv] [custom_exe] && date`

cd "${0%/*}" # go to script directory
set -e # exit if any command fails

CSV="${1:-prob2-$(date +%s).csv}" # arg 1 with default value
EXE="${2:-../project}" # arg 2 with default value


if [ ! -f "$EXE" ]; then
	echo "Executable (arg #2, defaults to ../project) does not exist!"
	echo -e "\tFile '$EXE' not found"
	exit 1
fi

echo "n,command,mean,stddev,median,user,system,min,max" > $CSV

test() {
	echo "Testing with n = $1 (and n=m, both vectors the same)"
	local VEC=$(python gen_vector.py $1)
	echo "2" > in.txt
	echo "$VEC" >> in.txt
	echo "$VEC" >> in.txt
	hyperfine "$EXE < in.txt" --warmup 10 --export-csv tmp.csv &>/dev/null
	echo -n $1, >> $CSV
	grep ./project tmp.csv >> $CSV # remove header
}

for i in {10..99..1}; do
	test $i
done

for i in {100..999..10}; do
	test $i
done

for i in {1000..9999..100}; do
	test $i
done

for i in {10000..99999..1000}; do
	test $i
done

echo 100000

# for i in {100000..999999..10000}; do
#     test $i
# done

# for i in {1000000..10000000..100000}; do
#     test $i
# done