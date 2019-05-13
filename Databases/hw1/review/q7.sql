SET @avgDuration=  (SELECT AVG(matchDuration)  FROM `match`);
--SELECT AVG(matchDuration) FROM `match`;
SELECT COUNT(*) AS numberOfPlayers, MAX(heals) AS maxHeals
FROM(player_statistic INNER JOIN `match` ON player_statistic.matchId=`match`.matchId)
WHERE `match`.matchDuration>@avgDuration AND player_statistic.damageDealt=0 AND player_statistic.winPlacePerc =1;
