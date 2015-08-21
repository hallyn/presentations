if &cp | set nocp | endif
map ;mk :!make
map ;vb O\begin{verbatim}\end{verbatim}O
map ;it O\begin{itemize}\end{itemize}O\item 
map ;en O\begin{enumerate}\end{enumerate}O\item 
map ;fr O\begin{frame}\end{frame}kO\frametitle{}i
map ;ini 1Gi\documentclass[12pt]{article}\usepackage{fullpage}\begin{document}Go\end{document}
map ;t :r! date "+\%H:\%M"
map ;d O============================================================================kyyjpk,,d
map ;cl 0i/*[11~A*/[11~
map ;q :q
map ;w :w
let s:cpo_save=&cpo
set cpo&vim
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(expand((exists("g:netrw_gx")? g:netrw_gx : '<cfile>')),netrw#CheckIfRemote())
map <F6> :set background=light
map <F5> :set background=dark
map <F7> CSerge Hallyn <serge.hallyn@canonical.com>
map <F8> oAcked-by: Serge E. Hallyn <serge.hallyn@ubuntu.com>
map <F12> :colorscheme evening
map <F11> :q
map <F10> :n
map <F9> :w
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set background=dark
set backspace=indent,eol,start
set expandtab
set fileencodings=ucs-bom,utf-8,default,latin1
set helplang=en
set nomodeline
set printoptions=paper:letter
set ruler
set runtimepath=~/.vim,/var/lib/vim/addons,/usr/share/vim/vimfiles,/usr/share/vim/vim74,/usr/share/vim/vimfiles/after,/var/lib/vim/addons/after,~/.vim/after
set shiftwidth=2
set showmatch
set smartindent
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set tabstop=2
set window=59
" vim: set ft=vim :
