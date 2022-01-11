#!/bin/sh

cd "${0%/*}" # go to script directory
set -e # exit if any command fails

csv="$1"

if [ "$csv" = "" ]; then
	csv="prob1-$(date +%s).csv"
fi

echo "n,command,mean,stddev,median,user,system,min,max" > $csv

test() {
	echo "Testing with n = $1"
	local VEC=$(python gen_vector.py $1)
	echo "1" > in.txt
	echo "$VEC" >> in.txt
	hyperfine "../project < in.txt" --warmup 10 --export-csv tmp.csv &>/dev/null
	echo -n $1, >> $csv
	grep ./project tmp.csv >> $csv # remove header
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

test 100000