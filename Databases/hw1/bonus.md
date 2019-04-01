#Introduction to Database Systems Homework 1 Bonus


For the first homeowrk assignment of the semester, we 
had to implement a simple DBMS and write queries that 
gave specific pieces of data as a result. For the bonus 
question, I decided to do a simple query yet one that 
may provide some useful observations.


Our query essentially finds the average kills of all players
in different matchTypes. For example, it will find the average
kills in a `normal-solo` match or `duo-fpp`, etc...


![bonus query table](/home/poncedeleon/school/107/spring/Databases/bonus.png "Query Result")

An interesting interpretation of this result can be applied whenever
the owner of the game wishes to create a tournament or encourage
video streaming of their game. What type of match should they invest in?
Judging by our query, it could be intepreted that the match with the most
average kills per player might be the most 'exciting' to watch for a live
audience, so the owner might be invested to spend their money like that.


Another applciation is to control the balancing of the game. Ifa an average player
is killing many opponents in a single match, there should be some other mechanic to
keep the matchType from becoming too easy to exploit. This would potentially remove
some of the fun from the game. 


The difference is not necessarily insignigicant either.
As can be seen, solo type matches have the players kill
two more opponents on average than team-based matchTypes,
so this might be an interesting fact for designers to analyze.
