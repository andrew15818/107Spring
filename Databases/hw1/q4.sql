SELECT player_statistic.Id AS name, AVG(player_statistic.kills) AS avgKills
FROM player_statistic INNER JOIN `match` ON player_statistic.matchId=`match`.matchId
AND `match`.numGroups<=10
GROUP BY name ORDER BY avgKills DESC LIMIT 20; 
