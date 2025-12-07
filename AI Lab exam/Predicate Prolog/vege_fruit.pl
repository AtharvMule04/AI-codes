/* -------------------------------
   Vegetable / Fruit Classification
   ------------------------------- */

% basic facts
fruit(apple).
fruit(banana).
fruit(mango).
fruit(orange).

vegetable(carrot).
vegetable(potato).
vegetable(tomato).     % tomato is debated but treated as vegetable here
vegetable(cabbage).

% color facts
color(apple, red).
color(banana, yellow).
color(carrot, orange).
color(cabbage, green).

% grows_on(Plant, Type)
% Type = tree | plant | underground
grows_on(apple, tree).
grows_on(mango, tree).
grows_on(orange, tree).
grows_on(banana, plant).

grows_on(carrot, underground).
grows_on(potato, underground).
grows_on(cabbage, plant).
grows_on(tomato, plant).

/* ------ Classification Rules ------ */

% edible_plant(X) :- X is a fruit or vegetable
edible_plant(X) :-
    fruit(X).

edible_plant(X) :-
    vegetable(X).

% underground vegetable
root_vegetable(X) :-
    vegetable(X),
    grows_on(X, underground).

% tree fruit
tree_fruit(X) :-
    fruit(X),
    grows_on(X, tree).
