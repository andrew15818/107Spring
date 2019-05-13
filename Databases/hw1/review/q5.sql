SELECT matchType, AVG(matchDuration) AS averageDuration FROM (player_statistic INNER JOIN `match` ON
		player_statistic.matchId =`match`.matchId)
GROUP BY matchType ORDER BY averageDuration ASC;
