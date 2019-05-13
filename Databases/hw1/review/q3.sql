SELECT matchType, count(*) as count  from `match`
WHERE matchType LIKE '%fpp%'
group BY matchType ORDER BY count ASC;
