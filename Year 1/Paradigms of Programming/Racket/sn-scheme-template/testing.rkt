;; Use this space for free use.
;; Nothing here well be marked.
;; You may copy any numbered item
;; for testing in REPL.


(require racket/set)
(require "sn-graph.rkt")
(require "sn-social-network.rkt")
(require "sn-utils.rkt")

(define my-dict
  (list
   (cons 'f2
         (list 'f3 'f4))
   (cons 'f3
         (list 'f2))
   (cons 'f4
         (list 'f3 'f2))
   (cons 'f13
         (list ))
   (cons 'f1
         (list ))
   ))

;; sn-utils.
;1
(sn-dict-ks-vs '(k1 k2 k3) '(v1 v2 v3))
;2
(sn-line->entry "A B C D")
;3
(sn-list->dict (list (cons 1 2) (cons 3 4)))

;; sn-graph.
;6
empty
;7
(sn-users my-dict)
;8
(sn-add-user my-dict 'f5)
;9
(sn-add-frndshp my-dict 'f1 'f2)

;; sn-social-network
;10
(sn-ff-for my-dict 'f4)
;11
(sn-cmn-frnds-btwn my-dict 'f2 'f4)
;12
(sn-frnd-cnt my-dict)
;13
(sn-frndlst-user my-dict)
;14
(sn-unfrndlst-user my-dict)