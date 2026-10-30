(set-logic QF_LIA)

(declare-const x Int)
(declare-const y Int)
(declare-const z Int)

(define-fun abs_diff ((a Int) (b Int)) Int
    (ite (>= a b) (- a b) (- b a))
)

 (assert (< (abs_diff x y) 0))
; (assert (distinct (abs_diff x y) (abs_diff y x)))
; (assert (distinct (= x y) (= (abs_diff x y) 0)))

(check-sat)
(get-value (x y))
(exit)