(set-logic QF_LRA)

(declare-const x Real)
(declare-const y Real)
(declare-const z Real)

(assert
    (and
        (>= 10 x 0)
        (>= 10 y 0)
        (>= 10 z 0)
    )
)

(assert
    (and
        (= (+ (* 2 x) (* 3 y) (* (- 1) z)) 7)
        (>= (+ x (* (- 1) y) (* 2 z)) 7)
        (>= (+ (* 3 x) (* 2 y) z) 10)
        (<= (+ x y z) 6)
    )
)

;(maximize (+ x y z))

(check-sat)
(get-value (x y z))
(exit)