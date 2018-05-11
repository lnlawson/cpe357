#!/bin/bash
for testInput in *.in; do
   # Strip off the file extension, i.e., the ".in"
   name=${testInput%.in}

   # make the expect file
   $1 < $testInput 1> test.expect 2> test.expect-err $2 $3 $4 $5

   # Run the test
   ./a.out < $testInput 1> test.out 2> test.out-err $2 $3 $4 $5

   # diff the results
   echo "diffs for $name"
   diff test.out test.expect
   echo "diffs for $name.err"
   diff test.out-err test.expect-err
done
