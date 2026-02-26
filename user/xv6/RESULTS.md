Assigmnent 3 Results Write-Up

------------------------------------------------------------------
Setup:
Three child processes created using 'fork()', each with a different number of tickets called 'settickets()'

------------------------------------------------------------------
Workload:
Test program 'testratio' was created to evaluate CPU time distribution. The settickets() process was called to execute CPU work for a fixed amount of time. Process A allocated 10 tickets, Process B allocated 20 tickets, and Process C allocated 40 tickets, all with the same duration

------------------------------------------------------------------
RESULTS: 

$ testlottery
PASS: settickets validation
testlottery: done

$ testratio
testratio: ms=2000 tickets=10,20,40
pid 4 tickets 10 units 30466
pid 5 tickets 20 units 52939
pid 6 tickets 40 units 63880
testratio: done

$ testratio 10000
testratio: ms=10000 tickets=10,20,40
pid 13 tickets 10 units 156310
pid 14 tickets 20 units 262200
pid 15 tickets 40 units 319658
testratio: done

------------------------------------------------------------------
As execution times become longer, the distribution converges due to the randomized nature