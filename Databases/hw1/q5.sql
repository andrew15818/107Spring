SELECT matchType, AVG(matchDuration) AS averageDuration FROM `match`
where matchDuration>0
GROUP BY matchType ORDER BY averageDuration ASC;
