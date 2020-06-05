(define (x) (4))
(define (y) (5))
(if 
    (< (x) (y))
    ((define (x) (6)) (x))
    ((define (z2) (7)) (z2))
)
