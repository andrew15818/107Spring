
SELECT (swimDistance+rideDistance+walkDistance) AS totalDistance,
walkDistance, swimDistance, rideDistance
FROM player_statistic
WHERE walkDistance>0 AND swimDistance>0 AND rideDistance>0
GROUP BY Id ORDER BY totalDistance DESC LIMIT 10;

