/*we had to set sql_mode variable in special config file
not sure if legit
ask!*/
SELECT SUM(walkDistance+swimDistance+rideDistance) AS totalDistance,
walkDistance, swimDistance, rideDistance
FROM (SELECT Id, walkDistance, swimDistance,rideDistance FROM player_statistic
	WHERE walkDistance>0 AND swimDistance>0 AND rideDistance>0
) AS temp 

GROUP BY Id  ORDER BY totalDistance DESC LIMIT 10;
