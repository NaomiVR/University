(module sn-console racket
  (require "sn-utils.rkt")
  (require "sn-io.rkt")
  (require "sn-graph.rkt")
  (require "sn-social-network.rkt")
  (provide sn-repl! )


  (define sn-print printf)

  ;; a -> String
  ;; formatting string.
  (define (sn-pp val )
    (cond
      [(dict? val)
       (sn-dict->string val 0)]
      [else (format "~a~n" val)])
    )


  ;; dict -> String
  ;; Think as a tree.
  ;; should be dict->[String]
  (define (sn-dict->string dic n)
    (cond
      [(empty? dic) ""]
      [else
       (let*
           ([fst (first dic)] ; (cons 1 4)
            [key (car fst)] ; 1
            [val (cdr fst)] ; 4
            [rst (rest dic)]
            [indent (make-string n #\tab)]
            [node? (not (dict? val))]
            )
         ;(printf "n: ~a fst: ~a key :~a val ~a node? ~a~n" n fst key val node?)
         (string-append
          indent
          (cond
            [node? (format "~a -> ~a~n"  key val)]
            [else (format "~a -> ~n~a"  key 
                          ;; deep
                          (sn-dict->string val (+ n 1)))])
          ;; breadth
          (sn-dict->string rst n)
          ))]))  
  ;; IO()
  (define (sn-banner!)
    (for-each
     printf
     (list
      "h (help) show this help~n"
      "q (quit)~n"
      "l [a] (load from file) empty network~n"
      "i (init) empty network~n"
      "sh (show)~n"
      "u (users)~n"
      "au (add user)~n"
      "fc (friend count)~n"
      "mkf [a] [b] (make friends a b)~n"
      "ff [a] (friend for)~n"
      "cfb [a] [b] (common frds. between)~n"
      "cf  (cmmn frds all)~n"
      "fst (friendliest user)~n"
      "ufst (unfriendliest user)~n")))
     
  (define sn-error-message
    (format "Wrong command: possible causes~n~c~a~c~a~c~a"
            #\tab
            "(fst,ufst): empty network~n"
            #\tab
            "(ff,mkf,cfb,rcf): either missig or wrong parameters (inexistent user)~n"
            #\tab
            "(l): missing, inexistent or wrong format file~n"
            ))
                 
  
  ;; Graph -> IO() ;
  (define (sn-repl-loop! sn)
    ;;
    ;; the catch.
    (with-handlers (;; hack to trap faulty implementations.
                    [exn:fail:contract:divide-by-zero? (lambda (e)
                                                         (printf "Running damage code. Repair~n")
                                                         (sn-repl-loop! sn)
                                                         )]
                    [exn:fail? (lambda (exn)
                                 (printf sn-error-message)
                                 (sn-repl-loop! sn))])
      (begin
        (printf "sn> ")
        ;; com-args
        (let*
            ([ input (sn-read-symbols!)]
             [ tmp   sn ]
             [ comm (first input)]
             [ args (rest input)]
             )
        
          (cond
            [(equal? comm 'q) (void)]
            [else
             (begin
               (cond
                 ;; help
                 [(equal? comm 'h)
                  (sn-banner!)  ]
                 ;; init
                 [(equal? comm 'i)
                  (set! tmp sn-empty)]
                 ;; load
                 [(equal? comm 'l)
                  (set! tmp (sn-load! (symbol->string (first args))))]
                 ;; users
                 [(equal? comm 'u)
                  (sn-print
                   (sn-pp (sn-users tmp)) )]
                 ;; add-user
                 [(equal? comm 'au)
                  (begin                  
                    (set! tmp (sn-add-user sn (first args)))
                    )]
                 ;; friends-for
                 [(equal? comm 'ff)
                  (sn-print
                   (sn-pp (sn-ff-for sn (first args))))]
                 ;; make friends
                 [(equal? comm 'mkf)
                  (set! tmp (sn-add-frndshp sn (first args) (second args)))
                  ]
                 ;; common friend between
                 [(equal? comm 'cfb)
                  (sn-print
                   (sn-pp (sn-cmn-frnds-btwn tmp (first args) (second args)) ))]
                 ;; show
                 [(equal? comm 'sh)
                  (sn-print
                   (sn-pp tmp ))]
                 ;; friend-count
                 [(equal? comm 'fc)
                  (sn-print
                   (sn-pp (sn-frnd-cnt tmp) ))]
                 ;; common friends all
                 [(equal? comm 'cf)
                  (sn-print
                   (sn-pp (sn-cmn-frnds tmp ) ))]
                 ;; friendliest
                 [(equal? comm 'fst)
                  (sn-print
                   (sn-pp (sn-frndlst-user tmp ) ))]
                 ;; unfriendlist
                 [(equal? comm 'ufst)
                  (sn-print
                   (sn-pp (sn-unfrndlst-user tmp ) ))]
                 [else (begin (printf "Check syntax~n") (sn-banner!))])
               (sn-repl-loop! tmp))])))))
  
  
  ;; IO()
  (define (sn-repl! )
    (sn-repl-loop! sn-empty))

  )