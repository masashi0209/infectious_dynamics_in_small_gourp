Thi is data set for Figure 2
Results of 10,000 Monte-Carlo simulations

Results of each iteration is listed as follows:
0 1 6 1 2 1

The first number shows the day that an infected individual appears in a group. 0 means an infected individual appears on a testing day. If it is 1, it means that an infected individual appears 1 day before the testing day.

The second number shows type of detection for infected individuals. 0 means detection by testing and 1 means detection by confirmation of symptom. 

The third number shows the day when the infected individuals are detected after the first appearance of infected individual in a group. By combining the first to the third numbers, it should be read "The first infected individual appears on a testing day, infected individuals are detected on a day 6 after the first infection and the detection was made by the confirmation of symptom" in the example. 

The forth number shows the number of infected individuals as exposed (E) on a day that the infected individuals are detected (either testing or symptom confirmation). 

The fifth number shows the number of infected individuals having infectability (either pre-symptomatic (P), infected and symptomatic (Is) or infected and asymptomatic (Ia)) after detected infected individuals are quarantined. In the example, 2 infected individuals are still remaining in the group. 

The sixth number shows the number of quarantined infected individuals. 

These numbers are recorded for a simulation that the infected individuals are detected, and hence the length of the list at each day of the first infection is not 10,000 (10,000 - length of the list represents the number of iteration that no infected individuals are detected within 14 days simulation). 

NOTE
These numbers should be slightly different depending on the random seed and the algorithm for the random number generator. 
