(module sn-utils racket
  (provide sn-dict-ks-vs
           sn-line->entry
           sn-list->dict
           )

  (require racket/string)

  ;; This first checks if ks and vs are infact lists, if false it will just return nothing
  ;; if true it will construct a dict object (list of nested lists) using the map function
  (define (sn-dict-ks-vs ks vs)
    (if (and (list? ks) (list? vs))
        (map cons ks vs) #f)
    )

  ;; First it creates a constant to store the split string of the ln input
  ;; after that it will return a constant list where all parts of the original line are converted to symbols
  ;; and sotred with the first symbol representing the key
  (define (sn-line->entry ln)
    (let ((lst (string-split ln)))
      (cons (string->symbol (car lst)) (map string->symbol (cdr lst)))
      )
    )

  ;; This takes a list containing two nested lists, these contain constants
  ;; and using a combination of the map and lambda functions it creates
  ;; a two new lists where each value of the original lists are now
  ;; a key value pair
  (define (sn-list->dict es)
    (map (lambda (entry) (cons (car entry) (cdr entry))) es)
    )
  )