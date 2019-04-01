
SELECT temp.groupRoadKills AS teamRoadKills,AVG(temp.groupAvg) AS avgWinPlacePerc
FROM (SELECT groupId,sum(roadKills) as groupRoadKills, winPlacePerc as groupAvg FROM(`match` INNER JOIN player_statistic ON `match`.matchId=player_statistic.matchID)
		WHERE `match`.matchType='squad' OR `match`.matchType='squad-fpp'
		GROUP BY  groupId
	) AS temp
GROUP BY teamRoadKills ORDER BY teamRoadKills DESC;
