
#!/bin/bash
# Basic while loop

#Generate random numbers in Python using [np.random.randint(10**7) for i in range(20)]
seed_array=(6780264)

# RUN SINGLE TIMEPOINT
#test_name=("P0_D1")
#test_name=("P45_D1") #deg mild 
#test_name=("P63_D1") #deg severe 
test_name=("P112_D1") # deg extreme 

counter=1
for seed in "${seed_array[@]}"; do
    python3 create_cpg.py $seed $test_name
    #echo $seed
    echo $counter
    ((counter++))
done

echo All done