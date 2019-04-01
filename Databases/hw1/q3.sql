--select all the mathTypes with 'fpp' in title and print
--the counts in order from lowest to highest
SELECT matchType, COUNT(*) FROM `match`
WHERE matchType LIKE '%fpp'
GROUP BY matchType
ORDER BY COUNT(*) ASC;
