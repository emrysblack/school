 (require 'cl)
cl

  (defun keep-only-up-to-seven-letter-words (words-filename)
    "Given a words-filename, extract and return as a list only
     those words with seven letters or fewer."
    (let ((good-list nil) begin word)
      (with-temp-buffer
        (insert-file-contents words-filename)
        (while (not (looking-at "^$"))
  	(setq begin (point))
  	(end-of-line)
  	(setq word (buffer-substring-no-properties begin (point)))
  	(if (<= (length word) 7)
  	    (setq good-list (cons word good-list)))
  	(forward-char 1)
  	))
      good-list))

  (defun word-size-frequencies-match (subset-of-words)
    (let* ((letter-counts (make-vector 20 0))
  	 (frequencies (make-vector 8 0))
  	 (target [0 1 5 4 3 2 3 2]))
      (loop for word in subset-of-words
  	  for i from 0
  	  do (aset letter-counts i (length word)))
      (loop for i from 1 to 7
  	  do (aset frequencies i (loop for n across letter-counts count (= i n))))
      (equal frequencies target)))

  (defun has-exactly-77-letters (subset-of-words)
    (= 77 (apply #'+ (mapcar #'length subset-of-words))))

  (defun is-good-candidate-subset (subset-of-words)
    (and (word-size-frequencies-match subset-of-words)
         (has-exactly-77-letters subset-of-words)))

  (defun word-list ()
    "Thirty-six words, some twenty-word subset of which is the right one."
    (quote ("digit"
  	  "is"
  	  "be"
  	  "perhaps"
  	  "to"
  	  "just"
  	  "a"
  	  "product"
  	  "two"
  	  "any"
  	  "numbers"
  	  "or"
  	  "pattern"
  	  "pieces"
  	  "first"
  	  "and"
  	  "five"
  	  "reason"
  	  "appear"
  	  "on"
  	  "inside"
  	  "short"
  	  "long"
  	  "third"
  	  "look"
  	  "it"
  	  "ten"
  	  "half"
  	  "that"
  	  "for"
  	  "alone"
  	  "of"
  	  "in"
  	  "chunks"
  	  "random"
  	  "the")))

  (defun choose-random-twenty-from-word-list ()
    (let ((twenty-list nil) 
  	(random-word nil)
  	(the-list (word-list)))
      (loop while (not (= 20 (length twenty-list)))
  	  do (setq random-word (nth (random 35) the-list))
  	  (unless (member random-word twenty-list)
  	    (setq twenty-list (cons random-word twenty-list))))
      twenty-list))

  (defun find-a-few-good-candidates (&optional n)
    (if (null n) (setq n 20000000))
    (let ((filename "good-candidates.txt"))
      (with-temp-buffer
        (and (file-readable-p filename) (insert-file-contents filename))
        (loop repeat n
  	    do (let ((random-twenty (choose-random-twenty-from-word-list)))
  		 (when (is-good-candidate-subset random-twenty)
  		   (insert (mapconcat #'identity random-twenty " "))
  		   (insert "\n"))))
        (write-file filename))))

  (defvar shell-command-format-string "curl -s https://firstthreeodds.org/run/app?lcdq+%d+%s")

  (defun lcd-query (pin counts-as-string)
    (let* ((response (shell-command-to-string (format shell-command-format-string pin counts-as-string)))
  	 (response (replace-regexp-in-string "\n" "" response))
  	 (distance (if (string= response "bad query") most-positive-fixnum
  		     (string-to-number response))))
      distance))

(defun gencounts (wordlist) ; turns list of string into counts for bro neff
(let((mystring (make-string 26 ?0)))
(loop for i from 0 to (length wordlist)
do
(map 'string #'(lambda (c) (aset mystring (- c 97) (string-to-char(format "%x" (-(+ (elt mystring (- c 97)) 1)48))))) (elt wordlist i)))
mystring))

(defun makelist (list num)
  (let (value)
    (dolist (elt list value)
      (unless (= (length elt) num)
          (setq list (remove elt list))
        )
      ))
  list)

(defun gencombos (wordlist offset k) ; generates all combinations for k words in the wordlist
    (if (= k 0)
	(print combolist) ; found combo, test and reset mincombo to these values if new minimum when compared with minscore
      (loop for i from offset to (- (length wordlist) k)
	    do(progn (setq combolist (cons (elt wordlist i) combolist))
		     (gencombos wordlist (+ i 1) (- k 1))
		     (setq combolist (delete (elt combolist 0) combolist))
	    )) ; loop to find combo
   ))

(defun getcombo (wordlist k)
(let ((combolist nil) (mincombo nil) (pin 3639) (minscore nil))
(setq minscore(lcd-query pin (gencounts combolist)) ; runs on empty set to establish min score
(gencombos wordlist 0 k)
mincombo ; variable that holds winning combo
))
   
(defun findwords ()
(setq list1 (makelist (word-list) 1))
(setq list2 (makelist (word-list) 2))
(setq list3 (makelist (word-list) 3))
(setq list4 (makelist (word-list) 4))
(setq list5 (makelist (word-list) 5))
(setq list6 (makelist (word-list) 6))
(setq list7 (makelist (word-list) 7))

)

(findwords)

(defun factorial (num)
(let ((ans 1))
(loop for i from 1 to num
   do (setq ans (* ans i)))
ans))
factorial


(factorial 3)

;; alt-x lisp-interaction-mode for running code