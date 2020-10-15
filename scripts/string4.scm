(lambda fizzbuzz-lite (n) (
        (if (== (% n 3) 0)
            "fizz"
            (if (== (% n 5) 0)
                "buzz"
                ""
            )
        )
    )
)
(fizzbuzz-lite 5)