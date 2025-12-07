/* ---------------------------------
   Simple Animal Identification System
   --------------------------------- */

% Basic facts about animals
has_fur(dog).
has_fur(cat).

has_feathers(parrot).
has_feathers(hen).

makes_sound(dog, barks).
makes_sound(cat, meows).
makes_sound(parrot, talks).
makes_sound(hen, clucks).

can_fly(parrot).
can_fly(bat).

gives_milk(cow).
has_horns(cow).

/* ----------- Identification Rules ----------- */

animal(dog) :-
    has_fur(dog),
    makes_sound(dog, barks).

animal(cat) :-
    has_fur(cat),
    makes_sound(cat, meows).

animal(parrot) :-
    has_feathers(parrot),
    can_fly(parrot).

animal(hen) :-
    has_feathers(hen),
    \+ can_fly(hen).

animal(cow) :-
    gives_milk(cow),
    has_horns(cow).
