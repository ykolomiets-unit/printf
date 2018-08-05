execute pathogen#infect()

set path=$PWD/**

set enc=utf-8
set fenc=utf-8
set termencoding=utf-8

set nocompatible
set autoindent
set smartindent

set tabstop=4
set shiftwidth=4

set textwidth=120
set t_Co=256

syntax on

set number

set showmatch
set wildmenu

set comments=sl:/*,mb:\ *,elx:\ */

highlight OverLength ctermbg=red ctermfg=white guibg=#592929
match OverLength /\%81v.\+/

set colorcolumn=110
highlight ColorColumn ctermbg=darkgray

set completeopt-=preview
let g:ycm_key_list_select_completion = ['<Down>']
:noremap <C-n> :NERDTreeToggle<CR>
autocmd vimenter * NERDTree

set hidden

nnoremap <silent> ` :BufExplorerVerticalSplit<CR>
let g:bufExplorerShowDirectories=0
let g:bufExplorerSplitRight=1
let g:bufExplorerVertSize=3

:noremap <C-j> <C-w>j
:noremap <C-k> <C-w>k
:noremap <C-h> <C-w>h
:noremap <C-l> <C-w>l

nnoremap <C-t> :make<CR>
