(set-logic QF_UF)
(declare-sort T 0)

(declare-fun a () T)
(declare-fun b () T)
(declare-fun c () T)
(declare-fun f (T) T)
(declare-fun g (T) T)

; (assert
;     (and
;         (= a b)
;         (distinct (f a) (f b))
;     )
; )

; (assert
;     (and
;         (= (f a) (f b))
;         (distinct a b)
;     )
; )

; (assert
;     (and
;         (= a b)
;         (distinct (g (f a)) (g (f b)))
;     )
; )

; (assert
;     (and 
;         (= (f a) b)
;         (= (f b) c)
;         (= (f c) a)
;         (distinct a b c)
;     )
; )

(assert
    (forall ((x T)(y T))
        (=> (= (f x) (f y)) (= x y))
    )
)

(assert
    (=> (= (f (f a)) (f (f b))) (= a b))
)

(check-sat)
(get-value (a b c f))
(exit)