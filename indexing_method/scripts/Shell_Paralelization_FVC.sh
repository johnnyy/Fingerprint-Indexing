#!/bin/bash



#$1 == Pasta da análise
#$2 == Pasta de saída


function Process(){

	# $1 = Pasta para analise
	# $2 = Pasta individual da execucao
	# $3 = Arquivos com as pessoas de cada processo
	# $4 = Pasta passada como paramentro igual a $2 da aplicacao geral


	count_search=0
	count_index=0
	while read person
		do
			####	
				ls $1$person/*.bmp > "$2/arquivo1.txt"
				while read line1 
					do 

						#line=$(echo "$line1" | sed "s/bmp/wsq/")
						line="$line1.wsq"
						./mat2wsq "$line1"
						name_=$(echo "$line" | sed "s|$1$person/||" )
						./NBIS/mindtct  -m1 $line $line


						#pwd
						value=$(./NBIS/nfiq "$line")
						echo "$name_ $value"
						echo "$name_,$value" >> "$2/quality.csv"

					    best_full_name=$line


							#value_search=$(cat $1/NFIQ.csv | grep $name_ | tail -c2)
						ls $1$person/p/*.bmp > "$2/arquivo5.txt"
						while read line2
							do

								line12="$line2.wsq"
								#line12=$(echo "$line2" | sed "s/bmp/wsq/")
								./mat2wsq "$line2"
								name_12=$(echo "$line12" | sed "s|$1$person/||" )

								search=$name_12
								search_full_name=$line12
							#echo $search $value_search
							
							#new=$(echo "$search_full_name" | sed 's/wsq/PNG/')
								./NBIS/mindtct  -m1 "$search_full_name" "$search_full_name"

								echo "$search_full_name.xyt" >> $2/finger_search.txt

								value=$(./NBIS/nfiq "$line12")
								echo "$name_12 $value"
								echo "$name_12,$value" >> "$2/quality.csv"
							#echo "$search.xyt $new"
							#java -cp ../jnbis/jnbis-develop/target/classes/:.  Wsq2Png  "$search_full_name" "$1$person/"
						
								count_search=$(($count_search + 1))
							done < $2/arquivo5.txt
							
						rm $1/$person/p/*.brw
						rm $1/$person/p/*.dm
						rm $1/$person/p/*.hcm
						rm $1/$person/p/*.lcm
						rm $1/$person/p/*.lfm
					#	rm $1/$person/*.min
						rm $1/$person/p/*.qm

					
		
					./NBIS/mindtct  -m1 "$best_full_name" "$best_full_name"

					echo "$best_full_name.xyt" >> $2/finger_index.txt 
					#echo "$best.xyt" "$new"
					echo $best $value_best "index"
					count_index=$(($count_index + 1))
				done < $2/arquivo1.txt

				#java -cp ../jnbis/jnbis-develop/target/classes/:.  Wsq2Png  "$best_full_name" "$1$person/"
				#new=$(echo "$best_full_name" | sed 's/wsq/PNG/')
				
	#		done
			rm $1/$person/*.brw
			rm $1/$person/*.dm
			rm $1/$person/*.hcm
			rm $1/$person/*.lcm
			rm $1/$person/*.lfm
		#	rm $1/$person/*.min
			rm $1/$person/*.qm
	#	fi
	done < $3
			
		#done
	#done
	rm $2/arquivo1.txt

	
	Index $2 $count_index $4&
	Search $2 $count_search $4
	
}


#------------------------- Inicio -----------------------


echo "Preparate partial files..."
rm -r $2/*
mkdir $2partial_data  $2Word_Index $2Word_Search
#rm -r $2partial_data/* 

count_index=0
count_search=0
ls $1 -1 > $2/persons.txt
num_total=$(cat $2/persons.txt | wc -l)
num_partial=$(($(cat $2/persons.txt | wc -l)/8))
resto=$(($(cat $2/persons.txt | wc -l)%8))
last=$(($resto + $num_partial))
echo $num_total
echo $num_partial
echo $last

begin=1
maxi=$num_partial

for ((i = 0; i < 32; i++)); do

	mkdir $2partial_data/exec$i
	mkdir $2partial_data/exec$i/Word_Search
	mkdir $2partial_data/exec$i/Word_Index
	mkdir $2partial_data/exec$i/Vetor_Search
	mkdir $2partial_data/exec$i/Vetor_Index
	echo $begin $maxi
	#echo "sed -n ' $begin , $maxi p' $2teste.txt > $2partial_data/exec$i/files.txt"
	sed -n "$begin, $maxi p" $2persons.txt > $2partial_data/exec$i/files.txt 
	if [ "$i" -lt "30" ]; then
		begin=$(($begin + $num_partial))
		maxi=$(($maxi + $num_partial))
	
	else 
		begin=$(($begin + $num_partial))
		maxi=$(($maxi + $last))
	fi

	
	cat /dev/null > $2partial_data/exec$i/finger_index.txt
	cat /dev/null > $2partial_data/exec$i/finger_search.txt
	Process $1  $2partial_data/exec$i/ $2partial_data/exec$i/files.txt  $2  &


done

wait
touch $2/quality.csv
touch $2/finger_search.txt
touch $2/finger_index.txt

for ((i = 0; i < 32; i++)); do
	
	cat $2partial_data/exec$i/quality.csv >> $2/quality.csv 
	cat $2partial_data/exec$i/finger_index.txt >> $2/finger_index.txt
	cat $2partial_data/exec$i/finger_search.txt >> $2/finger_search.txt 

	

done

echo "Generating Fingerprints for Search and Index..."





