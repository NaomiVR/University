(module sn-io racket
  
  (provide sn-load!
           sn-read-symbols!
           )

  (require "sn-utils.rkt")
  
  ;;https://stackoverflow.com/questions/25152308/scheme-ignoring-call-to-read-line/75411984#75411984
  (define (sn-read-line!)
    ;; BEGIN DR_RACKET
    (read-line )
    ;; END DR_RACKET
    ;; 
    ;; BEGIN RACKET
    ;        (let
    ;            ([line null])    
    ;        (begin
    ;          (set! line (read-line (current-input-port) 'return-linefeed))
    ;          (if (equal? line "")
    ;              (read-line (current-input-port) 'return-linefeed)
    ;              line)))
    ;; END RACKET
    )

  ;; IO([Symbols])
  ;; Easy
  (define (sn-read-symbols!)
    (let
        ([line null]
         [ss   null])
      (begin
        (set! line (sn-read-line!))
        (set! ss (string-split line))
        (map string->symbol ss))))
      

           
  
  ;; String -> IO(sn)
  (define (sn-load! path)
    (let
        ([lines null]
         [entries null]
         )
      (begin
        (set! lines (sn-read-lines-from! path))
        (set! entries (map sn-line->entry lines))
        ;;
        (sn-list->dict entries)
        )))
        
      

  ;; Side effect
  ;; Fd -> [String] -> IO ([String])
  ;; Hopefully scheme is TCO 
  (define (sn-read-line-from! port acc)
    (let
        ([stuff null])    
      (begin
        (set! stuff (read-line port 'return-linefeed))
        (if (eof-object? stuff)
            acc
            (sn-read-line-from! port
                                (cons stuff acc))))))
  ;; Side effect:
  ;; Strig-> IO([String])
  ;; Firing above
  (define (sn-read-lines-from! filename)
    (let
        ([ port null ]
         [ res null]       
         )
      (begin
        (set! port (open-input-file filename))
        (set! res (sn-read-line-from! port '()))
        ( close-input-port port)
        res)))
  )