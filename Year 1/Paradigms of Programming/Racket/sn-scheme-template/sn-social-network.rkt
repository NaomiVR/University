(module sn-social-network racket
  (provide 
   sn-ff-for
   sn-cmn-frnds-btwn
   sn-cmn-frnds
   sn-frnd-cnt
   sn-frndlst-user
   sn-unfrndlst-user  )

  (require "sn-graph.rkt")
  (require "sn-utils.rkt")
  
  ;; This simply returns the dict values of the given key using dict-ref
  (define (sn-ff-for graph u1)
    (dict-ref graph u1)
    )


  ;; This first assigns friends1 and 2 as variables containing the list of values for each friends key given, u1 and u2
  ;; after that it creates two variables, fofs1 and 2 which store the friends of friends using the friends of u1 and u2
  ;; as a reference
  ;; finally it creates the varible common-fofs where it converts the fofs1 and 2 to sets' before cominig them
  ;; using set-intersect, this creates a set of both sets of friends, and because it's a set it removes
  ;; non-unique values, this is before it converts it to a list and returning it
  (define (sn-cmn-frnds-btwn graph u1 u2)
    (let* ((friends1 (dict-ref graph u1))
           (friends2 (dict-ref graph u2))
           (fofs1 (map (lambda (f) (dict-ref graph f)) friends1))
           (fofs2 (map (lambda (f) (dict-ref graph f)) friends2))
           (common-fofs (set->list (set-intersect fofs1 fofs2))))
      common-fofs)
    )

  
  ;; This just returns a count of friends of each user in a given network, using lambda to iterate over the network
  (define (sn-frnd-cnt graph)
    (map (lambda (entry)
           (cons (car entry) (length (cdr entry))))
         graph)
    )

  ;; Using sn-frnd-cnt it sorts the returned list by the amount of friends the user has, most being on the left
  ;; before returning the first entry
  (define (sn-frndlst-user graph)
    (let ((frnd-cnt (sn-frnd-cnt graph)))
      (car (sort frnd-cnt (lambda (a b) (> (cdr a) (cdr b))))))
    )
              
          
  ;; This does the same as sn-frndls-user, but the opposite, as it orders them with the least on the left before
  ;; returning that
  (define (sn-unfrndlst-user graph)
    (let ((frnd-cnt (sn-frnd-cnt graph)))
      (car (sort frnd-cnt (lambda (a b) (< (cdr a) (cdr b))))))
    )

  ;; this is for free. Do not mdify (ROM)
  (define (sn-cmn-frnds-ff graph u)
    (let*
        ([keys (sn-users graph)]
         [vals (map
                (lambda (key)
                  (sn-cmn-frnds-btwn graph u key))
                keys)]
       
         )
      (sn-dict-ks-vs keys vals)))


  ;; this is for free. Do not mdify (ROM)
  (define (sn-cmn-frnds graph )
    (let*
        ([keys (sn-users graph)]
         [vals (map
                (lambda (key)
                  (sn-cmn-frnds-ff graph key))
                keys)]
         )
      (sn-dict-ks-vs keys vals)))

  )