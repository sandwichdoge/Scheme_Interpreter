(lambda (sum) (a) (b)
    (+ (b) (a))
)
(lambda (max) (a) (b)
    (if (> (a) (b))
        (a)
        (b)
    )
)
(lambda (factorial) (n)
    (if (= (n) (1))
        (1)
        (*
            (factorial (- (n) (1)))
            (n)
        )
    )
)

(sum (1) (2)) 
