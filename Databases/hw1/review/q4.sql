SELECT Id, AVG(kills) as avgKills FROM player_statistic, `match`
WHERE `match`.matchId=player_statistic.matchId AND `match`.numGroups<=10
group BY Id ORDER BY avgKills DESC LIMIT 20; 
