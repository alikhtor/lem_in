# lem_in
There is an ant farm, with tunnels and rooms; we place the ants on one side; and we look at how they find the exit.
Program lem-in helps ants to find the exit.
The goal of this program is to find the quickest way to get n ants across the farm.
File for lem-in must consists of:
number of ants;
the rooms (which are defined by: name coord_x coord_y);
the links (which are defined by: name1-name2);
At the beginning of the game, all the ants are in the room ##start.
The goal is to bring them to the room ##end with as few turns as possible.
Each room can only contain one ant at a time. (except at ##start and ##end which can contain as many ants as necessary.)
Also error managment is present, if smth goes wrong, or there is no enough data to perform.
Example file:
#num_of_ants
10
##start
1 23 3
2 16 7
#comment
3 16 3
4 16 5
5 9 3
6 1 5
7 4 8
##end
0 9 5
0-4
0-6
1-3
4-3
5-2
3-5
#another comment
4-2
2-1
7-6
7-2
7-4
