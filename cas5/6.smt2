(set-logic QF_LIA)

(declare-const n Int)
(declare-const d Int)

(assert (<= 0 n 9999))
(assert (<= 0 d 9))

(declare-const n0 Int)
(declare-const c0 Int)

(assert (= n0 n))
(assert (= c0 0))

(declare-const n1 Int)
(declare-const c1 Int)
(declare-const n2 Int)
(declare-const c2 Int)
(declare-const n3 Int)
(declare-const c3 Int)
(declare-const n4 Int)
(declare-const c4 Int)

(define-fun next_n ((n_i Int)) Int
    (div n_i 10)
)

(define-fun next_c ((n_i Int)(c_i Int)) Int
    (ite (= (mod n_i 10) d) (+ c_i 1) c_i)
)

(assert (= n1 (next_n n0)))
(assert (= n2 (next_n n1)))
(assert (= n3 (next_n n2)))
(assert (= n4 (next_n n3)))

(assert (= c1 (next_c n0 c0)))
(assert (= c2 (next_c n1 c1)))
(assert (= c3 (next_c n2 c2)))
(assert (= c4 (next_c n3 c3)))

;(assert (or (< c4 0) (> c4 4)))

(assert (and (= c4 4) (distinct n (* 1111 d))))

(check-sat)
(exit)