int: U = 76;

var 1..U: p;
var 1..U: g;
var 1..U: k;

var 46..U: ukupno = p + g + k;

constraint abs(ukupno - 61) <= 15;
constraint abs(p + g - 16) <= 15;
constraint abs(p + k - 20) <= 15;
constraint abs(k + g - 18) <= 15;

% constraint p = g /\ g = k;

solve satisfy;
% solve minimize ukupno;
% solve maximize ukupno;

output ["Petao: ", show(p), "\nGavran: ", show(g), "\nKukavica: ", show(k), "\nUkupno: ", show(ukupno)];

