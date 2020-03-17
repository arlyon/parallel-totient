./run

execute() {
  FILE=results/${1}-${2}.log
  if [ ! -f "$FILE" ]; then
    ./run -b ${FILE} totient_openmp -p -t ${1} 1 ${2}
  fi
}

export -f execute
echo -e {1..64}"\n"{15000,30000,100000}"\n" | awk '{$1=$1;print}' | awk 'NF' | parallel -j 8 -n 2 execute
