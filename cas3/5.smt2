(set-logic QF_BV)

(declare-const x (_ BitVec 8))
(declare-const y (_ BitVec 8))

(define-fun is_greater ((a (_ BitVec 8))(b (_ BitVec 8))) Bool
    (bvuge (bvadd a b) a)
)

(define-fun overflow ((a (_ BitVec 8))(b (_ BitVec 8))) Bool
    (bvult (bvsub (_ bv255 8) a) b)
)


(assert
    (= (is_greater x y) (overflow x y))
)

(check-sat)
(get-value (x y))
(exit)