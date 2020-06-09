(lambda inc a
    (+ 1 a)
)
(lambda (dec) (a)
    (- a 1)
)
(lambda (factorial) (n)
    (if (== n 1)
        (1)
        (*
            (factorial (dec n))
            (n)
        )
    )
)

(factorial (inc 7))
