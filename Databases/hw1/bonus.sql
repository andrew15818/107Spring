SELECT  matchType, AVG(kills)AS avgKills 
FROM (player_statistic INNER JOIN `match` ON player_statistic.matchId=`match`.matchId)
GROUP BY matchType ORDER BY avgKills DESC;
