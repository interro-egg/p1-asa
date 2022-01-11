#!/bin/sh

cd "${0%/*}" # go to script directory
set -e # exit if any command fails

CSV="$1"

if [ "$CSV" = "" ]; then
	CSV="prob1-$(date +%s).csv"
fi

echo "n,command,mean,stddev,median,user,system,min,max" > $CSV

test() {
	echo "Testing with n = $1"
	local VEC=$(python gen_vector.py $1)
	echo "1" > in.txt
	echo "$VEC" >> in.txt
	hyperfine "../project < in.txt" --warmup 10 --export-csv tmp.csv &>/dev/null
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

test 100000