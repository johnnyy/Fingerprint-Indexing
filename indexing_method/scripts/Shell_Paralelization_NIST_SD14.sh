#!/bin/bash



#$1 == Pasta da análise
#$2 == Pasta de saída
n_proc=8

function Process(){

	# $1 = Pasta para analise
	# $2 = Pasta individual da execucao
	# $3   = Inicio
	# $4 = Fim
	# $5 = Pasta passada como parametro igual a $2 da aplicacao geral

  for ((i=$3; i<=$4; i++)); do
    if [ "$i" -lt "676" ] ; then
      cd=1
    elif [ "$i" -lt "1351" ] ; then
      cd=2
    elif [ "$i" -lt "2026" ] ; then
      cd=3
    else
      cd=4

    fi


    fold=$(python get_folder.py $i $cd)
    path="$1CD$cd/data/mfcp2_$fold/$(ls $1CD$cd/data/mfcp2_$fold/ | grep "crd_[0]*$i\$")"
    ls $path -1 | grep "^[f][0-9]*.wsq$" >$2/arquivo5.txt
		while read line2
		do
			./NBIS/mindtct  -m1 $path/$line2 $path/$line2
			value=$(./NBIS/nfiq "$path/$line2")
      echo "$line2 $value"
      echo "$line2,$value" >> "$2/quality.csv"
      echo "$5Minutia_Index/$line2.xyt" >> $2/finger_index.txt
      mv "$path/$line2.xyt" "$5Minutia_Index/$line2.xyt"


    done < $2/arquivo5.txt

    if [ "$i" -gt "242" ] ; then
      ls $path -1 | grep "^[s][0-9]*.wsq$" >$2/arquivo5.txt
      while read line2
      do
        number=$(echo $line2 | cut -d 's' -f 2 | cut -d '.' -f 1)
        if [ "$number" -gt "24299" ] ; then
          ./NBIS/mindtct  -m1 $path/$line2 $path/$line2
          value=$(./NBIS/nfiq "$path/$line2")
          echo "$line2 $value"
          echo "$line2,$value" >> "$2/quality.csv"
          echo "$5Minutia_Search/$line2.xyt" >> $2/finger_search.txt
          mv "$path/$line2.xyt" "$5Minutia_Search/$line2.xyt"

        fi

      done < $2/arquivo5.txt
    fi





    rm $path/*.brw
    rm $path/*.dm
    rm $path/*.hcm
    rm $path/*.lcm
    rm $path/*.lfm
   	rm $path/*.min
    rm $path/*.qm

  done

	
}


#------------------------- Inicio -----------------------


echo "Preparate partial files..."
rm -r $2/*
mkdir $2partial_data  $2Minutia_Index $2Minutia_Search
#rm -r $2partial_data/* 

count_index=0
count_search=0
num_total=2700
num_partial=$(($num_total/$n_proc))
resto=$(($num_total%$n_proc))
last=$(($resto + $num_partial))
echo $num_total
echo $num_partial
echo $last


for ((i = 0; i < $n_proc; i++)); do

	mkdir $2partial_data/exec$i

	#echo "sed -n ' $begin , $maxi p' $2teste.txt > $2partial_data/exec$i/files.txt"
	#sed -n "$begin, $maxi p" $2persons.txt > $2partial_data/exec$i/files.txt


	if [ "$i" -lt "$(($n_proc -1))" ]; then
    begin=$(($i*$num_partial+ 1))
    maxi=$(($(( $i + 1))*$num_partial ))


	else
		begin=$(($i*$num_partial + 1))
		maxi=$(($begin + $last - 1))
	fi

  echo "$begin, $maxi"

	cat /dev/null > $2partial_data/exec$i/finger_index.txt
	cat /dev/null > $2partial_data/exec$i/finger_search.txt
	Process $1  $2partial_data/exec$i/ $begin $maxi  $2 &


done

wait
touch $2/quality.csv
touch $2/finger_search.txt
touch $2/finger_index.txt

for ((i = 0; i < $n_proc; i++)); do
	#cat $2partial_data/exec$i/quality.csv >> $2/quality.csv
	cat $2partial_data/exec$i/finger_index.txt >> $2/finger_index.txt
	cat $2partial_data/exec$i/finger_search.txt >> $2/finger_search.txt



done

echo "Generating Fingerprints for Search and Index..."


