(define x 4)
(define y (+ x 5))
(if (< x y)
    (
        (define x 6) 
        (x)
    )
    (y)
)
