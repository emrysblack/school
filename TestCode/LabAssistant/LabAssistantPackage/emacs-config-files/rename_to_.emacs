;;****************************************
;;****************************************
;;**                                    **
;;**       Stuff from BYUI .emacs       **
;;**                                    **
;;****************************************
;;****************************************

;; uncomment this line to disable loading of "default.el" at startup
;; (setq inhibit-default-init t)

;; turn on font-lock mode
(when (fboundp 'global-font-lock-mode)
  (global-font-lock-mode t))

;; enable visual feedback on selections
(setq transient-mark-mode t)

;; default to better frame titles
(setq frame-title-format
      (concat  "%b - emacs@" (system-name)))

;; default to unified diffs
(setq diff-switches "-u")

;; Change the indention style so we don't get too angry with Emacs
(defconst my-c++-style
  '((c-tab-always-indent        . t                                      )
    (c-comment-only-line-offset . 0                                      )
    (c-hanging-braces-alist     . (
                                   (substatement-open after              )
                                   (brace-list-open                      )
                                   )
                                )
    (c-hanging-colons-alist     . (
                                   (member-init-intro before             )
                                   (inher-intro                          )
                                   (case-label after                     )
                                   (label after                          )
                                   (access-label after                   )
                                   )
                                )
    (c-cleanup-list             . (scope-operator       defun-close-semi ) ;; empty-defun-braces
                                )
    (c-offsets-alist            . (
                                   (arglist-close     . c-lineup-arglist )
                                   (func-decl-cont    . 0                )
                                   (inline-open       . 0                )
                                   (substatement-open . 0                )
                                   (case-label        . +                )
                                   (block-open        . 0                )
                                   (knr-argdecl-intro . -                )
                                   )
                                )
    (c-echo-syntactic-information-p . t                                  )
    )
  )

