(lambda inc a
    (+ 1 a)
)
(lambda (dec) (a)
    (- a 1)
)
(lambda (factorial) (n)
        (*
            (factorial (dec n))
            (n)
        )
)

(factorial (inc 7))
