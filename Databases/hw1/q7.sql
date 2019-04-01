SET @avgDuration:=(SELECT AVG(matchDuration) FROM `match`);
SELECT  COUNT(*) AS numberOfPlayers ,MAX(heals) AS maxHeals
FROM (player_statistic   INNER JOIN `match` ON player_statistic.matchID=`match`.matchId )
WHERE matchDuration>@avgDuration AND winPlacePerc=1 AND damageDealt=0; 