;; Customizations for all of c-mode, c++-mode, and objc-mode
(defun my-c-mode-common-hook ()
  ;; add my personal style and set it for the current buffer
  (c-add-style "BYUI" my-c++-style t)
  ;; offset customizations not in my-c-style
  (c-set-offset 'member-init-intro '++)
  ;; other customizations

  ;; we don't like auto-newline and hungry-delete
  (c-toggle-auto-hungry-state -1)
  ;; keybindings for all supported languages.  We can put these in
  ;; c-mode-base-map because c-mode-map, c++-mode-map, objc-mode-map,
  ;; java-mode-map, and idl-mode-map inherit from it.
  (define-key c-mode-base-map "\C-m" 'newline-and-indent)
  ;; required so tab offset is really three
  (setq c-tab-always-indent 42)
  (setq c-basic-offset 3)
  )

(add-hook 'c-mode-hook 'my-c-mode-common-hook)

(when window-system
  ;; enable wheelmouse support by default
  (mwheel-install)
  ;; use extended compound-text coding for X clipboard
  (set-selection-coding-system 'compound-text-with-extensions))

;;****************************************
;;****************************************
;;**                                    **
;;**                                    **
;;**  Various Non-standard Enhancements **
;;**      Author: Morgen Peschke        **
;;**              except where noted    **
;;**                                    **
;;**                                    **
;;****************************************
;;****************************************

;;****************************************
;;****************************************
;;********                         *******
;;******** Environmental Variables *******
;;********                         *******
;;****************************************
;;****************************************

;;|=======================================
;;| Settings controlled by variables
;;|

;; tab inserts spaces, not tabs
(setq-default indent-tabs-mode nil)

;; Avoid <#> buffer names - similar to #include for c
(require 'uniquify)

(setq
 uniquify-buffer-name-style 'forward ;; Avoid <#> buffer names
 require-final-newline      t        ;; always end a file with a newline
 dabbrev-case-replace       nil      ;; preserve case when expanding dabbrevs
 inhibit-startup-screen     t        ;; Disable the startup screen
 compile-command            "make"   ;;Set default compile command to a simple make
)

;; These are confusing if you aren't expecting them, uncomment when ready
;;(put 'narrow-to-region 'disabled nil) ;; Enable narrowing the buffer to a region
;;(put 'upcase-region    'disabled nil) ;; Enable up-casing a entire region with one command
;;(put 'downcase-region  'disabled nil) ;; Enable down-casing a entire region with one command

;;|=======================================
;;| Settings controlled by function calls
;;|

(pending-delete-mode t) ;; Typing replaces text in region
(display-time         ) ;; Show time in the status bar
(menu-bar-mode       0) ;; Hide the menu bar
(column-number-mode  1) ;; Column numbers in mode line
(line-number-mode    1) ;; Row numbers in mode line
(global-linum-mode   1) ;; Display line numbers on side of frame

;;|=======================================
;;| Completion options
;;|

;; preserve case in hippie-expand
(defadvice hippie-expand (around hippie-expand-case-fold)
  "Try to do case-sensitive matching (not effective with all functions)."
  (let ((case-fold-search nil))
    ad-do-it))
(ad-activate 'hippie-expand)

;; This switches tab and space so space will be the one that completes as
;; far as possible, which is the one we usually want.
(define-key minibuffer-local-must-match-map "\040" 'minibuffer-complete      )
(define-key minibuffer-local-must-match-map "\011" 'minibuffer-complete-word )
(define-key minibuffer-local-completion-map "\040" 'minibuffer-complete      )
(define-key minibuffer-local-completion-map "\011" 'minibuffer-complete-word )

;;|=======================================
;;| Settings controlled by hooks
;;|

;; Ansi color in compile
(require 'ansi-color)
(defun colorize-compilation-buffer ()
  (toggle-read-only)

  (ansi-color-apply-on-region
   (point-min) (point-max))

  (toggle-read-only)
  )

(add-hook 'compilation-filter-hook 'colorize-compilation-buffer)

;; Add niceities to text modes and common programming modes
(add-hook 'text-mode-hook
          '(lambda ()
             (auto-fill-mode t   )
             (set-fill-column 80 )
             (flyspell-mode t    )
             ))

(defun prog-mode-hooks ()
  (auto-fill-mode t   )
  (set-fill-column 80 )
  (flyspell-prog-mode )
  )

(mapc (lambda (mode-hook) (add-hook mode-hook 'prog-mode-hooks))
      '(c-mode-hook
        sql-mode-hook
        emacs-lisp-mode-hook
        lisp-mode-hook
        java-mode-hook
        python-mode-hook
        sh-mode-hook
        python-mode-hook
        perl-mode-hook))

;; Delete trailing whitespace before save
(add-hook 'before-save-hook 'delete-trailing-whitespace)

;; Allow c mode to use case changes as word boundaries - this appears to be
;; missing from our install, and is left to explain it's absence
;; (add-hook 'c-mode-hook (lambda () (subword-mode 1)))

;;|=======================================
;;| Settings imported from shell
;;|

;; Have Emacs know about bash's exec path
(let ((path (shell-command-to-string ". ~/.bashrc; echo -n $PATH")))
  (setenv "PATH" path)
  (setq exec-path
        (append
         (split-string-and-unquote path ":")
         exec-path)))

;; Have emacs know about the prefered browser
(let ((envbrowser (shell-command-to-string ". ~/.bashrc; echo -n $BROWSER")))
  (setenv "BROWSER" envbrowser))

;;****************************************
;;************              **************
;;************ Custom Loads **************
;;************              **************
;;****************************************

;; add directories to load path
(add-to-list 'load-path "~/.emacs.d/")

;; Share the X11 clipboard, even running "emacs -nw"
(load "xclip.el")

;;|=======================================
;;| Auctex configuration - makes LaTeX much easier to work with for Bro. Neff's
;;| Computational Theory class.
;;|

(require 'tex-site)
(setq TeX-auto-save  t )
(setq TeX-parse-self t )
(setq TeX-PDF-mode   t )

(add-hook 'LaTeX-mode-hook (lambda () (flyspell-mode 1)))
(add-hook 'LaTeX-mode-hook 'flyspell-buffer)

(add-hook 'LaTeX-mode-hook (lambda () (outline-minor-mode 1)))
(add-hook 'latex-mode-hook (lambda () (outline-minor-mode 1)))
(setq outline-minor-mode-prefix "\C-c\C-o")

;; Reftex config. Invoke with C-c =
(add-hook 'latex-mode-hook 'reftex-mode)
(add-hook 'LaTeX-mode-hook 'reftex-mode)

(setq LaTeX-eqnarray-label  "eq"
      LaTeX-equation-label  "eq"
      LaTeX-figure-label    "fig"
      LaTeX-table-label     "tab"
      LaTeX-myChapter-label "chap"
      TeX-auto-save         t
      TeX-newline-function  'reindent-then-newline-and-indent
      TeX-parse-self        t
      TeX-style-path
      '("style/"
        "auto/"
        "/usr/share/emacs21/site-lisp/auctex/style/"
        "/var/lib/auctex/emacs21/"
        "/usr/local/share/emacs/site-lisp/auctex/style/")
      LaTeX-section-hook
      '(LaTeX-section-heading
        LaTeX-section-title
        LaTeX-section-toc
        LaTeX-section-section
        LaTeX-section-label))

;;****************************************
;;**********                  ************
;;********** Custom Functions ************
;;**********                  ************
;;****************************************

;;|=======================================
;;| Enhancements to built in commands
;;|

;; Wraps around move-beginning-of-line to jump to the indentation point if the
;; cursor is already at the beginning of the line.
(defun better-move-beginning-of-line ()
  (interactive)
  (if (eq (current-column) 0)
      (back-to-indentation)
    (move-beginning-of-line nil)))

;; Unfill paragraph
(defun unfill-paragraph ()
  (interactive)
  (save-excursion

    (if (region-active-p)
        (let ((fill-column (point-max)))
          (fill-region (region-beginning) (region-end) nil))

      (let ((fill-column (point-max)))
        (fill-paragraph nil))
      )))

;; Align all columns, from snippet on
;; http://www.emacswiki.org/emacs/AlignCommands
 (defun align-all-strings (start end regexp)
   "Repeat alignment with respect to
     the given regular expression."
   (interactive "r\nsAlign regexp: ")
   (align-regexp start end
                 (concat "\\(\\s-*\\)" regexp) 1 1 t))

;;|=======================================
;;| Web related
;;|

;; Search google in external browser
(defun search ()
  (interactive)
  (setq deactivate-mark t)
  (let (searchTerm))
  (setq searchTerm
        (if (region-active-p)
            (buffer-substring-no-properties (region-beginning)
                                            (region-end))
          (thing-at-point 'word)))
  (start-process "emacs-search"
                 (get-buffer-create "* emacs-search *")
                 (getenv "BROWSER")
                 (concat "http://www.google.com/search?q="
                         (url-hexify-string searchTerm))))

;; Open url in external browser
(defun open-url ()
  (interactive)
  (setq deactivate-mark t)
  (let (myURL))
  (setq myURL
        (if (region-active-p)
            (buffer-substring-no-properties (region-beginning)
                                            (region-end))
          (thing-at-point 'url)))
  (start-process "url-open"
                 (get-buffer-create "* url-open *")
                 (getenv "BROWSER")
                 myURL))

;;|=======================================
;;| For transferring stuff to the lab, and
;;| handy for semi-persistent notes
;;|

;; Copy/Paste from shared clipboard file
(defun paste ()
  (interactive)
  (insert-file "~/clipboard_scratchfile"))

(defun copy (b e)
  (interactive "r")
  (write-region b e "~/clipboard_scratchfile"))

;;|=======================================
;;| Date functions
;;|

;; Insert today's date as yymmdd
(defun today ()
  "Inserts today's date"  (interactive)
  (insert (format-time-string "%Y%m%d")))

(defun today-pretty ()
  "Inserts a pretty formatted date"  (interactive)
  (insert (format-time-string "%Y/%m/%d")))

;;|=======================================
;;| Comment block insertions
;;|

(defun comment-block-c ()
  "Inserts an empty comment block"  (interactive)
  (insert "/**********************************************************************"   ) (c-indent-line)
  (insert "\n*"                                                                       ) (c-indent-line)
  (insert "\n**********************************************************************/" ) (c-indent-line)
 )

(defun comment-block-c-small()
  "Inserts a smaller comment block"  (interactive)
  (insert "/****************************************"   ) (c-indent-line)
  (insert "\n*"                                         ) (c-indent-line)
  (insert "\n****************************************/" ) (c-indent-line)
  )

(defun comment-block-c-critical()
  "Inserts an opening and closing critical section comment block"
  (interactive)
  (insert "/****************************************"   ) (c-indent-line)
  (insert "\n* BEGIN Critical Section - "               ) (c-indent-line)
  (insert "\n****************************************/" ) (c-indent-line)
  (insert "\n/****************************************" ) (c-indent-line)
  (insert "\n* END   Critical Section"                  ) (c-indent-line)
  (insert "\n****************************************/" ) (c-indent-line))

(defun comment-block-lisp()
  "Inserts an opening and closing critical section comment block"
  (interactive)
  (insert ";;|=======================================\n") (lisp-indent-line)
  (insert ";;| \n"                                      ) (lisp-indent-line)
  (insert ";;| \n"                                      ) (lisp-indent-line)
  )

;;|=======================================
;;| Shell command extensions
;;|

;; Execute region in shell (http://stackoverflow.com/a/6293423/1188897)
(defun shell-region-as-command (start end)
  "execute region in an inferior shell"
  (interactive "r")
  (shell-command-with-aliases  (buffer-substring-no-properties start end)))

;; Execute shell command with aliases (functions really more than aliases)
(defun shell-command-with-aliases (cmd)
  (interactive (list (read-shell-command "Shell command: ")))
  (shell-command (concat "source ~/.bash-aliases;" cmd)))

;;|=======================================
;;| Miscellaneous
;;|

;; Removes extra characters from dos files
(defun dedosify ()
  "Remove any ^M or ^Z characters in a buffer."
  (interactive)

  (goto-char (point-min))
  (while (search-forward "\015" nil t)  ;^M
    (replace-match "\n" nil t))

  (goto-char (point-min))
  (while (search-forward "\032" nil t)  ;^Z
    (replace-match "" nil t))
  )

;; Processes ANSI color codes
(defun fixcolor ()
  "Correctly display ANSI color in a buffer - modifies file!"
  (interactive)
  (ansi-color-apply-on-region (point-min) (point-max)))

;; Insert file name
;; Normal   - no extension
;; 0 prefix - extension
;; 1 prefix - full path
(defun insert-file-name (p)
  (interactive "P")
  (if (equal p 0)
      (insert (file-relative-name buffer-file-name))
    (if p
        (insert buffer-file-name)
      (insert (file-name-sans-extension (file-relative-name buffer-file-name)))
      )
    )
  )

;; Current buffer mode
(defun current-mode ()
  (interactive)
  (buffer-local-value 'major-mode (current-buffer))
  (message "Current mode: %s" (symbol-value 'major-mode)))

;; Toggle between split windows and a single window
;; Source: Nelson Gonçalves via the Emacs Community on G+
(defun toggle-windows-split()
  "Switch back and forth between one window and whatever split offset windows we
might have in the frame. The idea is to maximize the current buffer, while being
able to go back to the previous split of windows in the frame simply by calling
this command again."
  (interactive)
  (if (not (window-minibuffer-p (selected-window)))
      (progn
        (if (< 1 (count-windows))
            (progn
              (window-configuration-to-register ?u)
              (delete-other-windows))
          (jump-to-register ?u)))))

;;****************************************
;;**********                     *********
;;********** Custom Key Bindings *********
;;**********                     *********
;;****************************************

;;|=======================================
;;| Mode specific hooks
;;|

;; Add hooks to create comment blocks in c mode
(add-hook 'c-mode-common-hook
          (lambda () (local-set-key (kbd "C-c b") 'comment-block-c         )))
(add-hook 'c-mode-common-hook
          (lambda () (local-set-key (kbd "C-c s") 'comment-block-c-small   )))
(add-hook 'c-mode-common-hook
          (lambda () (local-set-key (kbd "C-c c") 'comment-block-c-critical)))
(add-hook 'emacs-lisp-mode-hook
          (lambda () (local-set-key (kbd "C-c b") 'comment-block-lisp      )))

;; Bindings for the improved zap-to-char
(require 'jump-char)
(global-set-key [(meta m)]       'jump-char-forward )
(global-set-key [(shift meta m)] 'jump-char-backward)

;;|=======================================
;;| Global hooks
;;|

;; Misc
(global-set-key (kbd "C-a"     ) 'better-move-beginning-of-line )
(global-set-key (kbd "C-c d"   ) 'dedosify                      )
(global-set-key (kbd "C-n"     ) 'goto-line                     )
(global-set-key (kbd "C-c M-m" ) 'kill-compilation              )
(global-set-key (kbd "C-c m"   ) 'compile                       )
(global-set-key (kbd "C-z"     ) 'suspend-emacs                 )
(global-set-key (kbd "C-c M-q" ) 'unfill-paragraph              )

(global-set-key (kbd "C-x |"   ) 'toggle-windows-split ) ;; Maximize and restore windows
(global-set-key (kbd "C-x u"   ) 'ucs-insert           ) ;; Unicode insert
(global-set-key (kbd "M-SPC"   ) 'hippie-expand        ) ;; Autocomplete
(global-set-key (kbd "C-c w s" ) 'search               ) ;; Search term with default browser
(global-set-key (kbd "C-c w o" ) 'open-url             ) ;; Open URL with default browser
(global-set-key (kbd "M-i"     ) 'imenu                ) ;; Jump to keywords (like function defs )

;; Align shortcuts
(global-set-key (kbd "C-c a a"   ) 'align             )
(global-set-key (kbd "C-c a s"   ) 'align-regexp      )
(global-set-key (kbd "C-c a C-s" ) 'align-all-strings )

;; Adds expansion to lisp evals in the minibuffers
(define-key read-expression-map [(tab)]       'hippie-expand)
(define-key read-expression-map [(shift tab)] 'hippie-unexpand)

;;|=======================================
;;| Changes I liked from:
;;| http://en.wikipedia.org/wiki/User:Gwern/.emacs
;;|

;;Change C-x C-b behavior so it uses bs; shows only interesting buffers.
(global-set-key (kbd "C-x C-b") 'bs-show)

;;M-down and M-up do nothing! :(  Let's make them do something, like M-left and M-right do.
(global-set-key [M-down] '(lambda () (interactive) (progn (forward-line 10)  (recenter) ) ))
(global-set-key [M-up]   '(lambda () (interactive) (progn (forward-line -10) (recenter) ) ))

;;****************************************
;;**********                     *********
;;********** Customize Variables *********
;;**********                     *********
;;****************************************

(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(align-text-modes (quote (text-mode outline-mode org-mode)))
 '(hippie-expand-dabbrev-skip-space nil)
 '(hippie-expand-verbose nil)
 '(ispell-query-replace-choices t)
 '(org-archive-location "%s-archive::From %s")
 '(org-enforce-todo-checkbox-dependencies t)
 '(org-enforce-todo-dependencies t)
 '(org-modules nil)
 '(org-todo-keyword-faces (quote (("WAIT" . org-agenda-dimmed-todo-face))))
 '(org-todo-keywords (quote ((sequence "WAIT(3)" "TODO(2)" "DONE(1)"))))
 '(vc-checkout-carefully t)
 '(vc-command-messages t)
 '(vc-default-init-revision "0.1")
 '(vc-handled-backends (quote (RCS SVN Git)))
 '(vc-initial-comment t)
 '(vc-mistrust-permissions t))

(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(comint-highlight-prompt ((t (:foreground "light blue"))))
 '(link ((((class color) (background light)) (:foreground "light blue" :underline t))))
 '(minibuffer-prompt ((t (:foreground "light blue"))))
 '(org-agenda-dimmed-todo-face ((((background light)) (:foreground "dark blue"))))
 '(org-level-1 ((t (:inherit outline-1 :foreground "blue"))))
 '(org-table ((((class color) (min-colors 8) (background light)) (:foreground "light blue")))))
