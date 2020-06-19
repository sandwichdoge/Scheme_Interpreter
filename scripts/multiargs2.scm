(lambda sum a b
    (+ a b)
)
(lambda abs n
    (if (> n 0)
        n
        (- 0 n)
    )
)
(lambda diff a b
    (
        (define x (- a b))
        (abs x)
    )
)
(sum 5 (diff 1 2))